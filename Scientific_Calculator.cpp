/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
																				Scientific Calculator
																			Functions: + - * / sin cos log ln ^
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<vector>
#include<ctype.h>
using namespace std;
#define Max 100

typedef struct 
{
	double *base;
	double *top;
}OPND;         //store operand

typedef struct 
{
	char *base;
	char *top;	
}OPTR;		   //store operator

//Initiate OPND
int InitStack(OPND *s)											
{
	s->base=(double *)malloc(Max*sizeof(double));
	if (!s->base)
		return -1;
	else
		s->top=s->base;
	return 1;
}

//Initiate OPTR
int initStack(OPTR *s)
{
	s->base=(char *)malloc(Max*sizeof(char));
	if (!s->base)
		return -1;
	else
		s->top=s->base;
		*(s->base)='#';
	return 1;
}

//Return the top element of the stack OPND
double GetTop_OPND(OPND *s)
{
	double num;
	num=*(s->top);
	return num;
}

//Return the top element of the stack OPTR
char GetTop_OPTR(OPTR *s)
{
	char ch;
	ch=*(s->top);
	return ch;
}

//Push element into OPND stack
void Push_OPND(OPND *s,double num)
{
	*(++s->top)=num;
}

//Push element into OPTR stack
void Push_OPTR(OPTR *s,char ch)
{
	*(++s->top)=ch;
}

//judge the priority of the operators
char precede(char a,char b)
{
	switch(a)
	{
		case '+':
		case '-':
		{
			if (b=='+'||b=='-'||b==')')
				return '>';
			else if (b=='*'||b=='/'||b=='(')
				return '<';
			else
				return '>';
		}break;

		case '*':
		case '/':
		{
			if (b=='(')
				return '<';
			else
				return '>';
		}break;

		case '(':
		{
			if (b==')')
				return '=';
			else
				return '<';
		}break;

		case ')':
		{
			return '>';
		}break;

		case '#':
		{
			if (b=='#')
				return '=';
			else
				return '<';
		}break;

	}
}

//judge whether is operator or not
int is_OPTR(char c)
{
	if (c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='=')
		return 1;
	else 
		return 0;
}

//Pop an element from the top of OPND stack
double Pop_OPND(OPND *s)
{
	double num;
	num=*s->top;
	s->top--;
	return num;
}

//Pop an element from the top of OPTR stack
char Pop_OPTR(OPTR *s)
{
	char ch;
	ch=*s->top;
	s->top--;
	return ch;
}


//operating function
double operate(double x,char optr,double y)
{
	double result;
	switch(optr)
	{
		case '+':result=x+y;break;

		case '-':result=x-y;break;

		case '*':result=x*y;break;

		case '/':result=x/y;break;
	}
	return result;
}

