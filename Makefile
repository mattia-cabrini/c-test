CC="gcc"
DD="lldb"
FLAGS="-g"
LL="ar"

test: prepare
	@echo "Compiling test.c..."
	@$(CC) test.c -c -o x/test.o

	@echo "Linking object..."
	@$(LL) rc x/test.a x/test.o

	@echo "Cleaning up..."
	@rm x/test.o

runner: prepare
	[ ! -f main.c ] || ($(CC) main.c test.c -o x/test && x/test && rm x/test)

clean:
	echo "Cleaning up..."
	[ ! -d x ] || rm -r ./x

prepare:
	echo "Creating output directory..."
	[ -d x ] || mkdir x
