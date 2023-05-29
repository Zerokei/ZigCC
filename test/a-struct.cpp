int printf(char *s, ...);

struct X {
    int x;
    int y;
    int z;
};

int main() {
    X x;
    x.x = 1;
    x.y = 2;
    x.z = 3;
    printf("%d %d %d\n", x.x, x.y, x.z);

    X* p = new X;
    p->x = 4;
    p->y = 5;
    p->z = 6;
    printf("%d %d %d\n", p->x, p->y, p->z);

    return 0;
}