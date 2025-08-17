#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <bits/stdc++.h>
using namespace std;

struct User {
    string username;
    string password;
    string eventsFile;
    string email;
};

class UserManager {
    vector<User> users;
    string userFile = "users.txt";

public:
    UserManager();
    void loadUsers();
    void saveUsers();
    bool registerUser(string username, string password,string email = "");
    User* loginUser(string username, string password);
    vector<User> getAllUsers();

    //  Admin-only functions
    bool deleteUser(string username);
    bool resetPassword(string username, string newPassword);
};
//
#endif
