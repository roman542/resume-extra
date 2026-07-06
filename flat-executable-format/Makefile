CC := gcc -O2
AS := as
LD := ld

run: main hello/main.bin hello2/main.bin
	./main hello/main.bin
	./main hello2/main.bin

main: main.c
	$(CC) $< -o $@

hello/main.bin: hello/main.bin.o bin.ld
	$(LD) -T bin.ld $< -o $@

hello/main.bin.o: hello/main.S
	$(AS) $< -o $@

hello2/main.bin: hello2/main.c crt.o bin.ld
	$(CC) -T bin.ld crt.o $< -o $@ -fPIE -static-pie -nostdlib -lgcc

crt.o: crt.s
	$(AS) $< -o $@

clean:
	-rm main hello/main.bin hello2/main.bin crt.o || true
