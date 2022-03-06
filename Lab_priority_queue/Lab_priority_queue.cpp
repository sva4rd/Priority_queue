#include "Priority_queue.h"
#include <string>
#include <map>
#include <regex>
#include <windows.h>

void print(int n)
{
	cout << n << ' ';
}
bool queue_name_check(map <string, Priority_queue>& queue, string name, string task)
{
	if (task == "add")
	{
		if (queue.find(name) != queue.end())
		{
			cout << "\nНеверное название! Введите другое: ";
			return false;
		}
		return true;
	}
	if (task == "search")
	{
		if (queue.find(name) == queue.end())
		{
			cout << "\nНе существует очереди с таким названием!\n " << '\n';
			return false;
		}
		return true;
	}
}
bool command_check(const string& command)
{
	if ((command.size() == 1 && command >= "0" && command <= "9") ||
		(command >= "10" && command <= "15" && command.size() == 2))
		return true;
	else
		return false;
}

string name_for_new_queue;//1,2,3
void new_queue_name_input(map <string, Priority_queue>& queue)
{
	cout << "Введите название новой очереди: ";
	do
	{
		cin >> name_for_new_queue;
	} while (!queue_name_check(queue, name_for_new_queue, "add"));
}

//1
void Add_empty_queue(map <string, Priority_queue>& queue)
{
	Priority_queue new_queue;
	new_queue_name_input(queue);
	queue.emplace(name_for_new_queue, new_queue);
}

//2
void New_Copy (map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	new_queue_name_input(queue);
	Priority_queue new_queue(iter->second);
	queue.emplace(name_for_new_queue, new_queue);
}

//3
void New_Move(map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	new_queue_name_input(queue);
	Priority_queue new_queue(std::move(iter->second));
	queue.emplace(name_for_new_queue, new_queue);
}

//4
void Copy_in_real(map <string, Priority_queue>& queue, const string& original_name, const string& copy_name)
{
	auto original_iter = queue.find(original_name);
	auto copy_iter = queue.find(copy_name);
	copy_iter->second = original_iter->second;
}

//5
void Move_in_real(map <string, Priority_queue>& queue, const string& original_name, const string& copy_name)
{
	auto original_iter = queue.find(original_name);
	auto copy_iter = queue.find(copy_name);
	copy_iter->second = std::move(original_iter->second);
}

//6
string prior_choice;//6 and 8 
int choice_number;//6 and 8
void Queue_elements_number(const map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	cout << "\nВыберите приоритет(1-high, 2-medium, 3-low, 4-all): ";
	cin >> prior_choice;
	if(prior_choice.size() != 1 || prior_choice <= "0" || prior_choice > "4")
	{
		cout << "\nНеправильный приоритет!\n";
		return;
	}
	choice_number = stoi(prior_choice);
	switch (choice_number)
	{
		case 1:
		{
			cout << "\nКоличество элементов с высоким приоритетом: " << iter->second.GetSize(Priority::high) << '\n';
			break;
		}
		case 2:
		{
			cout << "\nКоличество элементов со средним приоритетом: " << iter->second.GetSize(Priority::medium) << '\n';
			break;
		}
		case 3:
		{
			cout << "\nКоличество элементов с низким приоритетом: " << iter->second.GetSize(Priority::low) << '\n';
			break;
		}
		case 4:
		{
			cout << "\nКоличество элементов всех элементов очереди: " << iter->second.GetSize() << '\n';
			break;
		}
		default:
		{
			cout << "\nОшибка ввода!\n";
			break;
		}
	}
}

//7
void Queue_empty_check(const map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	if (iter->second.IsEmpty())
		cout << "\nОчередь пустая\n";
	else 
		cout << "\nОчередь не пустая\n";
}

