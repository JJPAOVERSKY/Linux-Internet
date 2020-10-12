#include<stdio.h>
#include<arpa/inet.h>
#include<stdlib.h>

void main(int argc, char **argv)
{
	in_addr_t  t;
	char *str;
	struct in_addr numstr;

	if(argc < 2)
	{
		printf("usage %s strip\n\r",argv[0]);
		exit(1);
	}

	t = inet_addr(argv[1]);
	printf("%x\n\r",t);

	inet_aton(argv[1],&numstr);
	printf("%x\n\r",numstr.s_addr);
}
