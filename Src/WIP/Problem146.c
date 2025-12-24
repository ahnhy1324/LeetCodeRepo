/* 
Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.
Implement the LRUCache class:
LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
int get(int key) Return the value of the key if the key exists, otherwise return -1.
void put(int key, int value) Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.
The functions get and put must each run in O(1) average time complexity.

Example 1:
Input
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, null, -1, 3, 4]
Explanation
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // cache is {1=1}
lRUCache.put(2, 2); // cache is {1=1, 2=2}
lRUCache.get(1);    // return 1
lRUCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
lRUCache.get(2);    // returns -1 (not found)
lRUCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
lRUCache.get(1);    // return -1 (not found)
lRUCache.get(3);    // return 3
lRUCache.get(4);    // return 4
Constraints:
1 <= capacity <= 3000
0 <= key <= 10^4
0 <= value <= 10^5
At most 2 * 10^5 calls will be made to get and put
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int gCapacity;
    unsigned int *key;
    unsigned int *Value;
    unsigned int *RecentlyUsedIndex;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* pResult = NULL;
    if( capacity <=0 )
    {
        //do nothing
    }
    else 
    {
        if( capacity > 3000) capacity = 3000;//clip to max capacity
        pResult = malloc(sizeof(LRUCache));
        pResult->gCapacity = capacity;
        pResult->key = malloc( sizeof(unsigned int) * capacity);
        pResult->Value = malloc( sizeof(unsigned int) * capacity);
        pResult->RecentlyUsedIndex = malloc( sizeof(unsigned int) * capacity);
        for( int i =0; i< capacity; i++)
        {
            pResult->key[i] = 0xFFFFFFFF;
            pResult->Value[i] = 0;
            pResult->RecentlyUsedIndex[i] = 0;
        }
    }
    return pResult;
}

int lRUCacheGet(LRUCache* obj, int key) {
    int result = -1;
    if( obj->gCapacity <=0 || obj == NULL)
    {
       // do nothing
    }
    else
    {
        if( obj->key != NULL && obj->Value != NULL)
        {
            int index = 0 ;
            index = key% obj->gCapacity;
            for( int i =0; i< obj->gCapacity; i++)
            {
                if( obj->RecentlyUsedIndex[i] < 0xFFFFFFFF)obj->RecentlyUsedIndex[i]++;
            }
            for( int i =0; i< obj->gCapacity; i++)
            {
                if( obj->key[( index + i ) % obj->gCapacity ] == key)
                {
                    result = obj->Value[( index + i ) % obj->gCapacity];
                    obj->RecentlyUsedIndex[( index + i ) % obj->gCapacity] = 0; 
                    break;
                }
            }
        }
    }
    return result;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    int MaxIndex = 0;
    int skipflg= 0;
    for( int i =0; i< obj->gCapacity; i++)
    {
        if( obj->RecentlyUsedIndex[i] < 0xFFFFFFFF)obj->RecentlyUsedIndex[i]++;
        if( obj->key[i] == key)
        {
            obj->Value[i] = value;
            obj->RecentlyUsedIndex[i] = 0;
            skipflg = 1;
        }
    }
    if (skipflg == 1)
    {
        /* code */
    }
    else
    {
        for( int i = 0; i< obj->gCapacity; i++)
        {
            if( obj->RecentlyUsedIndex[i] > obj->RecentlyUsedIndex[MaxIndex])
            {
                MaxIndex = i;
            }
        }
        obj->key[MaxIndex] = key;
        obj->Value[MaxIndex] = value;
        obj->RecentlyUsedIndex[MaxIndex] = 0;
    }
}

void lRUCacheFree(LRUCache* obj) {
    if( obj != NULL)
    {
        free(obj);
        obj = NULL;
    }
    return;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/