#include "UserManager.h"
#include "EventManager.h"

int main() {
    UserManager userManager;
   
// menu no 1
while(true){
    User* currentUser = nullptr;
    bool isAdmin = false;

    while (!currentUser && !isAdmin) {
        cout << "\n==== Welcome to Smart Event Manager ====\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Admin Login\n";
        cout << "4. View All Users (Admin only)\n";
        cout << "0. Exit Program\n";
        cout << "Choice: ";
        int choice; cin >> choice;

        string uname, pass, email;
        switch (choice) {
            case 1: // Login
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pass;
                currentUser = userManager.loginUser(uname, pass);
                if (!currentUser) cout << "❌ Invalid credentials!\n";
                break;
            case 2: // Register
                cout << "Enter username: "; cin >> uname;
                cout << "Enter password: "; cin >> pass;
                cout << "Enter email: "; cin >> email;
                userManager.registerUser(uname, pass, email);
                break;
            case 3: // Admin Login
                cout << "Admin Username: "; cin >> uname;
                cout << "Admin Password: "; cin >> pass;
                if (uname == "admin" && pass == "admin123") {
                    isAdmin = true;
                } else {
                    cout << "❌ Wrong admin credentials!\n";
                }
                break;
            case 4: // View All Users (Admin only)
                if (isAdmin)
                {
                    auto allUsers = userManager.getAllUsers();
                    cout << "\n=== All Registered Users ===\n";
                    for (const auto &u : allUsers)
                    {
                        cout << "Username: " << u.username
                             << ", Email: " << u.email
                             << ", Events File: " << u.eventsFile << "\n";
                    }
                }
                else
                {
                    cout << "❌ Only admin can view all users!\n";
                }
                break;
            case 0: // Exit
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "❌ Invalid choice!\n";
        }
    }

    // Load EventManager based on user type
    EventManager manager(isAdmin ? "admin_events.txt" : currentUser->eventsFile,isAdmin ? "admin@system.com" : currentUser->email);

// menu no 2
    // === Main Menu Loop ===
    while (true) {
        cout << "\n==== Smart Event Manager ====\n";
        cout << "1. View All Events\n";
        cout << "2. View Today's Events\n";
        cout << "3. Search Event\n";
        cout << "4. Timeline (today)\n";
        cout << "5. Analytics\n";

        if (isAdmin) {
            cout << "--- Admin Options ---\n";
            cout << "6. Add Event\n";
            cout << "7. Edit Event\n";
            cout << "8. Delete Event\n";
            cout << "9. Send Reminders\n";
            cout << "10. Undo Last Action\n";
        } else {
            cout << "--- User Options ---\n";
            cout << "6. Add Event\n";
            cout << "7. Edit Event\n";
            cout << "8. Delete Event\n";
        }
        cout << "99. Logout\n"; // ✅ NEW
        cout << "0. Exit Program\n";

        int choice;
        cout << "Choice: "; cin >> choice; cin.ignore();

        // ✅ shared features
        switch (choice) {
            case 1: manager.viewEvents(); break;
            case 2: manager.viewToday(); break;
            case 3: {
                string key;
                cout << "Enter keyword: "; cin >> key;
                manager.searchEvent(key);
                break;
            }
            case 4: manager.timeline(); break;
            case 5: manager.analytics(); break;

            // ✅ available to both
            case 6: manager.addEvent(); break;
            case 7: manager.editEvent(); break;
            case 8: manager.deleteEvent(); break;

            // ✅ admin-only features
            case 9:
                if (isAdmin)
                {
                    // Admin can send reminders for all users
                    auto all = userManager.getAllUsers();
                    for (auto &u : all)
                    {
                        EventManager em(u.eventsFile);
                        em.sendReminders(u.email);
                    }
                }
                else
                {
                    // Normal user only gets their own reminders
                    manager.sendReminders(currentUser->email);
                }
                break;

            case 10: if (isAdmin) manager.undoLast();
                     else cout << "❌ Not allowed!\n"; 
                     break;

            case 0: return 0;
            default: cout << "❌ Invalid choice!\n";
        }
    }
LOGOUT:;
}
}
