#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <ctime>

using namespace std;

class edge						//class to enable connections between members
{								//primarily holds the ID of the friend of the member
public:							
	string friendID;			//creates variable to hold the friend's ID

	edge()						//default constructor that sets the class's variable to empty
	{
		friendID = "";
		return;
	}
	edge(string frndID)			//constructor that sets the variable to a passed in value
	{
		friendID = frndID;
		return;
	}
	string getFrndID()			//getter to return the ID of the friend
	{
		return friendID;
	}
};

class vertex					//class that will hold each member
{								//and their corresponding variables
public:
	string name, memberID, gender, status;	//sets all requested variables for the members
	list<edge> friends;						//creates a list to house any friends of the members

	vertex()					//defailt constructor that sets the class's variables to empty
	{
		name = "";
		memberID = "";
		gender = "";
		status = "";
	}
	vertex(string uName, string memID, string gndr, string stat)	//constructor to set the
	{							//class's variables to passed in values
		name = uName;
		memberID = memID;
		gender = gndr;
		status = stat;
	}

	string getName()			//getter to return the name of the member
	{
		return name;
	}
	string getMemberID()		//getter to return the member's ID
	{
		return memberID;
	}
	string getGender()			//getter to return the member's gender
	{
		return gender;
	}
	string getStatus()			//getter to return the member's status
	{
		return status;
	}
	void setName(string uName)	//setter to set the name of the member
	{
		name = uName;
		return;
	}
	void setMemberID(string memID)	//setter to set the ID of the member
	{
		memberID = memID;
		return;
	}
	void setGender(string gndr)	//setter to set the gender of the member
	{
		gender = gndr;
		return;
	}
	void setStatus(string stat)	//setter to set the status of the member
	{
		status = stat;
		return;
	}

	list<edge> getEdgeList()	//getter to return the friends of the member
	{
		return friends;
	}
};

class graph						//primary class to hold the graph structure
{
public:
	vector<vertex> vertices;	//vector to house the members

	bool memberExists(string memID)	//function to check if there is a duplicate
	{								//member that is trying to be added to the vector
		bool found = false;		//sets variable to determine the result of a search
		for (int i = 0; i < vertices.size(); i++)	//for loop to search the vector
		{
			if (vertices.at(i).getMemberID() == memID)	//checks the values in the
			{						//vector to search for the passed in value
				return true;	//search successful
			}
		}
		return found;
	}

	vertex getMember(string memID)	//function to retreive the members information
	{							//by searching with the member's ID
		vertex temp;			//temp value to house a new member
		for (int i = 0; i < vertices.size(); i++)	//for loop to search the vector
		{
			temp = vertices.at(i);	//sets the temp value to each member of the vector
			if (temp.getMemberID() == memID)	//checks the temp value's ID against
			{									//the function's ID parameter
				return temp;	//search successful
			}
		}
		return temp;
	}

	void addMember(vertex newMember)	//function to add a member to the vector
	{
		bool search = memberExists(newMember.getMemberID());	//searches if there is
								//already a member with the parameter's information
		if (search == true)		//if there is a duplicate
		{
			cout << "This member already exists" << endl;	//let the user know
		}
		else					//if there is not a duplicate
		{
			vertices.push_back(newMember);	//add the value to the vector
			cout << "New member successfully added" << endl;
		}
		return;
	}

	void deleteMember(string memID)	//function to delete a member from the vector
	{							//as well as remove it from any member's list of friends
		int vecIndex = 0;		//sets a variable to house the current index
		
		for (int i = 0; i < vertices.size(); i++)	//for loop to search the vector
		{
			if (vertices.at(i).getMemberID() == memID)	//if the search is successful
			{
				vecIndex = i;	//remember the spot of the member
			}
		}
		
		for (int i = 0; i < vertices.size(); i++)	//for loop to search the vector
		{
			for (auto it = vertices.at(i).friends.begin(); it != vertices.at(i).friends.end(); it++)
			{					//for every friend that the member has
				if (it->getFrndID() == memID)	//if the member ID that needs deleted
				{				//matches the friend of a member
					vertices.at(i).friends.erase(it);	//delete the connection
				}
			}
		}
		vertices.erase(vertices.begin() + vecIndex); //delete the member at the proper index
		cout << "Member successfully removed" << endl;
		return;
	}

