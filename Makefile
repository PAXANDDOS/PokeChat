NAME = uchat

SERVER_NAME = uchat_server
SERVER_DIR = server

CLIENT_DIR = client

LIBMX_DIR = frameworks/libmx
LIBCJSON_DIR = frameworks/cjson
LIBSQLITE_DIR = frameworks/sqlite3

MAKE_M = make -sf Makefile -C
MKDIR_M = mkdir -p
RM = /bin/rm -rf

all: required_dirs
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@

$(NAME):
	@$(MAKE_M) $(CLIENT_DIR)

$(SERVER_NAME):
	@$(MAKE_M) $(SERVER_DIR)

required_dirs:
	@$(MKDIR_M) media_client
	@$(MKDIR_M) media_server
	@$(MKDIR_M) temp

font:
	@cp client/data/fonts/Rubik/* ${HOME}/Library/Fonts/
	@cp client/data/fonts/UniSans/* ${HOME}/Library/Fonts/

clean:
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@

uninstall:
	@$(MAKE_M) $(CLIENT_DIR) $@
	@$(MAKE_M) $(SERVER_DIR) $@
	@$(MAKE_M) $(LIBMX_DIR) $@
	@$(MAKE_M) $(LIBCJSON_DIR) $@
	@$(MAKE_M) $(LIBSQLITE_DIR) $@

reinstall: uninstall all

.PHONY: all clean uninstall reinstall $(NAME) $(SERVER_NAME)
