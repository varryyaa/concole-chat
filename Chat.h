#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

struct UserLoginExp : public exception
{
	const char *what() const noexcept override { return "error: user login is busy"; }
};

struct UserNameExp : public exception
{
	const char *what() const noexcept override { return "error: user name is busy"; }
};

class Chat
{
	bool isChatWork_ = false;
	vector<User> users_;
	vector<Message> messages_;
	shared_ptr<User> currentUser_=nullptr;

	void login();
	void signUp();
	void showChat() const;
	void showAllUserName() const;
	void addMessage();
	vector<User>& getAllUsers() { return users_; }
	vector<Message>& getAllMessage() { return messages_; }
	shared_ptr<User> getUserByLogin(const string& login) const;
	shared_ptr<User> getUserByName(const string& name) const;

public:
	void start();
	bool isChatWork() const { return isChatWork_; }
	shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLoginMenu();
	void showUserMenu();
};