#include <iostream>

using namespace std;

struct Student
{
	string studID, studPW, studName, studPhone, studCompany, studEvaluation;
	Student* next;
};

class Student_Queue
{
	public:
		Student_Queue();
		bool isEmptyQueue();
		void addQueue(string, string, string, string, string, string);
		void deque();
		void deleteQueue();
		void displayQueue();
		void displayStudent(string);
		void updateStudent(string);
		void setStudentEvaluation(string, string);
		string searchQueue(string);
		int loginStudent(string, string);
		
	private:
		Student* queueFront;
		Student* queueRear;
};
