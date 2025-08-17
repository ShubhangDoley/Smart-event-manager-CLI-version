#include "EventManager.h"

// ===== Helper Functions =====
bool isValidDate(string date) {
    if (date.size() != 10 || date[2] != '-' || date[5] != '-') return false;
    int d = stoi(date.substr(0,2));
    int m = stoi(date.substr(3,2));
    int y = stoi(date.substr(6,4));
    if (m < 1 || m > 12) return false;
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((y%400==0)||(y%4==0 && y%100!=0)) daysInMonth[2]=29;
    if (d < 1 || d > daysInMonth[m]) return false;
    return true;
}

bool isValidTime(string time) {
    if (time.size() != 5 || time[2] != ':') return false;
    int h = stoi(time.substr(0,2));
    int m = stoi(time.substr(3,2));
    return (h>=0 && h<=23 && m>=0 && m<=59);
}

// ===== Constructors =====
EventManager::EventManager() { load(); }
EventManager::EventManager(string filename, string email) {
    file = filename;
    userEmail = email;
    load();
}

// ===== Save & Load =====
void EventManager::save() {
    ofstream fout(file);
    for (auto &e : events) {
        fout << e.id << "|" << e.name << "|" << e.date << "|" << e.time << "|"
             << e.type << "|" << e.location << "|" << e.recurrence << "\n";
    }
}

void EventManager::load() {
    events.clear();
    eventKeys.clear();
    ifstream fin(file);
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        Event e; string temp;
        getline(ss, temp, '|'); e.id = stoi(temp);
        getline(ss, e.name, '|');
        getline(ss, e.date, '|');
        getline(ss, e.time, '|');
        getline(ss, e.type, '|');
        getline(ss, e.location, '|');
        getline(ss, e.recurrence, '|');
        events.push_back(e);
        eventKeys.insert(e.name + "|" + e.date + "|" + e.time);
    }
}

// ===== Duplicate Check =====
bool EventManager::isDuplicate(const Event &e) {
    string key = e.name + "|" + e.date + "|" + e.time;
    return eventKeys.count(key) > 0;
}

// ===== Next ID =====
int EventManager::nextId() {
    int mx = 0;
    for (auto &e : events) mx = max(mx, e.id);
    return mx + 1;
}

// ===== Add Event (CLI-friendly) =====
void EventManager::addEvent(const Event &e) {
    if (isDuplicate(e)) {
        cout << "❌ Duplicate event!\n";
        return;
    }
    events.push_back(e);
    eventKeys.insert(e.name + "|" + e.date + "|" + e.time);
    save();
    history.push({"add", e});
}

// ===== Old interactive addEvent (kept if needed) =====
void EventManager::addEventInteractive() {
    Event e;
    e.id = nextId();
    cin.ignore();
    cout << "Enter Name: "; getline(cin, e.name);
    cout << "Enter Date (DD-MM-YYYY): "; getline(cin, e.date);
    cout << "Enter Time (HH:MM): "; getline(cin, e.time);
    cout << "Enter Type: "; getline(cin, e.type);
    cout << "Enter Location: "; getline(cin, e.location);
    cout << "Recurrence: "; getline(cin, e.recurrence);
    addEvent(e);
}

// ===== Other functions (unchanged) =====
void EventManager::editEvent() { /* same as before */ }
void EventManager::deleteEvent() { /* same as before */ }
void EventManager::viewEvents() { /* same as before */ }
void EventManager::viewToday() { /* same as before */ }
void EventManager::viewByDate(string d) { /* same as before */ }
void EventManager::searchEvent(string key) { /* same as before */ }
void EventManager::analytics() { /* same as before */ }
void EventManager::undoLast() { /* same as before */ }
void EventManager::timeline() { /* same as before */ }
string EventManager::todayDate() { /* same as before */ }
void EventManager::sendReminders(string email) { /* same as before */ }
