#include "EventManager.h"

// ===== Helper Functions Implementation =====
bool isValidDate(string date) {
    if (date.size() != 10 || date[2] != '-' || date[5] != '-') return false;
    int d = stoi(date.substr(0,2));
    int m = stoi(date.substr(3,2));
    int y = stoi(date.substr(6,4));
    if (m < 1 || m > 12) return false;
    int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((y%400==0)||(y%4==0 && y%100!=0)) daysInMonth[2]=29; // leap year
    if (d < 1 || d > daysInMonth[m]) return false;
    return true;
}

bool isValidTime(string time) {
    if (time.size() != 5 || time[2] != ':') return false;
    int h = stoi(time.substr(0,2));
    int m = stoi(time.substr(3,2));
    return (h>=0 && h<=23 && m>=0 && m<=59);
}

// ===== Constructor =====
EventManager::EventManager() { load(); }
EventManager::EventManager(string filename, string email) {
    file = filename;
    userEmail = email;     // ✅ store email
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

// ===== Add Event =====
void EventManager::addEvent() {
    Event e;
    e.id = nextId();
    cin.ignore();
    cout << "Enter Name: "; getline(cin, e.name);

    do {
        cout << "Enter Date (DD-MM-YYYY): ";
        getline(cin, e.date);
        if (!isValidDate(e.date))
            cout << "❌ Invalid date! Try again.\n";
    } while (!isValidDate(e.date));

    do {
        cout << "Enter Time (HH:MM): ";
        getline(cin, e.time);
        if (!isValidTime(e.time))
            cout << "❌ Invalid time! Try again.\n";
    } while (!isValidTime(e.time));

    cout << "Enter Type: "; getline(cin, e.type);
    cout << "Enter Location: "; getline(cin, e.location);
    cout << "Recurrence (none/weekly/monthly): "; getline(cin, e.recurrence);

    if (isDuplicate(e)) {
        cout << "❌ Duplicate event exists!\n";
        return;
    }

    events.push_back(e);
    eventKeys.insert(e.name + "|" + e.date + "|" + e.time);
    save();
    history.push({"add", e});
    cout << "✅ Event added successfully (ID = " << e.id << ")\n";
}

// ===== Edit Event =====
void EventManager::editEvent() {
    int id; cout << "Enter Event ID to edit: "; cin >> id; cin.ignore();
    for (auto &e : events) {
        if (e.id == id) {
            Event old = e;
            string s;

            cout << "New Name (blank=keep): "; getline(cin, s); if (!s.empty()) e.name = s;
            cout << "New Date (DD-MM-YYYY, blank=keep): "; getline(cin, s); if (!s.empty() && isValidDate(s)) e.date = s;
            cout << "New Time (HH:MM, blank=keep): "; getline(cin, s); if (!s.empty() && isValidTime(s)) e.time = s;
            cout << "New Type (blank=keep): "; getline(cin, s); if (!s.empty()) e.type = s;
            cout << "New Location (blank=keep): "; getline(cin, s); if (!s.empty()) e.location = s;
            cout << "New Recurrence (blank=keep): "; getline(cin, s); if (!s.empty()) e.recurrence = s;

            save();
            history.push({"edit", old});
            cout << "✏️ Event updated!\n";
            return;
        }
    }
    cout << "❌ Event not found.\n";
}

// ===== Delete Event =====
void EventManager::deleteEvent() {
    int id; cout << "Enter Event ID to delete: "; cin >> id;
    auto it = remove_if(events.begin(), events.end(),
                        [&](Event &e){ return e.id == id; });
    if (it != events.end()) {
        Event deleted = *it;
        events.erase(it, events.end());
        save();
        history.push({"delete", deleted});
        cout << "🗑️ Event deleted!\n";
    } else {
        cout << "❌ Event not found.\n";
    }
}

// ===== View Events =====
void EventManager::viewEvents() {
    if (events.empty()) { cout << "No events yet.\n"; return; }
    sort(events.begin(), events.end(), [](Event &a, Event &b){
        return a.date == b.date ? a.time < b.time : a.date < b.date;
    });
    for (auto &e : events) {
        cout << "[" << e.id << "] " << e.name << " | " << e.date << " " << e.time
             << " | " << e.type << " | " << e.location
             << " | Recurrence: " << e.recurrence << "\n";
    }
}

// ===== View Today =====
void EventManager::viewToday() {
    string today = todayDate();
    cout << "\n📅 Today (" << today << "):\n";
    bool found = false;
    for (auto &e : events) {
        if (e.date == today) {
            cout << "[" << e.id << "] " << e.name << " at " << e.time
                 << " (" << e.type << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No events today.\n";
}

// ===== View by Date =====
void EventManager::viewByDate(string d) {
    if (!isValidDate(d)) { cout << "❌ Invalid date!\n"; return; }
    cout << "\n📅 Events on " << d << ":\n";
    bool found = false;
    for (auto &e : events) {
        if (e.date == d) {
            cout << "[" << e.id << "] " << e.name << " at " << e.time
                 << " (" << e.type << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No events on this date.\n";
}

// ===== Search =====
void EventManager::searchEvent(string key) {
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    bool found = false;
    for (auto &e : events) {
        string name = e.name, type = e.type;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(type.begin(), type.end(), type.begin(), ::tolower);
        if (name.find(key) != string::npos || type.find(key) != string::npos) {
            cout << "[" << e.id << "] " << e.name << " on "
                 << e.date << " " << e.time << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matches.\n";
}

// ===== Analytics =====
void EventManager::analytics() {
    map<string,int> typeCount;
    for (auto &e : events) typeCount[e.type]++;
    cout << "\n📊 Analytics:\n";
    cout << "Total events: " << events.size() << "\n";
    for (auto &p : typeCount) {
        cout << p.first << " -> " << p.second << " events\n";
    }
}

// ===== Undo =====
void EventManager::undoLast() {
    if (history.empty()) {
        cout << "❌ Nothing to undo!\n";
        return;
    }
    Action last = history.top();
    history.pop();

    if (last.type == "add") {
        events.erase(remove_if(events.begin(), events.end(),
                               [&](Event &e){ return e.id == last.event.id; }),
                     events.end());
        cout << "↩️ Undid Add Event: " << last.event.name << "\n";
    }
    else if (last.type == "delete") {
        events.push_back(last.event);
        cout << "↩️ Undid Delete Event: " << last.event.name << "\n";
    }
    else if (last.type == "edit") {
        for (auto &e : events) {
            if (e.id == last.event.id) {
                e = last.event;
                break;
            }
        }
        cout << "↩️ Undid Edit Event: " << last.event.name << "\n";
    }
    save();
}

// ===== Timeline =====
void EventManager::timeline() {
    string today = todayDate();
    cout << "\n📅 Timeline for " << today << ":\n";
    vector<Event> todaysEvents;
    for (auto &e : events) {
        if (e.date == today) todaysEvents.push_back(e);
    }
    if (todaysEvents.empty()) {
        cout << "No events today.\n";
        return;
    }
    sort(todaysEvents.begin(), todaysEvents.end(), [](const Event &a, const Event &b) {
        return a.time < b.time;
    });
    for (auto &e : todaysEvents) {
        cout << e.time << " | " << e.name << " (" << e.type << ") at " << e.location << "\n";
    }
}

// ===== Get Today =====
string EventManager::todayDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    strftime(buf, sizeof(buf), "%d-%m-%Y", ltm);
    return string(buf);
}
// ===== Send Reminders with Email =====
void EventManager::sendReminders(string email) {
    cout << "📧 Sending reminders (simulated)...\n";
    for (auto &e : events) {
        cout << "Reminder: " << e.name 
             << " at " << e.time << " on " << e.date
             << " → Sent to " << userEmail << "\n";   // ✅ email shown
    }
}

