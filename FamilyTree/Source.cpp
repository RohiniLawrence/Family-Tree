


#include <iostream>
#include <string>
using namespace std;


const int numOfChildren = 6;
struct person
{
	string name;
	char gender;
	person* parent;
	person* children[numOfChildren] = { NULL,NULL, NULL, NULL, NULL, NULL };
};

person* eldestPerson;

int mainMenuDisplay();
void selectOption(int);
person* createPerson(string, char, person*);
person* createPersonUserInput();
person* findPerson(string);
void removePerson(string);
void outputPerson(person*);
void navigateFamily(string);
person* check(person* toCheck, string nameToFind);
string enterName();
void deletechild(person* toCheck);




int main()
{
	eldestPerson = createPerson("Eldest", 'F', NULL);


	selectOption(mainMenuDisplay());



	return 0;
}






int mainMenuDisplay()
{
	int opt;
label:

	cout << endl << "Select an option:" << endl
		<< "1) Create a person."
		<< endl << "2) Remove a person."
		<< endl << "3) Display a person."
		<< endl << "4) Navigate family tree."
		<< endl << "5) Exit."
		<< endl;

	cin >> opt;
	while (cin.fail() || cin.peek() != '\n' || opt < 1 || opt>5)
	{
		cin.clear();
		cin.ignore(512, '\n');
		cout << "The selection was invalid. Please try again..." << endl;

		goto label;
	}

	return opt;
}
void selectOption(int selection)
{
	string na;
	person* per[100];
	int i = 0, deleted = NULL;

	switch (selection)
	{
	case 1:
		if (deleted == NULL) {
			per[i] = createPersonUserInput();
		}
		else
		{
			per[deleted] = createPersonUserInput();
			deleted = NULL;
		}
		selectOption(mainMenuDisplay());


		break;

	case 2:

		removePerson(enterName());
		selectOption(mainMenuDisplay());
		break;

	case 3:
		na = enterName();
		if (check(eldestPerson, na) != NULL)
			outputPerson(findPerson(na));
		else
			cout << "not found";

		selectOption(mainMenuDisplay());

		break;
	case 4:

		navigateFamily(enterName());

		selectOption(mainMenuDisplay());
		break;

	case 5: cout << "BYE!";
		exit(0);
		break;
	}

}
person* createPerson(string name, char gender, person* parent)
{
	person* toReturn = new person();
	(*toReturn).name = name;
	toReturn->gender = gender;
	toReturn->parent = parent;
	if (toReturn->parent != NULL) {
		for (int i = 0; i < numOfChildren; i++)
		{
			if (parent->children[i] == NULL)
			{
				parent->children[i] = toReturn;
				break;
			}
			else if (i == 5) {
				cout << "Max children associated with this person...";
			}
		}
	}
	return toReturn;
}
person* createPersonUserInput()
{
	string na, prnt;
	char gen;
	int i = 0;

	cout << "Enter name of the person: ";
label2:
	cin >> na;
	if (check(eldestPerson, na) != NULL && check(eldestPerson, na)->name == na)
	{
		cout << "The name already exists! Please enter the name with slight variation..." << endl;
		goto label2;
	}

	cout << "Enter gender of the person (M/F) :";
label1:
	cin >> gen;

	while (cin.fail() || cin.peek() != '\n' || (toupper(gen) != 'M'  && toupper(gen) != 'F'))
	{
		cin.clear();
		cin.ignore(512, '\n');
		cout << "Please enter M or F, try again.." << endl;

		goto label1;
	}

label3:
	cout << "Enter parent's name:";
label4:
	cin >> prnt;
	if (check(eldestPerson, prnt) == NULL)
	{
		cout << "No such person found! Enter another name.... " << endl;
		goto label4;
	}

	createPerson(na, gen, check(eldestPerson, prnt));
	return NULL;
}


person* findPerson(string nameToFind)
{
	person* toReturn = check(eldestPerson, nameToFind);
	if (toReturn == NULL)
	{
		cout << "No such person found!";
	}


	return toReturn;
}
person* check(person* toCheck, string nameToFind)
{
	if ((*toCheck).name == nameToFind)
	{
		return toCheck;

	}
	else
	{
		for (int i = 0; i < numOfChildren; i++)
		{
			if (toCheck->children[i] != NULL)
			{
				person* p = check(toCheck->children[i], nameToFind);
				if (p != NULL)
					return p;
			}
		}
		return NULL;
	}
}


void deletechild(person* toCheck)
{
	cout << "Deleting: " << toCheck->name << endl;
	delete(toCheck);

	if ((*toCheck).children[0] != NULL)
	{
		for (int i = 0; i < numOfChildren; i++)
		{
			if (toCheck->children[i] != NULL) {
				deletechild(toCheck->children[i]);
			}
		}

	}
}


void removePerson(string name)
{

	if (findPerson(name) != NULL)
	{
		deletechild(findPerson(name));
	}

}
void outputPerson(person* p)
{
	cout << "***************************************";
	cout << endl << "Name of the Person: " + p->name << endl << "Gender: " << ((*p).gender) << endl << "Parent: " + ((p->parent == NULL) ? " " : p->parent->name) << endl << "Children: ";

	for (int i = 0; i < numOfChildren; i++)
	{
		if (p->children[i] != NULL)
		{
			cout << p->children[i]->name;
			if (p->children[i + 1] != NULL)
				cout << ",";

		}

	}

	cout << endl << "***************************************" << endl;
}
void navigateFamily(string s)
{

	string na = s;

label5:
	if (check(eldestPerson, na) != NULL)
		outputPerson(findPerson(na));
	else
		cout << "Person not found!" << endl;

	cout << endl << "To navigate: Enter the name of the person..." << endl
		<< "To quit: Enter -1.." << endl;
	cin >> na;
	if (na == "-1")
	{
		selectOption(mainMenuDisplay());
	}
	else
		goto label5;

}








string enterName()
{
	string name;
	cout << "Enter the name of the person : ";
	cin >> name;
	return name;
}

