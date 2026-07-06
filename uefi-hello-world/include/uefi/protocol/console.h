#ifndef __UEFI_PROTOCOL_CONSOLE_H
#define __UEFI_PROTOCOL_CONSOLE_H

#include "../../uefi_types.h"

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
 {0x387477c2, 0x69c7, 0x11d2, 0x8e, 0x39, \
	 {0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}}

typedef struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFIAPI EFI_STATUS (*EFI_TEXT_STRING) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
	IN CHAR16                             *String
);

typedef EFIAPI EFI_STATUS (*EFI_TEXT_SET_MODE) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This,
 	IN UINTN				ModeNumber
);

typedef EFIAPI EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL	*This
);

typedef EFIAPI EFI_STATUS (*EFI_TEXT_RESET) (
	IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *This,
	IN BOOLEAN                               ExtendedVerification
);

struct _EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET		Reset;
	EFI_TEXT_STRING		OutputString;
	void* TestString;
	void* QueryMode;
	EFI_TEXT_SET_MODE 	SetMode;
	void* SetAttribute;
	EFI_TEXT_CLEAR_SCREEN	ClearScreen;
	void* SetCursorPosition;
	void* EnableCursor;
	void	*Mode;
};


#endif
