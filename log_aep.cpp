#include "libpmemlog.h"
#include "test.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32

#else
#include <unistd.h>
#endif

/* size of the pmemlog pool -- 1 GB */
#define POOL_SIZE ((off_t)(1 << 26))

/*
 * printit -- log processing callback for use with pmemlog_walk()
 */
int
printit(const void* buf, size_t len, void* arg)
{
	fwrite(buf, len, 1, stdout);
	return 0;
}

TEST_F(TimeTest, io_pemefile)
{
	const char path[] = "D:\\pmem-fs\\log_aep.dat";
	PMEMlogpool* plp;
	size_t nbyte;

	/* create the pmemlog pool or open it if it already exists */
	plp = pmemlog_create(path, POOL_SIZE, 0666);

	if (plp == NULL)
		plp = pmemlog_open(path);

	if (plp == NULL) {
		perror(path);
		exit(1);
	}

	/* how many bytes does the log hold? */
	// nbyte = pmemlog_nbyte(plp);
	// printf("log holds %zu bytes\n", nbyte);

	/* append to the log... */
	const char* str = "This is the first string appended\n";
	for (int i = 0; i < LOG_CNT; i++) {
		if (pmemlog_append(plp, str, strlen(str)) < 0) {
			perror("pmemlog_append");
			exit(1);
		}
	}
	printf("pmem输出%d条日志。\n", LOG_CNT);

	/* print the log contents */
	// printf("log contains:\n");
	// pmemlog_walk(plp, 0, printit, NULL);

	pmemlog_close(plp);
}
