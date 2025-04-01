#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>
using json = nlohmann::json;
using namespace std;

int main() {
    ifstream file("tes.json");
    if (!file) {
        cout << "File not found/Failed to open file" << endl;
        return 1;
    }

    json data;
    file >> data;

    vector<string> states = data["states"].get<vector<string>>();
    map<string, map<string, pair<string, string>>> transitions;
    for (auto& [state, trans] : data["transitions"].items()) {
        for (auto& [input, next_info] : trans.items()) {
            transitions[state][input] = {next_info["next_state"], next_info["output"]};
        }
    }
    
    string initial_state = data["initial_state"];
    string input_sequence = data["input_sequence"];
    string current_state = initial_state;
    string path = current_state;
    string output_sequence;
    
    for (char input : input_sequence) {
        string input_str(1, input);
        if (transitions[current_state].count(input_str)) {
            auto [next_state, output] = transitions[current_state][input_str];
            output_sequence += output;
            current_state = next_state;
            path += " → " + current_state;
        } else {
            cout << "Invalid input encountered." << endl;
            return 1;
        }
    }

    cout << "Path: " << path << endl;
    cout << "Output: " << output_sequence << endl;
    
    return 0;
}
