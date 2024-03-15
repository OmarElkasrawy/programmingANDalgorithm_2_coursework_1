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

};


//test push IDK


int main() {

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