CC=/bin/clang
CCX=/bin/clang++

CFLAGS=-march=x86-64 -mtune=generic -O2 -pipe -fno-plt -fexceptions \
        -Wall -Werror \
        -Wp,-D_FORTIFY_SOURCE=3 -Wformat -Werror=format-security \
        -fstack-clash-protection -fcf-protection \
        -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer
LDFLAGS=-Wl,-O1 -Wl,--sort-common -Wl,--as-needed -Wl,-z,relro -Wl,-z,now \
         -Wl,-z,pack-relative-relocs,-fuse-ld=mold
LTOFLAGS=-flto=full

OUTPUT_DIR=dist/
EXT=
TRIPLE=x86_64-unknown-linux-gnu

objects:=calc counter

all: pre $(objects)

$(objects): %: %.c
	@$(CC) $(CFLAGS) $(LTOFLAGS) $^ -o $(OUTPUT_DIR)$@-$(TRIPLE)$(EXT) $(LDFLAGS)
	@cd $(OUTPUT_DIR) && sha256sum $@-$(TRIPLE)$(EXT) > $@-$(TRIPLE)$(EXT).sha256

pre:
	@mkdir -p dist/

clean:
	rm -rf dist/
