#include<stdio.h>
#include<stdlib.h>

struct Node;
typedef struct Node *PNode;
struct Node
{
    int exp;//指数
    int coef;//系数
    PNode link;
};

typedef struct Node *LinkList;
typedef LinkList *PLinkList;

PNode Add (int *pa, int *pb)
{
    PNode p,q,pAdd;
    int aexp, bexp, nexp,i,j;
    p = (PNode)malloc(sizeof(struct Node));
    pAdd = p;
    aexp = *(pa + 1);//取数组的第二个值，为多项式首项的次数
    bexp = *(pb + 1);
    nexp = (aexp>bexp)?aexp:bexp;//deg (f(x) + g(x)) <= max {degf(x), deg g(x)}
    for (i=nexp;i>=0;i--)//初始化链表
    {
        q = (PNode)malloc(sizeof(struct Node)); 
        p->link = q;
        p = q;
        p->exp = i;
        p->coef = 0;
    }
    p = pAdd;
    for (i=0;i<=nexp;i++)//把指数符合的项对应的系数加到链表里面
    {
        p = p->link;
        for (j=1;;j+=2)
        {
            if (*(pa+j)==0 && *(pa+j-1) ==0)
            {
                break;//读取到数组的末尾了
            }
            if (*(pa + j) == p->exp)
            {
                p ->coef += *(pa+j-1);
                break;//匹配到了之后，后面的一定都不满足，因为是降幂排列
            }
        }
        for (j=1;;j+=2)
        {
            if (*(pb+j)==0 && *(pb+j-1) ==0)
            {
                break;
            }
            if (*(pb + j) == p->exp)
            {
                p ->coef += *(pb+j-1);
                break;
            }
        }
    }
    return pAdd;//和用链表表示，返回该链表的指针
}

PNode Multiply (int *pa, int *pb)
{
    PNode p,q,pMutiply;
    int aexp, bexp, nexp, i,j,k;
    p = (PNode)malloc(sizeof(struct Node));
    pMutiply = p;
    aexp = *(pa+1);
    bexp = *(pb+1);
    nexp = aexp+bexp;//deg(f(x)*g(x)) = deg f(x) + deg(x)
    for (i=nexp;i>=0;i--)//初始化
    {
        q = (PNode)malloc(sizeof(struct Node));
        p->link = q;
        p = q;
        p->exp = i;
        p->coef = 0;
    }
    p = pMutiply;
    for (i=0;i<=nexp;i++)
    {
        p = p->link;
        for (j=1;;j+=2)
        {
            if (*(pa + j)==0 && *(pa + j - 1)==0)//遍历两个数组，查找满足的所有组合
            {
                break;
            }
            for (k=1;;k+=2)
            {
                if (*(pb + k) ==0 && *(pb + k -1)==0)
                {
                    break;
                }
                if (*(pa + j) + *(pb + k) == p->exp)
                {
                    p->coef += pa[j-1]*pb[k-1];
                    break;
                }
            }
        }
    }
    return pMutiply;
}

