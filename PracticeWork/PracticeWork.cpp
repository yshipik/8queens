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
    int n; // размерность
    int num; // кол-во решений
};

void rotate(myqueens &mq, int n) {
	/* поворот доски на 90
	влево и вправо */
	for(int i = 0; i < n;i++){
		mq.qd[mq.q[i]] =  n - i - 1;
		mq.qg[n - 1 - mq.q[i]] = i;
	}
}

double Horn(int *q, int n){
	// используем метод Горнера для вычисления формулы
	double s1 = 0, s2 = 0;
	for(int i = 0; i < 8; i++){
		s1 = s1*n + ( q[i] + 1);
		s2 = s2*n + ( q[n - i - 1] + 1);
	}
	return std::min(s1, s2);
}

bool is_beaten(int x1, int x2, int y1,int y2) {
	// проверка бьет ли один ферзь ферзь другого
    if (y1 == y2)
        return true;
    else if(abs(x1 - x2) == abs(y1 - y2))
        return true;
    return false;
}

void shift(int &i, int n, int *q){
	// сдвиг(поиск с возвратом)
    if (q[i] >= n - 1){
        q[i] = 0;
        i--;
        shift(i, n, q);
    } else 
        q[i] += 1;
}

void beat(int &i, myqueens &q){
	/* двигает фигру до тех пора, пока не найдет правильное расположение
	*/
    for(int m = 0; m < i; m++){
        if(is_beaten(m, i, q.q[m], q.q[i])){
            shift(i, q.n , q.q);
            beat(i, q);
        }
    }
}

void print_solution(myqueens &q){
	// вывод решения
    for(int j = 0; j < q.n; j++){
        std::cout << q.q[j] + 1 << " ";
    }
    std::cout << std::endl;
}

void ask_for_write(bool &flag) {
	int tmp;
	cout << "1 вывод в файл, 0 вывод на экран:";
	cin >> tmp;
	if(tmp == 1)  flag = true;
	else if (tmp == 0){
		flag = false;
		cout << "Запрошен вывод в ОКП" << endl;
	} else {
		flag = false;
		cout << "Запрошен вывод в ОКП" << endl;
		cout << "Был введен некорректный индекс, запись в файл проигнорирована" << endl;
	
	}
}

void init_file(ofstream &file, bool &flag) {
	char buff[40];
	cout << "Введите имя файла:";
	cin >> buff;
	file.open(buff, 'w');
	if (!file.is_open())
	{
		cout << "Не удалось открыть файл" << endl;
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
	cout << "Задача о восьми ферзях, исключение всех избыточных решений" 
		<< std::endl;
	bool do_write;
	ofstream file;
	ask_for_write(do_write);
	if(do_write) init_file(file, do_write);
    myqueens q; // создаем структуру
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
    cout << "Всего решений:" << q.num << endl;
	delete[] q.q;
	delete[] q.qd;
	delete[] q.qg;
	if (do_write) {
		file.close();
	}
    system("pause");
    return 0;
}
