#include <stdarg.h>
#include <stdio.h>
#include "my_ioq.h"

int mscan(const char *format, ...){
	int ret;
	va_list args;
	
	va_start(args, format);
	ret = vscanf(format,args);
	va_end(args);
	
	while(getchar()!='\n');//while(getchar()!='\n' && ret != E0F);
	
	return ret;
}
