#include <stdio.h>
#include <stdarg.h>

static void myPrintChar(char s)
{
    putchar(s);
}
static void myPrintNum(int num)
{
    char buf[10];
    int out = num;
    int i = 0;
    do
    {
        buf[i] = out % 10 + '0';
        out /= 10;
        i++;
    }while (out != 0);

    while (i>0)
    {
        myPrintChar(buf[--i]);
    }
}
static void myPrintDouble(double num)
{
    int intNum = 0;
    float floatNum = 0;
    intNum = (int)num;
    floatNum = num - intNum;
    floatNum *= 100;
    myPrintNum(intNum);    
    myPrintChar('.');
    if(floatNum<10)
    {
        myPrintChar('0');
    }
    myPrintNum((int)floatNum);
}

void myPrint(char *format,...)
{
    va_list va;
    va_start(va,format);
    int num;
    char *c;
    char ch;
    double x;
    while (*format != '\0')
    {
        if(*format == '%')
        {
            format++;
            switch(*format)
            {
                case 'd':
                    num = va_arg(va,int);
                    myPrintNum(num);
                    break;
                case 's':
                    c = va_arg(va,char *);
                    while (*c != '\0')
                    {
                        myPrintChar(*c++);
                    }
                    break;
                case 'c':
                    ch = va_arg(va, int);
                    myPrintChar(ch);
                    break;
                case 'f':
                    x = va_arg(va,double);
                    myPrintDouble(x);
                    break;
                default :
                    
                break;

            }
        }
        else
            myPrintChar(*format);
        format++;

    }
    va_end(va);
    myPrintChar('\n');
}

int main(void)
{
    myPrint("%f %c %s",123.038,'s',"abc");
    return 0;
}