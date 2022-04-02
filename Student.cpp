#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include "Student.h"

using namespace std;

Student_Queue::Student_Queue()
{
	queueFront = NULL;
	queueRear = NULL;
}


bool Student_Queue::isEmptyQueue()
{
	return (queueFront = NULL);
}

void Student_Queue::addQueue(string newID, string newPW, string newName, string newPhone, string newCompany, string newEvaluation)
{
	Student* newNode = new Student;
	newNode->studID = newID;
	newNode->studPW = newPW;
	newNode->studName = newName;
	newNode->studPhone = newPhone;
	newNode->studCompany = newCompany;
	newNode->studEvaluation = newEvaluation;	
	
	newNode->next = NULL; 	// set next pointer to null
	
	if(queueFront == NULL)
	{
		queueFront = newNode;
		queueRear = newNode;
	}
	else
	{
		queueRear->next = newNode;
		queueRear = newNode;
	}
}

void Student_Queue::deque()
{
	Student* temp;
	
	if(queueFront == NULL)
	{
		cout<<"\nOverflow..!!..Press a key to exit..\n";
		//getch();
		exit(2);
	}
	else
	{
		temp = queueFront;
		queueFront = queueFront->next;
		delete temp;
	}

}

void Student_Queue::deleteQueue()
{
	Student* temp;
	if(!isEmptyQueue())
	{
		temp = queueFront;
		queueFront = queueFront->next;
		delete temp;
		if(queueFront == NULL)
		{
			queueRear = NULL;
		}
	}
	else
	{
		cout << "Cannot remove anything. The queue linked list is empty." << endl;
	}
}

string Student_Queue::searchQueue(string studentID)
{
	Student* temp = queueFront;
	
	while(temp != NULL)
	{
		if(temp->studID == studentID)
		{
			return studentID;
		}
		else
		{
			temp = temp->next;
		}
	}
	return "NULL";
}

void Student_Queue::displayQueue()
{
	Student* temp = queueFront;
	
	while(temp != NULL)
	{
		cout << "\tName: " << temp->studName << endl;
		cout << "\tMatric ID: " << temp->studID << endl;
		cout << "\tPhone Number: " << temp->studPhone << endl;
		cout << "\tCompany: " << temp->studCompany << endl;
		cout << "\tEvaluation: " << temp->studEvaluation << endl << endl;
		temp = temp->next;
			
	}
}

int Student_Queue::loginStudent(string studentID, string studentPW)
{
	Student* temp = queueFront;
	int loginStatus = 1; // -1 means login unsucessful
	
	while(temp != NULL)
	{
		if(temp->studID == studentID)
		{
			if(temp->studPW == studentPW)
			{
				loginStatus = 0;
				return loginStatus;
			}
			else
				return loginStatus;
		}
		else
		{
			temp = temp->next;
		}
	}
	
	return loginStatus;
}

void Student_Queue::displayStudent(string id)
{
	Student* temp = queueFront;
	
	while(temp != NULL)
	{
		if(temp->studID == id)
		{
			cout << "\tName: " << temp->studName << endl;
			cout << "\tMatric ID: " << temp->studID << endl;
			cout << "\tPhone Number: " << temp->studPhone << endl;
			cout << "\tCompany: " << temp->studCompany << endl;
			cout << "\tEvaluation: " << temp->studEvaluation << endl;
			break;
		}
		else
			temp = temp->next;
	}
}

void Student_Queue::updateStudent(string id)
{
	ofstream Save;
	string newTelNo;
	string newCompany;
	Student* temp = queueFront;
	Save.open("student.txt");//Open student file
	while(temp != NULL)
	{
		if(temp->studID == id)
		{
			cout << "\tEnter new phone Number: ";
			cin >> newTelNo;
			temp->studPhone = newTelNo;
			cout << "\tEnter new company: ";
			cin.ignore();
			getline(cin,newCompany);
			temp->studCompany = newCompany;
			cout << "\tUpdate successful!" << endl;
			Save<<"\n"<<temp->studID<<";"<<temp->studPW<<";"<<temp->studName<<";"<<temp->studPhone<<";"<<temp->studCompany<<";"<<temp->studEvaluation;//Save new details
			break;
		}
		else
			Save<<"\n"<<temp->studID<<";"<<temp->studPW<<";"<<temp->studName<<";"<<temp->studPhone<<";"<<temp->studCompany<<";"<<temp->studEvaluation;//Maintain original details
			temp = temp->next;
	}
	Save.close();
}


void Student_Queue::setStudentEvaluation(string id, string newEvaluation)
{
	Student* temp = queueFront;
	ofstream Save;
	Save.open("student.txt");
	
	while(temp != NULL)
	{
		if(temp->studID == id)
		{
			temp->studEvaluation = newEvaluation;
			Save<<"\n"<<temp->studID<<";"<<temp->studPW<<";"<<temp->studName<<";"<<temp->studPhone<<";"<<temp->studCompany<<";"<<temp->studEvaluation;//Save new evaluation
			break;
		}
		else
			Save<<"\n"<<temp->studID<<";"<<temp->studPW<<";"<<temp->studName<<";"<<temp->studPhone<<";"<<temp->studCompany<<";"<<temp->studEvaluation;//Maintain original details
			temp = temp->next;
	}
	Save.close();
}

