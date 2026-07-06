OUTPUT_FORMAT(binary)

SECTIONS {
	.data 0 : {
		*(.text)
		*(.text*)
		*(.rodata*)
		*(.bss*)
		*(.data*)
	}

	/DISCARD/ : {
		*(*);
	}
}
