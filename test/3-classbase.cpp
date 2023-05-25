class Point {
public:
    Point(int x, int y) : x(x), y(y) {}
    Point() : Point(0, 0) { nothing(); }
    Point(const Point &p) : Point(p.x, p.y) {}
private:
    int x;
    int y;
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
    return 0;
}