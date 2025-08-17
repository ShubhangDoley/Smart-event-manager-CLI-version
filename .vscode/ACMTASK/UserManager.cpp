#include "UserManager.h"

// Constructor loads all users
UserManager::UserManager() {
    loadUsers();
}

// Load from users.txt
void UserManager::loadUsers() {
    users.clear();
    ifstream fin(userFile);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        User u;
        getline(ss, u.username, '|');
        getline(ss, u.password, '|');
        getline(ss, u.email, '|');    
        getline(ss, u.eventsFile, '|');
        if (!u.username.empty()) users.push_back(u);
    }
}

// Save back to users.txt
void UserManager::saveUsers() {
    ofstream fout(userFile);
    for (auto &u : users) {
        fout << u.username << "|" << u.password << "|" << u.email << "|" << u.eventsFile << "\n";
    }
}

// Register new user
bool UserManager::registerUser(string username, string password,string email) {
    for (auto &u : users) {
        if (u.username == username) {
            cout << "❌ Username already exists!\n";
            return false;
        }
    }
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.email = email;
    newUser.eventsFile = username + "_events.txt";

    users.push_back(newUser);
    saveUsers();

    ofstream fout(newUser.eventsFile);
    fout.close();

    cout << "✅ User registered successfully! Login to continue.\n";
    return true;
}

// Login existing user
User* UserManager::loginUser(string username, string password) {
    for (auto &u : users) {
        if (u.username == username && u.password == password) {
            return &u;
        }
    }
    return nullptr;
}

// Delete a user (and their events file)
bool UserManager::deleteUser(string username) {
    auto it = remove_if(users.begin(), users.end(),[&](User &u){ return u.username == username; });
    if (it != users.end()) {
        string eventsFile = it->eventsFile;
        users.erase(it, users.end());
        saveUsers();
        remove(eventsFile.c_str());
        cout << "🗑️ User '" << username << "' deleted.\n";
        return true;
    }
    cout << "❌ User not found.\n";
    return false;
}

// Reset password
bool UserManager::resetPassword(string username, string newPassword) {
    for (auto &u : users) {
        if (u.username == username) {
            u.password = newPassword;
            saveUsers();
            cout << "🔑 Password reset for user '" << username << "'.\n";
            return true;
        }
    }
    cout << "❌ User not found.\n";
    return false;
}

// Return all users
vector<User> UserManager::getAllUsers() {
    return users;
}
