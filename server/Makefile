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

all: install

font:
	@cp data/fonts/Rubik/* ${HOME}/Library/Fonts/

install: $(CJSON_FILES) $(LIB_FILES) uchat_server

uchat_server:
	@clang -std=c11 -lmx -lcjson $(WFLGS) $(SRCS) $(HDRS) $(LIB_INC) $(LIBS_FLAGS)
	@mv a.out ../$@

$(CJSON_FILES):
	@make -sC $(CJSON_DIR)

$(LIB_FILES):
	@make -sC $(LIB_DIR)

clean:
	@rm -rf inc/*.gch

uninstall: clean
	@rm -rf ../uchat_server

reinstall: uninstall install

.PHONY: all install uninstall clean reinstall
