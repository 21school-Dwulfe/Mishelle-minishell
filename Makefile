APP				= minishell

OBJDIR			= objs
SRCDIR			= srcs
LIBRARY_NAME	= lib
SYSTEM			= $(shell uname)

REL_PATH		:= $(shell pwd)
SRCS			:= $(shell find $(SRCDIR) -name '*.c')
SRCS			+= $(shell find ./libft -name '*.c')
SRCDIRS			:= $(shell find $(SRCDIR) -name '*.c' -exec dirname {} \; | uniq)
OBJS			:= ${SRCS:.c=.o} 
HEADERS			:= ${shell find ./includes -name '*.h'}

CFLAGS			= -Wall	-Wextra -Werror
DEBUG			= -g
INCLUDES		=  -I./includes
LDFLAGS			= -L$(REL_PATH)/lib/lib -lreadline -I$(REL_PATH)/includes/readline -L./libft -lft

ifeq ($(UNAME), Darwin)
	MAKEFILE 		= MAKE
endif
ifeq ($(UNAME), Linux)
	MAKEFILE 		= $(MAKE)
endif



${APP}:	  Makefile $(HEADERS) ${OBJS}
			@if [ ! -d "lib" ]; then \
				mkdir -p lib && \
				cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && MAKE install; \
			fi
			$(call make-repo)
			${CC} ${CFLAGS} -g  -fsanitize=address ${OBJS} ${LDFLAGS} -o ${APP}

lib :
	

*.o: %.c
		@echo $@...
		${CC} ${CFLAGS} -g $< -o $@

.PHONY: all clean fclean re bonus buildrepo lib

all : ${APP}

re : fclean all

clean : 
		rm -rf $(OBJDIR)
		cd readline-8.1 &&  MAKE distclean

fclean : clean
		rm -rf lib
		rm -rf $(APP)

buildrepo: 
	$(call make-repo)
	mkdir -p lib 
	cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && $(MAKEFILE) install 

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef