CC=/bin/clang
CFLAGS=-march=x86-64 -O2 -pipe -fno-plt -fexceptions \
         -D_FORTIFY_SOURCE=3 -Wall -Werror \
        -fstack-clash-protection -fcf-protection \
        -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
LDFLAGS=-Wl,-O1 -Wl,--sort-common -Wl,--as-needed -Wl,-z,relro -Wl,-z,now \
                 -Wl,-z,pack-relative-relocs,-fuse-ld=mold
LTOFLAGS=-flto=full

OUTPUT=dist/

all: pre calc counter

pre:
	mkdir -p dist/

calc: calc/main.c
	${CC} ${CFLAGS} ${LTOFLAGS} calc/main.c -o ${OUTPUT}calc ${LDFLAGS}

counter: counter/main.c
	${CC} ${CFLAGS} ${LTOFLAGS} counter/main.c -o ${OUTPUT}counter ${LDFLAGS}


clean:
	rm -rf dist/
