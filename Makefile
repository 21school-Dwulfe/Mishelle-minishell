# APP				= minishell

# OBJDIR			= ./objs/
# SRCDIR			= ./srcs/
# LIBRARY_NAME	= lib
# SYSTEM			:= $(shell uname)

# REL_PATH		:= $(shell pwd)
# SRCS			:= $(shell find ${SRCDIR} -name '*.c')

# SRCDIRS			:= ${shell find $(SRCDIR) -type d | awk -F"/" '{print $$3}'}
# OBJS			:= ${addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o))}
# HEADERS			:= ${shell find ./includes -name '%.h'}

# ifeq ($(SYSTEM), Darwin)
# 	MAKE 		= make
# endif

# ifeq ($(SYSTEM), Linux)
# 	MAKE		= make
# endif

# ifeq ($(SYSTEM), Darwin)
# 	ADD 		=
# endif
# ifeq ($(SYSTEM), Linux)
# 	ADD			= -ltinfo
# endif

# CFLAGS			:= -Wall	-Wextra -Werror
# DEBUG			:= -g
# INCLUDES		:=  -I./srcs
# LDFLAGS			:= -L$(REL_PATH)/lib/lib -lreadline $(ADD) -I./libft -I$(REL_PATH)/includes/readline -L./libft -lft
# CC				:= gcc
# DEFINE_FLAGS	:= -DQUOTES_ADD_REGIME="1" -DDEV_TOKENS=1
# SEGF_CATCHER	:= -fsanitize=address



# ${APP}:	  Makefile $(HEADERS) $(LIB) $(OBJDIR) ${OBJS} 
# 			@if [ ! -d "lib" ]; then \
# 				mkdir -p lib && \
# 				cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && $(MAKE) install; \
# 			fi
# 			cd ./libft && $(MAKE) && $(MAKE) bonus
			
# 			${CC} ${CFLAGS} $(DEBUG) ${OBJS} ${LDFLAGS} -o ${APP} 

# .PHONY: all clean fclean re bonus buildrepo lib print 



# print_src :
# 	@echo $(OBJS)

# # $(OBJDIR)%.o: $(SRCDIR)%.c
# # 		echo $@...
# # 		${CC} -DQUOTES_ADD_REGIME="1" -DDEV_TOKENS=1 ${CFLAGS}  -g -c $< -o $@

# # $(APP):  $(OBJS)
# # 	@mkdir -p `dirname $@`
# # 	@echo "Linking $@..."
# # 	@$(CC) $(OBJS) $(LDFLAGS) -o $@

# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	@echo "Generating dependencies for $<..."
# 	@$(call make-depend, $<, $@, $(subst .o,.d,$@))
# 	@echo "Compiling $<..."
# 	@$(CC) $(DEFINE_FLAGS) $(CFLAGS) $< -o $@

# all : ${APP}

# re : fclean all

# clean : $(OBJDIR)
# 		rm -rf $(OBJDIR)
# 		cd ./libft && $(MAKE) clean
# 		rm -rf $(shell find . -name '*.o')
# 		@if [ -d "lib" ]; then \
# 			cd readline-8.1 && $(MAKE) distclean; \
# 		fi

# fclean : clean
# 		cd ./libft && $(MAKE) fclean
# 		rm -rf lib
# 		rm -rf $(APP)

# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

# buildrepo: 
# 	$(call make-repo)
# 	mkdir -p lib 
# 	 cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib

# define make-repo
#    for dir in $(SRCDIRS); \
#    do \
# 	mkdir -p $(OBJDIR)/$$dir; \
#    done
# endef

# usage: $(call make-depend,source-file,object-file,depend-file)
# define make-depend
#   $(CC) -MM       \
#         -MF $3    \
#         -MP       \
#         -MT $2    \
#         $(CFLAGS) \
#         $1
# endef



# APP				= minishell

