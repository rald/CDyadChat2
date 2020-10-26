#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "dyad.h"

void *threadFunction(void *arg) {
	char *line=NULL;
	int lineLen=0;
	for(;;) {
		getline(&line,&lineLen,stdin);
		char *p=strrchr(line,'\n'); if(p) *p='\0';
		dyad_writef((dyad_Stream*)arg,"%s\n",line);
	}
}

static void onConnect(dyad_Event *e) {
	pthread_t thread;
  printf("connected.\n");
	pthread_create(&thread,NULL,threadFunction,e->stream);
}

static void onError(dyad_Event *e) {
  printf("error: %s\n", e->msg);
}

static void onLine(dyad_Event *e) {
  printf("%s\n", e->data);
}

static void onClose(dyad_Event *e) {
  printf("disconnected.\n");
}

int main(void) {
  dyad_Stream *s;
  dyad_init();

  s = dyad_newStream();
  dyad_addListener(s, DYAD_EVENT_CONNECT, onConnect, NULL);
  dyad_addListener(s, DYAD_EVENT_ERROR,   onError,   NULL);
  dyad_addListener(s, DYAD_EVENT_LINE,    onLine,    NULL);
  dyad_addListener(s, DYAD_EVENT_CLOSE,   onClose,   NULL);
  dyad_connect(s, "127.0.0.1", 14344);

  while (dyad_getStreamCount() > 0) {
    dyad_update();
  }

  dyad_shutdown();

  return 0;
}
