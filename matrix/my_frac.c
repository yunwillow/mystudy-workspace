#include "my_frac.h"

void simpy(frac *a){
	int lcm=a->a>a->b?a->b:a->a;
	if(a->a!=0){
		for(;lcm>0;lcm--){
			if(a->a%lcm==0&&a->b%lcm==0){
				a->a=a->a/lcm;a->b=a->b/lcm;
				break;
			}
		}
		for(;lcm<0;lcm++){
			if(a->a%lcm==0&&a->b%lcm==0){
			a->a=a->a/lcm;a->b=a->b/lcm;
			break;
			}
		}
	}else a->b=1;
	if(a->b!=1&&a->b!=-1){
		char ca[16],cb[16];
		itoa(a->a,ca,10);itoa(a->b,cb,10);
		sprintf(a->c,"%s/%s",ca,cb);
	}else if(a->b==-1){
		a->a=-a->a;a->b=1;
		char ca[16];
		itoa(a->a,ca,10);
		sprintf(a->c,"%s",ca);
	}else{
		char ca[16];
		itoa(a->a,ca,10);
		sprintf(a->c,"%s",ca);
	}
}

void frscan(frac *a){
	printf("enter:(a/b or a)");
	mscan("%d/%d",&a->a,&a->b);
	for(;a->b==0;mscan("%d/%d",&a->a,&a->b)){
		printf("Error with denominator=0!regain it:");
		a->b=1;
	}
	simpy(a);
}

frac frac_add(frac a,frac b){
	frac c;
	c.a=a.a*b.b+b.a*a.b;
	c.b=a.b*b.b;
	simpy(&c);
	return c;
}

frac frac_mis(frac a,frac b){
	frac c;
	c.a=a.a*b.b-b.a*a.b;
	c.b=a.b*b.b;
	simpy(&c);
	return c;
}

frac frac_mul(frac a,frac b){
	frac c;
	c.a=a.a*b.a;
	c.b=a.b*b.b;
	simpy(&c);
	return c;
}

frac frac_div(frac a,frac b){
	frac c;
	if(b.a!=0){
		c.a=a.a*b.b;
		c.b=a.b*b.a;
		simpy(&c);
	}else{
		printf("\t\terror with division by 0!!\n");
		c.a=114514;c.b=1;
		simpy(&c);
		return c;
	}
	
	return c;
}

