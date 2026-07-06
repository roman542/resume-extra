#include "uefi/protocol/console.h"
#include "uefi/system_table.h"

EFIAPI EFI_STATUS efi_main(
	EFI_HANDLE ImageHandle,
	EFI_SYSTEM_TABLE *SystemTable) {
	
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* con = SystemTable->ConOut;
	con->Reset(con, 0);
	con->SetMode(con, 0);
	con->OutputString(con, (short int *)"h\0e\0l\0l\0o\0 \0w\0o\0r\0l\0d\0!\0\n\0\r\0");
 	
	unsigned int i = 0;
  	while (1) { i++; };
}
