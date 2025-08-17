
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <bits/stdc++.h>
using namespace std;

// ===== Helper Functions =====
bool isValidDate(string date);
bool isValidTime(string time);

// ===== Event Struct =====
struct Event {
    int id;
    string name, date, time, type, location;
    string recurrence;
};

// ===== Action Struct (for Undo) =====
struct Action {
    string type;  // "add", "edit", "delete"
    Event event;
};

// ===== EventManager Class =====
class EventManager {
    vector<Event> events;
    set<string> eventKeys; 
    string file = "events.txt";
    string userEmail;   // ✅ store user’s email

    stack<Action> history;
    void save();
    void load();
    bool isDuplicate(const Event &e);
    string todayDate();  

public:
    EventManager();
    EventManager(string filename,string email = "");

    int nextId();
    void addEvent();
    void editEvent();
    void deleteEvent();
    void viewEvents();
    void viewToday();
    void viewByDate(string d);
    void searchEvent(string key);
    // void sendReminders();
    void analytics();
    void undoLast();
    void timeline();
    void sendReminders(string email = "");

};

#endif
