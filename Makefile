CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC_SERVER = server.c utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
SRC_CLIENT = client.c utils.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SERVER = server
CLIENT = client

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT)

clean:
	rm -f $(OBJ_SERVER)
	rm -f $(OBJ_CLIENT)

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
