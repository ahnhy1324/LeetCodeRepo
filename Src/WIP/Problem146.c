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
#include <string.h> 
#define MIN_CAPACITY (1)
#define MAX_CAPACITY (3000)
#define MAX_KEY      (10000)
#define FAULT        (-1)
#define CLIP_CAPACITY(X)       X>MAX_CAPACITY? MAX_CAPACITY : X    

typedef struct  CacheList{
    struct CacheList * pHead;
    struct CacheList * pTail;
    int Key;
}CacheList_t;
typedef struct{
    int data;
    CacheList_t * backward;
}storage_t;
typedef struct {
    int MaxCapacity;
    int SetCounter;
    CacheList_t * Root;
    CacheList_t * LastUsed;
    storage_t * storage;
} LRUCache;

/// @brief Init and Malloc Key Table
/// @param pCache 
/// @param Capacity 
void InitCache( LRUCache* pCache, int Capacity)
{
    if( pCache != NULL)
    {
        memset(pCache , 0, sizeof(LRUCache));//초기화
        pCache->MaxCapacity = Capacity;
        pCache->storage = (storage_t *)malloc((sizeof(storage_t)) * (MAX_KEY+1));
        if(pCache->storage != NULL){
            for( int i = 0 ; i < MAX_KEY+1; i++)
            {
                pCache->storage[i].data = FAULT;
                pCache->storage[i].backward = NULL;
            }
        }
        pCache->Root = (CacheList_t *)malloc(sizeof(CacheList_t)*Capacity);
        if(pCache->Root!= NULL)
        {
            pCache->LastUsed = pCache->Root;
            for(int nCapacityIndex = 1 ; nCapacityIndex < Capacity; nCapacityIndex++)
            {
                pCache->Root[nCapacityIndex].Key=-1;
                pCache->Root[nCapacityIndex].pHead = &(pCache->Root[nCapacityIndex-1]);
                pCache->Root[nCapacityIndex].pTail = &(pCache->Root[nCapacityIndex+1]);
            }
            pCache->Root[0].pHead = &pCache->Root[Capacity-1];
            pCache->Root[0].Key=-1;
            if(Capacity>1)
            {
                pCache->Root[0].pTail = &(pCache->Root[1]);
            }
            pCache->Root[Capacity-1].pTail = NULL;
            pCache->Root[Capacity-1].Key = -1;
        }
    }
}

/// @brief Create Cache
/// @param int capacity ( Min : 1 Max: 3000) 
/// @return LRU Cache* Result
LRUCache* lRUCacheCreate(int capacity) {
    LRUCache * Result = NULL;
    if( capacity>= MIN_CAPACITY)
    {
        Result = (LRUCache*)malloc( sizeof(LRUCache));
        InitCache(Result,CLIP_CAPACITY(capacity));
    }
    return Result;
}

void lRUCacheUpdate( LRUCache* obj , int key )
{
    if(obj->storage[key].backward!=NULL)
    {
       CacheList_t * pTmpList = pTmpList = obj->storage[key].backward;
       if(pTmpList->pTail==NULL );//가장 최근 사용된 노드인경우
       else
       {
            CacheList_t * pLast =obj->LastUsed[0].pHead;  // 가장 최근 노드
            pLast->pTail = obj->storage[key].backward;//제일 최근 사용된 노드에 추가.
            
            if(obj->storage[key].backward == obj->LastUsed)//제일 마지막 사용된 노드면
            {
                obj->LastUsed = obj->LastUsed[0].pTail;//마지막 사용된 노드 업데이트

            }
            else
            {
                (pTmpList->pTail)->pHead = pTmpList->pHead;
                (pTmpList->pHead)->pTail = pTmpList->pTail;//최근 사용된 노드 앞뒤에 있는 노드 붙이기.
            }
            pTmpList->pHead = pLast;
            pTmpList->pTail = NULL;
            obj->LastUsed[0].pHead = pTmpList;
       }
    }
    return;
}


int lRUCacheGet(LRUCache* obj, int key) {
    int result = FAULT;
    if(obj == NULL) return result;
    if((key>FAULT)&&(key<=MAX_KEY))
    {
        result = obj->storage[key].data;
        if(obj->storage[key].data != FAULT)lRUCacheUpdate(obj,key);
    }
    return result;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if(obj!=NULL){
        if((obj->Root!=NULL)&&(obj->storage!=NULL)&&(obj->LastUsed!=NULL))
        {
            if( obj->storage[key].data!=-1)
            {
                obj->storage[key].data = value;
            }
            else
            {
                if(obj->LastUsed[0].Key > FAULT)
                {
                    obj->storage[obj->LastUsed[0].Key].data = -1;
                    obj->storage[obj->LastUsed[0].Key].backward = NULL;
                }
                obj->LastUsed[0].Key = key;
                obj->storage[obj->LastUsed[0].Key].data = value;
                obj->storage[obj->LastUsed[0].Key].backward = obj->LastUsed;
            }
            lRUCacheUpdate(obj,key);
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    if(obj == NULL) return;
    free(obj->Root);
    free(obj->storage);
    free(obj);
    return;
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/