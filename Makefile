CC=/bin/clang
CCX=/bin/clang++

CFLAGS=-march=x86-64 -O2 -pipe -fno-plt -fexceptions \
        -D_FORTIFY_SOURCE=3 -Wall -Werror -flto=full \
        -fstack-clash-protection -fcf-protection \
        -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
LDFLAGS=-Wl,-O1 -Wl,--sort-common -Wl,--as-needed -Wl,-z,relro -Wl,-z,now \
                 -Wl,-z,pack-relative-relocs,-fuse-ld=mold

OUTPUT=dist/

objects:=calc counter

all: pre $(objects)

$(objects): %: %.c
	$(CC) $(CFLAGS) $(LTOFLAGS) -c $^ -o $(OUTPUT)$@ $(LDFLAGS)

pre:
	mkdir -p dist/

clean:
	rm -rf dist/
