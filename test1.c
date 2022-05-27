#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int main()
{
    unsigned char code[] = { 
        0x48, 0x89, 0xf8,
        0x48, 0x83, 0xc0, 0x04,
        0xc3
    };  
    const size_t size = 1024;
    void* ptr = mmap(NULL, size,
            PROT_READ | PROT_WRITE | PROT_EXEC,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
    if (ptr==(void*)-1) {
        fprintf(stderr, "mmap failed\n");
        return -1; 
    }   
    memcpy(ptr, code, sizeof(code));

    typedef long(*JittedFunc)(long);
    JittedFunc func = ptr;
    int result = func(2);
    printf("result = %d\n", result);

    return 0;
}
