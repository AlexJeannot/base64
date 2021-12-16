# VARIABLES
GREEN 		= \033[38;5;40m
RESET 		= \033[0m
FT_BASE64 		= ft_base64

# COMPILATION
CC 		= gcc
FLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf


# DIRECTORIES
DSRCS		= ./srcs/

DOBJS		= ./comp/


# SOURCES
SRCS 		=	main.c file.c error.c msg.c


# OBJS
OBJS 		= $(SRCS:%.c=$(DOBJS)%.o)


#HEADER FILE
HEADER	=	./incs/base64.h


all: $(FT_BASE64)

# COMPILATION
$(FT_BASE64):	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(FT_BASE64)
	echo -e "$(GREEN)FT_BASE64 DONE ✔$(RESET)"

$(OBJS): 	| $(DOBJS)

$(DOBJS)%.o:	$(DSRCS)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@


# OBJECT FILE DIRECTORY CREATION
$(DOBJS):
	mkdir -p $(DOBJS)

# CLEAR
clean:
	$(RM) ./comp

fclean: clean
	$(RM) $(FT_BASE64)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(FT_BASE64)