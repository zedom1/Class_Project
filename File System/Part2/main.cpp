#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <utility> 
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <math.h>
using namespace std;

///////////////////////////////////////////////////////////
///////////////////	Data Structure STA 	///////////////////
struct Table{
	string filename;
	int start;
	int length;
	Table(string name, int s, int l)
		:filename(name),start(s),length(l){}
};
///////////////////	Data Structure END 	///////////////////
///////////////////////////////////////////////////////////
///////////////////	Global Variable STA ///////////////////
const int MAXBLOCK = 100;
vector<Table> table;
int fat[MAXBLOCK];
int availableBlock = MAXBLOCK - 2;
///////////////////	Global Variable END ///////////////////
///////////////////////////////////////////////////////////
///////////////////	Function STA 		///////////////////
void init();
void listFAT();
void listFile();
void printOrder();
string trim(string s);
vector<string> split(const string &s,  string c);
int allocateSpace(int num);
int searchAvailable(int index = 2);
void writeBlock(int start , int logicBlock);
void insertBlock(int start , int logicBlock);
void create(string filename , int numBlock);
void write(string filename, int logicBlock);
void insert(string filename, int logicBlock); 
void deleteFile(string filename);
void deleteBlock(string filename, int logicBlock);
void handle(string order);
///////////////////	Function END		///////////////////
///////////////////////////////////////////////////////////

