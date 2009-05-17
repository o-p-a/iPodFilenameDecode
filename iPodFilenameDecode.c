/*
	iPod Filename Decode

	2005/10/06 opa
*/

#include <stdio.h>
#include <string.h>

int hexchr(char c)
{
	return strchr("01234567890AaBbCcDdEeFf",c)!=NULL;
}

void decode(char *dst,const char *src)
{
	char
		c,
		w[3];
	unsigned int
		n;

	while((c=*(src++))!='\0'){
#if 1
		if(c=='['){
			while(hexchr(*src) && hexchr(*(src+1))){
				w[0]=*(src++);
				w[1]=*(src++);
				w[2]='\0';
				sscanf(w,"%02x",&n);
				*(dst++)=n;
			}
			if(*src==']')
				++src;
		}else{
			*(dst++)=c;
		}
#else
		*(dst++)=c;
#endif
	}
	*(dst++)='\0';
}

int main()
{
	char
		d[4096],
		s[4096];

        while(!feof(stdin)){
		fgets(d,sizeof d,stdin);
		while(1){
			if(strlen(d)==0)
				break;
			if(d[strlen(d)-1]!='\n' && d[strlen(d)-1]!='\r')
				break;
			d[strlen(d)-1]='\0';
		}
		decode(s,d);

		printf("ren \"%s\" \"%s\"\r\n",d,s);
	}

        return 0;
}

