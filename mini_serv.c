#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client
{
	int	id;
	char	msg[200000];
}	t_clients;

t_clients clients[1024];
int	max_fd = 0;
int	gid = 0;
char	send_buffer[200500];
fd_set	write_set, read_set, current;

void	err(char * message)
{
	if (message)
		write(2, message, strlen(message));
	else
		write(2, "Fatal error", 11);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	send_to_all(int exception)
{
	for (int fd = 0; fd <= max_fd; fd++)
		if (FD_ISSET(fd, &write_set) && fd != exception)
			send(fd, send_buffer, strlen(send_buffer), 0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		err("Wrong number of arguments");
	struct sockaddr_in	serveraddr, cli;

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		err(NULL);

	FD_ZERO(&current);
	FD_SET(server_fd, &current);
	bzero(&clients, sizeof(clients));
	bzero(&serveraddr, sizeof(serveraddr));
	max_fd = server_fd;

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(atoi(argv[1]));

	if (bind(server_fd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1 || listen(server_fd, 128) == -1)
	{
		close(server_fd);
		err(NULL);
	}
	while(1)
	{
		read_set = current;
		write_set = current;
		if (select(max_fd + 1, &read_set, &write_set, 0, 0) == -1)
			continue;
		for(int fd = 0; fd <= max_fd; fd++)
		{
			if (FD_ISSET(fd, &read_set))
			{
				if (fd == server_fd)
				{
					socklen_t len = sizeof(cli);
					int client_fd = accept(server_fd, (struct sockaddr *)&cli, &len);
					if (client_fd < 0) continue;
					if (client_fd > max_fd) max_fd = client_fd;
					FD_SET(client_fd, &current);
					clients[client_fd].id = gid++;
					sprintf(send_buffer, "server: client %d just arrived\n", clients[client_fd].id);
					send_to_all(client_fd);
					break;
				}
				else
				{
					int readbytes = 1;
					bzero(&clients[fd].msg, sizeof(clients[fd].msg));
					while (readbytes == 1 && clients[fd].msg[strlen(clients[fd].msg) - 1] != '\n')
						readbytes = recv(fd, clients[fd].msg + strlen(clients[fd].msg), 1, 0);
					if (readbytes < 1)
					{
						sprintf(send_buffer, "server: client %d just left\n", clients[fd].id);
						FD_CLR(fd, &current);
						close(fd);
					}
					else
					{
						sprintf(send_buffer, "client %d: %s", clients[fd].id, clients[fd].msg);
					}
					send_to_all(fd);
					break;
				}
			}
		}
	}
	return (0);
}
