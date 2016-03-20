#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct s{

	int left;
	int right;
	char myString[200];

};


char myStack[1000000];
int evalStack[1000000];
int top=-1;
int evalTop=-1;

struct s Table[20][10000];
char operators[100000][10];
int myInd=0;
//int count=0;

void permHelper(char* set, int len, char* output, int k, int idx);
void perm(char* set, int len, int k);
void makeOpsReady(int size);
void evalPush(int p);
void push(char p);
int evalPop();
char pop();
int evaluate(char *expr, int result);
int convertToPostfix(char *expr, int result);
char* insOp(int size, char *expr, int result);

void permHelper(char* set, int len, char* output, int k, int idx)
{

  if (k == idx)
 {
   strcpy(operators[myInd++],output);
 }
  else
 {
 	int i;
   for (i = 0; i < len; i++)
 {
  output[idx] = set[i];
  permHelper(set, len, output, k, idx+1);
 }
 }

}


void perm(char* set, int len, int k) {
char *output = (char*) malloc (sizeof(char) * (k+1));
permHelper(set, len, output, k, 0);
}


void makeOpsReady(int size)
{

char ch[] = {'+', '-', '*','/'};
int len = sizeof(ch)/ sizeof(char);

int i,number=1;


for(i=0;i<size;i++)
number*=4;

for(i=0;i<number;i++)
	operators[i][0]='\0';

perm(ch, len, size);

}


void evalPush(int p)
{

	evalTop++;
	evalStack[evalTop]=p;
}


void push(char p)
{
	top++;
	myStack[top]=p;
}


int evalPop()
{
    int q;
   	if(evalTop!=-1)
	{
   	q=evalStack[evalTop];
	evalTop--;
	}
	return q;
}


char pop()
{
    char q;
   	if(top!=-1)
	{
   	q=myStack[top];
	top--;
	}
	return q;
}



int evaluate(char *expr, int result)
{

	int myInt;
	int mod,pole,signFlag=0,sum;
	char myChar[18];

		evalTop=-1;
		int v,first,second,compute;

		int i,j;
		int checking=0;
		for(i=0;i<strlen(expr);i++)
		{
			if(expr[i]=='+' || expr[i]=='-' || expr[i]=='*' || expr[i]=='/')
			{
				first=evalPop();
				second=evalPop();


				switch(expr[i])
				{
						case '+' :  compute=second+first;
									evalPush(compute);
									break;
						case '-' :  compute=second-first;
									evalPush(compute);
									break;
						case '*' :  compute=first*second;
									evalPush(compute);
									break;
						case '/' :  if(first==0 || second%first!=0)
									{
										checking=55;
										break;
									}
									compute=second/first;
									evalPush(compute);
				}

			}


			else
			{

				signFlag=0;
				pole=0;

					while(expr[i]!='#')
					{
							if(expr[i]=='&')
								signFlag=1;
							else
								myChar[pole++]=expr[i];
							i++;
					}

				myChar[pole]='\0';
				sum=0;

				for(j=0;j<strlen(myChar);j++)
				{
							mod=myChar[j]-'0';
							sum=(10*sum)+mod;
				}

				if(signFlag==1)
					sum*=-1;

					evalPush(sum);


			}

			if(checking==55)
				break;
		}

if(checking!=55)
{
	if(evalPop()==result)
		return 555;
	else
		return 0;
}
else
	return 0;



}


int convertToPostfix(char *expr, int result)
{

	char *newexpr=(char *)malloc(sizeof(char)*10000);
	char e;
	int answer,i,flag=0;
	top=-1;

	for(i=0;i<strlen(expr);i++)
	{
		if(expr[i]=='(')
			push('(');
		else if( expr[i]=='+' || expr[i]=='-' || expr[i]=='*' || expr[i]=='/')
			push(expr[i]);
		else if(expr[i]==')')
		{
			while(myStack[top]!='(')
			newexpr[flag++]=pop();
			e=pop();
		}
		else if(expr[i]=='&')
		{
			newexpr[flag++]='&';
			i++;

			while(expr[i]>='0' && expr[i]<='9')
			{

				newexpr[flag++]=expr[i];
				i++;
			}
			newexpr[flag++]='#';

			i--;
		}
		else
		{
		while(expr[i]>='0' && expr[i]<='9')	{
				newexpr[flag++]=expr[i];
				i++;
				}
						newexpr[flag++]='#';
				i--;
		}

	}
	newexpr[flag]='\0';
	answer=evaluate(newexpr, result);

	return answer;
}


