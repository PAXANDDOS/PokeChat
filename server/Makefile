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

SQLITE3_DIR = ../frameworks/sqlite3
SQLITE3_FILES:= $(SQLITE3_DIR)/libsqlite3.a
SQLITE3_INC_FILES:= $(SQLITE3_DIR)/inc

LIBS_FLAGS = -lmx -lcjson -lssl -lcrypto -lsqlite3\
			 -L$(CJSON_DIR) -I$(CJSON_INC_FILES) \
			 -L$(LIB_DIR) -I$(LIB_INC_FILES) \
			 -L$(SSL_FILES) -I$(SSL_INC_FILES) \
			 -L$(SQLITE3_DIR) -I$(SQLITE3_INC_FILES)

all: install

font:
	@cp data/fonts/Rubik/* ${HOME}/Library/Fonts/

install: $(SQLITE3_FILES) $(CJSON_FILES) $(LIB_FILES) uchat_server

uchat_server:
	@clang -std=c11 -lmx -lcjson $(WFLGS) $(SRCS) $(HDRS) $(LIB_INC) $(LIBS_FLAGS)
	@mv a.out ../$@

$(SQLITE3_FILES):
	@make -sC $(SQLITE3_DIR)

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
