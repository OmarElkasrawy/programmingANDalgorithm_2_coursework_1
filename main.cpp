#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;

class passwordManager {
private:
    unordered_map<string, string> users; // that's a way to store usernames and passwords

    // now use Caeser
    string encrypt(const string& password, int shift) {
        string encrypted = password;
        for (char& c : encrypted) {
            if (isalnum(c)) { // encrypt alpha chars and digits
                char base = isupper(c) ? 'A' : (isdigit(c) ? '0' : 'a');
                c = ((c - base + shift) % 26) + base;
            } else {
                c = ((c - 33 + shift) % 94) + 33; //94 total number of ASCII symbols
            }
        }


        /*for (char& c : encrypted) {
            if (isalpha(c)) {
                c = (c + shift - 'a') % 26 + 'a';
            }
        }*/
        return encrypted;
    }

    // now decrypt Caeser
    string decrypt(const string& encrypted, int shift) {
        string decrypted = encrypted;
        for (char& c : decrypted) {
            if (isalnum(c)) { // decrypt alpha chars and digits
                char base = isupper(c) ? 'A' : (isdigit(c) ? '0' : 'a');
                c = ((c - base - shift + 26) % 26) + base;
            } else {
                c = ((c - 33 - shift + 94) % 94) + 33; //94 total number of ASCII symbols
            }
        }

        /*for (char& c : decrypted) {
            if (isalpha(c)) {
                c = (c - shift - 'a' + 26) % 26 + 'a';
            }
        }*/
        return decrypted;
    }

    string generateRandomPassword(){
        const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|;:,.<>?\"";
        const int length = 12;
        string password;
        srand(time(nullptr));
        for (int i = 0; i < length; ++i) {
            password += charset[rand() % charset.length()];
        }
        return password;
    }

// const string& is used to refer to a constant reference to a string so the function wouldnt modify the content of the string

public:
    void addUser(const string& username, const string& password) {
        // now encrypt before storing it
        users[username] = encrypt(password, 10);
    }

    bool authenticate(const string& username, const string& password) {
        if (users.find(username) != users.end() && decrypt(users[username], 10) == password) {
            return true;
        }
        return false;
    }

    void retrievePassword(const string& username) {
        if (users.find(username) != users.end()) {
            cout << "Retrieved password for user '" << username << "': " << decrypt(users[username], 10) << endl;
        } else {
            cout << "User'" << username << "' not found!" << endl;
        }
    }

    void retrieveAllUsernames() {
        if (users.empty()) {
            cout << "There are no stored users. Please create a user!" << endl;
        } else {
            cout << "Usernames and Passwords (encrypted) stored are:" << endl;
            for (const auto &pair: users) {
                cout << "Username: " << pair.first << " Encrypted password: " << pair.second << endl;
            }
        }
    }

    void modifyPassword(const string&username, const string& newPassword) {
        if (users.find(username) != users.end()) {
            // encrypt before storing
            users[username] = encrypt(newPassword, 10);
            cout << "Password for user '" << username << "' modified successfully!" << endl;
        } else {
            cout << "User '" << username << "' not found!" << endl;
        }
    }

    string generateAndReturnPassword() {
        return generateRandomPassword();
    }

};


//test push IDK


int main() {
    passwordManager manager;
    string username, password;
    string option;

    while (true) {
        cout << "Are you a user? (yes/no(create a user)/retrieve/exit): ";
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
                    cout << "Do you want to (retrieve/modify/generate(password)/exit): ";
                    cin >> action;

                    if (action == "retrieve") {
                        manager.retrievePassword(username);
                    } else if (action == "modify") {
                        string newPassword;
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        manager.modifyPassword(username, newPassword);
                    } else if (action == "generate") {
                        string generatedPassword = manager.generateAndReturnPassword();
                        cout << "Generated Password is: " << generatedPassword << endl;
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
        } else if (option == "retrieve") {
            manager.retrieveAllUsernames();
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