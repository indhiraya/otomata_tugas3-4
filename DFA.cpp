#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
#include <algorithm>

using json = nlohmann::json;
using namespace std;

int main(){
    ifstream file("tes.json");
    if(!file){
        cout << "File not found/Failed to open file" << endl;
        return 1;
    }

    json data;
    file >> data;

    vector<string> states = data["states"].get<vector<string>>();
    vector<string> alphabet = data["alphabet"].get<vector<string>>();
    string start_state = data["start_state"];
    vector<string> accept_states = data["accept_states"].get<vector<string>>();
    map<string, map<string, string>> transitions;
    for (auto& [state, trans] : data["transitions"].items()) {
        for (auto& [input, next_state] : trans.items()) {
            transitions[state][input] = next_state;
        }
    }

    string test_string = data["test_string"];
    vector<string> Path;
    string current_state = start_state;
    Path.push_back(current_state);

    for (char input : test_string) {
        string input_str(1, input);
        if (transitions[current_state].find(input_str) != transitions[current_state].end()) {
            current_state = transitions[current_state][input_str];
            Path.push_back(current_state);
        } else {
            cout << "Path: ";
            for (int i = 0; i < Path.size(); i++) {
                cout << Path[i];
                if (i < Path.size() - 1) cout << " -> ";
            }

            cout << endl;

            bool result = (find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end());
            cout << "Status: " << (result ? "ACCEPTED" : "REJECTED") << endl;
            return 1;
        }
    }

    cout << "Path: ";
    for (int i = 0; i < Path.size(); i++) {
        cout << Path[i];
        if (i < Path.size() - 1) cout << " -> ";
    }
    cout << endl;

    bool result = (find(accept_states.begin(), accept_states.end(), current_state) != accept_states.end());
    cout << "Status: " << (result ? "ACCEPTED" : "REJECTED") << endl;

    return 0;
}
