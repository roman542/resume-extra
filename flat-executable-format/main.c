#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

typedef void (*call_t)(void);

int main (int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Error: no file specified\n");
		return 1;
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("Failed opening file");
		return 1;
	}
	
	ssize_t len = lseek(fd, 0, SEEK_END);
	if (len < 0) {
		perror("Failed measuring file");
		return 1;
	}
	call_t data = mmap(0, len, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (data == MAP_FAILED) {
		perror("Failed mapping file");
		return 1;
	}
	data();
	return 0;
}
