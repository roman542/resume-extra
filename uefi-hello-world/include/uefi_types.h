#ifndef __UEFI_TYPES_H
#define __UEFI_TYPES_H

#warning This is not a correct way of sizing things

#define BOOLEAN char
#define INTN INT64
#define UINTN unsigned INTN
#define INT8 char
#define UINT8 unsigned INT8
#define INT16 short int
#define UINT16 unsigned INT16
#define INT32 int
#define UINT32 unsigned INT32
#define INT64 long long int
#define UINT64 unsigned INT64

struct int128 {
	INT64 lo;
	INT64 hi;
};

struct uint128 {
	UINT64 lo;
	UINT64 hi;
};
#define INT128 struct int128
#define UINT128 struct uint128

#define CHAR8 char
#define CHAR16 short int

#define VOID void

struct mac {
	UINT8 a;
	UINT8 b;
	UINT8 c;
	UINT8 d;
	UINT8 e;
	UINT8 f;
};

struct uefi_guid {
	UINT32 time_low;
	UINT16 time_mid;
	UINT16 time_high_and_version;
	UINT8 clock_seq_high_and_reserved;
	UINT8 clock_seq_low;
	UINT8 node[6];
};

#define EFI_GUID struct uefi_guid
#define EFI_STATUS UINTN
#define EFI_HANDLE VOID*
#define EFI_EVENT VOID*
#define EFI_LBA UINT64
#define EFI_TPL UINTN
#define EFI_MAC_ADDRESS struct mac
#define EFI_IPv4_ADDRESS UINT32
#define EFI_IPv6_ADDRESS UINT128
#define EFI_IP_ADDRESS EFI_IPv6_ADDRESS

#define IN
#define OUT
#define OPTIONAL
#define CONST const
#define EFIAPI __attribute__((ms_abi))

#endif
