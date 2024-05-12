###############################################################################
######                            PROPERTIES                             ######
###############################################################################

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -MD -MP -g
LINKFLAGS	= -lncursesw
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= 2048
SRCSDIR		= srcs
SRCS		= \
			${SRCSDIR}/game_display.c \
			${SRCSDIR}/signals.c \
			${SRCSDIR}/game.c \
			${SRCSDIR}/menu.c \
			${SRCSDIR}/main.c

OBJSDIR		= objs
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.d))

###############################################################################
######                               LIBFT                               ######
###############################################################################

LIBDIR		= ./libft
LIBFT		= ${LIBDIR}/libft.a

###############################################################################
######                               RULES                               ######
###############################################################################

all		: $(NAME)

$(NAME)	: ${OBJS}
		$(MAKE) -C ${LIBDIR} all
		$(CC) -o $@ $^ $(LINKFLAGS) -L. ${LIBFT}

${OBJSDIR}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@

clean	:
		$(MAKE) -C ${LIBDIR} clean
		$(RM) $(OBJSDIR)

fclean	:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME)

re		:
		$(MAKE) -C ${LIBDIR} re
		$(RM) $(OBJSDIR) $(NAME)
		$(MAKE) all

run		:
		$(MAKE) re
		./$(NAME)

test	:
		$(MAKE) re
		valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all ./$(NAME)

-include $(DEPS)

.PHONY: all clean fclean bonus re test run
