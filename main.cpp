#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

struct User {
    string name;
    string email;
    vector<string> allergies;
};

struct Restaurant {
    string name;
    vector<string> safeForAllergies;
};

vector<User> users;
vector<Restaurant> restaurants = {
    {"Joe's Diner", {"peanuts", "dairy"}},
    {"Green Bowl", {"gluten", "soy"}},
    {"Ocean Bites", {"shellfish", "eggs"}},
    {"Happy Veggie", {"peanuts", "gluten", "dairy"}}
};

// Helper to convert input to lowercase
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void showBenefits() {
    cout << "Create an account to save your allergy profile and search safe restaurants.\n"; // IH#1
}

User registerUser() {
    User user;
    cout << "Enter your name: ";
    getline(cin, user.name);
    cout << "Enter your email: ";
    getline(cin, user.email);
    // IH#2: Explain costs
    cout << "⚠️ Your email is needed to save your profile.\n";
    users.push_back(user);
    return user;
}

void setupAllergyProfile(User &user) {
    cout << "\nSelect your allergies (type 'done' to finish):\n";
    vector<string> available = {"peanuts", "shellfish", "dairy", "gluten", "eggs", "soy"};

    for (const string &a : available) {
        cout << "- " << a << "\n";
    }

    string input;
    while (true) {
        cout << "Allergy: ";
        getline(cin, input);
        input = toLower(input);
        if (input == "done") break;
        if (find(available.begin(), available.end(), input) != available.end()) {
            user.allergies.push_back(input);
        } else {
            cout << "Unknown allergy.\n";
        }
    }

    // IH#3: Let users see as much info as they want
    cout << "You selected: ";
    for (const string &a : user.allergies) cout << a << " ";
    cout << "\n";
}

bool isSafe(const Restaurant &r, const vector<string> &allergies) {
    for (const string &a : allergies) {
        if (find(r.safeForAllergies.begin(), r.safeForAllergies.end(), a) == r.safeForAllergies.end()) {
            return false;
        }
    }
    return true;
}

void searchRestaurants(const User &user) {
    cout << "\nSearching restaurants safe for your allergies...\n";
    bool found = false;
    for (const Restaurant &r : restaurants) {
        if (isSafe(r, user.allergies)) {
            found = true;
            cout << "✅ " << r.name << " (Safe for: ";
            for (const string &a : r.safeForAllergies) cout << a << " ";
            cout << ")\n";
        }
    }

    if (!found) {
        cout << "⚠️ No restaurants matched your allergy profile.\n";
    }
}

void runApp() {
    showBenefits(); // IH#1
    User user = registerUser();
    cout << "\n--- Step 1: Set Your Allergy Profile ---\n"; // IH#6: Explicit path
    setupAllergyProfile(user);

    string choice;
    while (true) {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Search Restaurants\n";
        cout << "2. Update Allergies\n";
        cout << "3. Exit\n"; // IH#5: Backtracking available
        cout << "Choice: ";
        getline(cin, choice);

        if (choice == "1") {
            searchRestaurants(user);
        } else if (choice == "2") {
            setupAllergyProfile(user); // IH#7: Try different approaches
        } else if (choice == "3") {
            break;
        } else {
            cout << "Invalid input.\n";
        }
    }
}

int main() {
    cout << "🌟 Welcome to AllergySafeEats 🌟\n"; // IH#4: Familiar design
    runApp();
    cout << "Thanks for using our app. Stay safe and enjoy your meal! 🍽️\n"; // IH#8: Encouraging mindfulness
    return 0;
}

