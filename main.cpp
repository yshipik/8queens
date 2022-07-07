#include <iostream>
#include <cmath>
using std::endl;
using std::cout;

struct myqueens
{
    int q[8];
    int n;
    int num;
};


bool is_beaten(int x1, int x2, int y1,int y2) {
    if (y1 == y2)
        return true;
    else if(abs(x1 - x2) == abs(y1 - y2))
        return true;
    return false;
}

void shift(int &i, int n, int *q){
    if (q[i] >= n){
        q[i] = 1;
        i--;
        shift(i, n, q);
    } else 
        q[i] += 1;
}

void beat(int &i, myqueens &q){
    for(int m = 0; m < i; m++){
        if(is_beaten(m, i, q.q[m], q.q[i])){
            shift(i, q.n , q.q);
            beat(i, q);
        }
    }
}
void print_solution(myqueens &q){
    for(int j = 0; j < q.n; j++){
        std::cout << q.q[j] << " ";
    }
    std::cout << std::endl;
}
int main() {
    setlocale(LC_ALL, "Russian");
    myqueens q;
	q.n = 8;
	q.num = 0;
	for(int m = 0; m < q.n;m++) q.q[m] = 1;
    int i;
    i = 1;
	int last = 0;
	while(true){
		while(i < q.n) {
			beat(i, q);
			i += 1;
		}
		i--;
		q.num += 1;
		shift(i, q.n, q.q);
		if(last > q.q[0]){
			q.num -= 1;
			break;
		}
		last = q.q[0];
		print_solution(q);
	}
    cout << "Общее количество решений:" <<  q.num << endl;
    system("pause");
    return 0;
}
