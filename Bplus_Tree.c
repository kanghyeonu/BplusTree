#include "project.h"

/*char symbols[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-',
				  '_', '=', '+', '{', '}', ';', ':', '\'', '\"', ',', '.',
				  '/', '<', '>', '?', '\0'};*/

/*void rm_Symbols(char* str){
	int i = 0;
	char* temp = str;
	char temp2[100] = {0, };
	for(; *str != '\0'; str++){
		if((0xAC00 <= *str && *str <= 0xD7A3) || (0x3131 <= *str && *str <= 0x318E))
			continue;
		else if ((0x61 <= *str || *str <= 0x7A) || (0x41 <= *str || *str <= 0x5A))
			continue;
		else if(0x30 <= *str || *str <= 0x39)
			continue;
		else
			*str = ' ';
	}
	char* merge = strtok(temp, " ");
	while(temp != NULL){
		strcat(temp2, merge);
		merge = strtok(NULL, " ");
	}
	str = temp2;
}*/

bpTree CreateBplusTree(){
    bpTree bptree;
    bptree.root = CreateNode();
    bptree.root->isleaf = true;
    bptree.head = bptree.root;

    return bptree;
}

bpNode* CreateNode(){
    bpNode* newNode = (bpNode*)malloc(sizeof(bpNode));
    newNode->isleaf = false;
    newNode->key_len = 0;
    newNode->childs_len = 0;
    newNode->parent = NULL;
    newNode->next = NULL;
    newNode->childs = (bpNode**)malloc(sizeof(bpNode*)*DEGREE);
    newNode->value = (Values**)malloc(sizeof(Values*)*(DEGREE-1));

    return newNode;
}
//flag false: start from root / true: start from node
void Insert(bpTree* tree, bpNode* node, char* key, int dir_num ,int doc_num, bool flag) {
    bpNode *root = tree->root;
    bpNode *curr = node;
	int key_hashed = HashFunc(key);
    int i, ptr_index = 0;

    //find collect leafnode
    if (!(flag)) {
        while (!(root->isleaf)) {
            //internal node is full
            if (root->key_len == DEGREE - 1) {
                //root not have parent
                if (root->parent == NULL) {
                    bpNode *newNode = CreateNode();
                    newNode->isleaf = false;
                    newNode->childs[newNode->childs_len] = root;
                    newNode->childs_len++;
                    root = Split(newNode, 0);
                    tree->root = root;
                }
                    //already have parent node
                else
                    root = Split(root->parent, ptr_index);
            }

            for (i = 0; i < root->key_len; i++) {
                //printf("%d ", root->keys[i]);
                //find index after compare the key value
                if (key_hashed  < root->keys[i]) {
                    ptr_index = i;
                    break;
                }
                //be inserted key value is larger than the every key value in root node
                if (i == root->key_len - 1) {
                    ptr_index = i + 1;
                    break;
                }
            }
            root = root->childs[ptr_index];
            //printf("\n");
        }
        //leaf is full
        if (root->key_len == DEGREE - 1) {
            if (root->parent == NULL) { //case no parent: make new parent node
                //printf("case 1.1 root is leaf && root keys are full\n\n");
                bpNode *newNode = CreateNode();    //create new node for split
                tree->root = newNode;            //newnode is root
                tree->root->isleaf = false;        //is not leaf
                tree->root->childs[tree->root->childs_len] = root;    //newnode's child
                tree->root->childs_len++;
                //leaf node's spliting is always childs empty
                root = Split(tree->root, 0); //split before insert
                //printf("split complete\n");
                Insert(tree, root, key , dir_num ,doc_num, true);   //Insert restart(recursive)
            }
            else
            {
                //already have parent node
                root = Split(root->parent, ptr_index);
                Insert(tree, root, key , dir_num ,doc_num, true);
            }
        }
        else
        { //is not full -> insertvalue
            InsertValue(root, key, dir_num ,doc_num);
        }
    }

        //re-search from the node (alreaddy split) this node's child is always leaf
    else
    {
        for (i = 0; i < curr->key_len; i++) {
            if (key_hashed <  curr->keys[i]) {
                curr = curr->childs[i];
                break;
            }
            //be inserted key value is larger than the every key value in root node
            if (i == curr->key_len - 1) {
                curr = curr->childs[i + 1];
                break;
            }
        }
        InsertValue(curr, key , dir_num ,doc_num);
    }
}

