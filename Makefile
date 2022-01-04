APP				= minishell

OBJDIR			= ./objs/
SRCDIR			= ./srcs/
LIBRARY_NAME	= lib
SYSTEM			:= $(shell uname)

REL_PATH		:= $(shell pwd)
SRCS			:= $(shell find $(SRCDIR) -name '*.c')

SRCDIRS			:= $(shell find $(SRCDIR) -name '*.c' -exec dirname {} \; | uniq)
OBJS			:= ${addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o))} 
HEADERS			:= ${shell find ./includes -name '%.h'}

ifeq ($(SYSTEM), Darwin)
	MAKE 		= make 
endif
ifeq ($(SYSTEM), Linux)
	MAKE		= make
endif

ifeq ($(SYSTEM), Darwin)
	ADD 		= 
endif
ifeq ($(SYSTEM), Linux)
	ADD			= -ltinfo
endif
CFLAGS			= -Wall	-Wextra -Werror
DEBUG			= -g
INCLUDES		=  -I./includes
LDFLAGS			= -L$(REL_PATH)/lib/lib -lreadline $(ADD) -I./libft -I$(REL_PATH)/includes/readline -L./libft -lft
CC				= gcc

${APP}:	  Makefile $(HEADERS) $(LIB) $(OBJDIR) ${OBJS} 
			@if [ ! -d "lib" ]; then \
				mkdir -p lib && \
				cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && $(MAKE) install; \
			fi
			cd ./libft && $(MAKE) && $(MAKE) bonus
			
			${CC} -DQUOTES_ADD_REGIME=0 ${CFLAGS}  -g  ${OBJS} ${LDFLAGS}  -o ${APP} #-fsanitize=address

.PHONY: all clean fclean re bonus buildrepo lib print 

print : 
	echo $(OBJS)

$(OBJDIR)%.o: $(SRCDIR)%.c
		echo $@...
		${CC} -DQUOTES_ADD_REGIME="0" ${CFLAGS}  -g -c $< -o $@



all : ${APP}

re : fclean all

clean : $(OBJDIR)
		rm -rf $(OBJDIR)
		cd ./libft && $(MAKE) clean
		rm -rf $(shell find . -name '*.o')
		@if [ -d "lib" ]; then \
			cd readline-8.1 && $(MAKE) distclean; \
		fi

fclean : clean
		cd ./libft && $(MAKE) fclean
		rm -rf lib
		rm -rf $(APP)

$(OBJDIR):
	mkdir -p $(OBJDIR)

buildrepo: 
	$(call make-repo)
	mkdir -p lib 
	 cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib 