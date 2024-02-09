#include <iostream> // Проект часть 1 создания окна регистрации и входа в личный кабинет

using namespace std;

class Client { // Создаем класс клиент
private:
	string login = " ";
	string name = " ";
	string surname = " ";
	int age = 0;
	int pasword = 0;
public:
	Client(){
		cout << "\tLogin" << endl;
	}
	void setData(string login, string name, string surname, int age, int pasword) { // Записываем данные клиента
		this->login = login;
		this->name = name;
		this->surname = surname;
		this->age = age;
		this->pasword = pasword;
	}

	string getLogin() { // Геттеры вывода данных для сравнения и показа
		return login;
	}
	string getName() {
		return name;
	}
	string getsurname() {
		return surname;
	}
	int getAge() {
		return age;
	}
	int getPasword() {
		return pasword;
	}
};

void LoginData(string log, string nam, string sur, int ag, int pas) { // Запрашиваем данные от пользователя
	cout << "Enter you login: ";
	cin >> log;
	cout << "Enter you pasword: ";
	cin >> pas;
	if (log != " " && pas > 100) {
		cout << "Enter you name: ";
		cin >> nam;
		cout << "Enter you surname: ";
		cin >> sur;
		cout << "Enter you age: ";
		cin >> ag;
	}
	else { // Если логина нет и пароль маленький - запрашиваем его заного
		
		cout << "Error data, pleas correct login and pasword" << endl;
		system("pause");
		system("cls");
		LoginData(log,nam,sur,ag,pas);

	}
	
}

int main() {
	int age = 0, pasword = 0;
	string name, surname, login;
	Client Vladimir;
	LoginData(login, name, surname, age, pasword);
	Vladimir.setData(login, name, surname, age, pasword);

	return 0;
}