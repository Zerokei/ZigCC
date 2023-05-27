int x = 0;
void fun(int aa) {
    ;
}
int ff(int a, int b) {
    a = a + b;
    return a;
}
int fff() {
    return 1;
}
int main(int z) {
	z = 1;
	int y = 2;
    if(x+y < z) {
        x = 2;
        int y = 1;
        y = 3;
    } 
	fun(y);
    ff(x, y);
    fff();
}
