/* SPDX-FileCopyrightText: 2021 John Scott <jscott@posteo.net>
 * SPDX-LicenseIdentifier: GPL-2.0-or-later */
#define _POSIX_C_SOURCE 200809L
#include <netinet/in.h>
#include <signal.h>
#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
extern char **environ;

#define XMOTO_PORT 4130

static noreturn void xmoto_died(int s) {
	_Exit(EXIT_FAILURE);
}

int main(void) {
	struct sigaction act = { .sa_handler = xmoto_died };
	if(sigemptyset(&act.sa_mask) == -1) {
		perror("Failed to empty signal set");
		exit(EXIT_FAILURE);
	}

	pid_t xmoto;
	int k = posix_spawnp(&xmoto, "xmoto", NULL, NULL, (char*[]){"xmoto", "--server", NULL}, environ);
	if(k) {
		fprintf(stderr, "Failed to start X-Moto: %s\n", strerror(k));
		exit(EXIT_FAILURE);
	}

	/* Try IPv6 first, then IPv4. */
	sa_family_t fam = AF_INET6;
	int sock;
startconn:
	sock = socket(fam, SOCK_STREAM, IPPROTO_TCP);
	if(sock == -1) {
		perror("Failed to create socket");
		if(kill(xmoto, SIGTERM) == -1) {
			perror("Failed to terminate X-Moto");
		}
		exit(EXIT_FAILURE);
	}

	union {
		struct sockaddr sa;
		struct sockaddr_in in;
		struct sockaddr_in6 in6;
	} addr = {0};
	switch(addr.sa.sa_family = fam) {
	case AF_INET:
		addr.in.sin_port = htons(XMOTO_PORT);
		addr.in.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		break;
	case AF_INET6:
		addr.in6.sin6_port = htons(XMOTO_PORT);
		addr.in6.sin6_addr = in6addr_loopback;
		break;
	default:
		if(kill(xmoto, SIGTERM) == -1) {
			perror("Failed to terminate X-Moto");
		}
		if(close(sock) == -1) {
			perror("Failed to close socket");
		}
		abort();
	}

	sleep(3U); /* X-Moto needs a chance to start */
	if(connect(sock, &addr.sa, sizeof(addr)) == -1) {
		if(fam == AF_INET6) {
			/* Try again with IPv4. */
			fam = AF_INET;
			goto startconn;
		}
		perror("Failed to connect to X-Moto");
		if(kill(xmoto, SIGTERM) == -1) {
			perror("Failed to terminate X-Moto");
		}
		if(close(sock) == -1) {
			perror("Failed to close socket");
		}
		exit(EXIT_FAILURE);
	}

	if(close(sock) == -1) {
		perror("Failed to close socket");
		if(kill(xmoto, SIGTERM) == -1) {
			perror("Failed to terminate X-Moto");
		}
		exit(EXIT_FAILURE);
	}
	if(kill(xmoto, SIGTERM) == -1) {
		perror("Failed to terminate X-Moto");
		exit(EXIT_FAILURE);
	}
}
