#include "project.h"

int main(){
    int input, flag = 0;
	double N;
	char str[20] = {0, };
	while(1){
        printf("|-----------------*CHOOSE MENU*------------------|\n");
        printf("| 1. Insert(Make B+ Tree for reading *.html file)|\n");
        printf("| 2. Search                                      |\n");
        printf("| 3. Exit                                        |\n");
        printf("|------------------------------------------------|\n");
        printf(" Select Menu: ");
        scanf("%d", &input);
        switch(input){
            case 1:
                if(flag == 1){
                    printf("Already Create Tree\n");
                    break;
                }
                bpTree bpt = CreateBplusTree();
                /*int i = 0;
                char str[20];
                while(i < 300){
					printf("input: ");
                    scanf("%s", str);
                    Insert(&bpt, bpt.head, str, "1111", false);
					setTreeRoot(&bpt);
                    PrintLeaf(&bpt);
                    i++;
                }*/
                printf("Creating Tree.....\n");
                N = LoadFiles(&bpt);
                printf("COMPLETE\n");
                flag = 1;
				input = 0;
                break;
            case 2:
				if(flag == 1){
					printf(" Keyword for Searching: ");
					scanf("%s", str);
					Search(&bpt, str, N);
				}
				else{
					printf(" Please make a Tree first\n");
				}
                break;
            case 3:
                printf(" Terminate\n");
                exit(1);
                break;
            default:
                printf(" Wrong input, Please restart Program\n");
				exit(1);
                break;
        }
    }
}