# OBJDIR			= ./objs/
# SRCDIR			= ./srcs/
# LIBRARY_NAME	= lib
# SYSTEM			:= $(shell uname)

# REL_PATH		:= $(shell pwd)
# SRCS			:= $(shell find ${SRCDIR} -name '*.c')

# SRCDIRS			:= ${shell find $(SRCDIR) -type d | awk -F"/" '{print $$3}'}
# OBJS			:= ${addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o))}
# HEADERS			:= ${shell find ./includes -name '%.h'}


APP				= minishell

SRCEXT			= c

SRCDIR			= srcs
OBJDIR			= objs
BINDIR			= bin
# OBJDIR			= ./objs/
# SRCDIR			= ./srcs/
# LIBRARY_NAME	= lib
# SYSTEM			:= $(shell uname)

# REL_PATH		:= $(shell pwd)
# SRCS			:= $(shell find ${SRCDIR} -name '*.c')

# SRCDIRS			:= ${shell find $(SRCDIR) -type d | awk -F"/" '{print $$3}'}

SRCS			:= $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
SRCDIRS			:= $(shell find ./srcs -name '*.$(SRCEXT)' -exec dirname {} \; | uniq)
OBJS			:= $(patsubst %.$(SRCEXT),$(OBJDIR)/%.o,$(SRCS))
HEADERS			:= ${shell find ./includes -name '%.h'}

UNAME			:= $(shell uname)
CFLAGS			:= -Wall -Wextra -Werror
DEBUG			:= -g
INCLUDES		:=  -I./srcs -I./includes
LDFLAGS			:= -L$(REL_PATH)/lib/lib -lreadline $(ADD) -I./libft -I$(REL_PATH)/includes/readline -L./libft -lft
CC				:= gcc
DEFINE_FLAGS	:= -DQUOTES_ADD_REGIME="1" -DDEV_TOKENS=1
SEGF_CATCHER	:= -fsanitize=address


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

ifeq ($(SRCEXT), cpp)
CC			= $(CXX)
else
CFLAGS		+= -std=gnu99
endif


.PHONY:  all clean fclean re bonus print

all: buildrepo $(BINDIR)/$(APP)

print :
	@echo $(SRCDIRS)

write_src_b : 
	@echo $(SRCS_B)


#		  Makefile $(HEADERS) $(LIB) $(OBJDIR) ${OBJS} 
# 			@if [ ! -d "lib" ]; then \
# 				mkdir -p lib && \
# 				cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && $(MAKE) install; \
# 			fi
# 			cd ./libft && $(MAKE) && $(MAKE) bonus
			
# 			${CC} ${CFLAGS} $(DEBUG) ${OBJS} ${LDFLAGS} -o ${APP} 


$(BINDIR)/$(APP):  $(HEADERS) $(LIB) $(OBJDIR)
	if [ ! -d "lib" ]; then \
				mkdir -p lib && \
				cd readline-8.1 && ./configure --prefix=$(REL_PATH)/lib && $(MAKE) install; \
			fi
			cd ./libft && $(MAKE) && $(MAKE) bonus
	@mkdir -p `dirname $@`
	@echo "Linking $@..."
	@$(CC) $(DEFINE_FLAGS) $(SEGF_CATCHER) $(OBJS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: %.$(SRCEXT)
	@echo "Generating dependencies for $<..."
	@$(call make-depend, $<, $@, $(subst .o,.d,$@))
	@echo "Compiling $<..."
	@$(CC)  $(CFLAGS) $< -o $@

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

re:	fclean all

buildrepo:
	@$(call make-repo)

define make-repo
   for dir in $(SRCDIRS); \
   do \
	mkdir -p $(OBJDIR)/$$dir; \
   done
endef

usage: $(call make-depend,source-file,object-file,depend-file)
define make-depend
  $(CC) -MM       \
        -MF $3    \
        -MP       \
        -MT $2    \
        $(CFLAGS) \
        $1
endef