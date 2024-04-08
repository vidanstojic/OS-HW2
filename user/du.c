#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"


char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}




void duTotal(char *path){
	char buf[512], *p;
	int fd, n;
	char name[512];
	struct dirent de, di;
	struct stat st;
	int flag = 0;
	if((fd = open(path, 0)) < 0){
		flag = 1;
	}

	if(stat(path, &st)){
		printf("%s %d\n", fmtname(path), st.blocks);
		return;
	}
	switch(st.type){
	case T_DIR:
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("du: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
		*p++ = '/';
		int total = 0;
			while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);

			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0){
				printf("du: cannot stat %s\n", buf);
				continue;
			}
			total+= st.blocks;
			printf("%s %d\n", fmtname(buf), st.blocks);
		}
		printf("TOTAL %d\n", total);
		break;
	default:
		printf("%s %d\n", fmtname(path), st.blocks);
		break;
	}
	close(fd);
}



int
main(int argc, char *argv[])
{
	if(argc < 2){
		duTotal(".");
		exit();
	}
	else
    {
        duTotal(argv[1]);
    }
	exit();
}
