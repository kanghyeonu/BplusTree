#include "project.h"

void TF_IDF(Values* values, double N) {
	Values* value = values;
	DocList* doclist = value->head;
	//printf("%f\n", N);
	if(value->doc_List_size == 1){
		char* file_name = getDocNum(doclist->doc_num);
		printf(" result: %s number of files: %d\n", value->word, value->doc_List_size);
		printf(" Directory Number: %d\tFile Name: %s\t frequency: %d\n", doclist->dir_num, file_name, doclist->cnt);
		free(file_name);
		return;
	}

	//natural logarithm
	int size = value->doc_List_size;

	while(doclist->next != NULL){
		doclist = doclist->next;
	}
	doclist = value->head;

	tf_idf* head = CreateTF_IDF(doclist->dir_num, doclist->doc_num, doclist->cnt ,doclist->cnt*log10((double)N/(1+size)));

	tf_idf* temp;
	
	printf(" result: %s number of files: %d\n", value->word, value->doc_List_size);
	//printf("%d, %d, %d, %f\n",head->dir_num, head->index, head->cnt, head->w );
	
	//sort linkedlist based on weight
	doclist = doclist->next;
	while(doclist->next != NULL){
		temp = CreateTF_IDF(doclist->dir_num, doclist->doc_num, doclist->cnt, doclist->cnt*log10((double)N/(1+size))); 
		//printf("%f ", temp->w);
		head = InsertTF_IDF(head, temp);
		doclist = doclist->next;
	}
	temp = CreateTF_IDF(doclist->dir_num, doclist->doc_num, doclist->cnt,doclist->cnt*log10((double)N/(1+size)));
	head =InsertTF_IDF(head, temp);
	temp = head;

	//print
	char* filename;	
	while(temp->next != NULL){
		filename = getDocNum(temp->index);
		printf(" Directory Number: %d\tFile Name: %s\tfrequency: %d\tW: %f\n", temp->dir_num, filename, temp->cnt, temp->w);
		temp = temp->next;
		free(filename);
	}
	filename = getDocNum(temp->index);
	printf(" Directory Number: %d\tFile Name: %s\tfrequency: %d\tW: %f\n", temp->dir_num, filename, temp->cnt, temp->w);
	free(filename);

	//tf_idfs free
	temp = head;
	while(temp->next != NULL){
		head = temp;
		temp = temp->next;
		free(head);
	}
	free(temp);
}

tf_idf* CreateTF_IDF(int dir_num ,int index,int cnt ,double w){
	//printf("create tf idf\n");
	tf_idf* newtf_idf = (tf_idf*)malloc(sizeof(tf_idf));
	newtf_idf->dir_num = dir_num;
	newtf_idf->index = index;
	newtf_idf->w = w;
	newtf_idf->cnt = cnt;
	newtf_idf->next = NULL;

	return newtf_idf;
}

tf_idf* InsertTF_IDF(tf_idf* head, tf_idf* value){
	//printf("inserttf_idf\n");
	tf_idf* temp = head;
	if(temp->w <= value->w){
		value->next = temp;
		head = value;
		return head;
	}
	while(temp->next != NULL){
		if(temp->next->w <= value->w)
			break;
		else
			temp = temp->next;	
	}
	if(temp->next == NULL && temp->w >= value->w){
		temp->next = value;

		return head;
	}
	value->next = temp->next;
	temp->next = value;
	return head;
}
