#include "project.h"

double LoadFiles(bpTree* tree){
    char copy_path[30] = {0, };
    char copy_path2[50] = {0, };

    DIR* dir;
    DIR* dir2;
    struct dirent *entry;
    struct dirent *entry2;
    int cnt = 0;

	double N=0;

    FILE* fp;
    char buf[1024] = {0, };
    char buf2[30] = {0, };
    char *str;
    char str_num[15] = {0, };
    int doc_num = 0;
	int dir_num;
	int key_hashed;
	
	FILE* tablefp = fopen("table.txt", "w");

    //char *cur_path = "D:/news2021/";
    char *cur_path = realpath(".", buf2);

    if(cur_path)
        printf("%s\n", buf2); /* ./ADS */
    else {
        printf("fail to get file path");
        exit(1);
    }
    strcat(cur_path, "/news2021/");
    printf("%s\n", cur_path); // ./ADS/news2021/

    dir = opendir(cur_path);
    if( dir != NULL){
        while((entry = readdir (dir))!= NULL){
            if(strncmp(entry->d_name, ".", 1) == 0) continue; //current dir, parent dir exception
            strcpy(copy_path, cur_path);
            strcat(copy_path, entry->d_name);
            //printf("%s\n", copy_path); //result = complete file path
			dir_num = atoi(entry->d_name);
            //./ADS/news2021/*/
            dir2 = opendir(copy_path);
            if(dir2 == NULL){
                printf("file path loading fail\n");
                exit(1);
            }
            while((entry2 = readdir (dir2)) != NULL){
                if(strncmp(entry2->d_name, ".", 1) == 0) continue; //current dir, parent dir exception
                //printf("%s\t%d\n", entry2->d_name, cnt++);	// *.html file name print
                strcpy(copy_path2, copy_path);
                strcat(copy_path2, "/");
                strcat(copy_path2, entry2->d_name);
                printf("%s\t%d\n", copy_path2, cnt++); //./ADS/news2021/*/

                strcpy(str_num, strtok(entry2->d_name, ".html"));
                //buffer init
                memset(buf, 0 , 1024);

                doc_num ++;
				
				fputs(strcat(str_num, "\n"), tablefp);
                //html file open
				//printf("%s\n", copy_path2);
                fp = fopen(copy_path2, "r");
                if(fp == NULL){
                    closedir(dir2);
                    closedir(dir);
                    printf("fail to open file2\n");
                    exit(1);
                }
                //printf("file open complete\n");
                //*.html read
                while(fgets(buf, sizeof(buf), fp) != NULL){
					if(buf[strlen(buf) - 1] =='\n'){
	                    buf[strlen(buf) - 1] = '\0';
					}
					//printf("%s\n", buf);
                    //printf("%s\n", buf);
                    //rm_Symbols(buf);
                    str = strtok(buf, " ");

                    //printf("split complelte\n");
                    //split
                    while(str != NULL){
                        //string is inserted
						key_hashed = HashFunc(str);
                        Insert(tree, tree->head ,str , dir_num ,doc_num, false);
						N++;
                        //printf("string: %s, hashvalue: %d, dir_num: %d,doc_num:  %d\n",str, key_hashed, dir_num, doc_num);

                        //PrintLeaf(tree);
                        str = strtok(NULL, " ");

                    }
                }
                fclose(fp);
                memset(copy_path2, 0, 50);
            }
            closedir(dir2);
            memset(copy_path, 0, 30);
			//PrintLeaf(tree);
        }
    }
    else
        exit(1);
	fclose(tablefp);
    closedir (dir);

	return N;
}
char* getDocNum(int index){
	char* str = malloc(sizeof(char)*(14+1));
	char buffer[14] = {0, };
	FILE* fp = fopen("table.txt", "r");
	
	fseek(fp, 14 * (index-1), SEEK_SET);
	fgets(buffer,  14, fp);
	
	strcpy(str, buffer);
	fclose(fp);

	return str;
}



