SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/*.h)

WFLGS := $(addprefix -W, all extra error pedantic)

CJSON_DIR = ../frameworks/cJSON
CJSON_FILES:= $(CJSON_DIR)/libcjson.a
CJSON_INC_FILES:= $(CJSON_DIR)/inc

LIB_DIR = ../frameworks/libmx
LIB_FILES:= $(LIB_DIR)/libmx.a
LIB_INC_FILES:= $(LIB_DIR)/inc

SSL_DIR = ../frameworks/openssl
SSL_FILES:= ../local_lib/lib
SSL_INC_FILES:= $(SSL_DIR)

LIBS_FLAGS = -lmx -lcjson -lssl -lcrypto \
			 -L$(CJSON_DIR) -I$(CJSON_INC_FILES) \
			 -L$(LIB_DIR) -I$(LIB_INC_FILES) \
			 -L$(SSL_FILES) -I$(SSL_INC_FILES)

GTK_LINK_FLAGS = `pkg-config --cflags --libs gtk+-3.0`

SDL_INC_FLAGS = -rpath ./frameworks -F ../frameworks \
				-framework SDL2 \
				-framework SDL2_mixer \
				-I ../frameworks/SDL2.framework/SDL2 \
				-I ../frameworks/SDL2_mixer.framework/Headers

all: install

install: $(CJSON_FILES) $(LIB_FILES) uchat

uchat:
	@clang -std=c11 -lmx -lcjson $(WFLGS) $(SRCS) $(HDRS) $(GTK_LINK_FLAGS) $(SDL_INC_FLAGS) $(LIB_INC) $(LIBS_FLAGS)
	@mv a.out ../$@

$(CJSON_FILES):
	@make -sC $(CJSON_DIR)

$(LIB_FILES):
	@make -sC $(LIB_DIR)

clean:
	@rm -rf inc/*.gch

uninstall: clean
	@rm -rf ../uchat

reinstall: uninstall install

.PHONY: all install uninstall clean reinstall
