📝 Smart Event Manager (CLI Version)
📌 Overview

Smart Event Manager is a C++ command-line application for managing users and their events.
It supports user registration, login, event scheduling, reminders, and analytics.
Admins can manage users and monitor events system-wide.

⚡ Features
👤 User Management

Register, login, reset password

View personal events

Search, analytics, timeline

📅 Event Management

Add, edit, delete events

View events by date or today

Search events by keyword

Undo last change

🔑 Admin Functions

Admin login (admin / admin123)

List all users

Delete users

Send reminders to all users

🚀 Usage

Compile with:

g++ main.cpp UserManager.cpp EventManager.cpp -o event_manager


Run commands as:

./event_manager <command> [arguments...]

🔧 Commands
👤 User Commands
./event_manager register <username> <password> <email>
./event_manager login <username> <password>
./event_manager reset-password <username> <newpassword>

📅 Event Commands
./event_manager add-event <username> <password> <name> <date> <time> <type> <location> <recurrence>
./event_manager view-events <username> <password>
./event_manager view-today <username> <password>
./event_manager view-date <username> <password> <dd-mm-yyyy>
./event_manager search <username> <password> <keyword>
./event_manager analytics <username> <password>
./event_manager timeline <username> <password>

🔑 Admin Commands
./event_manager list-users
./event_manager delete-user <username>

✅ Example Workflow
./event_manager register alice 1234 alice@mail.com
./event_manager add-event alice 1234 "Birthday Party" 25-12-2025 18:00 party Home none
./event_manager view-events alice 1234
./event_manager search alice 1234 party


⚡ Tip: User data is stored in users.txt, and each user has their own <username>_events.txt.
