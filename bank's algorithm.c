#include"stdio.h"
#include"math.h"
#include"string.h"
int **MKCreatArray(int x, int y)/*��ʼ����ά����*/
{
	int i,j, **p=NULL;
	/*��������䶯̬�ռ�*/
	p=(int**)malloc(sizeof(int)*x);
	for(i=0;i<x;i++)
	p[i]=(int *)malloc(sizeof(int)*y);
	/*��������ĵ�ַ��ʹ��*/
	return p;
	
}
int *MKC(int x)/*��ʼ��һά����*/
{
	int *p=(int *)malloc(sizeof(int)*x),i;/*��������䶯̬�ռ�*/
	if(!p)
	{
		free(p);
		return NULL;
	}
	/*��ʽ������ռ�*/
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
	/*��������ĵ�ַ��ʹ��*/
	return p;
}
void MKF(int *p)/*�ͷ�����ռ�*/
{
	if(p!=NULL)
	{
		free(p);
	}
	p=NULL;
}
	
	
	
	
int jiex(int x)/*����׳�X��ֵ*/
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
int SY(int *ava,int **all,int **need,int n,int m)/*��ȫ�㷨*/
{
	/*�����������ȷֱ�Ϊm��n������work��finish*/
	int *work=(int *)malloc(sizeof(int)*m),*finish=(int *)malloc(sizeof(int)*n),i,j,x,y=0,count=0,count1=0;
	/*�����ж�*/
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
	/*��ʼ��workΪava��ʽ*/
	for(i=0;i<m;i++)
	{
		work[i]=ava[i];
	}
	/*��ʼ��finish ȫ�����ݳ�ʼΪ0*/
	for(j=0;j<n;j++)
	{
		finish[j]=0;
	}
	/*�Խ��̽����жϣ���Ϊϵͳ��ȫ��ÿ�α�Ȼ����һ�����̣��������д��������Ϊn�Ľ׳�*/
	while(y<x)
	{
		for(i=0;i<n;i++)
		{
			/*�Խ��̰���Ž����жϣ�countΪ�Խ�����Ҫ��������Դ����һ������*/
			count=0;
			for(j=0;j<m;j++)
		    {
		    	//Ѱ��i��ʹ��finish[i]=FALSE������NEED[i]<=work[i],������ڼ���ִ�У������ж��Ƿ����е�finishԪ�ض�Ϊ1����ϵͳ���ڰ�ȫ״̬��
			    if((!finish[i])&&(need[i][j]<=work[j]))
			    {
			    	//�������i�е���Դ���㣬���������1��
				    count++;
				    //�������i�е����н��̾�����
			        if(count==m)
				    {
				    	//�˽��̽��ܻ����Դ��
					    int z=0;
					    for(z=0;z<m;z++)
				        {
				    	    work[z]=work[z]+all[i][z];
				        }
				        //������̺�
				        printf("p[%d]  ",i);
				        finish[i]=1;
				        //���ܱ�����Ľ����������жϡ�
				        count1++;
				    }
				
			    }
		    }
		    //ѭ���Ĵ������м�����ʹ���ܹ��Ƴ�ѭ��
		    y++;
		}
	}
	//ѭ����ɺ󣬶Է���Ľ����������жϣ�����������������ܽ���������ȫ�����򲻰�ȫ��
	if(count1<n)
	{
		//�ͷ�����ռ�
		free(work);
		free(finish);
		return 0;
	}
	else
	{
		//�ͷ�����ռ�
		free(work);
		free(finish);
		return 1;
	}
}
//��ԴҪ���㷨
void RRA(int **request,int **all,int *ava,int **need,int n,int m,int n1)
{
	//i��ѭ�������жϡ�count���м�����bΪ������̵Ľ��̺š�
	int i=0, b,j,count=0,n2=0;
	n2=jiex(n1);
	/*�Խ��̽����жϣ���Ϊϵͳ��ȫ��ÿ�α�Ȼ����һ�����̣��������д��������Ϊn�Ľ׳�*/
	while(i<n2)
	{
		b=request[i][0]-1;
		count=0;
		for(j=0;j<m;j++)
	    {
	    	//���������Դ��С���������������ִ�У�����ȴ���
	    	if(request[i][j+1]<=need[b][j])
	    	{
	    	//���������Դ��С��ϵͳ���ṩ���������ִ�С�
	            if(request[i][j+1]<=ava[j])
	    		{
	    			//��i���̵������������Դ���̽��м���
	    		    count++;
	    		    //���Է������Դ
	    			ava[j]=ava[j]-request[i][j+1];
	    			all[b][j]=all[b][j]+request[i][j+1];
	    			need[b][j]=need[b][j]-request[i][j+1];
	    			//���i���̵�������Դ������
	    			if(count==m)
	    			{
	    			    //�����ȫ���򰴴˷��䣬�����ذ�ȫֵ
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
	    			    //����ȫ����ȡ�����䡣��������
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
	//��ʼ��������Ҫ�����ݡ�
	int i,j,n1,count=-1,*ava=NULL,**all=NULL,**need=NULL,**request=NULL,**max=NULL;
	static int n,m;
	//������Ҫ�Ľ�����
	printf("please input the nums of process \n");
	scanf("%d",&n);
	//������Ҫ����Դ��
	printf("please input the nums of resource \n");
	scanf("%d",&m);
	//��ʼ����ά����
	all=MKCreatArray(n,m);
	//��ʼ����ά����
	need=MKCreatArray(n,m);
	//��ʼ����ά����
	max=MKCreatArray(n,m);
	//�Խ���ӵ����Դ���и�ֵ
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

	//�Խ������������Դ���и�ֵ
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
	//ת��Ϊ���̵�ǰ��Ҫ��Դ
	for(i=0;i<n;i++)
	for(j=0;j<m;j++)
	{
		need[i][j]=max[i][j]-all[i][j];
	}
	//��ʼ��ϵͳ������Դ
	ava=MKC(m);
	while(1)
	{
		//�û�����
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
		//count��ֵ����ʾ���û���Ҫ�ķ���
		switch(count)
		{
			case 1:
			//�жϵ�ǰϵͳ�Ƿ�ȫ
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
	        //�жϰ���Ŀǰ�ķ��䷽ʽ��ϵͳ�Ƿ�ȫ
	        printf("please input the nums of request \n");
	        scanf("%d",&n1);
	        //��ʼ�������ά���顣��������ÿ�����̵ĵ�1��������ʾ��Ϊ���̺�
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
	        //�����жϡ�
	        RRA(request,all,ava,need,n,m,n1);
	        //�ͷ�����ռ䡣
			if(NULL!=request)
			{
				for(i=0;i<n1;i++)
	            free(request[i]);
	            free(request);
				request=NULL;
			}
	        break;
	        case 3:
	        //�ͷ�����ռ�
	        if(NULL!=all)
	        {
		        for(i=0;i<n;i++)
	            free(all[i]);
	            free(all);
	            all=NULL;
	        }
	        //�ͷ�����ռ�
	        if(NULL!=max)
	        {
		        for(i=0;i<n;i++)
	            free(max[i]);
	            free(max);
	            max=NULL;
	        }
	        //�ͷ�����ռ�
	        if(NULL!=need)
	        {
		        for(i=0;i<n;i++)
	            free(need[i]);
	            free(need);
	            need=NULL;
	        }
	        //�ͷ�����ռ�
	        MKF(ava);
	        //������Ҫ�Ľ�����
	        printf("please input the nums of process \n");
	        scanf("%d",&n);
	        //������Ҫ����Դ��
	        printf("please input the nums of resource \n");
	        scanf("%d",&m);
	        //��ʼ����ά����
	        all=MKCreatArray(n,m);
	        //��ʼ����ά����
	        need=MKCreatArray(n,m);
	        //��ʼ����ά����
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
            //�Խ������������Դ���и�ֵ
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
	        //ת��Ϊ���̵�ǰ��Ҫ��Դ
	        for(i=0;i<n;i++)
	        for(j=0;j<m;j++)
	        {
		        need[i][j]=max[i][j]-all[i][j];
	        }
	        //��ʼ��ϵͳ������Դ
	        ava=MKC(m);
	        break;
	        
	        case 4:
	        //�����������������Դ��
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
	        //������̵�ǰӵ�е���Դ��
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
	        //�����ǰϵͳӵ�е���Դ��
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
	//�ͷ�����ռ�
	if(NULL!=all)
	{
		for(i=0;i<n;i++)
	    free(all[i]);
	    free(all);
	    all=NULL;
	}
	//�ͷ�����ռ�
	if(NULL!=max)
	{
		for(i=0;i<n;i++)
	    free(max[i]);
	    free(max);
	    max=NULL;
	}
	//�ͷ�����ռ�
	if(NULL!=need)
	{
		for(i=0;i<n;i++)
	    free(need[i]);
	    free(need);
	    need=NULL;
	}
	//�ͷ�����ռ�
	
	MKF(ava);
	return 1;
}
	    			    	
	    				
		
	


	