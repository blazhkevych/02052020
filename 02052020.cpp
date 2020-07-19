#include <iostream>
#include <string.h>
using namespace std;

struct Student {
	char Name[50];
	int Age;
	int Marks[5];
	double Money;
	double AvgMarks() {
		double avg = 0;
		int countmarks = sizeof(Marks) / sizeof(*Marks);
		for (size_t i = 0; i < countmarks; i++)
			avg += Marks[i];
		return avg / countmarks;
	}
};

void Print(Student& student) {
	printf_s("|%-20s|%3d |%10.2lf UAH|", student.Name, student.Age, student.Money);
	int countmarks = sizeof(student.Marks) / sizeof(*student.Marks);
	for (size_t i = 0; i < countmarks; i++)
		printf_s("%3d|", student.Marks[i]);
	printf_s("%5.2lf|", student.AvgMarks());
	printf_s("\n");
}
void Input(Student& student) {
	printf_s("Enter name:");
	scanf_s("%s", &student.Name, 50);
	printf_s("Enter age:");
	scanf_s("%d", &student.Age);
	printf_s("Enter money:");
	scanf_s("%lf", &student.Money);
	int countmarks = sizeof(student.Marks) / sizeof(*student.Marks);
	for (size_t i = 0; i < countmarks; i++) {
		printf_s("Enter mark %d:", i + 1);
		scanf_s("%d", &student.Marks[i]);
	}
}
void InputGroup(Student* gr, int n) {
	for (size_t i = 0; i < n; i++)
	{
		Input(gr[i]);
		cout << "---------------------------------------\n";
	}
}
void PrintGroup(Student* gr, int n) {
	cout << "--------------------------------------------------------------------\n";
	for (size_t i = 0; i < n; i++)
		Print(gr[i]);
	cout << "--------------------------------------------------------------------\n";
}
void FindByName(Student* gr, int n, const char* name) {
	for (size_t i = 0; i < n; i++)
		//	if (strcmp(name ,gr[i].Name)==0)
		//	if (strstr(strlwr(strdup(gr[i].Name)), strlwr(strdup(name))))
		if (strstr(gr[i].Name, name))
			Print(gr[i]);
}
//sort name asc desc
//strcmp(a[j].Name, x.Name) > 0
typedef bool (*TCMP)(Student, Student);

bool ByNameAsc(Student a, Student b) {
	return strcmp(a.Name, b.Name) > 0;
}
bool ByNameDesc(Student a, Student b) {
	return strcmp(a.Name, b.Name) < 0;
}
//void InsertSort(Student* a, long size, bool (*CMP)(Student, Student)) {
void InsertSort(Student* a, long size, TCMP CMP) {
	Student x;
	long i, j;
	for (i = 0; i < size; i++) {  // цикл проходов, i - номер прохода
		x = a[i];
		// поиск места элемента в готовой последовательности 
		for (j = i - 1; j >= 0 && CMP(a[j], x); j--)
			a[j + 1] = a[j];  	// сдвигаем элемент направо, пока не дошли
		  // место найдено, вставить элемент
		a[j + 1] = x;
	}
}
int main()
{
	const int countst = 4;
	Student group[countst]{
		{ "Ivan",15,{10,12,3,4,5},1596.15 },
		{ "Piter",25,{10,12,6,8,9},2636.39632 },
		{ "Oleksandr",25,{10,12,6,8,9},2636.39632 },
		{ "Anna",20,{10,10,6,8,9},1636.39632 }
	};
	//InputGroup(group, countst);
	PrintGroup(group, countst);
	cout << "------f---------------------\n";
	FindByName(group, countst, "i");
	cout << "------f---------------------\n";
	InsertSort(group, countst, ByNameAsc);
	PrintGroup(group, countst);
	cout << "------f---------------------\n";
	InsertSort(group, countst, ByNameDesc);
	PrintGroup(group, countst);

	//Student Ivan{ "Ivan",15,{10,12,3,4,5},1596.15 };
	//Input(Ivan);
	//Print(Ivan);
	//Student Sasha{ "Oleksandr",15,{10,12,6,8,9},2636.39632 };
	//Input(Sasha);
	//Print(Sasha);
}