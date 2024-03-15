#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdlib>

using namespace std;

class passwordManager {
private:
    unordered_map<string, string> users; // thats a way to store usernames and passwords

    // now use Caeser
    string encrypt(const string& password, int shift) {
        string encrypted = password;
        for (char& c : encrypted) {
            if (isalpha(c)) {
                c = (c + shift - 'a') % 26 + 'a';
            }
        }
        return encrypted;
    }

    // now decrypt Caeser
    string decrypt(const string& encrypted, int shift) {
        string decrypted = encrypted;
        for (char& c : decrypted) {
            if (isalpha(c)) {
                c = (c - shift - 'a' + 26) % 26 + 'a';
            }
        }
        return decrypted;
    }
// const string& is used to refer to a constant reference to a string so the function wouldnt modify the content of the string

public:
    void addUser(const string& username, const string& password) {
        // now encrypt before storing it
        users[username] = encrypt(password, 3);
    }

    bool authenticate(const string& username, const string& password) {
        if (users.find(username) != users.end() && decrypt(users[username], 3) == password) {
            return true;
        }
        return false;
    }

    void retrievePassword(const string& username) {
        if (users.find(username) != users.end()) {
            cout << "Retrieved password for user '" << username << "': " << decrypt(users[username], 3) << endl;
        } else {
            cout << "User'" << username << "' not found!" << endl;
        }
    }

    //void modifyPassword

};


//test push IDK


int main() {
    passwordManager manager;
    string username, password;
    string option;

    while (true) {
        cout << "Are you a user? (yes/no/exit): ";
        cin >> option;

        if (option == "yes") {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (manager.authenticate(username, password)) {
                cout << "authorized!\n";
                string action;
                while (true) {
                    cout << "Do you want to (retrieve/exit): ";
                    cin >> action;

                    if (action == "retrieve") {
                        manager.retrievePassword(username);
                    } else if (action == "exit") {
                        break;
                    } else {
                        cout <<"invalid option!\n";
                    }
                }
            } else {
                cout << "invalid username or password!\n";
            }
        } else if (option == "no") {
            cout << "Create a new user!\n";
            cout << "Enter new username: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;

            manager.addUser(username, password);
            cout << "User created!\n";
        } else if (option == "exit") {
            cout << "Ok!";
            break;
        } else {
            cout << "Invalid option!\n";
        }
    }





    return 0;
}













/* References
 * unordered_map https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
 * ctime https://cplusplus.com/reference/ctime/
 * cstdlib https://cplusplus.com/reference/cstdlib/
 *
 *
 *
 * */