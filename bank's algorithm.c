#include"stdio.h"
#include"math.h"
#include"string.h"
int **MKCreatArray(int x, int y)/*初始化二维数组*/
{
	int i,j, **p=NULL;
	/*给数组分配动态空间*/
	p=(int**)malloc(sizeof(int)*x);
	for(i=0;i<x;i++)
	p[i]=(int *)malloc(sizeof(int)*y);
	/*返回数组的地址供使用*/
	return p;
	
}
int *MKC(int x)/*初始化一维数组*/
{
	int *p=(int *)malloc(sizeof(int)*x),i;/*给数组分配动态空间*/
	if(!p)
	{
		free(p);
		return NULL;
	}
	/*格式化数组空间*/
	memset(p,0x00,sizeof(int)*x);
	printf("please input the nums of the available\n");
	for(i=0;i<x;i++)
	{
		if(!i)
		{
			printf("ava[%d]=  ",i+1);
		}
		
		scanf("%d",p+i);
	}
	/*返回数组的地址供使用*/
	return p;
}
void MKF(int *p)/*释放数组空间*/
{
	if(p!=NULL)
	{
		free(p);
	}
	p=NULL;
}
	
	
	
	
int jiex(int x)/*计算阶乘X的值*/
{
	if(x==1)
	{
		return 1;
	}
	else
	{
		return x*jiex(x-1);
	}
}
int SY(int *ava,int **all,int **need,int n,int m)/*安全算法*/
{
	/*声明两个长度分别为m与n的数组work和finish*/
	int *work=(int *)malloc(sizeof(int)*m),*finish=(int *)malloc(sizeof(int)*n),i,j,x,y=0,count=0,count1=0;
	/*出错判断*/
	if(!work)
	{
		free(work);
		return 0;
	}
	if(!finish)
	{
		free(finish);
		return 0;
	}
	
	x=jiex(n);
	/*初始化work为ava格式*/
	for(i=0;i<m;i++)
	{
		work[i]=ava[i];
	}
	/*初始化finish 全部数据初始为0*/
	for(j=0;j<n;j++)
	{
		finish[j]=0;
	}
	/*对进程进行判断，因为系统安全，每次必然会少一个进程，所以运行次数，最大为n的阶乘*/
	while(y<x)
	{
		for(i=0;i<n;i++)
		{
			/*对进程按序号进行判断；count为对进程需要的所有资源进行一个计数*/
			count=0;
			for(j=0;j<m;j++)
		    {
		    	//寻找i，使得finish[i]=FALSE，而且NEED[i]<=work[i],如果存在继续执行，否这判断是否所有的finish元素都为1，则系统处于安全状态。
			    if((!finish[i])&&(need[i][j]<=work[j]))
			    {
			    	//如果进程i中的资源满足，则计数器加1；
				    count++;
				    //如果进程i中的所有进程均满足
			        if(count==m)
				    {
				    	//此进程将能获得资源。
					    int z=0;
					    for(z=0;z<m;z++)
				        {
				    	    work[z]=work[z]+all[i][z];
				        }
				        //输出进程号
				        printf("p[%d]  ",i);
				        finish[i]=1;
				        //对能被分配的进程数进行判断。
				        count1++;
				    }
				
			    }
		    }
		    //循环的次数进行计数，使其能够推出循环
		    y++;
		}
	}
	//循环完成后，对分配的进程数进行判断，如果进程数等于了总进程数，则安全，否则不安全。
	if(count1<n)
	{
		//释放数组空间
		free(work);
		free(finish);
		return 0;
	}
	else
	{
		//释放数组空间
		free(work);
		free(finish);
		return 1;
	}
}
//资源要求算法
void RRA(int **request,int **all,int *ava,int **need,int n,int m,int n1)
{
	//i对循环进行判断。count进行计数，b为请求进程的进程号。
	int i=0, b,j,count=0,n2=0;
	n2=jiex(n1);
	/*对进程进行判断，因为系统安全，每次必然会少一个进程，所以运行次数，最大为n的阶乘*/
	while(i<n2)
	{
		b=request[i][0]-1;
		count=0;
		for(j=0;j<m;j++)
	    {
	    	//如果请求资源数小于需求数，则继续执行，否则等待。
	    	if(request[i][j+1]<=need[b][j])
	    	{
	    	//如果请求资源数小于系统可提供数，则继续执行。
	            if(request[i][j+1]<=ava[j])
	    		{
	    			//对i进程的满足请求的资源进程进行计数
	    		    count++;
	    		    //尝试分配额资源
	    			ava[j]=ava[j]-request[i][j+1];
	    			all[b][j]=all[b][j]+request[i][j+1];
	    			need[b][j]=need[b][j]-request[i][j+1];
	    			//如果i进程的所有资源都满足
	    			if(count==m)
	    			{
	    			    //如果安全，则按此分配，并返回安全值
	    				if(SY(ava,all,need,n,m))
	    			    {
	    				    int x1;
	    				    for(x1=0;x1<m;x1++)
	    				    {
	    					    printf("%2d  ",request[i][x1+1]);
	    					        
	    				    }
	    				    printf("\n");
	    				    printf("the request is safety\n");
	    				        
	    			    }
	    			    //不安全，则取消分配。继续进行
	    			    else
	    			    {
	    			    	ava[j]=ava[j]+request[i][j+1];
	    			        all[b][j]=all[b][j]-request[i][j+1];
	    			        need[b][j]=need[b][j]+request[i][j+1];
	    			        printf("the request isn't safety\n");
	    			    }
	    			}
	    		}
	    	}
	    }
	    i++;
	 }
}
int main()
{
	//初始化所有需要的数据。
	int i,j,n1,count=-1,*ava=NULL,**all=NULL,**need=NULL,**request=NULL,**max=NULL;
	static int n,m;
	//输入需要的进程数
	printf("please input the nums of process \n");
	scanf("%d",&n);
	//输入需要的资源数
	printf("please input the nums of resource \n");
	scanf("%d",&m);
	//初始化二维数组
	all=MKCreatArray(n,m);
	//初始化二维数组
	need=MKCreatArray(n,m);
	//初始化二维数组
	max=MKCreatArray(n,m);
	//对进程拥有资源进行赋值
	printf("please input the allcation \n");
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{
		if(!j)
		{
			printf("the all[%d][%d]=    ",i+1,j+1);
		}
		    scanf("%d",&all[i][j]);
		
		if(j==(m-1))
		{
			printf("\n");
		}
	}

	//对进程最大需求资源进行赋值
	printf("please input the maxist need \n");
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{
		if(!j)
		{
			printf("the all[%d][%d]=    ",i+1,j+1);
		}
		scanf("%d",&max[i][j]);
		
		if(j==(m-1))
		{
			printf("\n");
		}
	}
	//转化为进程当前需要资源
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{
		need[i][j]=max[i][j]-all[i][j];
	}
	//初始化系统可用资源
	ava=MKC(m);
	while(1)
	{
		//用户界面
		printf("what do you  want to do \n");
		printf("tepe the current PID and resource,please input the 4\n");
	    printf("if you want to input a new resource and PID,please input the 3\n");
		printf("if you want to test the request, please input the 2\n");
		printf("if you want  to test the safety, please input the 1\n");
		printf("if you want  to exit, please input the 0\n");
		scanf("%d",&count);
		printf("\n");
		if(!count)
		break;
		//count的值来表示出用户需要的服务。
		switch(count)
		{
			case 1:
			//判断当前系统是否安全
			if(SY(ava,all,need,n,m))
	        {
		        printf("\nSAFETY\n");
	        }
	        else
	        {
		        printf("\nUNSAFETY\n");
	        }
	        break;
	        case 2:
	        //判断按照目前的分配方式，系统是否安全
	        printf("please input the nums of request \n");
	        scanf("%d",&n1);
	        //初始化分配二维数组。其中它的每个进程的第1个数，表示的为进程号
	        request=MKCreatArray(n1,m+1);
	        for(i=0;i<n1;i++)
	        for(j=0;j<=m;j++)
	        {
	        	if(!j)
	    	    {
	    		    printf("the PID is    ");
	    		    scanf("%d",&request[i][j]);
	    		}
		        else
		        {
					if(j==1)
					{
						printf("the request[%d][%d]=    ",i+1,j);
					}
		            scanf("%d",&request[i][j]);
		        }
		
		        if(j==(m))
		        {
			        printf("\n");
		        }
	        }
	        //进行判断。
	        RRA(request,all,ava,need,n,m,n1);
	        //释放数组空间。
			if(NULL!=request)
			{
				for(i=0;i<n1;i++)
	            free(request[i]);
	            free(request);
				request=NULL;
			}
	        break;
	        case 3:
	        //释放数组空间
	        if(NULL!=all)
	        {
		        for(i=0;i<n;i++)
	            free(all[i]);
	            free(all);
	            all=NULL;
	        }
	        //释放数组空间
	        if(NULL!=max)
	        {
		        for(i=0;i<n;i++)
	            free(max[i]);
	            free(max);
	            max=NULL;
	        }
	        //释放数组空间
	        if(NULL!=need)
	        {
		        for(i=0;i<n;i++)
	            free(need[i]);
	            free(need);
	            need=NULL;
	        }
	        //释放数组空间
	        MKF(ava);
	        //输入需要的进程数
	        printf("please input the nums of process \n");
	        scanf("%d",&n);
	        //输入需要的资源数
	        printf("please input the nums of resource \n");
	        scanf("%d",&m);
	        //初始化二维数组
	        all=MKCreatArray(n,m);
	        //初始化二维数组
	        need=MKCreatArray(n,m);
	        //初始化二维数组
	        max=MKCreatArray(n,m);
            printf("please input the allcation \n");
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
		        if(!j)
				{
					printf("the all[%d][%d]=    ",i+1,j+1);
				}
		        scanf("%d",&all[i][j]);
		        if(j==(m-1))
		        {
			        printf("\n");
		        }
	        }
            //对进程最大需求资源进行赋值
	        printf("please input the maxist need \n");
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
				if(!j)
				{
					printf("the max[%d][%d]=    ",i+1,j+1);
				}
		        scanf("%d",&max[i][j]);
		
		        if(j==(m-1))
		        {
			        printf("\n");
		        }
	        }
	        //转化为进程当前需要资源
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
		        need[i][j]=max[i][j]-all[i][j];
	        }
	        //初始化系统可用资源
	        ava=MKC(m);
	        break;
	        
	        case 4:
	        //输出进程最大需求的资源数
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
				if(!j)
				{
					printf("the max[%d][%d]=%2d",i+1,j+1,max[i][j]);
				}
				else
				{
					printf("%2d",max[i][j]);
				}

		        if(j==(m-1))
		        {
			        printf("\n");
		        }
	        }
			printf("\n");
	        //输出进程当前拥有的资源数
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
				if(!j)
				{
					printf("the all[%d][%d]=%2d",i+1,j+1,all[i][j]);
				}
				else
				{
					printf("%2d",all[i][j]);
				}
				if(j==(m-1))
		        {
			        printf("\n");
		        }
	        }
			printf("\n");
	        //输出当前系统拥有的资源数
	        for(i=0;i<m;i++)
	        {
				if(!i)
				{
	        	printf("the ava[%d]=%2d",i+1,ava[i]);
				}
				else
				{
					printf("%2d",ava[i]);
				}
	        }
	        printf("\n");
	        break;
	       
	
	        default:break;
		}
		
	}
	//释放数组空间
	if(NULL!=all)
	{
		for(i=0;i<n;i++)
	    free(all[i]);
	    free(all);
	    all=NULL;
	}
	//释放数组空间
	if(NULL!=max)
	{
		for(i=0;i<n;i++)
	    free(max[i]);
	    free(max);
	    max=NULL;
	}
	//释放数组空间
	if(NULL!=need)
	{
		for(i=0;i<n;i++)
	    free(need[i]);
	    free(need);
	    need=NULL;
	}
	//释放数组空间
	
	MKF(ava);
	return 1;
}
	    			    	
	    				
		
	


	