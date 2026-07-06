#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <assert.h>

#define PAGE_SIZE 4096

// The cyclic buffer.
// It is a part of Wayland protocol library (replacement to libwayland-{client,server}) I am writing.
//
// Typical usage (writing into):
// 
// int len = cyclic_buf_free_size(buf);
// char *head = cyclic_buf_head(buf);
// size_t readbytes = read(fd, head, len);
// cyclic_buf_advance_head(buf, readbytes);
// 
// Typical usage (reading from):
//
// int len = cycic_buf_data_size(buf);
// char *tail = cyclic_buf_tail(buf);
// size_t readbytes = process_single_msg(tail);
// cycic_buf_advance_tail(buf, readbytes);
//
// It is your responsibility to not overrun the buffer.
//
// main() in this file only demonstrates the wrapping feature of the buffer.

struct cyclic_buf {
	char *base;
	// Could be pointers.
	unsigned head; // Data ends here.
	unsigned tail; // Data starts here.
	unsigned sizemask; // A single chunk size mask, size - 1, and only works if size is a power of 2.
};

// Return the size of the occupied area, i.e. the one you can read from.
// This is basically buf.head - buf.tail. Note that head == tail is empty condition.
unsigned cyclic_buf_data_size(struct cyclic_buf *buf) {
	unsigned head = buf->head;
	unsigned tail = buf->tail;
	if (head < tail) {
		head += buf->sizemask + 1;
	}
	return head - tail;
}

// Return the size of the free area, i.e. the one you can write to.
// This is total - occupied - 1, as head == tail is empty condition.
unsigned cyclic_buf_free_size(struct cyclic_buf *buf) {
	return buf->sizemask - cyclic_buf_data_size(buf);
}

// Wrapping of head and tail is done in advance_*() but could as well be done here instead.
// In such a case, data_size() wouldn't even need the head < tail check except if we expect the buffer to be exceptionally long lived.
char *cyclic_buf_head(struct cyclic_buf *buf) {
	return buf->base + buf->head;
}

char *cyclic_buf_tail(struct cyclic_buf *buf) {
	return buf->base + buf->tail;
}

void cyclic_buf_advance_head(struct cyclic_buf *buf, unsigned len) {
	assert(cyclic_buf_free_size(buf) >= len);
	buf->head = (buf->head + len) & buf->sizemask;
}

void cyclic_buf_advance_tail(struct cyclic_buf *buf, unsigned len) {
	assert(cyclic_buf_data_size(buf) >= len);
	buf->tail = (buf->tail + len) & buf->sizemask;
}

// -1 on error.
//
int cyclic_buf_init(struct cyclic_buf *buf, unsigned size, char *name) {
	if (size & (size - 1)) {
		fprintf(stderr, "Size must be a power of 2\n");
		return -1;
	}
	if (size & (PAGE_SIZE - 1)) {
		fprintf(stderr, "Size must be a multiple of pages\n");
		return -1;
	}
	buf->sizemask = size - 1;
	buf->head = 0;
	buf->tail = 0;
	int fd = memfd_create(name, MFD_CLOEXEC);
	if (fd < 0) {
		perror("Failed creating memfd");
		return -1;
	}
	if (ftruncate(fd, size)) {
		perror("Failed ftruncate on memfd");
		return -1;
	}
	void *reserved = mmap(NULL, size * 2, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (reserved == MAP_FAILED) {
		perror("Failed mmap the whole region");
		return -1;
	}
	void *base = mmap(reserved, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
	if (base == MAP_FAILED) {
		perror("Failed to mmap base 1");
		return -1;
	}
	void *base_2 = mmap(reserved + size, size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, fd, 0);
	if (base_2 == MAP_FAILED) {
		perror("Failed to mmap base 2");
		return -1;
	}
	buf->base = base;

	close(fd);
	return 0;
}

int main() {
	struct cyclic_buf buf = {0};
	if(cyclic_buf_init(&buf, 4096, "buf"))
		return 1;
	buf.base[0] = 12;
	printf("%d\n", buf.base[4096]);
}
