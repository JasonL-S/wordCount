#include<iostream>           
#include<stdlib.h>
#include<string.h>
#include<queue>
#pragma warning(disable : 4996)
using namespace std;
struct word
{
	char str1[100];
	int num;
}A[1000];
int n=10;
int X;
int re;
char str1[1000][100];
FILE* fp = NULL;
FILE* fq = NULL;
int totalNum[3];
int t=0;
void countphrase(char *str);
int *getCharNum(int *totalNum){
    char buffer[1003];  //缓冲区，存储读取到的每行的内容
    int bufferLen;  // 缓冲区中实际存储的内容的长度
    int i;  // 当前读到缓冲区的第i个字符
    char c;  // 读取到的字符
    int isLastBlank = 0;  // 上个字符是否是空格
    int charNum = 0;  // 当前行的字符数
    int wordNum = 0; // 当前行的单词数

    printf("\n");
    // 每次读取一行数据，保存到buffer，每行最多只能有1000个字符
    while(fgets(buffer, 1003, fp) != NULL){
        bufferLen = strlen(buffer);
        // 遍历缓冲区的内容
        countphrase(buffer);
        for(i=0; i<bufferLen; i++){
            c = buffer[i];
            if( c==' ' || c=='\t'){  // 遇到空格
                !isLastBlank && wordNum++;  // 如果上个字符不是空格，那么单词数加1
                isLastBlank = 1;
            }else if(c!='\n'&&c!='\r'){  // 忽略换行符
                charNum++;  // 如果既不是换行符也不是空格，字符数加1
                isLastBlank = 0;
            }
        }

        !isLastBlank && wordNum++;  // 如果最后一个字符不是空格，那么单词数加1
        isLastBlank = 1;  // 每次换行重置为1

        // 一行结束，计算总字符数、总单词数、总行数
        totalNum[0]++;  // 总行数
        totalNum[1] += charNum;  // 总字符数
        totalNum[2] += wordNum;  // 总单词数

       // printf("%-7d%-7d%d\n", totalNum[0], wordNum, charNum);

        // 置零，重新统计下一行
        charNum = 0;
        wordNum = 0;
    }
    return totalNum;
}

void print(int n,int t)
{
	if(n<t)
		t=n;
	for(int i=0;i<t;i++)
		//cout<<"<"<<A[i].str1<<">"<<A[i].num<<endl; 
		fprintf(fq,"<%s>: %d\n",A[i].str1,A[i].num);
}
void sort1(int t)
{
	struct word a;
	for(int i=0;i<t;i++)
	{
		for(int j=i+1;j<t;j++)
		{
			if(A[i].num<A[j].num)
			{
				a=A[i];A[i]=A[j];A[j]=a;
			}
		}
	}
}
void findsame(int n)
{ 
	int s[n];
		for(int i=0;i<n;i++)
			s[i]=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]==0)
		{
			for(int j=0;;j++)
			{
				A[t].str1[j]=str1[i][j];
				if(!str1[i][j])
				break;
			}
			A[t].num++;
			s[i]=1;
			for(int m=0;m<n;m++)
			if(s[m]==0&&strcmp(A[t].str1,str1[m])==0)
			{
				A[t].num++;
				s[m]=1;
			}
			t++;
		}
	}
	sort1(t);
}


void countphrase(char *str)
{
	int k=0,t=0;
	int count=0;
	int N=strlen(str); 
	for(int i=0;i<N+1;i++)
	{
		if(str[i]<='Z'&&str[i]>='A')
		str[i]=str[i]+32;
	}
	for(int i=0;i<N+1;i++)
	{
		if((str[i]<='z'&&str[i]>='a')&&count<=4)
		count++;
		if(count>4&&str[i]!=' '&&str[i]!='\0')
		count++;
		if(count>=4&&(str[i]==' '||str[i]=='\0'))
		{
			int m;
			if(count==4)
			m=i-count;
			else
			m=i-count+1;
			for(int j=m;j<i;j++)
			{
				str1[k][t]=str[j];
				t++;
			}
			k++;
			t=0;
			count=0;
		}
		if((str[i]==' '||str[i]=='\0')&&count<4)
		count=0;
	}
	findsame(k);
}

int main(int argc, char* argv[])
{
	string inputname;                //命令行输入处理 
	string outputname;
	string a,b,c,d;
	a="-m";
	b="-n";
	c="-i";
	d="-o";
	for(int i=1;i<argc;i++)
	{
		if(argv[i]==c)
		{
			fp = fopen(argv[++i], "r");     //以文本方式打开文件。
			if (fp == NULL)               //打开文件出错
			{
				cout<<"Input not found.\n"<<endl; 
				return 0;
			} 
			continue;
		}
		if(argv[i]==d)
		{
			fq = fopen(argv[++i], "w");     //以文本方式打开文件。
			if (fq == NULL)               //打开文件出错
			{
				cout<<"Output not found.\n"<<endl; 
				return 0;
			} 
			continue;
		}
		if(argv[i]==a)
		{
			X=argv[++i][0]-'0';
			continue;
		}
		if(argv[i]==b)
		{
			re=argv[++i][0]-'0';
			continue;
		}
	}
	 int totalNum[3] = {0, 0, 0};

   	if(fq==NULL)
	{
		cout<<"Output not found.\n"<<endl;
		return 0;
	}
	
    if(getCharNum(totalNum)){
    	fprintf(fq,"characters: %d\n",totalNum[1]);
    	fprintf(fq,"words: %d\n",totalNum[2]);
    	fprintf(fq,"lines: %d\n",totalNum[0]);
        }
		else{
        fprintf(fq,"Error!\n");
    }
    print(n,t);
	if (fp != NULL)   fclose(fp);
	if (fq != NULL)  fclose(fq);
	return 0;
}

