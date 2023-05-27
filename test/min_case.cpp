int printf(char *s, ...);

void fun(int *A, int a) {
    int i = 2;
    printf("A[2] = %d\n", A[2]);
    A[i] = a;
    printf("A[2] = %d\n", A[2]);
    a = A[i-1];
    printf("a = %d\n", a);
}

int main() {
    int A[4];
    A[0] = 1;
    A[1] = 2;
    A[2] = 3;
    A[3] = 4;
    printf("A[2] = %d\n", A[2]);
    fun(&A[0], 10);
    printf("A[2] = %d\n", A[2]);
    return 0;
}
