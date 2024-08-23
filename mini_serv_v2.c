#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

typedef struct clients
{
	int id;
	char msg[200000];
}	t_clients;

t_clients clients[1024];
char buff[200500];
int maxfd, servfd, ids = 0;
fd_set set, rd, wr; // set is all fds

void err(char *str)
{
	write(2, str, strlen(str));
	exit(1);
}

void sendbuff(int excludefd)
{
	for (int fd = 0; fd <= maxfd; fd++)
		if (fd != excludefd && FD_ISSET(fd, &wr))
			send(fd, buff, strlen(buff), 0);
}

int main(int ac, char **av)
{
	if (ac != 2)
		err("Wrong number of arguments\n");

	bzero(&clients, sizeof(clients));
	servfd = socket(AF_INET, SOCK_STREAM, 0);
	if (servfd < 0)
		err("Fatal error\n");

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));

	if (bind(servfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) != 0
		|| listen(servfd, 128) != 0)
	{
		close(servfd);
		err("Fatal error\n");
	}

	maxfd = servfd;
	FD_ZERO(&set);
	FD_SET(servfd, &set);

	while (1)
	{
		rd = set;
		wr = set;
		if (select(maxfd + 1, &rd, &wr, 0, 0) < 0)
			continue;
		for (int fd = 0; fd <= maxfd; fd++)
		{
			if (FD_ISSET(fd, &rd))
			{
				if (fd == servfd)
				{
					struct sockaddr_in cliaddr;
					socklen_t len = sizeof(cliaddr);

					int newfd = accept(servfd, (struct sockaddr *)&cliaddr, &len);
					if (newfd < 0)
						continue;
					if (newfd > maxfd) maxfd = newfd;
					FD_SET(newfd, &set);
					clients[newfd].id = ids++;
					sprintf(buff, "server: client %d just arrived\n", clients[newfd].id);
					sendbuff(newfd);
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
						sprintf(buff, "server: client %d just left\n", clients[fd].id);
						FD_CLR(fd, &set);
						close(fd);
					}
					else
						sprintf(buff, "client %d: %s", clients[fd].id, clients[fd].msg);
					sendbuff(fd);
					break;
				}
			}
		}
	}
}
