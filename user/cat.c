#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"

char buf[512];
char buf2[512];
struct stat st;

void
cat(int fd)
{
	int n;

	while((n = read(fd, buf, sizeof(buf))) > 0) {
		if (write(1, buf, n) != n) {
			printf("cat: write error\n");
			exit();
		}
	}
	if(n < 0){
		printf("cat: read error\n");
		exit();
	}
}

int
main(int argc, char *argv[])
{
	int fd, i;

	if(argc <= 1){
		cat(0);
		exit();
	}

	for(i = 1; i < argc; i++){
		stat(argv[i], &st);
		if(st.type == T_SYMLINK)
		{
			if((fd = open(argv[i], O_NOFOLLOW)) > 0){
				exit();
			}else{
				printf("cat: cannot open %s\n", argv[i]);
				exit();
			}
		}
		else if((fd = open(argv[i], 0)) < 0){
			printf("cat: cannot open %s\n", argv[i]);
			exit();
		}
		cat(fd);
		close(fd);
	}
	exit();
}
