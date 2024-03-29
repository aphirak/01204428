#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h> // for memset and strlen

int main(int argc ,char *argv[])
{
        assert(argc > 1);
        char buf[100] ;
        char i = 0;
        memset(buf, 0, 100);
        printf("Input: %s\n", argv[1]);

        int fp = open("/dev/mychar", O_RDWR);
        write(fp, argv[1], strlen(argv[1]));
        read(fp, &buf, 1);
        close(fp);
     
        printf("Reversed by the driver: %s\n" ,buf);
}

