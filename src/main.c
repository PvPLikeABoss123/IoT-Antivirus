#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "headers/include.h"

#define INIT_PIDBUF_MAX 4096

struct scan_pids_t {
	char pid_s[16];
	int pid_i;
	enum state {
		SCAN_QUEUED,// waiting to be sent to thread
		SCAN_CMDLINE,// check if bin still on device
		SCAN_EXE,
		SCAN_MAPS,
		SCAN_DELBIN,
	};
};

struct str_t {
	int *loc_x, *loc_y;// NOTE: begining of str, end of str
	
};

struct scan_pids_t **scan_pids = NULL;
unsigned int *scan_pids_size = NULL;
pthread_t *tid_hndl = NULL;
pthread_t **tids_worker = NULL;

void *procscan_worker(void *args) {
	
}

void *procscan_handler(void *args) {
	tids_worker = malloc(sizeof(pthread_t *));// TODO: make enough threads for pids
}

struct str_t **util_tokint(unsigned char *buf, int delim) {
	char *tmp = ("%s", buf);
	struct str_t **strs = malloc(1 * sizeof(struct str_t *));
	int i, str_size = 0;
	
	for(i = 0; *tmp != '\0'; i++) {
		if(*tmp != delim) {
			*tmp++;
		} else {
			struct str_t *str = malloc(1 * sizeof(struct str_t *));
			str->loc_x = &(*tmp)-i;
			str->loc_y = &(*tmp)-1;
			i = 0;
			
			strs = realloc(sizeof(struct str_t *), str_size+1);
			*strs[str_size] = str;
			str_size++;
			*tmp++;
			free(&str);
		}
	}
}

static void init_scanpids() {
	unsigned char fbuf[INIT_PIDBUF_MAX] = malloc(INIT_PIDBUF_MAX * sizeof(char *));
	int i, fbuf_fd, fbuf_got;
	
	fbuf_fd = open("/bin/ls /proc/", O_RDONLY);

	if(fbuf_got = read(fbuf_fd, fbuf, INIT_PIDBUF_MAX)) {
		buffer[fbuf_got] = '\0';
		printf("[init] Gathered pids to scan!\r\n");
	} else {
		printf("Something Wrong Occured!\r\n");
		printf("Bailing Out (init_scanpids() -> reading /proc)\r\n");
		exit(0);
	}
	
	unsigned char *pids[scan_pids_size] = NULL;
	
	util_tokint(fbuf, " ");
	
	for(i = 0; i < scan_pids_size, i++) {
		strcpy(scan_pids[i]->pid_s, pids[i]);
		scan_pids[i]->pid_i = atoi(pids[i]);
		scan_pids[i]->state = SCAN_QUEUED;
	}
	
	free(fbuf);
	free(pids);
}

int main(int argc, char *argv[]) {
	// TODO: Daemonize and run scan every 24 hours
	
	init_scanpids();
	
	tid_hndl = malloc(sizeof(pthread_t));
	
}