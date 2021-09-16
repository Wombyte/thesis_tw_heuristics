#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#ifndef INDEXEDLIST_H
#define INDEXEDLIST_H

class IndexedList {
    private:
    struct IndexedEntry {
        int value;
        int index;
    };
    vector<IndexedEntry> values;
    vector<IndexedEntry*> pointer;
    vector<int> pos;

    void updatePos() {
        for (int i = 0; i < pointer.size(); i++) {
            pos[pointer[i]->index] = i;
        }
    }

    public:
    IndexedList(vector<int>* list) {
        int length = list->size();
        values = vector<IndexedEntry> (length);
        pointer = vector<IndexedEntry*> (length);
        pos = vector<int> (length);
        for (int i = 0; i < length; i++) {
            values[i] = {list->at(i), i};
            pointer[i] = &values[i];
        }
        sort(0,length);
    }

    void sort(int startIndex, int endIndex) {
        std::sort(pointer.begin() + startIndex, pointer.begin() + endIndex, [](const IndexedEntry* a, const IndexedEntry* b) {
            if (a->value != b->value) {
                return a->value < b->value;
            } 
            return a->index < b->index;
        });
        updatePos();
    }

    int getValueAtPos(int pos) {
        return pointer[pos]->value;
    }
    int getIndexAtPos(int pos) {
        return pointer[pos]->index;
    }
    int getValueAtIndex(int index) {
        return values[index].value;
    }
    int getPositionOfIndex(int index) {
        return pos[index];
    }
    /* position could be invalidated by this method 
     * call sort() is recommanded
     */
    void setAtIndex(int index, int value) {
        values[index] = {value, index};
    }

    void print() {
        cout << "values: ";
        for (IndexedEntry e : values) {
            cout << "(" << e.value << "," << e.index << ") ";
        }
        cout << endl << "pointer: ";
        for (IndexedEntry* e : pointer) {
            cout << "(" << e->value << "," << e->index << ") ";
        }
        cout << endl << "pos: ";
        for (int p : pos) {
            cout << p << " ";
        }
        cout << endl;
    }

    void printOnlyValues() {
        for (IndexedEntry e : values) {
            cout << e.value << " ";
        }
        cout << endl;
    }
};

#endif