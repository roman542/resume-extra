#include <stdio.h>
#include <stdlib.h>

struct cpuid {
	int a;
	int b;
	int c;
	int d;
};

void cpuid(struct cpuid *id) {
	unsigned int a = id->a, b = 0, c = id->c, d = 0;
	asm volatile (
		"cpuid\n"
		: "+a" (a), "+b" (b), "+c" (c), "+d" (d)
	);
	*id = (struct cpuid){a, b, c, d};
}


int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "%s: Not enough arguments\n", argv[0]);
		return 1;
	}
	int a = strtol(argv[1], 0, 16);
	int c = strtol(argv[2], 0, 16);
	struct cpuid id = {a, 0, c, 0};
	cpuid(&id);
	printf("%08x %08x %08x %08x\n", id.a, id.b, id.c, id.d);
	
}
