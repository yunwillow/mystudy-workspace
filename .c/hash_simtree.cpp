#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

// 键值对结构体
typedef struct Pair {
    char *key;
    int value;
    struct Pair *left;
    struct Pair *right;
} Pair;

// HashMap结构体
typedef struct {
    Pair *table[HASH_SIZE];
} HashMap;

// 哈希函数
unsigned int hash(const char *key) {
    unsigned int hash_value = 998;
    while (*key) {hash_value = (hash_value << 5) + *key++;}
    return hash_value % HASH_SIZE;
}

// 初始化HashMap
void init_hashmap(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        map->table[i] = NULL;
    }
}

// 创建新的键值对
Pair *create_pair(const char *key, int value) {
    Pair *new_pair = (Pair *)malloc(sizeof(Pair));
    if (new_pair == NULL) {return NULL;}
    
    new_pair->key = strdup(key);
    new_pair->value = value;
    new_pair->left = NULL;
    new_pair->right = NULL;
    
    return new_pair;
}

// 向二叉树插入键值对
Pair *insert_to_tree(Pair *root, Pair *new_pair) {
    if (root == NULL) return new_pair;
    
    int cmp = strcmp(new_pair->key, root->key);
    if (cmp < 0) {
        root->left = insert_to_tree(root->left, new_pair);
    } else if (cmp > 0) {
        root->right = insert_to_tree(root->right, new_pair);
    } else {   			// 键已存在，更新值
        root->value = new_pair->value;
        free(new_pair->key);
        free(new_pair);
    }
    
    return root;
}

// 向HashMap中添加键值对
void hashmap_put(HashMap *map, const char *key, int value) {
    unsigned int index = hash(key);
    Pair *new_pair = create_pair(key, value);
    if (new_pair == NULL) return;
    
    map->table[index] = insert_to_tree(map->table[index], new_pair);
}

// 在二叉树中查找键
Pair *search_in_tree(Pair *root, const char *key) {
    if (root == NULL) {
        return NULL;
    }
    
    int cmp = strcmp(key, root->key);
    if (cmp == 0) {
        return root;
    } else if (cmp < 0) {
        return search_in_tree(root->left, key);
    } else {
        return search_in_tree(root->right, key);
    }
}

// 从HashMap中获取值
int hashmap_get(HashMap *map, const char *key, int *value) {
    unsigned int index = hash(key);
    Pair *found = search_in_tree(map->table[index], key);
    
    if (found != NULL) {
        *value = found->value;
        return 1; // 找到
    }
    
    return 0; // 未找到
}

// 释放二叉树内存
void free_tree(Pair *root) {
    if (root == NULL) {
        return;
    }
    
    free_tree(root->left);
    free_tree(root->right);
    free(root->key);
    free(root);
}

// 释放HashMap内存
void free_hashmap(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        free_tree(map->table[i]);
        map->table[i] = NULL;
    }
}

// 打印二叉树内容（中序遍历）
void print_tree(Pair *root) {
    if (root == NULL) {
        return;
    }
    
    print_tree(root->left);
    printf("(%s: %d) ", root->key, root->value);
    print_tree(root->right);
}

// 打印HashMap内容
void print_hashmap(HashMap *map) {
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Bucket %d: ", i);
        print_tree(map->table[i]);
        printf("\n");
    }
}

int main() {
    HashMap map;
    init_hashmap(&map);
    
    // 添加一些键值对
    hashmap_put(&map, "apple", 10);
    hashmap_put(&map, "banana", 20);
    hashmap_put(&map, "orange", 30);
    hashmap_put(&map, "grape", 40);
    hashmap_put(&map, "pear", 50);
    hashmap_put(&map, "apple", 15); // 更新已存在的键
    
    // 打印HashMap内容
    printf("HashMap contents:\n");
    print_hashmap(&map);
    
    // 查找值
    int value;
    if (hashmap_get(&map, "banana", &value)) {
        printf("\nFound banana: %d\n", value);
    } else {
        printf("\nbanana not found\n");
    }
    
    if (hashmap_get(&map, "watermelon", &value)) {
        printf("Found watermelon: %d\n", value);
    } else {
        printf("watermelon not found\n");
    }
    
    // 释放内存
    free_hashmap(&map);
    
    return 0;
}










//Pair *insert_to_tree(Pair *root, Pair *new_pair) {
//    if (root == NULL) return new_pair;
//    Pair*current=root;
//    
//    for(;current!=NULL;){
//	    int cmp = strcmp(new_pair->key, root->key);
//	    if (cmp < 0) {
//	        if(current->left!=NULL){
//	        	current=current->left;
//	        	continue;
//			}else{
//				current->left=new_pair;
//				return root;
//			}
//	    } else if (cmp > 0) {
//	        if(current->right!=NULL){
//	        	current=current->right;
//	        	continue;
//			}else{
//				current->right=new_pair;
//				return root;
//			}
//	    } else {   			// 键已存在，更新值
//	        root->value = new_pair->value;
//	        free(new_pair->key);
//	        free(new_pair);
//	        break;
//	    }
//	}
//    
//    return root;
//}
