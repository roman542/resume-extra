#include <stdio.h>
#include "uefi_types.h"

#define S(X) printf("%ld ", sizeof(X))
#define S_F(X) printf( #X "\t\t\t\t%ld\n", sizeof(X))

int main(int argc, char *argv[]) {
	if (argc >= 2) {
		S(BOOLEAN);
		S(INTN);
		S(UINTN);
		S(INT8);
		S(UINT8);
		S(INT16);
		S(UINT16);
		S(INT32);
		S(UINT32);
		S(INT64);
		S(UINT64);
		S(INT128);
		S(UINT128);
		
		S(CHAR8);
		S(CHAR16);
		
		S(VOID);
		
		S(EFI_GUID);
		S(EFI_STATUS);
		S(EFI_HANDLE);
		S(EFI_EVENT);
		S(EFI_LBA);
		S(EFI_TPL);
		S(EFI_MAC_ADDRESS);
		S(EFI_IPv4_ADDRESS);
		S(EFI_IPv6_ADDRESS);
		S(EFI_IP_ADDRESS);
	} else {
		S_F(BOOLEAN);
		S_F(INTN);
		S_F(UINTN);
		S_F(INT8);
		S_F(UINT8);
		S_F(INT16);
		S_F(UINT16);
		S_F(INT32);
		S_F(UINT32);
		S_F(INT64);
		S_F(UINT64);
		S_F(INT128);
		S_F(UINT128);
		
		S_F(CHAR8);
		S_F(CHAR16);
		
		S_F(VOID);
		
		S_F(EFI_GUID);
		S_F(EFI_STATUS);
		S_F(EFI_HANDLE);
		S_F(EFI_EVENT);
		S_F(EFI_LBA);
		S_F(EFI_TPL);
		S_F(EFI_MAC_ADDRESS);
		S_F(EFI_IPv4_ADDRESS);
		S_F(EFI_IPv6_ADDRESS);
		S_F(EFI_IP_ADDRESS);
	}
}

