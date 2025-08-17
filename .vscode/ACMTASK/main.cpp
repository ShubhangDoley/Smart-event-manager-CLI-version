#include "UserManager.h"
#include "EventManager.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: ./event_manager <command> [args...]\n";
        return 1;
    }

    string command = argv[1];
    UserManager userManager;

    // ---------- User Commands ----------
    if (command == "register") {
        if (argc < 5) { cout << "Usage: register <username> <password> <email>\n"; return 1; }
        userManager.registerUser(argv[2], argv[3], argv[4]);
    }
    else if (command == "login") {
        if (argc < 4) { cout << "Usage: login <username> <password>\n"; return 1; }
        cout << (userManager.loginUser(argv[2], argv[3]) ? " Login success\n" : " Invalid login\n");
    }
    else if (command == "list-users") {
        for (auto &u : userManager.getAllUsers()) {
            cout << u.username << " | " << u.email << " | " << u.eventsFile << "\n";
        }
    }
    else if (command == "delete-user") {
        if (argc < 3) { cout << "Usage: delete-user <username>\n"; return 1; }
        userManager.deleteUser(argv[2]);
    }
    else if (command == "reset-password") {
        if (argc < 4) { cout << "Usage: reset-password <username> <newpassword>\n"; return 1; }
        userManager.resetPassword(argv[2], argv[3]);
    }

    // ---------- Event Commands ----------
    else if (command == "add-event") {
        if (argc < 10) { cout << "Usage: add-event <username> <password> <name> <date> <time> <type> <location> <recurrence>\n"; return 1; }
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) { cout << " Invalid login\n"; return 1; }
        EventManager em(u->eventsFile, u->email);
        Event e{em.nextId(), argv[4], argv[5], argv[6], argv[7], argv[8], argv[9]};
        em.addEvent(e);
        cout << " Event added\n";
    }
    else if (command == "view-events") {
        if (argc < 4) { cout << "Usage: view-events <username> <password>\n"; return 1; }
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) { cout << " Invalid login\n"; return 1; }
        EventManager em(u->eventsFile, u->email);
        em.viewEvents();
    }
    else if (command == "view-today") {
        if (argc < 4) return 1;
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) return 1;
        EventManager em(u->eventsFile, u->email);
        em.viewToday();
    }
    else if (command == "view-date") {
        if (argc < 5) return 1;
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) return 1;
        EventManager em(u->eventsFile, u->email);
        em.viewByDate(argv[4]);
    }
    //
    else if (command == "search") {
        if (argc < 5) return 1;
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) return 1;
        EventManager em(u->eventsFile, u->email);
        em.searchEvent(argv[4]);
    }
    else if (command == "analytics") {
        if (argc < 4) return 1;
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) return 1;
        EventManager em(u->eventsFile, u->email);
        em.analytics();
    }
    else if (command == "timeline") {
        if (argc < 4) return 1;
        User* u = userManager.loginUser(argv[2], argv[3]);
        if (!u) return 1;
        EventManager em(u->eventsFile, u->email);
        em.timeline();
    }
    else {
        cout << " Unknown command\n";
    }

    return 0;
}
