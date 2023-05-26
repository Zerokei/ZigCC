class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
public:
    Point() : Point(0, 0) { nothing(); }
public:
    Point(const Point &p) : Point(p.x, p.y) {}
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
    // Point p1;
    // Point p2(1, 2);
    // Point p3 = p1;
    // Point p4 = Point(3, 4);
    // Point p5 = {5, 6};
    // Point p6{7, 8};
    // Point* p7 = new Point(9, 10);
    int* a = new int(1);
    delete a;
    return 0;
}