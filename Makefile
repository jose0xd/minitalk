CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_SERVER = server.c utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
SRC_CLIENT = client.c utils.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SRV_BONUS = server_bonus.c utils.c
OBJ_SRV_BONUS = $(SRC_SRV_BONUS:.c=.o)
SRC_CLT_BONUS = client_bonus.c utils.c
OBJ_CLT_BONUS = $(SRC_CLT_BONUS:.c=.o)

SERVER = server
CLIENT = client

NAME = minitalk

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

bonus: $(OBJ_SRV_BONUS) $(OBJ_CLT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_SRV_BONUS) -o $(SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLT_BONUS) -o $(CLIENT)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_SRV_BONUS)
	rm -f $(OBJ_CLIENT) $(OBJ_CLT_BONUS)

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