void Write (PLinkList plist)//格式化输出多项式
{
    PNode p;
    p = *plist;
    p = p->link;
    while (p->coef == 0)//先找到系数不为零的第一个元素
    {
        p = p->link;
    }
    if (p->exp == 0)//如果是最后一个
    {
        if (p->coef == 0)//是最后一个而且系数为零
        {
            printf ("0\n");
        }
        else//是最后一个系数不为零
        {
            printf ("%d\n", p->coef);
        }
    }
    else 
    {
        //printf ("%dx^%d", p->coef, p->exp);
        if (p->coef == 1)//系数为1 
        {
            if (p->exp == 1)//系数为一而且指数为一
            {
                printf ("x");
            }
            else
            {
                printf ("x^%d", p->exp);  //系数为一但指数不为一
            }
            //printf ("x^%d", p->exp);
        }
        else if (p->coef == -1)//系数为-1
        {
            if (p->exp == 1)//系数为-1而且指数为1
            {
                printf ("-x");
            }
            else
            {
                printf ("-x^%d", p->exp);//系数为-1而且指数不为一
            }
            //printf ("-x^%d", p->exp);
        }
        else//系数既不是1，也不是-1
        {
            if (p->exp == 1)//系数既不是1也不是-1而且指数为1
            {
                printf ("%dx", p->coef);
            }
            else //系数既不是1也不是-1而且指数不为1
            {
                printf ("%dx^%d", p->coef, p->exp);
            }
            //printf ("%dx^%d", p->coef, p->exp);
        }
        p = p->link;//移到下一位
        if (p->exp == 0)//如果下一位是最后一位
        {
            if (p->coef > 0)//系数dayu0
            {
                printf ("+%d\n", p->coef);
            }
            if (p->coef < 0)//系数小于0
            {
                printf ("%d\n", p->coef);
            }
        }
        else//如果不是最后一位
        {
            while (p->exp != 0)//当移到最后一位前
            {
                while(p->coef == 0)//找到下一个系数不是零的
                {
                    p = p->link;
                }
                if (p->exp != 0)//如果这个不是最后一个
                {
                    if (p->coef > 0)//系数不是零，不是最后一个，且系数大于0
                    {
                        if (p->coef == 1)//系数不是0.不是最后一个，系数大于0，而且系数为1
                        {
                            if (p->exp == 1)//系数不是0.不是最后一个，系数大于0，而且系数为1，而且指数为一
                            {
                                printf ("+x");
                            }
                            else //系数不是0.不是最后一个，系数大于0，而且系数为1，且指数不为一
                            {
                               printf ("+x^%d", p->exp);
                            }
                            //printf ("+x^%d", p->exp);
                        }
                        else//系数不是零，不是最后一个，系数大于0 而且不是1
                        {
                            if (p->exp == 1)//系数不是零，不是最后一个，系数大于0 而且不是1，而且指数是1
                            {
                                printf ("+%dx", p->coef);
                            }
                            else//系数不是零，不是最后一个，系数大于0 而且不是1，指数不是1
                            {
                                printf ("+%dx^%d", p->coef, p->exp);
                            }
                            //printf ("+%dx^%d", p->coef, p->exp);
                        }
                        //printf ("+%dx^%d", p->coef, p->exp);
                    }
                    if (p->coef < 0)//
                    {
                        if (p->coef == -1)
                        {
                            if (p->exp == 1)
                            {
                                printf ("-x");
                            }
                            else
                            {
                                printf ("-x^%d", p->exp);
                            }
                            //printf ("-x^%d", p->exp);
                        }
                        else 
                        {
                            if (p->exp == 1)
                            {
                                printf ("%dx", p->coef);
                            }
                            else
                            {
                                printf ("%dx^%d", p->coef, p->exp);
                            }
                            //printf ("%dx^%d", p->coef, p->exp);
                        }
                        //printf ("%dx^%d", p->coef, p->exp);
                    }
                }
                else 
                {
                    break;
                }
                p = p->link;
                if (p->exp == 0)
                {
                    break;
                }
            }
            if (p->coef > 0)
            {
                printf ("+%d\n", p->coef);
            }
            if (p->coef < 0)
            {
                printf ("%d\n", p->coef);
            }
        }
    }
    

}

int main ()
{
    LinkList ADD,MULTIPLY;
    int a[201],b[201];
    int a1,a2,b1,b2,i=0,j=0;
    scanf ("%d%d", &a1, &a2);
    while (a1 != 0 || a2!= 0)
    {
        a[i] = a1;
        a[i+1] = a2;
        i+=2;
        scanf ("%d%d", &a1, &a2);
    }
    a[i] = 0;
    a[i+1] = 0;

    scanf ("%d%d", &b1, &b2);
    while (b1 != 0 || b2!= 0)
    {
        b[j] = b1;
        b[j+1] = b2;
        j+=2;
        scanf ("%d%d", &b1, &b2);
    }
    b[j] = 0;
    b[j+1] = 0;

    ADD = Add(a,b);
    Write (&ADD);
    MULTIPLY = Multiply (a,b);
    Write (&MULTIPLY);
    /*MULTIPLY = Multiply (a, b);
    int n;
    MULTIPLY = MULTIPLY ->link;
    n = MULTIPLY->exp;
    for (i=n;i>=0;i--)
    {
        printf ("%d %d ", MULTIPLY->coef, MULTIPLY->exp);
        MULTIPLY = MULTIPLY->link;
    }*/

    return 0;
}
