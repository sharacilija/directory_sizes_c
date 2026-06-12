#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

size_t dirsize = 0;

// This is our custom function to sum up all the filesizes
int add_to_filesize(const char *fpath, 
    const struct stat *sb, int typeflag, 
    struct FTW *ftwbuf)
{
    dirsize += sb->st_size;
    return 0;
} 

// Print the file size in bytes, KB, MB, GB or TB
void pretty_print_size(void)
{
    char *sizes[] = {"B", "KB", "MB", "GB", "TB"};

    int count = sizeof(sizes) / sizeof(sizes[0]);

    double bytes = dirsize;

    int i = 0;

    while (bytes >= 1024 && i < count - 1)
    {
        bytes /= 1024;
        i++;
    }

    printf("Dirsize: %.2f %s\n", bytes, sizes[i]);
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <dirname>\n", argv[0]);
        exit(0);
    }

    // Find the size of the entire directory

    // 1. Get the directory name
    char *dirname = argv[1];
    printf("Dirname: %s\n", dirname);

    // 2. Recursively walk user-provided directory
    nftw(dirname, add_to_filesize, 20, 0);

    // 3. Print the accumulated size of the directory
    pretty_print_size();

    return 0;
}
