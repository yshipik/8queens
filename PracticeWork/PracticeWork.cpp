#include "stdafx.h"
#include <cmath>
#include <iostream>
using std::endl;
using std::cout;

struct myqueens
{
    int q[8], qd[8], qg[8];
    int n; // �����������
    int num; // ���-�� �������
};

void rotate(myqueens &mq, int n) {
	/* ������� ����� �� 90
	����� � ������ */
	for(int i = 0; i < n;i++){
		mq.qd[mq.q[i]] =  n - i - 1;
		mq.qg[n - 1 - mq.q[i]] = i;
	}
}

double Horn(int *q, int n){
	// ���������� ����� ������� ��� ���������� �������
	double s1 = 0, s2 = 0;
	for(int i = 0; i < 8; i++){
		s1 = s1*n + ( q[i] + 1);
		s2 = s2*n + ( q[n - i - 1] + 1);
	}
	return std::min(s1, s2);
}

bool is_beaten(int x1, int x2, int y1,int y2) {
	// �������� ���� �� ���� ����� ����� �������
    if (y1 == y2)
        return true;
    else if(abs(x1 - x2) == abs(y1 - y2))
        return true;
    return false;
}

void shift(int &i, int n, int *q){
	// �����(����� � ���������)
    if (q[i] >= n - 1){
        q[i] = 0;
        i--;
        shift(i, n, q);
    } else 
        q[i] += 1;
}

void beat(int &i, myqueens &q){
	/* ������� ����� �� ��� ����, ���� �� ������ ���������� ������������
	*/
    for(int m = 0; m < i; m++){
        if(is_beaten(m, i, q.q[m], q.q[i])){
            shift(i, q.n , q.q);
            beat(i, q);
        }
    }
}

void print_solution(myqueens &q){
	// ����� �������
    for(int j = 0; j < q.n; j++){
        std::cout << q.q[j] + 1 << " ";
    }
    std::cout << std::endl;
}
int main() {
    setlocale(LC_ALL, "Ru");
	cout << "������ � ������ ������, ���������� ���� ���������� �������" 
		<< std::endl;
    myqueens q; // ������� ���������
	q.n = 8;
	q.num = 0;
	bool isrot;
	for(int m = 0; m < q.n;m++) q.q[m] = 0;
    int i = 1;
	while(q.q[0] - 4 < 0){
		while(i < q.n) {
			beat(i, q);
			i += 1;
		}
		isrot = true;
		rotate(q, q.n);
		double x = Horn(q.qd, q.n);
		double y = Horn(q.qg, q.n);
		double z = Horn(q.q, q.n);
		if(x < z || y < z)	isrot = false;
		if(q.q[0] < q.q[7] && isrot){
			q.num += 1;
			print_solution(q);
		}
		i--;
		shift(i, q.n, q.q);
	}
    cout << "����� �������:" << q.num << endl;
    system("pause");
    return 0;
}