//8
int ins_del_number;//8 and 9(insert and delete)
string ins_del_number_str;
int queue_element;
string element_value;
regex number_or_not("^([0-9]*)$");
void priority_input()
{
	while (true)
	{
		cout << "\nВыберите приоритет элемента(1-high, 2-medium, 3-low): ";
		cin >> prior_choice;
		if (prior_choice.size()!= 1 || prior_choice <= "0" || prior_choice > "3")
		{
			cout << "\nНеправильный приоритет!\n";
			continue;
		}
		choice_number = stoi(prior_choice);
		break;
	}
}
void value_input()
{
	while (true)
	{
		cout << "\nВведите значение элемента: ";
		cin >> element_value;
		if (!regex_match(element_value, number_or_not))
		{
			cout << "\nНеправильное значение!\n";
			continue;
		}
		queue_element = stoi(element_value);
		break;
	}
}
void elements_number_input()
{
	while (true)
	{
		cout << "\nВведите количество элементов для добавления в очередь: ";
		cin >> ins_del_number_str;
		if (!regex_match(ins_del_number_str, number_or_not))
		{
			cout << "\nНеправильное значение!\n";
			continue;
		}
		ins_del_number = stoi(ins_del_number_str);
		break;
	}
}
void Insert_elements(map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	elements_number_input();
	if (ins_del_number <= 0)
	{
		cout << "\nНеправильное значение!\n" << '\n';
		exit;
	}
	
	for (int i = 0; i < ins_del_number; i++)
	{
		value_input();
		priority_input();
		switch (choice_number)
		{
			case 1:
			{
				iter->second.Push(queue_element, Priority::high);
				break;
			}
			case 2:
			{
				iter->second.Push(queue_element, Priority::medium);
				break;
			}
			case 3:
			{
				iter->second.Push(queue_element, Priority::low);
				break;
			}
		}
	}
}

//9
void elements_number_delete(map <string, Priority_queue>::iterator iter)
{
	while (true)
	{
		cout << "\nВведите количество элементов для удаления из очереди: ";
		cin >> ins_del_number_str;
		if (!regex_match(ins_del_number_str, number_or_not))
		{
			cout << "\nНеправильное значение!\n";
			continue;
		}
		ins_del_number = stoi(ins_del_number_str);
		if (ins_del_number > iter->second.GetSize())
		{
			cout << "\nНеправильное значение!\n";
			continue;
		}
		break;
	}
}
void Delete_queue_elements(map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	if (iter->second.IsEmpty())
	{
		cout << "\nОшибка! Очередь пустая!\n";
		exit;
	}
	elements_number_delete(iter);
	if (ins_del_number <= 0)
	{
		cout << "\nНеправильное значение!\n" << '\n';
		exit;
	}
	for (int i = 0; i < ins_del_number; i++)
		iter->second.Pop();
}

//10
void Front_element_info(map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	try
	{
		cout << "\nЗначение элемента: " << iter->second.GetFirst();
		cout << "\nПриоритет элемента: ";
		switch (iter->second.GetFirstPriority())
		{
		case Priority::high:
		{
			cout << "Высокий\n";
			break;
		}
		case Priority::medium:
		{
			cout << "Средний\n";
			break;
		}
		case Priority::low:
		{
			cout << "Низкий\n";
			break;
		}
		}
	}
	catch (exception& ex)
	{
		cout << '\n' << ex.what() << '\n';
	}
}

//11
void Print_queue(const map <string, Priority_queue>& queue, const string& name)
{
	auto iter = queue.find(name);
	try
	{
		iter->second.Browse(print);
	}
	catch (exception& ex)
	{
		cout << ex.what();
	}
	cout << '\n';
}

//12
void Print_all_queues(const map <string, Priority_queue>& queue)
{
	for (auto iter = queue.begin(); iter != queue.end(); iter++)
	{
		cout << "\nНазвание: " << iter->first << '\n';
		try
		{
			cout << "Элементы: ";
			iter->second.Browse(print);
			cout << '\n';
		}
		catch (exception& ex)
		{
			cout << ex.what() << '\n';
		}
	}
}

//13
void Delete_queue(map <string, Priority_queue>& queue, const string& queue_name)
{
	auto iter = queue.find(queue_name);
	queue.erase(iter);
}


bool Queue_Search(map <string, Priority_queue>& queue, string& queue_name)
{
	cout << "\nВведите название очереди: ";
	cin >> queue_name;
	if (queue_name_check(queue, queue_name, "search"))
		return true;
	return false;
}

void menu(map <string, Priority_queue> &queue)
{
	string queue_name, queue_name2;
	string command;
	int n;
	while (true)
	{
		cout << "Введите номер команды(для просмтора команд нажмите 0): ";
		cin >> command;
		if (!command_check(command))
		{
			cout << "\nНеправильный номер команды!\n" << '\n';
			continue;
		}
		n = stoi(command);

		if (n == 15)
			break;
		
		switch (n)
		{
			case 0:
			{
				cout << "1. Создать пустую очередь\n";
				cout << "2. Создать очередь(конструктор копирования)\n";
				cout << "3. Создать очередь(конструктор перемещения)\n";
				cout << "4. Скопировать очередь в существующую(копирующий оператор присваивания)\n";
				cout << "5. Переместить очередь в существующую(перемещающий оператор присваивания)\n";
				cout << "6. Вывести количество элементов очереди\n";
				cout << "7. Проверить очередь на пустоту\n";
				cout << "8. Вставить элементы в очередь\n";
				cout << "9. Удалить элементы из очереди\n";
				cout << "10. Получение информации о приоритете и значении элемента, стоящего в голове очереди\n";
				cout << "11. Вывести очередь\n";
				cout << "12. Вывести все очереди\n";
				cout << "13. Удалить очередь\n";
				cout << "14. Очистить консоль\n";
				cout << "15. Выйти\n";
				break;
			}
			case 1:
			{
				Add_empty_queue(queue);
				break;
			}
			case 2:
			{
				cout << "\nВведите название копируемой очереди: ";
				cin >> queue_name;
				if (queue_name_check(queue, queue_name, "search"))
					New_Copy(queue, queue_name);
				break;
			}
			case 3:
			{
				cout << "\nВведите название перемещаемой очереди: ";
				cin >> queue_name;
				if (queue_name_check(queue, queue_name, "search"))
					New_Move(queue, queue_name);
				break;
			}
			case 4:
			{
				cout << "\nВведите название копируемой очереди: ";
				cin >> queue_name;
				if (queue_name_check(queue, queue_name, "search"))
				{
					cout << "\nВведите название копирующей очереди: ";
					cin >> queue_name2;
					if (queue_name_check(queue, queue_name2, "search"))
						Copy_in_real(queue, queue_name, queue_name2);
				}
				break;
			}
			case 5:
			{
				cout << "\nВведите название перемещаемой очереди: ";
				cin >> queue_name;
				if (queue_name_check(queue, queue_name, "search"))
				{
					cout << "\nВведите название принимающей очереди: ";
					cin >> queue_name2;
					if (queue_name_check(queue, queue_name2, "search"))
						Move_in_real(queue, queue_name, queue_name2);
					break;
				}
			}
			case 6:
			{
				if (Queue_Search(queue, queue_name))
					Queue_elements_number(queue, queue_name);
				break;
			}
			case 7:
			{
				if (Queue_Search(queue, queue_name))
					Queue_empty_check(queue, queue_name);
				break;
			}
			case 8:
			{
				if (Queue_Search(queue, queue_name))
					Insert_elements(queue, queue_name);
				break;
			}
			case 9:
			{
				if (Queue_Search(queue, queue_name))
					Delete_queue_elements(queue, queue_name);
				break;
			}
			case 10:
			{
				if (Queue_Search(queue, queue_name))
					Front_element_info(queue, queue_name);
				break;
			}
			case 11:
			{
				if (Queue_Search(queue, queue_name))
					Print_queue(queue, queue_name);
				break;
			}
			case 12:
			{
				if (queue.empty())
				{
					cout << "\nОчередей нет!\n";
					break;
				}
				Print_all_queues(queue);
				break;
			}
			case 13:
			{
				if (Queue_Search(queue, queue_name))
					Delete_queue(queue, queue_name);
				break;
			}
			case 14:
			{
				system("cls");
				break;
			}
		}
	}
	
	
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	map <string, Priority_queue> queue;
	menu(queue);
	return 0;
}