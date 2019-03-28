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
#define POOL_SIZE LOG_MAX_BYTE
#define PMEM_MAX_OPS 1024
/*
 * printit -- log processing callback for use with pmemlog_walk()
 */
int
printit(const void* buf, size_t len, void* arg)
{
	fwrite(buf, len, 1, stdout);
	return 0;
}

double
pmem_write(const char *path, int block_size)
{
	PMEMlogpool *plp;
	size_t nbyte;

	/* create the pmemlog pool or open it if it already exists */
	plp = pmemlog_create(path, POOL_SIZE, 0666);

	if (plp == NULL)
		plp = pmemlog_open(path);

	if (plp == NULL) {
		perror(path);
		exit(1);
	}

	int cnt = LOG_MAX_BYTE / block_size;
	if (cnt > PMEM_MAX_OPS)
		cnt = PMEM_MAX_OPS;

	long _start = GET_TIME_STAMP_US;
	/* how many bytes does the log hold? */
	// nbyte = pmemlog_nbyte(plp);
	// printf("log holds %zu bytes\n", nbyte);

	/* append to the log... */
	char *buf = (char *)malloc(block_size);
	for (int i = 0; i < cnt; i++) {
		if (pmemlog_append(plp, buf, block_size) < 0) {
			perror("pmemlog_append");
			break;
		}
	}

	long dur = GET_TIME_STAMP_US - _start;
	free(buf);
	printf("test-pmem-write block_size :%5d : %.3f M/s.\n", block_size,
	       static_cast<double>(cnt) * block_size / dur);
	/* print the log contents */
	// printf("log contains:\n");
	// pmemlog_walk(plp, 0, printit, NULL);

	pmemlog_rewind(plp);
	pmemlog_close(plp);
	return 1;
}

TEST(IOTest, pmem_io)
{
	std::string path = PMEM_ROOT + (std::string) "/log_aep.dat";
	pmem_write(path.c_str(), (32));
	pmem_write(path.c_str(), (1 << 10));
	pmem_write(path.c_str(), 4 * (1 << 10));
}

/*
TEST_F(TimeTest, io_pemefile)
{
	const char path[] = "D:\\pmem-fs\\log_aep.dat";
	PMEMlogpool* plp;
	size_t nbyte;

	/* create the pmemlog pool or open it if it already exists #1#
	plp = pmemlog_create(path, POOL_SIZE, 0666);
	
	if (plp == NULL)
		plp = pmemlog_open(path);

	if (plp == NULL) {
		perror(path);
		exit(1);
	}

	/* how many bytes does the log hold? #1#
	// nbyte = pmemlog_nbyte(plp);
	// printf("log holds %zu bytes\n", nbyte);

	/* append to the log... #1#
	const char* str = "This is the first string appended\n";
	for (int i = 0; i < PMEM_MAX_OPS; i++) {
		if (pmemlog_append(plp, str, strlen(str)) < 0) {
			perror("pmemlog_append");
			exit(1);
		}
	}
	printf("pmem输出%d条日志。\n", PMEM_MAX_OPS);

	/* print the log contents #1#
	// printf("log contains:\n");
	// pmemlog_walk(plp, 0, printit, NULL);

	pmemlog_close(plp);
}
*/
