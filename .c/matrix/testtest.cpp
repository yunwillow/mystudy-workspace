//#include<stdio.h>
//#include<my_ioq.h>
//#include<string.h>
//#include<stdlib.h>
//
//
//
//typedef struct int_frac{
//	int a;
//	int b;
////	void(*fs)(int*,int*,char*);	
//	char c[32];
//}frac;
//
////void frscan(int* a,int* b,char* c){
//////	*a=0;*b=1;
////	for(;b==0;printf("Error with denominator=0!"))mscan("%d/%d",a,b);
////	if(*b!=1){
////		int lcm=*a>*b?*b:*a;
////		for(;lcm>0;lcm--){
////			if(*a%lcm==0&&*b%lcm==0)break;
////		}
////		*a=*a/lcm;*b=*b/lcm;
////	}
////	char ca[16],cb[16];
////	itoa(*a,ca,10);itoa(*b,cb,10);
////	sprintf(c,"%s/%s",ca,cb);
////}
//
//void frscan(frac *a){
//	for(;a->b==0;mscan("%d/%d",&a->a,&a->b))printf("Error with denominator=0!regain it:");
//	if(a->b!=1){
//		int lcm=a->a>a->b?a->b:a->a;
//		for(;lcm>0;lcm--){
//			if(a->a%lcm==0&&a->b%lcm==0)break;
//		}
//		a->a=a->a/lcm;a->b=a->b/lcm;
//	}
//	if(a->b!=1){
//		char ca[16],cb[16];
//		itoa(a->a,ca,10);itoa(a->b,cb,10);
//		sprintf(a->c,"%s/%s",ca,cb);
//	}else{
//		char ca[16];
//		itoa(a->a,ca,10);
//		sprintf(a->c,"%s",ca);
//	}
//}
//
//int main(){
//	int x,y=1;
//	mscan("%d/%d",&x,&y);
//	frac a={x,y,};
//	frscan(&a);
//	printf("%s",a.c);
//}
