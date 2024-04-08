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






void
symlinkinfo(char *path)
{
    int sviSymLinkovi = 0;
    if(path == 0){
        sviSymLinkovi = 1;
        printf("\nPath: %s\n", path);
    }
	char buf[512], *p;
	int fd, n;
	char name[512];
	struct dirent de, di;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "symlinkinfo: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "symlinkinfo: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch(st.type){
    case T_SYMLINK:
        int symlink_fd = open(path, O_RDONLY);
        if (symlink_fd < 0) {
            printf("symlininfo: cannot open symlink %s\n", path);
        } else {
            // Pročitaj sadržaj simboličke veze
            int nbytes = read(symlink_fd, name, sizeof(name) - 1);
                if (nbytes < 0) {
                    printf("symlininfo: cannot read symlink %s\n", path);
            } else {
                    // Null-terminate string
                    name[nbytes] = '\0';
            }
        }
        printf("%s %d %d %d -> %s\n", fmtname(path), st.type, st.ino, st.size, name);

        break;
	case T_DIR:
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("symlinkinfo: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
		*p++ = '/';
			while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);

			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0){
				printf("symlininfo: cannot stat %s\n", buf);
				continue;
			}
			if (st.type == T_SYMLINK) {
				// Otvori fajl simboličke veze
				int symlink_fd = open(buf, O_RDONLY);
				if (symlink_fd < 0) {
					printf("symlininfo: cannot open symlink %s\n", path);
				} else {
					// Pročitaj sadržaj simboličke veze
					int nbytes = read(symlink_fd, name, sizeof(name) - 1);
						if (nbytes < 0) {
							printf("symlininfo: cannot read symlink %s\n", path);
					} else {
							// Null-terminate string
							name[nbytes] = '\0';
							// Ispisi sadržaj simboličke veze
							if(path == "."){
                                printf("%s %d %d %d -> %s\n", fmtname(buf), st.type, st.ino, st.size, name);
                            }
							else{

                                if(fmtname(buf) == path){
                                    printf("%s %d %d %d -> %s\n", fmtname(buf), st.type, st.ino, st.size, name);
                                }
                            }
                        }
					// Zatvori fajl simboličke veze
					close(symlink_fd);
				}
			}
		}
		break;
	}
	close(fd);
}



int
main(int argc, char *argv[])
{
    int i;

	if(argc < 2){
		symlinkinfo(".");
		exit();
	}
	else
    {
        symlinkinfo(argv[1]);
    }
	/*for(i=1; i<argc; i++)
		symlinkinfo(argv[i]);*/
	exit();
}
