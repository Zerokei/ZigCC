class Point {
public:
    Point(int x, int y) { this->x = x; this->y = y; }
public:
    Point() { this->x = 0; this->y = 0; }
public:
    Point(const Point &p) { this->x = p.x; this->y = p.y; }
public:
    ~Point() {}
private:
    int x;
private:
    int y;
private:
    void nothing() {
        int x = this->x;
        int y = this->y;
    }
};

int main() {
    Point p1;
    Point p2(1, 2);
    Point p3 = p1;
    Point* p4 = new Point(9, 10);
    Point* p5 = new Point;
    Point* p6 = new Point(p2);
    Point* p7 = new Point[10];
    int* a = new int(1);
    int* b = new int[10];
    delete a;
    return 0;
}