#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <limits.h>
// 键值对节点结构体 
typedef struct Node {  
	char *key; // 键，这里假设是字符串类型  
	int value; // 值  
	struct Node *next; // 指向下一个节点的指针 
} Node;


// 哈希表结构体 
typedef struct HashTable {  
	Node **buckets; // 桶数组  
	int size; // 当前键值对数量  
	int capacity; // 当前桶数量 
} HashTable;


// DJB2哈希算法 
unsigned int hash_function(const char *key, int capacity) {  
	unsigned long hash = 5381; // 魔法种子值  
	int c;
	while ((c = *key++)) {  hash = ((hash << 5) + hash) + c; } // 等效于 hash * 33 + c 
	return (unsigned int)(hash % capacity); // 取模确保在数组范围内 
}


// 创建并初始化哈希表 
HashTable *create_hash_table(int initial_capacity) {  
	HashTable *table = ( HashTable *)malloc( sizeof( HashTable ) );  
	if ( !table ) {  
		printf( "内存分配失败！\n" );  
		return NULL;  
	}
// 确保容量是2的幂次，提高哈希效率  
	table->capacity = 1;  
	while ( table->capacity < initial_capacity ) {  table->capacity *= 2;  }
	table->buckets = ( Node ** )malloc( table->capacity * sizeof( Node * ) );  
	if ( !table->buckets ) {  
		free( table );  
		printf( "内存分配失败！\n" );  
		return NULL;  
	}
	// 初始化所有桶为空  
	for ( int i = 0; i < table->capacity; i++ ) {  table->buckets[i] = NULL;  }
	table->size = 0;
	return table; 
}



void insert( HashTable *table, const char *key, int value ) {  // 将键值对插入哈希表 
	if ( !table || !key ) {  return;  }
// 检查是否需要扩容  
	if ( (double)table->size / table->capacity >= 0.75 ) {  
		int new_capacity = table->capacity * 2;  
		Node **new_buckets = ( Node ** )malloc( new_capacity * sizeof( Node * ) );
		if ( !new_buckets ) {  
			printf( "扩容内存分配失败！\n" );  
			return;  
		}
// 初始化新桶数组  
		for ( int i = 0; i < new_capacity; i++ ) {  new_buckets[i] = NULL;  }
// 将旧桶中的所有元素重新哈希到新桶  
		for ( int i = 0; i < table->capacity; i++ ) {  
			Node *current = table->buckets[i];  
			while ( current ) {  
				Node *next = current->next;  
				unsigned int new_index = hash_function( current->key, new_capacity );  
				current->next = new_buckets[new_index];  
				new_buckets[new_index] = current;  
				current = next;  
			}  
		table->buckets[i] = NULL;  // 清空旧桶 
		}
// 更新哈希表信息  
		free( table->buckets );  
		table->buckets = new_buckets;  
		table->capacity = new_capacity;  
	}
// 计算当前键的哈希值  
	unsigned int index = hash_function( key, table->capacity );
// 创建新节点  
	Node *new_node = ( Node *)malloc( sizeof( Node ) );  
	if ( !new_node ) {  
		printf( "内存分配失败！\n" );  
		return;  
	}
// 复制键字符串  
	new_node->key = strdup( key );  
	if ( !new_node->key ) {  
		free( new_node );  
		printf( "内存分配失败！\n" );  
		return;  
	}
	for(Node*current=table->buckets[index];current!=NULL;current=current->next){
		if(strcmp(current->key,key)==0){
			current->value=value;
			return;
		}
	}
	new_node->value = value;  
	new_node->next = table->buckets[index]; // 头插法
// 将新节点插入到对应桶的链表头部  
	table->buckets[index] = new_node;  
	table->size++; 
}


// 根据键查找对应的值 
int find( HashTable *table, const char *key ) {  
	if ( !table || !key ) {  return INT_MIN;   }// 假设不存在的值返回INT_MIN
// 计算键的哈希值  
	unsigned int index = hash_function( key, table->capacity );
// 遍历对应桶的链表查找键  
	Node *current = table->buckets[index];  
	while ( current ) {  
		if (strcmp(current->key, key) == 0 ) {  return current->value;   }  // 找到键，返回值
		current = current->next;  
	}
	return INT_MIN; // 未找到键，返回默认值 
}


// 根据键删除对应的键值对 
void delete_key( HashTable *table, const char *key ) {  
	if ( !table || !key ) {  return;  }
// 计算键的哈希值  
	unsigned int index = hash_function( key, table->capacity );
// 遍历对应桶的链表查找键  
	Node *current = table->buckets[index];  
	Node *prev = NULL;
	while ( current ) {  
		if (strcmp(current->key, key) == 0 ) {  
		// 找到键，进行删除  
			if ( prev ) {  prev->next = current->next;  } 
			else {  table->buckets[index] = current->next;  }
// 释放节点内存和键字符串内存  
			free( current->key );  
			free( current );
			table->size-=1;  
			return;  
		}
		prev = current;  
		current = current->next;  
	}
// 未找到键，无需操作  
	return; 
}


// 销毁哈希表，释放所有内存 
void destroy_hash_table( HashTable *table ) {  
	if ( !table ) {  return;  }
// 遍历所有桶，释放每个链表中的节点  
	for ( int i = 0; i < table->capacity; i++ ) {  
		Node *current = table->buckets[i];  
		while ( current ) {  
			Node *next = current->next;  
			free( current->key ); // 释放键字符串内存  
			free( current ); // 释放节点内存  
			current = next;  
		}  
		table->buckets[i] = NULL;  
	}
	free( table->buckets ); // 释放桶数组内存  
	free( table ); // 释放哈希表结构体内存 
}
// 测试函数 
int main() {  
	HashTable *table = create_hash_table(16);// 创建哈希表
	
	insert(table, "apple", 10);  insert(table, "banana", 20);  
	insert(table, "cherry", 30);// 插入一些键值对
	
	printf("apple的值是: %d\n", find(table, "apple"));  
	printf("banana的值是: %d\n", find(table, "banana"));  
	printf("未存在的键的值是: %d\n", find(table, "grape"));// 查找并打印值
	
	delete_key(table, "banana");// 删除一个键值对
	printf("删除后banana的值是: %d\n", find(table, "banana"));// 再次查找已删除的键
	destroy_hash_table(table);// 销毁哈希表
	return 0; 
} 
