#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, vector<string>> map;
unordered_map<string, vector<vector<int>>> output;

void pyramidScheme(string currentId){
    vector<int> choose = {1, stoi(map[currentId][map[currentId].size() - 1])};
    vector<int> dontChoose = {0, 0};
    vector<vector<int>> current = {{0, 0}, {0, 0}};
    
    for (int i = 0; i < (int)map[currentId].size() - 1; i++){
        pyramidScheme(map[currentId][i]);
        current = output[map[currentId][i]];
        
        if (current[0][0] > current[1][0]){
            choose[0] += current[1][0];
            choose[1] += current[1][1];
        }
        else if (current[0][0] < current[1][0]){
            choose[0] += current[0][0];
            choose[1] += current[0][1];
        }
        else if (current[0][1] < current[1][1]){
            choose[0] += current[1][0];
            choose[1] += current[1][1];
        }
        else{
            choose[0] += current[0][0];
            choose[1] += current[0][1];
        }
        
        dontChoose[0] += current[0][0];
        dontChoose[1] += current[0][1];
    }
    
    output[currentId] = {choose, dontChoose};
}

int main() {
    string line;
    while(getline(cin, line)){
        map = unordered_map<string, vector<string>>();
        output = unordered_map<string, vector<vector<int>>>();
        
        while(line != "-1"){
            vector<string> splitLine = vector<string>();
            
            size_t pos = 0;
            string space = " ";
            while ((pos = line.find(" ")) != string::npos) {
                splitLine.push_back(line.substr(0, pos));
                line.erase(0, pos + space.length());
            }
            splitLine.push_back(line);
            
            string id = splitLine[0];
            splitLine.erase(splitLine.begin());
            
            map[id] = splitLine;
            getline(cin, line);
        }
        
        pyramidScheme("0");
        
        if (output["0"][0][0] > output["0"][1][0])
            cout << output["0"][1][0] << " " << output["0"][1][1] << "\n";
        else if (output["0"][0][0] < output["0"][1][0])
            cout << output["0"][0][0] << " " << output["0"][0][1] << "\n";
        else if (output["0"][0][1] < output["0"][1][1])
            cout << output["0"][1][0] << " " << output["0"][1][1] << "\n";
        else
            cout << output["0"][0][0] << " " << output["0"][0][1] << "\n";
    }
}
