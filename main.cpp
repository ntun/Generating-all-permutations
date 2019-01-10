#include <iostream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>
using namespace std;

unordered_set<string> cache;

string value = "";

string old_value = "";

int factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial(n-1);
}

/* 2 print vector functions for debugging purposes if desired */
void printVector(vector<int> nums) {
    for (int i : nums) {
        cout << i << " ";
    }
    cout << endl;
}

void printVector(vector<bool> nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] == 1) {
            cout << i+1 << " ";
        }
    }
    cout << endl;
}

void print2dVector(vector< vector<int> > nums) {
    for (vector<int> i : nums) {
        cout << "[";
        for (int j : i) {
            cout << j << " ";
        }
        cout << "]";
    }
    cout << endl;
}


vector<vector<int>> helper(vector<int>& nums, int start_index, vector<int> entry,
        vector< vector<int> >& permutations, vector<bool> visited) {

    /* @param:
     *   - nums: array of integers
     *   - start_index: to choose the start node among nums
     *   - entry: 1d vector to store one permutation entry
     *   - permutations: 2d vector to store multiple permutation entries
     *   - visited: boolean array that serves as a characteristic function
     *       to keep track of what is already in the entry
     *
     * @return:
     *   - permutations: all possible permutations with a given
     *       start node
     */

    /* This function is a backtracking DFS algorithm that spans through
     * all possible Hamiltonian paths with a given start_index.
     */

    if (permutations.size() == factorial(nums.size() - 1)) {
        // since the start node is fixed,
        // total number of possible Hamiltonian path
        // with that start node is (n-1)!

        return permutations;
    }


    if (entry.empty()) {
        old_value = to_string(nums[start_index]);
        cout << "empty " << old_value << endl;
    }

    entry.push_back(nums[start_index]);

    value += to_string(nums[start_index]);

    visited[start_index] = true;
    cout << value << " (" << start_index << ") " << endl;

    if (entry.size() == nums.size() && cache.find(value) == cache.end()) {
        cout << value << " not found" << endl;
        permutations.push_back(entry);
        cache.insert(value);
        value = old_value;
        old_value = "";
    }

    if (cache.find(value) != cache.end()) {
        value = old_value;
        old_value = "";
    }

    for (int i = 0; i < nums.size(); i++) {
        if (visited[i] == 0) {
            helper(nums, i, entry, permutations, visited);
        }
    }

    return permutations;
}

vector<vector<int>> permute(vector<int>& nums) {

    /* Generating all permutations in nums[] vector can be translated
     * as generating all permutations of Hamiltonian paths in a complete
     * graph with the number of nodes equal to nums' size.
     */

    vector< vector<int> > permutations;
    vector< vector<int> > p; // permutation vector for different starting node
    vector<int> entry; // each permutation entry
    vector<bool> visited(nums.size());

    for (int i = 0; i < nums.size(); i++) {
        // initialize visited array to false values
        // since none of the nodes are visited at start
        visited[i] = 0;
    }

    for (int i = 0; i < nums.size(); i++) {
        // for loop to set different starting node

        p = helper(nums, i, entry, p, visited);
        // returns all permutations with starting value as nums[i]

        permutations.insert(permutations.end(), p.begin(), p.end());
        // append p to the whole permutations vector

        p = {}; // initialize p as empty vector for each starting value
    }

    return permutations;
}


int main() {
    vector<int> nums = {1, 1, 2};

    vector<vector<int>> permutations = permute(nums);

    print2dVector(permutations);
}