void operate()
{
	OPTR optr;
	OPND opnd;
	double a,b,result,temp,temp1;
	int i = 1,j=0;
	char ch,theta;
	
	vector<char> array;

	InitStack(&opnd);
	initStack(&optr);

	cout<<"Please input the formula:"<<endl;

	ch = cin.get();
	while (ch != '\n')                                             //read the data string
	{
		array.push_back(ch);
		ch = cin.get();
	}


	ch=array[j];
	while (ch!='='||GetTop_OPTR(&optr)!='#')
	{
		if (!is_OPTR(ch))
			{
				if (isdigit(ch))   									//judge number                                
				{
					temp=atof(&ch);
					temp1 = temp;
					ch=array[++j];
						
					if (ch=='.')									//if number has '.'
					{
							ch=array[++j];
							temp=temp+atof(&ch)/pow(10,i);
							i++;
							j++;
							for (ch=array[j];!is_OPTR(ch);j++,i++)
								temp=temp+atof(&ch)/pow(10,i);								
					}
					else if (isdigit(ch))
						temp=temp*10+atof(&ch);	
					else if (ch == '^')								//the function of '^'
					{
						
						ch = array[++j];
						temp = atof(&ch);
						ch = array[++j];
						if (isdigit(ch))
						{
							if (ch == '.')
							{
								ch = array[++j];
								temp = temp + atof(&ch) / pow(10, i);
								i++;
								j++;
								for (ch = array[j]; !is_OPTR(ch); j++, i++)
									temp = temp + atof(&ch) / pow(10, i);
							}
						else if (isdigit(ch))
							temp = temp * 10 + atof(&ch);
						}
						temp = pow(temp1, temp);
					}
					Push_OPND(&opnd,temp);									//after operating,push the result into stack
				}
				else 
				{
					switch(ch)
					{
						case 's':											//the function of 'sin'
						{
							j++;
							if (array[j] == 'i'&&array[++j] == 'n')
							{
								ch = array[++j];
								temp = atof(&ch);
								ch = array[++j];
								if (isdigit(ch))									
								{
									if (ch == '.')
									{
										ch = array[++j];
										temp = temp + atof(&ch) / pow(10, i);
										i++;
										j++;
										for (ch = array[j]; !is_OPTR(ch); j++, i++)
											temp = temp + atof(&ch) / pow(10, i);
									}
									else if (isdigit(ch))
										temp = temp * 10 + atof(&ch);
								}
								temp = sin(temp);
								Push_OPND(&opnd, temp);
							}
							else
								cout << "Input error!";
						}break;

						case 'c':											//the function of 'cos'
						{
							j++;
							if (array[j] == 'o'&&array[++j] == 's')
							{
								ch = array[++j];
								temp = atof(&ch);
								ch = array[++j];
								if (isdigit(ch))
								{
									if (ch == '.')
									{
										ch = array[++j];
										temp = temp + atof(&ch) / pow(10, i);
										i++;
										j++;
										for (ch = array[j]; !is_OPTR(ch); j++, i++)
											temp = temp + atof(&ch) / pow(10, i);
									}
									else if (isdigit(ch))
										temp = temp * 10 + atof(&ch);
								}
								temp = cos(temp);
								Push_OPND(&opnd, temp);
							}
							else
								cout << "Input error!";
						}break;

						case 'l':											//the function of 'log'
						{
							j++;
							if (array[j] == 'o'&&array[++j] == 'g')
							{
								ch = array[++j];
								temp = atof(&ch);
								ch = array[++j];
								if (isdigit(ch))
								{
									if (ch == '.')
									{
										ch = array[++j];
										temp = temp + atof(&ch) / pow(10, i);
										i++;
										j++;
										for (ch = array[j]; !is_OPTR(ch); j++, i++)
											temp = temp + atof(&ch) / pow(10, i);
									}
									else if (isdigit(ch))
										temp = temp * 10 + atof(&ch);
								}
								temp = log10(temp);
								Push_OPND(&opnd, temp);
							}
							else if (array[j] == 'n') 						//the function of 'ln'
							{
								ch = array[++j];
								temp = atof(&ch);
								ch = array[++j];
								if (isdigit(ch))
								{
									if (ch == '.')
									{
										ch = array[++j];
										temp = temp + atof(&ch) / pow(10, i);
										i++;
										j++;
										for (ch = array[j]; !is_OPTR(ch); j++, i++)
											temp = temp + atof(&ch) / pow(10, i);
									}
									else if (isdigit(ch))
										temp = temp * 10 + atof(&ch);
								}
								temp = log(temp);
								Push_OPND(&opnd, temp);
							}
							else
								cout << "Input error!";
						}break;
					}
				}

			}
		else
		{
			switch(precede(GetTop_OPTR(&optr),ch))        								//judge the priority of the operator
			{
				case '<':
				Push_OPTR(&optr,ch);
				ch = array[++j];
				break;

				case '=':
				theta=Pop_OPTR(&optr);
				ch = array[++j];
				break;

				case '>':
				theta=Pop_OPTR(&optr);
				b=Pop_OPND(&opnd);
				a=Pop_OPND(&opnd);
				result=operate(a,theta,b);
				Push_OPND(&opnd,result);
				break;
			}
		}
	}


	cout << "The result is:";
	cout<<GetTop_OPND(&opnd);
}
int main(void)
{
	operate();
}
