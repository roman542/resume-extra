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

#define LEAF(X) (struct cpuid) {X, 0, 0, 0}
#define SUBLEAF(X, Y) (struct cpuid) {X, 0, Y, 0}

#define HASBIT(X, B) (X & (1 << B))
#define YESNO(X) (X) ? "yes" : "no"

const char* id01_ecx[32] = {
	"SSE3",
	"PCLMULQDQ",
	"64-bit DS Area",
	"MONITOR",
	"DS_CPL (Debug store related)",
	"VMX (Virtual machines)",
	"SMX (Safer mode extensions)",
	"Enhanced Intel SpeedStep",
	"Thermal Monitor 2",
	"SSSE3 (Supplemental SSE3)",
	"L1d context mode switch",
	"DEBUG_INTERFACE (silicon debug)",
	"FMA (FMA extensions using YMM state)",
	"CMPXCHG16B",
	"XTPR_UPDATE_CONTROL",
	"PERF_CAPABILITIES",
	0,	
	"Process context IDs",
	"DCA (prefetch from memory mapped device)",
	"SSE4.1",
	"SSE4.2",
	"x2APIC",
	"MOVBE",
	"POPCNT",
	"TSC_DEADLINE (local APIC timer thing)",
	"AESNI",
	"XSAVE",
	"OS support for XSAVE",
	"AVX",
	"Float 16-bit conversions",
	"RDRAND",
	0,
};

const char* id01_edx[32] = {
	"x87 FPU",
	"Virtual 8086 mode enhancements",
	"I/O breakpoints (debugging feature)",
	"Page size extensions (4MB pages and other 32-bit cruft)",
	"Time Stamp Counter (RDTSC)",
	"Model specific registers",
	"Physical address extension",
	"Machine check exception 18",
	"CHPXCHG8B",
	"APIC",
	0,
	"SYSENTER and SYSEXIT",
	"Memory type range registers",
	"Page global bit",
	"Machine check architecture",
	"CMOV (conditional mov)",
	"Page attribute table",
	"Page size extension 36-bit (32-bit cruft)",
	"Processor serial number support",
	"CLFLUSH",
	0,
	"Debug store",
	"ACPI Thermal monitor and SW controlled clock",
	"MMX (very old SIMD)",
	"FXSAVE and FXRSTOR",
	"SSE",
	"SSE2",
	"Self snoop",
	"Intel hyper-threading",
	"Thermal monitor",
	0,
	"Peanding break enable",
};

const char *id07_00_ebx[32] = {
	"FSGSBASE",
	"TSC_ADJUST",
	"Software guard extensions",
	"BMI1",
	"HLE (Hardware lock elision (deprecated feature))",
	"AVX2",
	"x87 FPU data pointer updated only on x87 exceptions",
	"Supervisor-mode execution prevention",
	"BMI2",
	"Enhanced REP MOVSB/STOSB",
	"INVPCID",
	"RTM (Restricted transactional memory (supersedes HLE))",
	"Resource director technology monitoring",
	"Deprecate FPU's CS and DS values",
	"Memory protection Extensions",
	"Resouce director technology allocation",
	"AVX512F",
	"AVX512DQ",
	"RDSEED",
	"Supervisor-mode Access prevention",
	"AVX512_IFMA",
	0,
	"CLFLUSHOPT",
	"CLWB",
	"Intel processor trace",
	"AVX512PF",
	"AVX512ER",
	"AVX512CD",
	"SHA",
	"AVX512BW",
	"AVX512VL",
};

const char *id07_00_ecx[32] = {
	"PREFETCHWT1",
	"AVX512_VBMI",
	"User-mode instruction prevention",
	"User-mode protection keys (memory management feature)",
	"Os support for protection keys",
	"WAITPKG (TPAUSE, UMONITOR, UMWAIT instructions)",
	"AVX512_VBMI2",
	"CET shadow stack features",
	"GFNI",
	"VAES",
	"VPCLMULQDQ",
	"AVX512_VNNI"
	"AVX512_BITALG",
	"TME_EN",
	"AVX512_VPOPCNTDQ",
	0,
	"5-level paging 57-bit linear address space",
	0,
	0,
	0,
	0,
	0,
	"RDPID",
	"Key locker",
	"OS bus-lock detection",
	"Cache line demote",
	0,
	"MOVDIRI",
	"MOVDIR64B",
	"Enqueue stores",
	"SGX Launch configuration",
	"Protection keys for supervisor-mode pages",
};


const char *id07_00_edx[32] = {
	0,
	"Attestation services for SGX",
	"AVX512_4VNNIW",
	"AVX512_4FMAPS",
	"Fast Short REP MOVSB",
	"User interrupts",
	0,
	0,
	"AVX512_VP2INTERSECT",
	"MCU_OPT_CTRL",
	"MD_CLEAR",
	"XBEGIN (part of RTM) always aborts",
	0,
	"Force XBEGIN to abort as configuration option",
	"SERIALIZE",
	"Hybrid part",
	"TSX suspend/resume of load address tracking (part of RTM)",
	0,
	"PCONFIG",
	"Architectural LBRs",
	"CET indirect branch tracking",
	0,
	"AMX_BF16 (tile computation operations for 16-bit floats)",
	"AVX512_FP16",
	"AMX_TILE (tile operations)",
	"AMX_INT8",
	"Indirect branch restricted speculation and predictor barrier",
	"Single thread indirect branch predictors",
	"L1d flush",
	"Arch capabilities MSR",
	"Core capabilities MSR",
	"Speculative store bypass disable",
};

void print_bitflags(const char **labels, int flags) {
	for (int i = 0; i < 32; i++) {
		if (labels[i]
			// && HASBIT(flags, i)
			) {
			printf("%s: %s\n", labels[i], YESNO(HASBIT(flags, i)));
		}
	}
}

int main(int argc, char **argv) {
	struct cpuid id = LEAF(0);
	cpuid(&id);
	printf("Vendor: %.4s%.4s%.4s\n", (char*)&id.b, (char*)&id.d, (char*)&id.c);
	printf("Max leaf: %1$d 0x%1$02x\n", id.a);
	int max_leaf = id.a;
	if (max_leaf >= 0x01) {
		id = LEAF(0x01);
		cpuid(&id);
		print_bitflags(id01_ecx, id.c);
		print_bitflags(id01_edx, id.d);
	}
	if (max_leaf >= 0x07) {
		id = LEAF(0x07);
		cpuid(&id);
		print_bitflags(id07_00_ebx, id.b);
		print_bitflags(id07_00_ecx, id.c);
		print_bitflags(id07_00_edx, id.d);
	}
	return 0;
}
