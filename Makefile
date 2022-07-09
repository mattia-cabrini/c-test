CC="gcc"
DD="lldb"
FLAGS="-g"

test: prepare
	$(CC) test.c -c -o x/test.a

runner: prepare
	[ ! -f main.c ] || ($(CC) main.c test.c -o x/test && x/test && rm x/test)

clean:
	echo "Cleaning up..."
	[ ! -d x ] || rm -r ./x

prepare:
	echo "Creating output directory..."
	[ -d x ] || mkdir x
