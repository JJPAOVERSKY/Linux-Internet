#include<arpa/inet.h>
#include<stdio.h>

void main()
{
	int i;
	char buf[64];
	struct in_addr *in;
	struct in6_addr *in6;

	inet_pton(AF_INET,"1.2.34.5",buf);
	in = (struct in_addr*)buf;
	printf("%x\n\r",in->s_addr);

	inet_pton(AF_INET6,"1234:5678::",buf);
	in6 = (struct in6_addr*)buf;

	for(i = 0;i < 16;i++)
	{
		printf("%02x",in6->s6_addr[i]);
		if((i&1)&&(i<15))
			printf(":");
	}

	printf("\n\r");


}
