int printf(char *s, ...);

class Point {
public:
    Point() { printf("default ctor\n"); }
public:
    Point(int p) { printf("copy ctor\n"); }
public:
    ~Point() { printf("dtor\n"); }
private:
    int x;
private:
    int y;
};

int main() {
    Point p1;
    Point p2 = p1;
    Point* p3 = new Point;
    Point* p4 = new Point(p2);
    Point* p5 = new Point[10];
    return 0;
}