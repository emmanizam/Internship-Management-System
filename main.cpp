#include <iostream>
#include<iomanip>
#include<fstream>
#include "Student.h"

using namespace std;

void addAdvisor(string, string, string);
int loginAdvisor(string, string);

struct Advisor
{
	string advID, advPW, advName;
	Advisor* next;
};

const int n = 5; // n is size of array of Advisor struct
struct Advisor advisor[n];

int main() {
	int i=0;
	int userType, menuLoop = -1;
	int loginLoop = -1;
	int signUpLoop = -1, signUpType;
	int loginStatus = -1;
	string studentID, studentPW, studentName, studentPhone, studentCompany,studentEvaluation;
	string advisorID, advisorPW, advisorName;
	Student_Queue student;
	
	//File operations
	ifstream Read;
	ofstream Save;
	Read.open("student.txt");//Open student file
	while (!Read.eof())//Loop until end of file
	{
		getline(Read,studentID,';');
		getline(Read,studentPW,';');
		getline(Read,studentName,';');
		getline(Read,studentPhone,';');
		getline(Read,studentCompany,';');
		getline(Read,studentEvaluation);
		student.addQueue(studentID,studentPW,studentName,studentPhone,studentCompany,studentEvaluation);//Add data from file into student queue
	}
	Read.close();
	Read.open("advisor.txt");//Open advisor file
	while (!Read.eof())//Loop until end of file
	{
		getline(Read,advisorID,';');
		getline(Read,advisorPW,';');
		getline(Read,advisorName);
		//Set advisor details 
		advisor[i].advID=advisorID;
		advisor[i].advPW=advisorPW;
		advisor[i].advName=advisorName;
		i++;
	}
	Read.close();
	int indexCurrent = 1;
	// end

	do
	{
		system("cls");
		//Display menu
		cout << "\n\t\tINTERNSHIP MANAGEMENT SYSTEM" << endl;
		cout << "\t\t*******************************" << endl;
		cout << "Please choose an option (1: Log In As Advisor | 2: Log In As Student | 3: Sign Up | 4: Exit ): ";
		cin >> userType;
			
		if((userType == 1)||(userType == 2))
		{
			do
			{
				if(userType == 1) // login as advisor
				{
					cout << "\n\tEnter Advisor ID: ";
					cin >> advisorID;
					cout << "\tEnter Password: ";
					cin >> advisorPW;
					loginStatus = loginAdvisor(advisorID, advisorPW);//Check login
					
					if( loginStatus == 0)//Login successful
					{	
						loginLoop = loginStatus;
						menuLoop = 0;
					}
					else
					{
						cout << "\nLogin Failed! Please enter correct advisor ID and password to login." << endl;	
						cout << "NOTE: Advisor ID must be in capital letters" << endl;
						cout << "\nTo retry enter any number or enter 0 to exit login page: ";
						cin >> loginLoop;
						cout << "\n\n";
					}
			
				}
				else // login as student
				{
					cout << "\n\tEnter Student ID: ";
					cin >> studentID;
					cout << "\tEnter Password: ";
					cin >> studentPW;
					loginStatus = student.loginStudent(studentID, studentPW);//Check login

					if( loginStatus == 0)//Login successful
					{	
						loginLoop = loginStatus;
						menuLoop = 0;	
					}
					else
					{
						cout << "\nLogin Failed! Please enter correct student ID and password to login." << endl;	
						cout << "NOTE: Student ID must be in capital letters" << endl;
						cout << "\nTo retry enter any number or enter 0 to exit login page: ";
						cin >> loginLoop;
						cout << "\n\n";
					}
				}	
			}while(loginLoop != 0);
		}
		else if(userType == 3)//Sign up
		{
			int confirm = 0;
			
			cout << "\n\t1: SIGN UP AS ADVISOR | 2: SIGN UP AS STUDENT" << endl;
			cout << "Enter an option: ";
			cin >> signUpType;
			
			do
			{
				if(signUpType == 1)//Sign up as advisor
				{
					do
					{
						cout << "\n\nSIGN UP - ADVISOR" << endl;
						cout << "Enter advisor ID (in capital letter): ";
						cin >> advisorID;
						cout << "Create a password: ";
						cin >> advisorPW;
						if(advisorID.at(0) != 'A')
						{
							cout << "Advisor ID is invalid! \nNOTE: Advisor ID must start with capital A." << endl;
							confirm = -1;
							
							cout << "\nTo retry enter any number or enter 0 to exit login page: ";
							cin >> signUpLoop;
							
							if(signUpLoop == 0)
								break;
						}
						else
						{
							for(int i = 0; i < n; i ++)
							{
								if(advisor[i].advID == advisorID)//Existing advisor ID
								{
									cout << "Advisor ID is invalid! \nNOTE: Advisor ID is already registered in the system." << endl;
									confirm = -1;
									
									cout << "\nTo retry enter any number or enter 0 to exit login page: ";
									cin >> signUpLoop;
									
									if(signUpLoop == 0)
										break;
									break;
								}
								else
									confirm = 0;
							}
	
						}
					}while(confirm != 0);
					
					if(confirm == 0)//If new advisor ID 
					{
						cout << "\n\n\tENTER ADVISOR DETAILS" << endl;
						cout << "Name: ";
						cin.ignore();
						getline(cin,advisorName);
						advisor[indexCurrent+1].advID=advisorID;
						advisor[indexCurrent+1].advPW=advisorPW;
						advisor[indexCurrent+1].advName=advisorName;
						cout << "Account is signed up successfully!" << endl;
						Save.open("advisor.txt",ios::app);//Open advisor file
						Save<<"\n"<<advisorID<<";"<<advisorPW<<";"<<advisorName;//Save details to file
						Save.flush();//Save details without terminating program
						Save.close();
						cout << "\nTo back to home page enter any number or enter 0 to exit: ";
						cin >> signUpLoop;
						if(signUpLoop == 0)
							menuLoop = 0;
						else
							signUpLoop = 0;	
					}	
				}
				else if(signUpType == 2)//Sign up as student
				{	
					do
					{
						cout << "\n\nSIGN UP - STUDENT" << endl;
						cout << "Enter student ID (in capital letter): ";
						cin >> studentID;
						cout << "Create a password: ";
						cin >> studentPW;
						if(studentID.at(0) != 'S')//If initial input is not S
						{
							cout << "Student ID is invalid! \nNOTE: Student ID must start with capital S." << endl;
							confirm = -1;
							
							cout << "\nTo retry enter any number or enter 0 to exit login page: ";
							cin >> signUpLoop;
							
							if(signUpLoop == 0)
								break;
						}
						else if(student.searchQueue(studentID) != "NULL")//Search for same student ID
						{
							cout << "Student ID is invalid! \nNOTE: Student ID is already registered in the system." << endl;
							confirm = -1;
							
							cout << "\nTo retry enter any number or enter 0 to exit login page: ";
							cin >> signUpLoop;
							
							if(signUpLoop == 0)
								break;
						}
						else
						{
							confirm = 0;
						}

					}while(confirm!=0);
					
					if(confirm == 0)//If new student ID
					{
						cout << "\n\n\tENTER STUDENT DETAILS" << endl;
						cout << "Name: ";
						cin.ignore();
						getline(cin,studentName);
						cout << "Phone No. : ";
						cin >> studentPhone;
						cout << "Company: " ;
						cin.ignore();
						getline(cin,studentCompany);
						student.addQueue(studentID, studentPW, studentName, studentPhone, studentCompany, "Not available yet"); // new student added, thus evaluation not available yet
						cout << "Account is signed up successfully!" << endl;
						Save.open("student.txt",ios::app);//Open student file
						Save<<"\n"<<studentID<<";"<<studentPW<<";"<<studentName<<";"<<studentPhone<<";"<<studentCompany<<";"<<"Not available yet";//Save student details
						Save.flush();//Save without terminating program
						Save.close();
						cout << "\nTo back to home page enter any number or enter 0 to exit: ";
						cin >> signUpLoop;
						if(signUpLoop == 0)
							menuLoop = 0;
						else
							signUpLoop = 0;	
					}	
				}
				else
				{
					cout << "Option invalid!" << endl;
					cout << "\nTo continue enter any number or enter 0 to exit: ";
					cin >> signUpLoop;
				}
				
			}while(signUpLoop != 0);
			
		}
		else if(userType == 4)//Exit
		{
			cout << "THANK YOU!" << endl;
			menuLoop = 0;
		}
		else//Invalid option
		{
			cout << "Option invalid!" << endl;
			cout << "\nTo continue enter any number or enter 0 to exit: ";
			cin >> signUpLoop;
		}
	}while(menuLoop != 0);
	
	if((userType == 1)&&(loginStatus == 0))//Login as advisor is successful
	{
		int advOption, advLoop = -1;
		
		do
		{
			system("cls");
			cout << "\n\t\t========= ADVISOR =========" << endl;
			cout << "\t\t1: Display Student List\n\t\t2: Student Evaluation\n\t\t3: Delete Student";
			cout << "\n\t\tEnter an option: ";
			cin >> advOption;
			
			if(advOption == 1)//Display student list
			{
				cout << "\n\t\t\tSTUDENT LIST" << endl;
				cout << "\t**********************************************" << endl;
				student.displayQueue();
				cout << "\nTo choose another option enter any number or enter 0 to exit: ";
				cin >> advLoop;
			}
			else if(advOption == 2)//Give evaluation to students
			{
				int confirmStudent = -1;
				string newEvaluation;
				
				cout << "\n\t\t\tSTUDENT EVALUATION" << endl;
				cout << "\t**********************************************" << endl;
				cout << "Evaluate and give updates to students regarding their internships here." << endl;
				cout << "Enter student ID: ";
				cin >> studentID;
				student.searchQueue(studentID);
				
				if(student.searchQueue(studentID) != "NULL")//Search for student ID
				{
					student.displayStudent(studentID);
					cout << "\n\nIs this the student you want to evaluate? Enter any number to continue or enter 0 to cancel: ";
					cin >> confirmStudent;
					if(confirmStudent == 0)
						cout << "Evaluation cancelled" << endl;
					else
					{
						cout << "Enter new evaluation: ";
						cin.ignore();
						getline(cin,newEvaluation);					
						student.setStudentEvaluation(studentID, newEvaluation);
						cout << "New evaluation successfully updated!" << endl;
					}
				}
				else
					cout << "Student ID is not found. Evaluation cancelled" << endl;
				
				cout << "\nTo choose another option enter any number or enter 0 to exit: ";
				cin >> advLoop;
			}
			else if(advOption == 3)//Student deletion
			{
				int dequeueConfirmation = -1;
				
				cout << "\n\t\t\tDELETE STUDENT" << endl;
				cout << "\t**********************************************" << endl;
				cout << "You can delete student details who has completed their internship from the system here." << endl;
				cout << "This process will automatically delete the student at the front of the list." << endl;
				cout << "\n\t\t===== STUDENT CURRENT LIST =====" << endl;
				student.displayQueue();
				cout << "\nEnter any number to proceed or enter 0 to cancel: ";
				cin >> dequeueConfirmation;
				
				if(dequeueConfirmation != 0)
				{
					student.deque();
					cout << "\n\t\t===== STUDENT NEW LIST =====" << endl;
					student.displayQueue();
				}
				else
					cout << "Operation cancelled" << endl;
					
				cout << "\nTo choose another option enter any number or enter 0 to exit: ";
				cin >> advLoop;	
			}
			else
			{
				cout << "Option invalid!" << endl;
				cout << "To choose another option enter any number or enter 0 to exit: ";
				cin >> advLoop;
			}
		}while(advLoop!=0);
	}
	if((userType == 2)&&(loginStatus == 0))//Login as student successful
	{	
		int studOption, studLoop = -1;
		
		do
		{
			system("cls");
			cout << "\n\t\t========= STUDENT =========" << endl;
			cout << "\t\t1: Display Details\n\t\t2: Update Details";
			cout << "\n\t\tEnter an option: ";
			cin >> studOption;
			
			if(studOption == 1)//Display student detail
			{
				cout << "\n\t\t\tSTUDENT DETAILS" << endl;
				cout << "\t**********************************************" << endl;
				student.displayStudent(studentID);
				cout << "\nTo choose another option enter any number or enter 0 to exit: ";
				cin >> studLoop;
			}
			else if(studOption == 2)//Update details
			{
				cout << "\n\t\t\tUPDATE DETAILS" << endl;
				cout << "\t**********************************************" << endl;
				cout << "\tNOTE: Student is allowed to modify their phone number and company only." << endl;
				student.updateStudent(studentID);
				cout << "\nTo choose another option enter any number or enter 0 to exit: ";
				cin >> studLoop;
			}
			else
			{
				cout << "Option invalid!" << endl;
				cout << "To choose another option enter any number or enter 0 to exit: ";
				cin >> studLoop;
			}
		}while(studLoop!=0);
	}
	
	return 0;
}

int loginAdvisor(string id, string password)
{
	int status = -1; // if status = 0 indicates login success
	for(int i = 0; i < n; i++)
	{
		if(advisor[i].advID == id)
		{
			if(advisor[i].advPW == password)
			{
				status = 0;
				return status;
				break;
			}	
		}
	}
	return status;
}


