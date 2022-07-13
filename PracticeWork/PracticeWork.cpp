#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <fstream>
using std::endl;
using std::cout;
using std::cin;
using std::ofstream;
struct myqueens
{
    int *q, *qd, *qg;
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

void ask_for_write(bool &flag) {
	int tmp;
	cout << "1 ����� � ����, 0 ����� �� �����:";
	cin >> tmp;
	if(tmp == 1)  flag = true;
	else if (tmp == 0){
		flag = false;
		cout << "�������� ����� � ���" << endl;
	} else {
		flag = false;
		cout << "�������� ����� � ���" << endl;
		cout << "��� ������ ������������ ������, ������ � ���� ���������������" << endl;
	
	}
}

void init_file(ofstream &file, bool &flag) {
	char buff[40];
	cout << "������� ��� �����:";
	cin >> buff;
	file.open(buff, 'w');
	if (!file.is_open())
	{
		cout << "�� ������� ������� ����" << endl;
		flag = false;
		return;
	}
}
void write_solution(ofstream &file, myqueens q) {
	for(int j = 0; j < q.n; j++){
		file << q.q[j] + 1 << " ";
	}
    file << std::endl;
}
int main() {
    setlocale(LC_ALL, "Ru");
	system("color f0");
	cout << "������ � ������ ������, ���������� ���� ���������� �������" 
		<< std::endl;
	bool do_write;
	ofstream file;
	ask_for_write(do_write);
	if(do_write) init_file(file, do_write);
    myqueens q; // ������� ���������
	q.n = 8;
	q.q = new int[q.n];
	q.qd = new int[q.n];
	q.qg = new int[q.n];
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
			if(do_write) write_solution(file, q);
			else print_solution(q);
		}
		i--;
		shift(i, q.n, q.q);
	}
    cout << "����� �������:" << q.num << endl;
	delete[] q.q;
	delete[] q.qd;
	delete[] q.qg;
	if (do_write) {
		file.close();
	}
    system("pause");
    return 0;
}
