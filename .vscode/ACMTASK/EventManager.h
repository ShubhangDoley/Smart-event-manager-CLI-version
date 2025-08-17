#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <bits/stdc++.h>
using namespace std;

bool isValidDate(string date);
bool isValidTime(string time);

struct Event {
    int id;
    string name, date, time, type, location;
    string recurrence;
};

struct Action {
    string type;
    Event event;
};

class EventManager {
    vector<Event> events;
    set<string> eventKeys; 
    string file = "events.txt";
    string userEmail;
    stack<Action> history;

    void save();
    void load();
    bool isDuplicate(const Event &e);
    string todayDate();  

public:
    EventManager();
    EventManager(string filename,string email = "");
// ===== Save & Load =====
    int nextId();
    void addEventInteractive();   // old interactive version (optional)
    void addEvent(const Event &e); // new CLI-friendly version
    void editEvent();
    void deleteEvent();
    void viewEvents();
    void viewToday();
    void viewByDate(string d);
    void searchEvent(string key);
    void analytics();
    void undoLast();
    void timeline();
    void sendReminders(string email = "");
};

#endif
