#include<stdio.h>
#include<stdlib.h>

void pwn(){
    system("/bin/sh");
}

void vulnerable(){
    char buffer[32];
    char hello[] = "Hello,I'm dyf.";
    printf("%s\n",hello);
    printf("\nQAQ\n");
    printf("\nDo you have something to say?\n");
    gets(buffer);
    return;
}

int main(){
    vulnerable();
    return 0;
}
