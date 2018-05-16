#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    struct stat buf;
    char * path = "./tmp";
    stat(path, &buf);
    printf("./tmp file size = %lu\n", buf.st_size);

    int fd = open(path, O_CREAT|O_TRUNC|O_RDWR, S_IRUSR|S_IWUSR);
    if (fd == -1)
    {
        printf("open file %s failed, [%d-%s]\n", path, errno, strerror(errno));
        return -1;
    }

    char tmp[1204];
    int num = read(fd, tmp, buf.st_size);
    if( num < 0)
    {
        printf("read file %s failed, [%d-%s]\n", path, errno, strerror(errno));
        //return -1;
    }else{
        unsigned char * it = tmp;
        int i = 0;
        for(i; i < buf.st_size; i++)
        {
            printf(" out char as %u\n", *it++);
        }
    }
    //printf("file output as %s \n", tmp);
    
    char * tmp2 = "123456";
 
    if (write(fd, tmp2, strlen(tmp2)) != strlen(tmp2))
    {
        printf("write file %s failed, [%d-%s]\n", path, errno, strerror(errno));
        return -2;
    } 

}

/*************************************************************************/
/*
struct stat {
    dev_t         st_dev;       //文件的设备编号
    ino_t         st_ino;       //节点
    mode_t        st_mode;      //文件的类型和存取的权限
    nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
    uid_t         st_uid;       //用户ID
    gid_t         st_gid;       //组ID
    dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
    off_t         st_size;      //文件字节数(文件大小)
    unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
    unsigned long st_blocks;    //块数
    time_t        st_atime;     //最后一次访问时间
    time_t        st_mtime;     //最后一次修改时间
    time_t        st_ctime;     //最后一次改变时间(指属性)
};

*/
