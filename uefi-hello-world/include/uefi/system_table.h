#ifndef __UEFI_SYSTEM_TABLE_H
#define __UEFI_SYSTEM_TABLE_H

#include "../uefi_types.h"
#include "protocol/console.h"

//typedef EFIAPI EFI_STATUS ( *EFI_IMAGE_ENTRY_POINT) (
//	IN EFI_HANDLE		ImageHandle,
//	IN EFI_SYSTEM_TABLE	*SystemTable
//);

typedef struct {
	UINT64	Signature;
	UINT32	Revision;
	UINT32	HeaderSize;
	UINT32	CRC32;
	UINT32	Reserved;
} EFI_TABLE_HEADER;

typedef struct {
  EFI_TABLE_HEADER                 Hdr;
  CHAR16                           *FirmwareVendor;
  UINT32                           FirmwareRevision;
  EFI_HANDLE                       ConsoleInHandle;
  void *ConIn;
  EFI_HANDLE                       ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
  EFI_HANDLE                       StandardErrorHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *StdErr;
  void *RuntimeServices;
  void *BootServices;
  UINTN                            NumberOfTableEntries;
  void *ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
