#include <iostream>
#include <string>
#include <set> // Для использования set
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
                                                                //задача 1
    string input;
    cout << "[IN]:";
    getline(cin, input); // Считывание строки
    
    unordered_map<char, int> count; 
    
    for (char c : input) {
        count[c]++;
    }
    
    vector<pair<char, int>> alt_count(count.begin(), count.end());
    
    
    sort(alt_count.begin(), alt_count.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first > b.first;
        }
    });
    
    cout << "[OUT]:" << endl;
    for (const auto& p : alt_count) {
        cout << p.first << ": " << p.second << endl;
    }
                                                                 //задача 2
    
    int n;
    cin >> n;
    set<int, greater<int>> unique_numbers;
    
    cout << "[IN]:" << endl;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        unique_numbers.insert(num);
    }
    
    cout << "[OUT]:" << endl;
    for (int num : unique_numbers) {
        cout << num << endl;
    }
    return 0;   
}