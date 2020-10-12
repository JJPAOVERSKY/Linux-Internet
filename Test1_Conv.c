#include<arpa/inet.h>
#include<stdio.h>
void main()
{
    in_addr_t  t;
    char *str;
    struct in_addr numstr;

    t = inet_addr("111.222.8.9");
    printf("%x\n\r",t);

    
    inet_aton("202.11.22.35",&numstr);
    printf("%x\n\r",numstr.s_addr);

    str = inet_ntoa(numstr);
    printf("%s\n\r",str);    
}
