#include <stdio.h>
#define 整数 int
#define 精整数 double
#define 如果 if
#define 否则 else
#define 返回 return
#define 输出 printf
#define 输入 scanf
#define 结果 result
#define 总和 sum
#define 呃 i
#define 嗯 n
#define 为 =
#define 等于 ==
#define 加 +
#define 减 -
#define 乘 *
#define 除 /
#define 模 %
#define 小于等于 <=
#define 大于等于 >=
#define 地址 &
#define 指针 *
#define 累乘 far
#define 入口 main
#define 整位 %d
#define 乘以 *=
#define 加加 ++
#define 加上 +=
#define 减去 -=
#define PP_NARG(...) PP_NARG_IMPL(__VA_ARGS__, 3, 2, 1, 0)
#define PP_NARG_IMPL(_1, _2, _3, N, ...) N
#define 对(...) PP_LOOP_SELECT(PP_NARG(__VA_ARGS__))(__VA_ARGS__)
#define PP_LOOP_SELECT(N) PP_LOOP_SELECT_(N)
#define PP_LOOP_SELECT_(N) PP_LOOP_##N
#define PP_LOOP_1(condition) while(condition)
#define PP_LOOP_3(init, condition, increment) for(init; condition; increment)


精整数 累乘(整数 嗯) {
    精整数 结果 为 1;
    整数 呃;
    对 ( 呃 为 1, 呃 小于等于 嗯, 呃 加加) 结果 乘以 呃;
    返回 结果;
}
int main() {
    精整数 总和 为 0;
    整数 嗯;
    输出("计算1！-2！+3！-......+（-1）?n！输入n：");
    输入("%d",地址 嗯);
    对 (整数 呃 为 1, 呃 小于等于 嗯, 呃 加加)
    如果 (呃 模 2 等于 1) 总和 加上 累乘(呃);
    否则 总和 减去 累乘(呃);
    输出("1！-2！+3！-......+（-1）?n！总和为: %f\n", 总和);
}

//int main(){
//	int m,n,gcd,lcm;
//	scanf("%d%d",&m,&n);
//	
//	if(m<=0||n<=0)printf("ERROR");
//	else{
//		for(gcd=m>n?n:m;/*m%gcd!=0||n%gcd!=0*/;gcd--){
//			if(m%gcd==0&&n%gcd==0)break;
//		}
//		for(lcm=m>n?m:n;lcm%m!=0||lcm%n!=0;lcm++);
//	}
//	printf("gcd=%d,lcm=%d",gcd,lcm);
//}

