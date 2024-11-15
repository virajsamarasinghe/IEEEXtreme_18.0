//Task Score: 60%
//Did you do more than us committe to it in this repo

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class RestaurantPathFinder {
private:
    vector<vector<int>> adjacency_list;
    vector<int> star_ratings;
    int max_path_length;
    int num_cities;
    
    void dfs(int city, int parent, vector<int>& current_path) {
        if (current_path.capacity() < star_ratings.size()) {
            current_path.reserve(star_ratings.size());
        }
        
        auto position = lower_bound(current_path.begin(), current_path.end(), star_ratings[city]);
        bool inserted = false;
        
        if (position == current_path.end()) {
            current_path.push_back(star_ratings[city]);
            inserted = true;
        } else {
            int original_value = *position;
            *position = star_ratings[city];
            max_path_length = max(max_path_length, (int)current_path.size());
            
            for (const int& neighbor : adjacency_list[city]) {
                if (neighbor != parent) {
                    dfs(neighbor, city, current_path);
                }
            }
            
            *position = original_value;
            return;
        }
        
        max_path_length = max(max_path_length, (int)current_path.size());
        
        for (const int& neighbor : adjacency_list[city]) {
            if (neighbor != parent) {
                dfs(neighbor, city, current_path);
            }
        }
        
        if (inserted) {
            current_path.pop_back();
        }
    }

public:
    RestaurantPathFinder(int size) : num_cities(size), max_path_length(0) {
        adjacency_list.resize(size);
        star_ratings.resize(size);
    }
    
    void setStarRating(int index, int value) {
        star_ratings[index] = value;
    }
    
    void addConnection(int city1, int city2) {
        adjacency_list[city1].push_back(city2);
        adjacency_list[city2].push_back(city1);
    }
    
    int findLongestRestaurantPath() {
        vector<int> current_path;
        current_path.reserve(num_cities); 
        
        for (int i = 0; i < num_cities; i++) {
            if (adjacency_list[i].size() == 1) { 
                dfs(i, -1, current_path);
            }
        }
        
        return max_path_length;
    }
};

int main() {
    ios_base::sync_with_stdio(false);  
    cin.tie(nullptr);
    
    int num_cities;
    cin >> num_cities;
    
    RestaurantPathFinder finder(num_cities);
    
    for (int i = 0; i < num_cities; i++) {
        int star_rating;
        cin >> star_rating;
        finder.setStarRating(i, star_rating);
    }
    
    for (int i = 0; i < num_cities - 1; i++) {
        int city1, city2;
        cin >> city1 >> city2;
        finder.addConnection(--city1, --city2);
    }
    
    cout << finder.findLongestRestaurantPath() << endl;
    
    return 0;
}