//node1 = will being parent node, index = position
bpNode* Split(bpNode* node1, int index){
    //printf("Split\n");
    bpNode* node2 = node1->childs[index];	//original node(spliting node)
    bpNode* node3 = CreateNode();	//will being node2's cousin

    //case 1 isleaf
    //in this case, split the leaf node and set the median value to parent node
    if(node2->isleaf){
        //node3->value = (Values**)malloc(sizeof(Values*) * (DEGREE - 1));
        //printf("node2 is leaf\n");
        node3->isleaf = node2->isleaf; //any node is leaf, then that's cousin is always leaf
        //printf("isleaf");
        node3->key_len = MIN_DEGREE;

        node2->parent = node1;
        node3->parent = node1;
        //leaf nodes are linkedlist
        if(node2->next != NULL)
            node3->next = node2->next;
        node2->next = node3;
        //copy node2's keys to node3
        int i;
        for(i = 0; i < MIN_DEGREE; i++){
            node3->keys[i] = node2->keys[i + MIN_DEGREE - 1];
        }
        node2->key_len = MIN_DEGREE - 1;
        //printf("node 2, 3 keys  process complete\n");

        //printf("copy node2's keys to node3\n");

        //values setting of parent node of node2 and node3
        for(i = 0; i < MIN_DEGREE; i++){
            node3->value[i] = node2->value[i + MIN_DEGREE - 1];
        }

    }
        //case 2 is not leaf
        //in this case, b tree split
    else{
        //printf("node2 is not leaf\n");
        node3->isleaf = node2->isleaf; //if node2 is not leaf, then that's cousin is not leaf
        node3->key_len = MIN_DEGREE - 1;

        node2->parent = node1;
        node3->parent = node1;

        //move node2's keys to node3
        int i;
        for(i = 0; i < MIN_DEGREE - 1; i++)
            node3->keys[i] = node2->keys[i+MIN_DEGREE];

        node2->key_len = MIN_DEGREE - 1;

        //move node2's childs to node3
        node2->childs_len = MIN_DEGREE;
        node3->childs_len = MIN_DEGREE;

        for(i = 0; i < MIN_DEGREE; i++){
            node3->childs[i] = node2->childs[i + MIN_DEGREE];
            node3->childs[i]->parent = node3;
        }
        //printf("node2, 3 keys and childs process complete");
    }
    //set the parent node's key
    //printf("set the parent node \n");
    int i;
    for(i = node1->key_len - 1; i >= index; i--)
        node1->keys[i+1] = node1->keys[i];
    //printf("key move comp\n");

    node1->keys[index] = node2->keys[MIN_DEGREE - 1];
    node1->key_len++;
    //printf("key insert comp\n");

    //set the parent node's cilhds
    for(i = node1->childs_len - 1; i > index; i--)
        node1->childs[i+1] = node1->childs[i];

    //printf("child move  comp\n");
    node1->childs[index+1] = node3;
    node1->childs_len++;

    return node1;
}

//insert the key to node
void InsertValue(bpNode* node,char* key,  int dir_num ,int doc_num){
	bpNode* leaf = node;
	int key_hashed = HashFunc(key);
    int keys_size = leaf->key_len;
    int i, j, index = 0;
    //printf("InsertValue\n");

    /*------------------------------------------------------*/
    //Inserttion is always at the leaf
    if(leaf->isleaf){
        //printf("node is leaf\n");
        //find the inserting index
        for(i = 0; i < keys_size; i++){
            //printf("node have any key, compare to %s\n", node->keys[i]);
			//printf("%d, %d\n", node->keys[i], key_hashed);

			// is collision??
            if(key_hashed == leaf->keys[i]){
				//printf("%d %d, collision\n", leaf->keys[i], key_hashed);
				Values* tempValues = CompareWord(leaf->value[i], key);
				//no duplicate -> newValue
				if(strcmp(tempValues->word, key)!=0 ){
					Values* newValue = CreateValues(key);
					newValue->head = CreateDocList(doc_num, dir_num);
					newValue->next = leaf->value[i]->next;
					leaf->value[i]->next = newValue;
				}
				//duplicate -> compare DocList
				else{
					DocList* tempDocList = CompareDocList(tempValues->head, doc_num);
					//no duplicate
					if(tempDocList->doc_num != doc_num ){
						DocList* newDocList = CreateDocList(doc_num, dir_num);
						newDocList->next = tempValues->head;
						tempValues->head = newDocList;
						tempValues->doc_List_size ++;
					}
					//duplicate
					else{
						tempDocList->cnt++;
					}
				}
                return;
            }
            else if(key_hashed > leaf->keys[i])
                continue;

            else {
                //printf("%d\n", index);
                break;
            }
        }
        index = i;
        //move pointer based on found index
        for(i = keys_size - 1; i >= index; i-- ){
            leaf->keys[i+1] = leaf->keys[i];
            leaf->value[i+1] = leaf->value[i];
        }

        //printf("key and value setting");
        leaf->keys[index] = key_hashed;
        leaf->key_len++;

        //key's value setting
		Values* newValues = CreateValues(key);
		DocList* newDocList = CreateDocList(doc_num, dir_num);
		newValues->head = newDocList;
        leaf->value[index] = newValues;
    }
        /*----------------------------------------------------------*/
    else{
        printf("b+tree is Inserted only leaf node\nerror\n");
        exit(1);
    }
}

void Search(bpTree* tree, char* key, double N){
	//printf(" search\n");
	int hashvalue = HashFunc(key);
	//printf(" make hashvalue, %d\n", hashvalue);
	bpNode* root = tree->root;
	int i, ptr_index;
	char* doc_number;
	while(!(root->isleaf)){
		for(i = 0; i < root->key_len; i++){
		//	printf("%d ", root->keys[i]);
			if (hashvalue  < root->keys[i]){ 
               root = root->childs[i];
			   break;
			}
			
            //be inserted key value is larger than the every key value in root node
       	 	if (i == root->key_len - 1 || hashvalue == root->keys[i]) {
				root = root->childs[i+1];
				break;
			}
		}
	}
	//printf("found leaf node\n");
	//need to checking duplicated 
	for(i = 0; i < root->key_len; i++){
		//printf("%d %d\n", root->keys[i], hashvalue);
		//compare hashvalue
		if(hashvalue == root->keys[i]){	//case exist in node
			//printf("same\n");
			Values* temp  = root->value[i];
			while(temp->next != NULL){
				if(strcmp(temp->word, key) == 0)
					break;
				else
					temp = temp->next;
			}
			//printf("%s, %s\n", temp->word, key);
			if(strcmp(temp->word, key) == 0){
				TF_IDF(temp, N);
				/*printf(" result: %s, number of the files: %d\n", temp->word, temp->doc_List_size);
				DocList* doclist = temp->head;
				for(i = 0; i < temp->doc_List_size; i++){
					doc_number = getDocNum(doclist->doc_num);
					printf("Directory_num: %d\t File Name: %s\t Frequency: %d\n", doclist->dir_num, doc_number, doclist->cnt);
					free(doc_number);
					doclist = doclist->next;
				}*/

				return;
			}
			else{
				break;
			}

		}
	}
	printf("no result: \" %s \"\n", key);
	return;
}

Values* CreateValues(char* word){
	Values* newValues = (Values*)malloc(sizeof(Values));
	char* newword = (char*)malloc(sizeof(char)*(strlen(word) + 1));
	strcpy(newword, word);
	newValues->word = newword;
	newValues->doc_List_size = 1;
	newValues->next = NULL;
	newValues->head = NULL;
	return newValues;
}

DocList* CreateDocList(int doc_num, int dir_num){
	DocList* newDocList = (DocList*)malloc(sizeof(DocList));
	newDocList->dir_num = dir_num;
	newDocList->doc_num = doc_num;
	newDocList->cnt = 1;
	newDocList->next = NULL;

	return newDocList;
}

Values* CompareWord(Values* values, char* key){
	Values* temp = values;
	while(temp->next !=  NULL){
		if(strcmp(temp->word, key) == 0)
			break;
		else
			temp = temp->next;
	}
	return temp;
}

DocList* CompareDocList(DocList* doclist, int doc_num){
	DocList* temp = doclist;
	while(temp->next != NULL){
		if(temp->doc_num == doc_num)
			break;
		else
			temp = temp->next;
	}
	return temp;
}

void PrintLeaf(bpTree* tree){
    bpNode* cur = tree -> head;
    int i;
    //printf("now tree's leaf\n");
    while(cur != NULL){
        for(i = 0; i < cur->key_len; i++)
            printf("%d ", cur->keys[i]);

        cur = cur->next;
        printf("//\t");
    }
    printf("\n");
}


