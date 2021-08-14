#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void khoitao(int x[][10],int n,int m);
void yeucau(int A[10][10],int N[10][10],int AV[10][10],int m);
int suantoan(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[]);
void nhap(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m);
int banker(int A[][10],int N[][10],int W[1][10],int n,int m);
void docFile(int A[][10],int N[][10],int M[10][10],int AV[1][10],int *n,int *m);

//ham main

int main()
{
	int r;
	int A[10][10];
	int M[10][10];
	int N[10][10];
	int W[1][10];
	int n,m,p,ch;
	docFile(A,N,M,W,&n,&m);
	r=banker(A,N,W,n,m);
	if(r!=0)
	{
		printf("\n\n Ban co muon thuc hien mot yeu cau bo sung ? (1=Yes|0=No): ");
		
		do
		{
			scanf("%d",&ch);
			if(ch == 1)
				{
					printf("\n Nhap quy trinh. : ");
					scanf("%d",&p);
					yeucau(A,N,W,m);
					r=banker(A,N,W,n,m);
					if(r == 0 )
						exit(0);
				}
			else if (ch == 0)
			{
				printf("\nchuong trinh dung tai day vi ban khong muon cap phat");
				getch();
				exit(0);
			}
			else
			{
				printf("\nnhap sai yeu cau vui long nhap lai\nnhap lai di:");
				getch();
			}
		} while (ch!= 1);
		
	}
	else
		{
			exit(0);
		}
	return 0;
	getch();
}
 //ham thuc thi xuat so tai nguyen va tien trinh
void khoitao(int x[][10],int n,int m)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		printf("\nP%d\t",i);
		for(j=0;j<m;j++)
		{
			printf(" %d\t",x[i][j]);
		}
	}	
}

//thuat toan yeu cau cap phat tai nguyen
void yeucau(int A[10][10],int N[10][10],int AV[10][10],int m)
{
	int request[1][10];//Tao bien request để cap phat
	int i;
	printf("\n nhap yeu cau bo sung : \n");
	for(i=0;i<m;i++)
	{
		printf(" yeu cau tai nguyen %d : ",i+1);
		scanf("%d",&request[0][i]);
	}
	for(i=0;i<m;i++)

		if(request[0][i] > N[0][i])
		{
			printf("\n da xay ra loi do so tai nguyen ma ban yeu cau vuot gioi han.\n");
			getch();
			exit(0);
		}
		if(request[0][i] > AV[0][i])
		for(i=0;i<m;i++)
		{
			printf("\n tai nguyen khong co san (treo tien trinh).\n");
			getch();
			exit(0);
		}
	//neu 2 truong hop tren khong xay ra thi cap phat thanh cong
		printf("\nphat hien 1 so yeu cau cap phat tai nguyen cho tien trinh\n");
		for(i=0;i<m;i++)
		{
			
			//Pi thay doi thong tin
			AV[0][i]-=request[0][i];
			A[0][i]+=request[0][i];
			N[0][i]-=request[0][i];
			printf("%d ", AV[0][i]);//Available sau cung(out put so 2 cua bai toan)
		}
		
	printf("\nCAP PHAT TAI NGUYEN AN TOAN, TIEN TRINH Pi CAP PHAT TAI NGUYEN THANH CONG AMAZING GOOD JOB");
	getch();
}

//thuat toan kiem tra safe
int suantoan(int A[][10],int N[][10],int AV[1][10],int n,int m,int a[])
{
	int i,j,k,x=0;
	int F[10],W[1][10];
	int pflag=0,flag=0;
	for(i=0;i<n;i++)
	{
		F[i]=0;
	}
	for(i=0;i<m;i++)
	{
		W[0][i]=AV[0][i];
	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			if(F[i] == 0)
			{
				flag=0;
				for(j=0;j<m;j++)
				{
					if(N[i][j] > W[0][j])
						flag=1;
				}
				if(flag == 0 && F[i] == 0)
				{
					for(j=0;j<m;j++)
					{
						W[0][j]+=A[i][j];
					}
					F[i]=1;
					pflag++;
					a[x++]=i;
				}
			}
		}
		if(pflag == n)
			return 1;
	}
	return 0;
}


//thuat toan cua banker nhap tien trinh va tai nguyen tu ban phim
void nhap(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m)
{
	int i,j;
	printf("\n nhap tong so cua processes : ");
	scanf("%d",n);
	printf("\n nhap tong so cua resources : ");
	scanf("%d",m);
	for(i=0;i<*n;i++)
	{
		printf("\n tientrinh %d\n",i+1);
		for(j=0;j<*m;j++)
		{
			printf(" Allocation %d : ",j+1);
			scanf("%d",&A[i][j]);
			printf(" Max %d : ",j+1);
			scanf("%d",&M[i][j]);
		}
	}
	printf("\n Available : \n");
	for(i=0;i<*m;i++)
	{
		printf(" tai nguyen %d : ",i+1);
		scanf("%d",&W[0][i]);
	}
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*m;j++)
		{
			N[i][j]=M[i][j]-A[i][j];
		}
	}
	printf("\n Allocation ");
	khoitao(A,*n,*m);
	printf("\n Max ");
	khoitao(M,*n,*m);
	printf("\n Need ");
	khoitao(N,*n,*m);

}

//giai thuat phat hien an toan hoac deadlock
int banker(int A[][10],int N[][10],int W[1][10],int n,int m)
{
	int j,i,a[10];//tao bien gan gia tri
	j = suantoan(A,N,W,n,m,a); 
	if (j != 0 )
	{
		printf("\n\n");
		printf("<");
		for(i=0;i<n;i++)
		     printf(" P%d  ",a[i]);// day tien trinh an toan(out put so 1 cua giai thuat)
		printf(">  An Toan");
		return 1;
	}
	else
	{
		printf("\n deadlock xay ra.\n");
		return 0;
	}
}

void docFile(int A[][10],int N[][10],int M[10][10],int W[1][10],int *n,int *m)
{
	int i,j;
	FILE * f = fopen("Text.txt","r");
	fscanf(f,"%d",n);
	fscanf(f,"%d",m);
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*m;j++)
		{
			fscanf(f,"%d",&A[i][j]);
			fscanf(f,"%d",&M[i][j]);
		}
	}
	for(i=0;i<*m;i++)
		{
		
			fscanf(f,"%d",&W[0][i]);
		}
	for(i=0;i<*n;i++)
	{
		for(j=0;j<*m;j++)
		{
			N[i][j]=M[i][j]-A[i][j];
		}
	}
	printf("\nAllocation\n ");
	khoitao(A,*n,*m);
	printf("\n\nMax\n");
	khoitao(M,*n,*m);
	printf("\n\nNeed\n ");
	khoitao(N,*n,*m);
	printf("\n\nAvailable :\n\n");
	for(i=0;i<*m;i++)
	{
		
		fscanf(f,"%d",&W[0][i]);
		printf("\t %d     ",W[0][i]);
	}
	getch();
	fclose(f);
}