vector<string> split(const string &s,  string c){
	string::size_type pos1,pos2;
	pos2 = s.find(c);
	pos1 = 0;
	vector<string> v;
	while(string::npos != pos2){
		v.push_back(s.substr(pos1,pos2-pos1));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

string trim(string s){
	if(s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ")+1);
	return s;
}

void init(){
	memset(fat,0,sizeof(fat));

	// random create file:
	srand(time(0));
	for(int i=0; i<rand()%4+2; i++){
		stringstream stream;
		stream<<"File"<<(char)(i+'A')<<i;
		create(stream.str(), rand()%10+5);
	}

}

void printOrder(){
	printf("==================================\n");
	printf("Providing orders: \n");
	printf("1. ls \t// list all the files.\n");
	printf("2. listFAT \t// list the File Allocate Table(FAT).\n");
	printf("3. create(filename, length); \t// create a file with filename and length. \n");
	printf("4. write(filename, logicBlock); \t// write a file with filename and logicBlock. \n");
	printf("5. insert(filename, logicBlock); \t// insert the file after logicBlock. \n");
	printf("6. delete(filename, logicBlock); \t// delete the logicBlock of the given file. \n");
	printf("7. deleteFile(filename); \t// delete the file. \n");
	printf("==================================\n");
}

int searchAvailable(int index) {
	for(int i=index ; i<MAXBLOCK; i++){
		if(fat[i]==0)
			return i;
	}
	return -1;
}

void listFile(){
	if(table.size()==0){
		printf("Empty file list.\n");
		return;
	}
	for(int i=0; i<table.size(); i++){
		printf("File name: %s.\t Start Block: %d. \t Length: %d.\n",table[i].filename.c_str(), table[i].start, table[i].length);
	}
}

void listFAT(){
	for(int i=0; i<MAXBLOCK; i++){
		printf("Block Num: %d.\t Next: %d.\n",i, fat[i]);
	}
}

void create(string filename , int numBlock){
	int start = allocateSpace(numBlock);
	if(start == -1){
		printf("%s\n", "Not enough space.");
		return;
	}
	Table t(filename, start, numBlock);
	table.push_back(t);
}

void writeBlock(int start , int logicBlock){
	
	int current = start ;
	for(int i=0; i<logicBlock ; i++){
		if(current != -1)
			current = fat[current];
	}
	if(current==-1){
		printf("Logic Block Error.\n");
		return;
	}
	printf("Write Logic Block :%d, Actual Block:%d. \n", logicBlock, current);
}

void insertBlock(int start , int logicBlock){
	if(availableBlock<1){
		printf("Not enough blocks.\n");
		return;
	}
	--availableBlock;
	int current = start ;
	for(int i=0; i<logicBlock ; i++){
		if(current != -1)
			current = fat[current];
	}
	if(current==-1){
		printf("Logic Block Error.\n");
		return;
	}
	int newBlock = searchAvailable();
	fat[newBlock] = fat[current];
	fat[current] = newBlock;
	printf("Insert After Logic Block :%d, Actual Block:%d. \n", logicBlock, newBlock);
}

void write(string filename, int logicBlock){
	for(int i=0; i<table.size(); i++){
		if(table[i].filename == filename){
			writeBlock(table[i].start, logicBlock);
			return;
		}
	}
	printf("File not found.\n");
}

void insert(string filename, int logicBlock){
	for(int i=0; i<table.size(); i++){
		if(table[i].filename == filename){
			insertBlock(table[i].start, logicBlock);
			++table[i].length;
			--availableBlock;
			return;
		}
	}
	printf("File not found.\n");
}

void deleteFile(string filename){
	Table *t = NULL;
	int i=0;
	for(; i<table.size(); i++){
		if(table[i].filename == filename){
			t = &table[i];
			break;
		}
	}
	if(!t){
		printf("File Not Found.\n");
		return;
	}
	availableBlock += t->length;
	int start = t->start;
	int current = start;
	for(int i=0; i<t->length-1; i++){
		current = fat[current];
		fat[current] = 0;
	}
	fat[start] = 0;
	table.erase(table.begin()+i, table.begin()+i+1);
	printf("Delete file : %s. Sucessfully.\n",filename.c_str());
}

void deleteBlock(string filename, int logicBlock){
	Table *t = NULL;
	int i=0;
	for(; i<table.size(); i++){
		if(table[i].filename == filename){
			t = &table[i];
			break;
		}
	}
	if(!t){
		printf("File Not Found.\n");
		return;
	}
	if(logicBlock>t->length){
		printf("%s\n", "Invalid logicBlock.\n");
		return;
	}
	if(t->length == 1){
		printf("Delete logicBlock : %d.of File : %s. Sucessfully.\n",logicBlock, filename.c_str());
		deleteFile(filename);
		return;
	}
	int current = t->start;
	int pre = -1;
	for(int i=0; i<logicBlock; i++){
		pre = current;
		current = fat[current];
	}
	if(pre!=-1)
		fat[pre] = fat[current];
	else
		t->start = fat[current];
	t->length--;
	availableBlock++;
	fat[current] = 0;
	printf("Delete logicBlock : %d.of File : %s. Sucessfully.\n",logicBlock, filename.c_str());
	t = NULL;
}

int allocateSpace(int num){
	if(availableBlock < num)
		return -1;
	int start = searchAvailable();
	int current = start;
	fat[start] = -2;
	for(int i=0; i<num-1; i++){
		fat[current] = searchAvailable();
		current = fat[current];
		fat[current] = -2;
	}
	fat[current] = -1;
	availableBlock -= num;
	return start;
}

void handle(string order){
	vector<string> v = split(order, "(");
	if(v.size()<2){
		if(trim(v[0])== "ls" ){
			listFile();
			return;
		}
		if(trim(v[0])== "listFAT" ){
			listFAT();
			return;
		}
		printf("Input error!\n");
		return;
	}
	string filename;
	string functionName =trim(v[0]), body = split(v[1],")")[0];
	
	v = split(body,",");
	if(v.size()>2){
		printf("Input error!\n");
		return;
	}
	filename = v[0];
	if(v.size()==1){
		if(strcmp(functionName.c_str(),"deleteFile")==0){
			deleteFile(filename);
		}
		else{
			printf("Invalid Input.\n");
		}
	}
	else if(v.size()==2){
		int num = atoi(v[1].c_str());

		if(strcmp(functionName.c_str(),"write")==0){
			write(filename, num);
		}
		else if(strcmp(functionName.c_str(),"insert")==0){
			insert(filename, num);
		}
		else if(strcmp(functionName.c_str(),"create")==0){
			create(filename, num);
		}
		else if(strcmp(functionName.c_str(),"deleteBlock")==0){
			deleteBlock(filename, num);
		}
		else{
			printf("Invalid Input.\n");
		}
	}
	
}

int main(){
	init();
	string order;
	printOrder();
	printf("Random put files: .\n");
	listFile();
	while(1){
		printf("Input your order : ");
		getline(cin, order);
		handle(order);
	}
	return 0;
}