char* insOp(int size, char *expr, int result)
{
char *incorrect=(char *)malloc(sizeof(char)*2);

strcpy(incorrect, "XX");
int answer,i,j,p,k;
int number=1;
int q;

for(i=0;i<size;i++)
number*=4;

char *fin=(char *)malloc(sizeof(char)*10000);
char *temp=(char *)malloc(sizeof(char)*10000);

for(i=0;i<number;i++)
{
	temp[0]='\0';


	    for(k=0;k<strlen(expr);k++)
	        temp[k]=expr[k];
	        temp[k]='\0';

	p=0;

	for(j=0;j<strlen(temp);j++)
	{
		if(temp[j]==' ')
		{
			temp[j]=operators[i][p++];
		}
	}

temp[strlen(expr)]='\0';

answer=convertToPostfix(temp, result);

if(answer==555)
{
	q=0;
	for(k=0;k<strlen(temp);k++)
	{
		if(temp[k]=='+' || temp[k]=='-' || temp[k]=='*' || temp[k]=='/')
		{
			fin[q++]=' ';
			fin[q++]=temp[k];
			fin[q++]=' ';
		}
		else if(temp[k]=='&')
			fin[q++]='-';
		else
			fin[q++]=temp[k];
	}
	fin[q]='\0';

	break;
}

}

if(answer==555)
	return fin;
else
	return incorrect;

}

char *OpJumble(int nElems, int *inArray)
{
	myInd=0;

	char *final;

	int f;
	int index;
int myInt;
int mod,pole;
char myChar[50];

	final=(char *)malloc(sizeof(char)*10000);
	int result=inArray[nElems-1];
	char w;
	int mySize=nElems-1;
	int i,j,b,p,q,r,k,answer;
int veryimpindex;

if(nElems>2)
{
	for(i=0;i<20;i++)
	{
		for(j=0;j<10000;j++)
		{
			Table[i][j].left=-1;
			Table[i][j].right=-1;
			Table[i][j].myString[0]='\0';
		}
	}

	for(i=0;i<mySize;i++)
	{
		Table[1][i].left=i;
		Table[1][i].right=i;
		index=0;

		myInt=inArray[i];
pole=0;

if(myInt!=0)
{
 if(myInt<0)
{
    Table[1][i].myString[index++]='&';
    myInt*=-1;
}

pole=0;

while(myInt>0)
{
mod=myInt%10;
myInt/=10;
myChar[pole++]=mod+'0';
}

}
else
{
myChar[pole++]='0';
}

myChar[pole]='\0';

for(k=strlen(myChar)-1;k>=0;k--)
{
Table[1][i].myString[index++]=myChar[k];
}


Table[1][i].myString[index++]='\0';

	}


	for(i=2;i<=mySize;i++)
	{
		q=1;
		p=-1;
		while(q!=i)
		{
			r=i-q;
			for(j=0;Table[q][j].left!=-1;j++)
			{
				for(k=0;Table[r][k].left!=-1;k++)
				{
					if( ( Table[r][k].right-Table[q][j].left==(i-1) ) &&  Table[r][k].left-Table[q][j].right==1 )
					{
				p++;
						veryimpindex=0;

						Table[i][p].myString[veryimpindex++]='(';

						Table[i][p].left=Table[q][j].left;


						for(b=0;Table[q][j].myString[b]!='\0';b++)
							Table[i][p].myString[veryimpindex++]=Table[q][j].myString[b];

						Table[i][p].myString[veryimpindex++]=' ';


						Table[i][p].right=Table[r][k].right;

						for(b=0;Table[r][k].myString[b]!='\0';b++)
							Table[i][p].myString[veryimpindex++]=Table[r][k].myString[b];


						Table[i][p].myString[veryimpindex++]=')';


	                    //strcat(Table[i][p].myString,")");

						Table[i][p].myString[veryimpindex]='\0';

					}
				}
			}
			q++;
		}
	}

makeOpsReady(mySize-1);

for(j=0;Table[mySize][j].left!=-1;j++)
{
		final=insOp(mySize-1,Table[mySize][j].myString, result);
		if(final!="XX")
		{
		break;
		}
}
for(i=0;i<100000;i++)
	operators[i][0]='\0';

}
else
{


pole=0;
if(result!=0)
{
index=0;

if(result<0)
	{
		final[index++]='-';
		result*=-1;
	}

while(result>0)
{
mod=result%10;
result=result/10;
myChar[pole++]=mod+'0';
}

myChar[pole]='\0';


for(k=strlen(myChar)-1;k>=0;k--)
{
final[index++]=myChar[k];
}
final[index]='\0';
}
else
{
final[0]='0';
final[1]='\0';
}



}
return final;
}


int main()
{
printf(" This program generates Expressions given (n-1) LHS elements and the last element being the R.H.S \n\n");
char *abc;
abc=(char *)malloc(sizeof(char)*200);
int n,i;
int a[100];
int t;
printf("Enter the number of test cases \n");

scanf("%d", &t);

while(t--)
{

printf("Enter no of elements you want to enter : ");
scanf("%d", &n);
for(i=0;i<n;i++)
scanf("%d", &a[i]);

abc=OpJumble(n,a);
if(abc!="XX")
{
printf("%s", abc);
printf(" = %d\n", a[n-1]);
}
else
	printf("Not Possible!!");
}



return 0;

}