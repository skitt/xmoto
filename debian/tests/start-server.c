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
#include <time.h>
#include <unistd.h>
extern char **environ;

#define XMOTO_PORT 4130

static noreturn void xmoto_died(int s) {
	_Exit(EXIT_FAILURE);
}

static int cleanup(pid_t xmoto, int sock, int status) {
	if (kill(xmoto, SIGTERM) == -1) {
		perror("Failed to terminate X-Moto");
	}
	if (sock >= 0 && close(sock) == -1) {
		perror("Failed to close socket");
	}
	exit(status);
}

int main(void) {
	struct sigaction act = { .sa_handler = xmoto_died };
	if(sigemptyset(&act.sa_mask) == -1) {
		perror("Failed to empty signal set");
		exit(EXIT_FAILURE);
	}
	sigaction(SIGCHLD, &act, NULL);

	pid_t xmoto;
	int k = posix_spawnp(&xmoto, "xmoto", NULL, NULL, (char*[]){"xmoto", "--server", NULL}, environ);
	if(k) {
		fprintf(stderr, "Failed to start X-Moto: %s\n", strerror(k));
		exit(EXIT_FAILURE);
	}

	time_t start = time(NULL);
	/* Try IPv6 first, then IPv4. */
	sa_family_t families[] = { AF_INET6, AF_INET };

	while (1) {
		if (time(NULL) - start > 60) {
			perror("Timed out waiting for X-Moto");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < 2; i++) {
			sa_family_t fam = families[i];
			int sock;
			sock = socket(fam, SOCK_STREAM, IPPROTO_TCP);
			if (sock == -1) {
				perror("Failed to create socket");
				cleanup(xmoto, sock, EXIT_FAILURE);
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
				cleanup(xmoto, sock, EXIT_FAILURE);
			}

			if (connect(sock, &addr.sa, sizeof(addr)) == 0) {
				/* Success! */
				cleanup(xmoto, sock, EXIT_SUCCESS);
			}
			if (close(sock) == -1) {
				perror("Failed to close socket");
				cleanup(xmoto, -1, EXIT_FAILURE);
			}
		}

		sleep(1);
	}

	cleanup(xmoto, -1, EXIT_FAILURE);
}