	bool checkIfFriend(string fromMember, string toMember)	//function to check for and
	{							//avoid a member having a duplicate entry on their list of friends
		vertex v = getMember(fromMember);	//gets the information of the member that is
								//sending the friend request
		list<edge> e;			//creates a list to house member's connections
		e = v.getEdgeList();	//sets the list of connections to mirror a member's existing
								//connections
		bool found = false;
		
		for (auto it = e.begin(); it != e.end(); it++)	//for loop to search the member's friend list
		{
			if (it->getFrndID() == toMember)	//if the member's friend list already contains
			{					//the member that will be receiving the friend request
				found = true;	//target has been found
				return found;
			}
		}
		return found;
	}

	void addFriend(string fromMember, string toMember)	//function to add a friend to a member
	{
		bool check1 = memberExists(fromMember);	//variable to hold whether the member exists
		bool check2 = memberExists(toMember);	//variable to hold whether the member exists
		bool check3 = checkIfFriend(fromMember, toMember);	//variable to hold whether the two
															//member's are already connected

		if (check1 == true && check2 == true)	//if both members exist
		{
			if (check3 == true)	//and they are already connected
			{
				cout << "These members are already friends" << endl; //let the user know
			}
			else
			{
				for (int i = 0; i < vertices.size(); i++)	//for loop to search the members
				{
					if (vertices.at(i).getMemberID() == fromMember)	//if the member is found
					{
						edge e(toMember);	//create the list as a variable of the member
						vertices.at(i).friends.push_back(e);	//inserts the connection
					}											//into the member's data

					else if (vertices.at(i).getMemberID() == toMember)	//do the same for the
					{						//other member to mirror each other
						edge e(toMember);
						vertices.at(i).friends.push_back(e);
					}
				}
				cout << "A friendship has been made" << endl;
			}
		}
		else
		{
			cout << "One of the members couldn't be found" << endl;
		}
		return;
	}

	void getFriends(string memID)	//function to find a member's friends and output them
	{
		cout << getMember(memID).getName() << " [" << getMember(memID).getMemberID() << "] " << endl;

		for (int i = 0; i < vertices.size(); i++) //for loop to search the members
		{
			if (vertices.at(i).getMemberID() == memID)	//if the parameter's value matches one
			{											//of the members

				cout << "Friends:";
				for (auto it = vertices.at(i).friends.begin(); it != vertices.at(i).friends.end(); it++)
				{				//search through the member's friends
					cout << " [" << it->friendID << "]";	//display the member's friends
				}
				cout << endl;
			}
		}
	}
};

int main()
{
	int menuChoice = NULL;
	graph graph1;
	vertex tempVertex;
	string name, memID, gender, status, id1, id2;
	bool search;


	time_t tt;		//functionality to get current date and time
	struct tm* ti;
	time(&tt);
	ti = localtime(&tt);

	cout << "Welcome to the friend list" << endl;
	cout << "Current date: " << asctime(ti) << endl;

	do
	{
		cout << "******************MENU******************" << endl;
		cout << "Enter 1 to add a member" << endl;
		cout << "Enter 2 to remove a member" << endl;
		cout << "Enter 3 to add a friend to a member" << endl;
		cout << "Enter 4 to display a member's friends" << endl;
		cout << "Enter 9 to exit the program" << endl;
		cin >> menuChoice;

		cin.ignore(INT_MAX, '\n');	//makes sure the buffer is clear for the
									//getline function when adding elements to the list
		switch (menuChoice)
		{
		case 9:
			break;
		case 1:
			cout << "Enter the member's name" << endl;
			getline(cin, name);
			cout << "Enter their member ID" << endl;
			getline(cin, memID);
			cout << "Enter their gender" << endl;
			getline(cin, gender);
			cout << "Enter their status" << endl;
			getline(cin, status);
			tempVertex.setName(name);
			tempVertex.setMemberID(memID);
			tempVertex.setGender(gender);
			tempVertex.setStatus(status);
			graph1.addMember(tempVertex);
			cout << endl;
			break;

		case 2:
			cout << "Enter the member ID to remove" << endl;
			getline(cin, memID);
			graph1.deleteMember(memID);
			cout << endl;
			break;

		case 3:
			cout << "Enter the first member(ID)" << endl;
			getline(cin, id1);
			cout << "Enter the second member(ID)" << endl;
			getline(cin, id2);
			graph1.addFriend(id1, id2);
			cout << endl;
			break;

		case 4:
			cout << "What member's (ID) friends would you like to see?" << endl;
			getline(cin, id1);
			graph1.getFriends(id1);
			cout << endl;
			break;
		}
	} while (menuChoice != 9);

	return 0;
}
