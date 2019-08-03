
#include<stdio.h>
#include<time.h>


int maxSubArray(int, int);
int maxSubArrayDivideConquer(int, int, int);

int main()
{
    clock_t start = clock();
    
    
    int i,n;
    int A = [31, -41, 59, 26, -53, 58, 97, -93, -23, 84];
    printf("The array contains :\n");
    for(i = 0; i <= n; i++)
        printf(" %d ", A(i));
    
    printf("\nThe maximum sum in the array is :\n");
    for(i=0;i<=n;i++)
        printf(" %d ", maxSubArray(i));
    
    
    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f", elapsed);
}


int maxSubArray(int A[], int n) {
    // base case
    if(n == 0)
        return 0;
    return maxSubArrayDivideConquer(A, 0, n-1);
}



int maxSubArrayDivideConquer(int A[], int left, int right) {
    
    if(right == left)
        return A[left];
    
    int arrayMid = (left + right)/2;
    int arrayLeft = maxSubArrayDivideConquer(A, left, arrayMid);
    int arrayRight = maxSubArrayDivideConquer(A, arrayMid + 1, right);
    int maxLeft = A[arrayMid];
    int maxRight = A[arrayMid + 1];
    int temp = 0;
    
    
    for(int i = arrayMid; i >= arrayLeft; i--) {
        temp += A[i];
        if(temp > maxLeft)
            maxLeft = temp;
    }
    
    temp = 0;
    for(int i = arrayMid + 1; i <= right; i++)
        
    {
        temp += A[i];
        if(temp > maxRight)
            maxRight = temp;
    }
    
    return max(max(arrayLeft, arrayRight), maxLeft + maxRight);
}
