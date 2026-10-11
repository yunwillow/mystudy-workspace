#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 哈希节点结构（链地址法）
typedef struct Node {
    char* key;          // 键（字符串）
    int value;          // 值
    struct Node* next;  // 指向下一个节点的指针
} Node;

// 哈希表主体结构
typedef struct {
    Node** buckets;     //Node* head[n]       存储桶数组（指向链表头节点）
    int capacity;       // 总容量（建议为质数）
    int size;           // 当前元素数
} HashMap;


unsigned long hash_function(const char* key, int capacity) {
    unsigned long hash = 998;  // 初始种子
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return hash % capacity;
}


HashMap* createHashMap(int capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->capacity = capacity;
    map->size = 0;
    map->buckets = (Node**)calloc(capacity, sizeof(Node*));  // 初始化空链表
    return map;
}


void put(HashMap* map, const char* key, int value) {
    unsigned long index = hash_function(key, map->capacity);
    Node* current = map->buckets[index];

    // 遍历链表查找键
    while (current) {
        if (strcmp(current->key, key) == 0) {
            current->value = value;  // 更新值
            return;
        }
        current = current->next;
    }

    // 插入新节点（头插法）
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);  // 复制键（避免野指针）
    newNode->value = value;
    newNode->next = map->buckets[index];
    map->buckets[index] = newNode;
    map->size++;
}


int get(HashMap* map, const char* key,int*i) {
	*i=0;
    unsigned long index = hash_function(key, map->capacity);
    Node* current = map->buckets[index];
    while (current) {
    	*i+=1;
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;  // 未找到
}


void mapdelete(HashMap* map, const char* key) {
    unsigned long index = hash_function(key, map->capacity);
    Node* current = map->buckets[index];
    Node* prev = NULL;
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free(current->key);  // 释放键内存
            free(current);       // 释放节点内存
            map->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}


void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        Node* current = map->buckets[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}


int main() {
	int i;
    HashMap* map = createHashMap(10);
    put(map, "apple", 1);
    put(map, "banana", 2);
    put(map, "applo", 3);
    printf("apple: %d\n", get(map, "apple",&i));  // 输出: apple: 1
    printf("   %d\n",i);
    mapdelete(map, "banana");
    printf("banana: %d\n", get(map, "banana",&i));  // 输出: banana: -1
    printf("   %d\n",i);
    printf("applo: %d\n", get(map, "applo",&i));
    printf("   %d\n",i);
    freeHashMap(map);
    return 0;
}

//unsigned long hash_function;
//HashMap* createHashMap;
//void put(HashMap* map, const char* key, int value);
//int get(HashMap* map, const char* key,int*i);
//void mapdelete(HashMap* map, const char* key);
//void freeHashMap(HashMap* map);










