#include "communication.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>
#include <sys/epoll.h>
#include <stdlib.h>  /* malloc() */
#include <stdbool.h>  /* boolean */
#include <stdio.h>  /* printf() */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


#define MAX_EVENTS    1
#define SOCKBUFLEN       8192
#define NODELAY             0

int create(int *epfd) {

  *epfd = epoll_create (MAX_EVENTS); /* plan to watch ~MAX_EVENTS fds */

  if (*epfd < 0) {
    perror ("epoll_create");
    return *epfd;
  }
  return 0;
}


int add(int epfd, int fd) {
  struct epoll_event event;
  int ret;

  event.data.fd = fd; /* return the fd to us later */
  event.events = EPOLLIN | EPOLLOUT;

  ret = epoll_ctl (epfd, EPOLL_CTL_ADD, fd, &event);

  if (ret) {
    printf("NEJ: %s\n", strerror(errno));
    return ret;
  }
  return 0;
}

/*



*/
int handle_request(int fd, int *connection) {

  int listnum;			/* Current item in connectlist for for loops */
  struct sockaddr_in their_addr;	/* connector's address information */
  socklen_t sin_size;

  /* We have a new connection coming in!  We'll
     try to find room for it in connectlist. */
  sin_size = sizeof their_addr;
  *connection =  accept (fd, (struct sockaddr *) &their_addr, &sin_size);

  if (*connection < 0)
    {
    printf("NEJ: %s\n", strerror(errno));
    }


}

main() {

  struct epoll_event events[MAX_EVENTS];
  int nr_events, i, epfd, listen, ret, connection;

  /* Create a file descriptor instance */
  create(&epfd);

  /* Create a listening socket ... */
  listen = createService(4390,  SOCKBUFLEN, NODELAY);

  /* Add a listen to that instance ... */
  add(epfd, listen);

#if 0
  events[0].data.fd = listen; /* return the fd to us later */
  events[0].events = EPOLLIN | EPOLLOUT;
#endif

  ret = epoll_ctl (epfd, EPOLL_CTL_ADD, listen, events);

  if (ret) {
    printf("NEJ: %s\n", strerror(errno));
  }

  /* Start polling ... */
  while(true) {

    nr_events = epoll_wait (epfd, events, MAX_EVENTS, 0);

    if (nr_events < 0) {
      perror ("epoll_wait");
    }

    for (i = 0; i < nr_events; i++) {

      /*
       * We now can, per events[i].events, operate on
       * events[i].data.fd without blocking.
       */

      /* Handle a new request from a client? */
      if (events[i].data.fd == listen) {
	handle_request(events[i].data.fd, &connection);
        printf ("event=%ld on fd=%d\n", events[i].events, events[i].data.fd);
	add(epfd, connection);
      }

    }
    


  }

}
