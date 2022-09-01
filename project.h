#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define DEGREE 6
#define MIN_DEGREE 3
#define DIVISOR 100000037

/*
 * -- B+Tree descripton -- *
 * b+tree internal node can have DEGREE/2 to DEGREE children
 * b+tree internal node can have (DEGREE/2 - 1) to DEGREE - 1 Keys
 * b+tree have to satisfy the following DEGREE = 2*t - 1 (t = (min children))
 *
 * except root and leaf
 * when DEGREE 6
 * internal node can have 3 to 6 children
 * internal node can have 2 to 5 keys
 * t = (DEGREE + 1) / 2 = 3 -> MIN_DEGREE
 */

typedef struct bplustreeNode{
    bool isleaf; 		//leaf or internal
    int key_len; 		//number of keys in Node
    int childs_len;		//number of childern in Node
    int keys[DEGREE-1]; //keys array
    struct bplustreeNode** childs;		//childs array
    struct bplustreeNode* parent;
    struct bplustreeNode* next;			//bptree's leaves are linkedlist
    struct ValueList** value;
}bpNode;

typedef struct bpTree{
    struct bplustreeNode* root;
    struct bplustreeNode* head;
}bpTree;

typedef struct ValueList{
    char* word;			//word
    int doc_List_size;	//number of doc
	struct ValueList* next; //chaining
    struct doc_List* head;	//info of doc
	
}Values;

typedef struct doc_List{
	int dir_num;
    int doc_num;
    int cnt;
    struct doc_List* next;
}DocList;

typedef struct TF_IDF{
	int dir_num;
	int index;
	int cnt;
	double w;
	struct TF_IDF* next;
}tf_idf;

//void rm_Symbols(char*);
//html files load
double LoadFiles(bpTree* tree);

//Bplus Tree methods
bpTree CreateBplusTree();
bpNode* CreateNode();
void Insert(bpTree* tree, bpNode* node, char* key ,int dir_num ,int doc_num, bool flag);
bpNode* Split(bpNode* node, int index);
void InsertValue(bpNode* node, char* key, int dir_num,int doc_num);
void PrintLeaf(bpTree* tree);
void Search(bpTree* tree ,char* key, double N);

Values* CreateValues(char* word);
DocList* CreateDocList(int doc_num, int dir_num);
Values* CompareWord(Values* values, char* key);
DocList* CompareDocList(DocList* doclist, int doc_num);

//hash methods
int HashFunc(char *str);
//table read
char* getDocNum(int index);
//TF_IDF methods
void TF_IDF(Values* values, double N);
tf_idf* CreateTF_IDF(int idr_num, int index, int cnt, double w);
tf_idf* InsertTF_IDF(tf_idf* head, tf_idf* value);
