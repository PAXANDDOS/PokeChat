NAME		= uchat_server

SRC_DIR		= src/
OBJ_DIR		= obj/
INC_DIR		= inc/
DIRS		= $(notdir $(wildcard $(SRC_DIR)*))
FILES		= $(foreach dir, $(DIRS), $(basename $(wildcard $(SRC_DIR)$(dir)/*.c)))
SRC			= $(FILES:%=%.c)
OBJ			= $(SRC:src/%.c=$(OBJ_DIR)%.o)
INC_H		= $(wildcard $(INC_DIR)*.h)

LIB_DIR		= ../frameworks
LIB_LIST	= $(notdir $(wildcard $(LIB_DIR)/*))
LIB_DIRS	= $(foreach libdirs, $(LIB_LIST), $(LIB_DIR)/$(libdirs)/)
LIB_BIN		= $(join $(LIB_DIRS), $(addsuffix .a, $(LIB_LIST)))
LIB_INC		= $(addsuffix $(INC_DIR), $(LIB_DIRS))

CC			= clang
GFLAGS		= -std=c11 -pipe -Wall -Wextra -Werror -Wpedantic -Wno-unused-command-line-argument -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter -g 
CFLAGS		= -lsqlite3 -lpthread
IFLAGS		= $(addprefix -I, $(LIB_INC) $(INC_DIR))

COMPILE		= $(CC) $(GFLAGS) $(IFLAGS) $(CFLAGS) $(LIB_BIN)
MAKE_M		= make -sf Makefile -C
MKDIR		= mkdir -p
RM			= /bin/rm -rf

all: $(LIB_LIST) $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIB_BIN)
	@$(COMPILE) $(OBJ) -lmx -o $(NAME)
	@printf "\r\33[2K$@ \033[32;1mcreated\033[0m\n"

$(LIB_LIST): $(LIB_DIRS)
	@$(MAKE_M) $(LIB_DIR)/$@

$(OBJ_DIR):
	@$(MKDIR) $@ $(foreach dir, $(DIRS), $@/$(dir))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_H)
	@$(COMPILE) -o $@ -c $<
	@printf "\r\33[2K$(NAME) \033[33;1mcompile \033[0m$(<:$(SRC_DIR)/%.c=%) "

clean:
	@$(RM) $(OBJ_DIR)
	@printf "$(OBJ_DIR)\t   \033[31;1mdeleted\033[0m\n"

uninstall:
	@$(RM) $(OBJ_DIR) $(NAME)
	@printf "$(NAME) \033[31;1muninstalled\033[0m\n"

reinstall: uninstall all

.PHONY: all uninstall clean reinstall
