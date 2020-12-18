NAME = libcjson.a

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILES:%.c=%.o)))
INC_FILES = $(wildcard $(INC_DIR)/*.h)

CC = clang

CFLAGS = -std=c11 $(addprefix -W, all extra error pedantic) -g

SFLAGS = -fPIC -pedantic -Wstrict-prototypes -Wwrite-strings -Wshadow \
		 -Winit-self -Wcast-align -Wformat=2 -Wmissing-prototypes \
		 -Wstrict-overflow=2 -Wcast-qual -Wc++-compat -Wundef \
		 -Wswitch-default -Wconversion

AR = ar
AFLAGS = rcs

MKDIR = mkdir -p
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $(AFLAGS) $@ $^
	@printf "\r\33[2K$@\t \033[32;1mcreated\033[0m\n"

$(OBJ_FILES): | $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)
	@printf "\r\33[2K$(NAME)\033[33;1m\t compile \033[0m$(<:$(SRC_DIR)/%.c=%)\r"

$(OBJ_DIR):
	@$(MKDIR) $@

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR) in $(NAME)\t \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@@printf "$(NAME)\t \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall