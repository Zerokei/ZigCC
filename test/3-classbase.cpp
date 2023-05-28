int printf(char *s, ...);

class Point {
public:
    Point() { printf("default ctor\n"); }
public:
    ~Point() { printf("dtor\n"); }
private:
    int x;
private:
    int y;
};

int main() {
    Point p1;
    Point* p2 = new Point;
    Point* p3 = new Point[10];
    return 0;
}