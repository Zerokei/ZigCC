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
    Point p4 = Point(3, 4);
    Point p5 = {5, 6};
    Point p6{7, 8};
    Point* p7 = new Point(9, 10);
    int* a = new int(1);
    delete a;
    return 0;
}