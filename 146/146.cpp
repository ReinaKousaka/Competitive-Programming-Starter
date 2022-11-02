#include <unordered_map>
#include <list>
using namespace std;

class LRUCache {
public:
    list<int> cached_keys;      // keys
    unordered_map<int, list<int>::iterator> mp_it;     // key --> iterator
    unordered_map<int, int> mp_val;     // key --> value
    int capacity;

    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (mp_it.find(key) == mp_it.end()) {
            return -1;
        } else {
            // move iterator mp_it[key] to front
            cached_keys.splice(cached_keys.begin(), cached_keys, mp_it[key]);
            return mp_val[key];
        }
    }
    
    void put(int key, int value) {
        mp_val[key] = value;
        if (mp_it.find(key) == mp_it.end()) {
            cached_keys.push_front(key);
            mp_it.insert({key, cached_keys.begin()});
            if (cached_keys.size() > capacity) {
                mp_it.erase(cached_keys.back());   // last one is the least used one
                cached_keys.pop_back();
            }
        } else {
            // move iterator mp[key] to front
            cached_keys.splice(cached_keys.begin(), cached_keys, mp_it[key]);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */