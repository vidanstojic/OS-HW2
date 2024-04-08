#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    if(symlink(argv[1], argv[2]) != 0){
        printf("\nNeuspesno ucitavanje.");
    }

	exit();
}
