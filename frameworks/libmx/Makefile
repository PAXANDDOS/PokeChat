NAME	=	libmx.a

CFLG	=	-std=c11 -Wall -Wextra -Werror -Wpedantic -g
COMP 	= 	clang

SRCD	=	src
INCD	=	inc
OBJD	=	obj

INC		=	libmx.h
INCS	=	$(addprefix $(INCD)/, $(INC))

SRC		= 	mx_binary_search.c mx_bubble_sort.c mx_count_substr.c mx_count_words.c mx_create_node.c \
			mx_del_extra_spaces.c mx_del_strarr.c mx_file_to_str.c mx_foreach.c mx_get_char_index.c \
			mx_get_substr_index.c mx_hex_to_nbr.c mx_isalpha.c mx_isdigit.c mx_islower.c mx_itoa.c \
			mx_isspace.c mx_isupper.c mx_list_size.c mx_memccpy.c mx_memchr.c mx_memcmp.c mx_memcpy.c \
			mx_memmem.c mx_memmove.c mx_memrchr.c mx_memset.c mx_nbr_to_hex.c mx_pop_back.c mx_pop_front.c \
			mx_pow.c mx_print_strarr.c mx_print_unicode.c mx_printchar.c mx_printint.c mx_printstr.c \
			mx_push_back.c mx_push_front.c mx_quicksort.c mx_read_line.c mx_realloc.c mx_replace_substr.c \
			mx_sort_list.c mx_sqrt.c mx_str_reverse.c mx_strcat.c mx_strcmp.c mx_strcpy.c mx_strdel.c \
			mx_strdup.c mx_strjoin.c mx_strlen.c mx_strncmp.c mx_strncpy.c mx_strndup.c mx_strnew.c \
			mx_strsplit.c mx_strstr.c mx_strtrim.c mx_swap_char.c mx_strchr.c

SRCS	=	$(addprefix $(SRCD)/, $(SRC))
OBJS	=	$(addprefix $(OBJD)/, $(SRC:%.c=%.o))

all: install
	
install: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@printf "\r\33[2K$@\t   \033[32;1mcreated\033[0m\n"

$(OBJD)/%.o: $(SRCD)/%.c $(INCS)
	@$(COMP) $(CFLG) -c $< -o $@ -I$(INCD)
	@printf "\r\33[2K$(NAME)\t   \033[33;1mcompile \033[0m$(<:$(SRCD)/%.c=%) "

$(OBJS): | $(OBJD)

$(OBJD):
	@mkdir -p $@

clean:
	@rm -rf $(OBJD)
	@printf "$(OBJD)\t   \033[31;1mdeleted\033[0m\n"

uninstall: clean
	@rm -rf $(NAME)
	@printf "$(NAME)\t   \033[31;1muninstalled\033[0m\n"

reinstall: uninstall install
