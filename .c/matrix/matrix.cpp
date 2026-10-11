#include <stdio.h>
#include "my_ioq.h"
#include "my_frac.h"
#include <stdlib.h>



frac** inverse(int n,frac** a){
	int i,j,k=0;
	frac temp;
	frac **inv=(frac**)malloc(n * sizeof(frac*));
	for(i=0;i<n;i++){
		inv[i]=(frac*)malloc(n * sizeof(frac));
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				inv[i][j].a=1;
				inv[i][j].b=1;
				simpy(&inv[i][j]);
			}else{
				inv[i][j].a=0;
				inv[i][j].b=1;
				simpy(&inv[i][j]);
			}
		}
	}
	for(i=0;i<n;i++){
		if(a[i][i].a==0){
			for(j=i;j<n;j++){
				if(a[j][i].a!=0){
					for(k=0;k<n;k++){
						temp=a[j][k];
						a[j][k]=a[i][k];
						a[i][k]=temp;
						temp=inv[j][k];
						inv[j][k]=inv[i][k];
						inv[i][k]=temp;
					}
				}
			}
			if(j==n&&k==0){
				printf("cannot inverse!!\n");
				for(i=0;i<n;i++){
					for(j=0;j<n;j++){
						inv[i][j].a=0;
						simpy(&inv[i][j]);
					}
				}
				return inv;
			}
		}else{
			frac m=a[i][i];
			for(j=0;j<n;j++){
				a[i][j]=frac_div(a[i][j],m);
				inv[i][j]=frac_div(inv[i][j],m);
			}
			for(j=0;j<n;j++){
				if(j==i)continue;
				frac p=a[j][i];
				for(k=0;k<n;k++){
					a[j][k]=frac_mis(a[j][k],frac_mul(p,a[i][k]));
					inv[j][k]=frac_mis(inv[j][k],frac_mul(p,inv[i][k]));
				}
			}
		}
	}
	for(i=0;i<n;i++){
		if(a[i][i].a==0){
			printf("cannot inverse!!\n");
			for(i=0;i<n;i++){
				for(j=0;j<n;j++){
					inv[i][j].a=0;
				}
			}
			return inv;
		}
	}
	return inv;
}

void free_matrix(frac **matrix,int n){
	for(int i=0;i<n;i++){
		free(matrix[i]);
	}
	free(matrix);
}

int main(){
	int n,i,j,x=0,y=1;
	printf("the size of matrix:");
	mscan("%d",&n);
//	frac (*arr1)[n]=malloc(n*sizeof(frac[n]));
//	if(!arr1)return 1;
	frac **arr1=(frac**)malloc(n*sizeof(frac*));
	frac **inv=(frac**)malloc(n*sizeof(frac*));
	for(i=0;i<n;i++){
		arr1[i]=(frac*)malloc(n*sizeof(frac));
		inv[i]=(frac*)malloc(n*sizeof(frac));
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			arr1[i][j].a=x;
			arr1[i][j].b=y;
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			frscan(&arr1[i][j]);
			simpy(&arr1[i][j]);
		}
	}
	printf("the matrix of enter:\n\n");
	for(i=0;i<n;i++){
		printf("| ");
		for(j=0;j<n;j++)printf("%s ",arr1[i][j].c);
		printf(" |\n");
	}
	
	inv=inverse(n,arr1);

	printf("the inverse of it:\n\n");
	for(i=0;i<n;i++){
		printf("| ");
			for(j=0;j<n;j++){
				printf("%s ",inv[i][j].c);
		}
		printf(" |\n");
	}
	free_matrix(arr1,n);
	free_matrix(inv,n);
}

