#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

int desicion = -1;
// вариант 19


void server(int N) {
	int check_desicion;
	do {
		cout << "Введите № выбранной валентинки: ";
		cin >> check_desicion;
		cout << endl;
		if (check_desicion > N) {
			cout << "Номер выбранной валентинки не может превышать общее количесвто валентинок: " << endl;
		}
	} while (check_desicion > N);
	desicion = check_desicion;
}

void client(int my_number) {
	
	while (desicion == -1) {
		continue;
	}
	if (desicion != my_number) {
		mtx.lock();
		cout << "Валентинка №" << my_number << " отклонена" << endl;
		mtx.unlock();
	}
	else {
		mtx.lock();
		cout << "валентинка №" << my_number << " принята" << endl;
		mtx.unlock();
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	int N;
	cout << "Введите количество валентинок N: ";
	cin >> N;
	vector<thread> clients(N);
	for (int i = 0; i < N; i++) {
		clients[i] = thread(client, i);
	}

	thread thr(server, N);
	for (int i = 0; i < N; i++) {
		clients[i].join();
	}
	thr.join();
}
