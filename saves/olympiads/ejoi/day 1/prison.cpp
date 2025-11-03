#include "prison.h"

int setup(int M)
{
    if(M % 2 == 0)
        return (M-3)*2-1;
    else
        return (M-4)*-1;
}

std::vector<int> encode(int A)
{
    int temp = A/2;
    if(A%2 == 0)
    {
        return {temp, temp+1, temp+3};
    }
    else
    {
        return {temp, temp, temp+4};
    }
}

int decode(int X, int Y)
{
    int temp;
    if(X>Y)
    {
        temp = X;
        X = Y;
        Y = temp;
    }
    if(Y-X == 1)
        return X*2;
    if(Y-X == 2)
        return (X-1)*2;
    if(Y-X == 3)
        return X*2;
    if(Y == X)
        return X*2+1;
    if(Y-X == 4)
        return X*2+1;
    return -123;
}

