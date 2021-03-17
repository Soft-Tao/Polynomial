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
    aexp = *(pa + 1);
    bexp = *(pb + 1);
    nexp = (aexp>bexp)?aexp:bexp;
    for (i=nexp;i>=0;i--)
    {
        q = (PNode)malloc(sizeof(struct Node));
        p->link = q;
        p = q;
        p->exp = i;
        p->coef = 0;
    }
    p = pAdd;
    for (i=0;i<=nexp;i++)
    {
        p = p->link;
        for (j=1;;j+=2)
        {
            if (*(pa+j)==0 && *(pa+j-1) ==0)
            {
                break;
            }
            if (*(pa + j) == p->exp)
            {
                p ->coef += *(pa+j-1);
                break;
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
    return pAdd;
}

PNode Multiply (int *pa, int *pb)
{
    PNode p,q,pMutiply;
    int aexp, bexp, nexp, i,j,k;
    p = (PNode)malloc(sizeof(struct Node));
    pMutiply = p;
    aexp = *(pa+1);
    bexp = *(pb+1);
    nexp = aexp+bexp;
    for (i=nexp;i>=0;i--)
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
            if (*(pa + j)==0 && *(pa + j - 1)==0)
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

void Write (PLinkList plist)
{
    PNode p;
    p = *plist;
    p = p->link;
    while (p->coef == 0)
    {
        p = p->link;
    }
    if (p->exp == 0)
    {
        if (p->coef == 0)
        {
            printf ("0\n");
        }
        else
        {
            printf ("%d\n", p->coef);
        }
    }
    else 
    {
        //printf ("%dx^%d", p->coef, p->exp);
        if (p->coef == 1)
        {
            if (p->exp == 1)
            {
                printf ("x");
            }
            else
            {
                printf ("x^%d", p->exp);  
            }
            //printf ("x^%d", p->exp);
        }
        else if (p->coef == -1)
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
        p = p->link;
        if (p->exp == 0)
        {
            if (p->coef > 0)
            {
                printf ("+%d\n", p->coef);
            }
            if (p->coef < 0)
            {
                printf ("%d\n", p->coef);
            }
        }
        else
        {
            while (p->exp != 0)
            {
                while(p->coef == 0)
                {
                    p = p->link;
                }
                if (p->exp != 0)
                {
                    if (p->coef > 0)
                    {
                        if (p->coef == 1)
                        {
                            if (p->exp == 1)
                            {
                                printf ("+x");
                            }
                            else 
                            {
                               printf ("+x^%d", p->exp);
                            }
                            //printf ("+x^%d", p->exp);
                        }
                        else
                        {
                            if (p->exp == 1)
                            {
                                printf ("+%dx", p->coef);
                            }
                            else
                            {
                                printf ("+%dx^%d", p->coef, p->exp);
                            }
                            //printf ("+%dx^%d", p->coef, p->exp);
                        }
                        //printf ("+%dx^%d", p->coef, p->exp);
                    }
                    if (p->coef < 0)
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