int x = 0;
void fun(int aa) {
    ;
}
int main(int z) {
	z = 1;
	int y = 2;
    while(x+y < z) {
        x = 2;
        int y = 1;
        if(x > y) {
            break;
        }
        do{
            int x = 3;
            for(int i = 0; i < 10; ++i) {
                y = 4;
                int x = 9;
                if(x == y) {
                    break;
                }
                continue;
            }
            if(x < y) {
                int x = 5;
                continue;
            }
        } while(x);
        y = 3;
    } 
	fun(y);
}
