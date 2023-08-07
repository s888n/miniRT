NAME = rt
CC = cc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f
MLX_FLAGS = -lmlx -framework openGL -framework appkit
SRCS = main.c parse.c color.c inter.c draw.c vec.c ray.c cylinder.c sphere.c A_C_L.c sp_pl_cy.c utils.c utils2.c get_next_line/get_next_line_utils.c get_next_line/get_next_line.c
OBJS = $(SRCS:.c=.o)
INC = rt.h

%.o : %.c $(INC)
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
all : $(NAME)
	@echo "\033[0;32m done.\033[0m"
$(NAME) :  $(OBJS)
	@$(CC) $(CFLAGS)  -o $(NAME) $(OBJS) $(MLX_FLAGS)

all : $(NAME)
clean :
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "\033[0;31m removed obj.\033[0m"
fclean : clean
	@$(RM) $(NAME)
	@echo "\033[0;31m removed bin. \033[0m"
re : fclean all

.PHONY : all clean fclean re bonus