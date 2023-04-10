#include <iostream>
#include "Chat.h"
void Chat::start()
{
	isChatWork_ = true;
}

shared_ptr<User> Chat::getUserByLogin(const string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getUserLogin())
			return make_shared<User>(user);
	}
	return nullptr;
}
shared_ptr<User> Chat::getUserByName(const string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getUserName())
			return make_shared<User>(user);
	}
	return nullptr;
}

void Chat::login()
{
	string login, password;
	char oper;

	do
	{
		cout << "Login: ";
		cin >> login;
		cout << "Password: ";
		cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;
			cout << "Login failed!" << endl;
			cin >> oper;

			if (oper == '0')
				break;
		}
	} while (!currentUser_);
}

void Chat::signUp()
{
	string login, password, name;

	cout << "Login: ";
	cin >> login;
	cout << "Password: ";
	cin >> password;
	cout << "Name: ";
	cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserNameExp();
	}
	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = make_shared<User>(user);
}

void Chat::showChat() const
{
	string from;
	string to;

	cout << "--------CHAT--------" << endl;

	for (auto& mess : messages_)
	{
		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{
			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "all";
			}
			else 
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
			}
			cout << "Message from: " << from << " to " << to << endl;
			cout << "Text: " << mess.getText() << endl;
		}
	}
	cout << "--------------------" << endl;
}

void Chat::showLoginMenu()
{
	currentUser_ = nullptr;

	char oper;

	do
	{
		cout << "Choose an action:" << endl;
		cout << "(1)Login || (2)SignUp || (3)Exit" << endl;
		cin >> oper;

		switch (oper)
		{
		case'1':
			login();
			break;
		case'2':
			try
			{
				signUp();
			}
			catch (const exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case'0':
			isChatWork_ = false;
			break;
		default:
			cout << "Choose an action: 1 or 2 or 0" << endl;
			break;
		}
	} while (!currentUser_ && isChatWork_);
}

void Chat::showUserMenu()
{
	char oper;

	cout << "Hi, " << currentUser_->getUserName() << endl;

	while (currentUser_)
	{
		cout << "UserMenu: (1)Show chat || (2)Add Message || (3)Show users || (0)Logout" << endl;

		cin >> oper;

		switch (oper)
		{
		case'1':
			showChat();
			break;
		case'2':
			addMessage();
			break;
		case'3':
			showAllUserName();
			break;
		case'0':
			currentUser_ = nullptr;
			break;
		default:
			cout << "Choose an action: 1 or 2 or 3 or 0" << endl;
			break;
		}
	}
}

void Chat::showAllUserName() const
{
	cout << "--------USERS--------" << endl;
	for (auto& user : users_)
	{
		cout << user.getUserName() << endl;

		if (currentUser_->getUserLogin() == user.getUserLogin())
			cout << "(me)" << endl;
	}
	cout << "---------------------" << endl;
}

void Chat::addMessage()
{
	string to, text;

	cout << "To (name or all) ";
	cin >> to;
	cout << "Text: ";
	cin.ignore();
	getline(cin, text);

	if (!(to == "all" || getUserByName(to)))
	{
		cout << "Error send message! Try again " << to << endl;
		return;
	}
	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}