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
// 文件目录表类，记录文件名、起始位置及总长度
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
const int MAXBLOCK = 100;				// 最大块数
vector<Table> table;					// 全局变量，目录表实例
int fat[MAXBLOCK];						// 文件分配表
int availableBlock = MAXBLOCK - 2;		// 可用块数目
///////////////////	Global Variable END ///////////////////
///////////////////////////////////////////////////////////
///////////////////	Function STA 		///////////////////
void init();
// 查看文件分配表FAT，对应命令listFAT
void listFAT();
// 查看所有文件，对应命令ls
void listFile();
// 查看支持的所有命令，对应命令help
void printOrder();
// 辅助函数，删除字符串首尾的空格
string trim(string s);
// 辅助函数，将字符串s根据c进行分割
vector<string> split(const string &s,  string c);
// 根据要分配的块数目进行分配，返回起始块号
int allocateSpace(int num);
// 从给定的起始位置开始搜索，返回空闲块的块号
int searchAvailable(int index = 2);
// 检测是否有重复的文件名
bool detectFilename(string filename);
// 给定起始块号和逻辑块号，覆盖写相应逻辑块
void writeBlock(int start , int logicBlock);
// 在给定逻辑块后面插入一个新的块（逻辑插入，物理上可能不相邻）
void insertBlock(int start , int logicBlock);
// 给定文件名和块数创建文件，包含空间分配
void create(string filename , int numBlock);
// 给定文件名和逻辑块号覆盖写逻辑块
void write(string filename, int logicBlock);
// 给定文件名，在逻辑块号后插入新逻辑块
void insert(string filename, int logicBlock); 
// 删除文件
void deleteFile(string filename);
// 删除给定文件的特定逻辑块
void deleteBlock(string filename, int logicBlock);
// 处理用户输入
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
	srand(time(0));
	// 随机生成文件
	for(int i=0; i<rand()%4+2; i++){
		stringstream stream;
		stream<<"File"<<(char)(i+'A')<<i;
		create(stream.str(), rand()%10+5);
	}

}

void printOrder(){
	printf("==================================\n");
	printf("Providing orders: \n");
	printf("0. help \t\t\t\t// view commands list.\n");
	printf("1. ls \t\t\t\t\t// list all the files.\n");
	printf("2. listFAT \t\t\t\t// list the File Allocate Table(FAT).\n");
	printf("3. create(filename, length); \t\t// create a file with filename and length. \n");
	printf("4. write(filename, logicBlock); \t// write a file with filename and logicBlock. \n");
	printf("5. insert(filename, logicBlock); \t// insert the file after logicBlock. \n");
	printf("6. deleteBlock(filename, logicBlock); \t// delete the logicBlock of the given file. \n");
	printf("7. deleteFile(filename); \t\t// delete the file. \n");
	printf("8. exit \t\t\t\t// exit the program.\n");
	printf("==================================\n");
}

int searchAvailable(int index) {
	for(int i=index ; i<MAXBLOCK; i++){
		if(fat[i]==0)
			return i;
	}
	return -1;
}

bool detectFilename(string filename){
	for(int i=0; i<table.size(); i++){
		if(filename == table[i].filename)
			return true;
	}
	return false;
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
	// 没有足够的空闲快
	if(availableBlock<1){
		printf("Not enough blocks.\n");
		return;
	}
	--availableBlock;
	int current = start ;
	// 先找到给定的逻辑块的物理块号
	for(int i=0; i<logicBlock ; i++){
		if(current != -1)
			current = fat[current];
		else
			break;
	}
	if(current==-1){
		printf("Logic Block Error.\n");
		return;
	}
	// 找一个空闲块
	int newBlock = searchAvailable();
	// 将空闲块插入原块链接中间
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
	// 根据文件名在文件表中找到相应项
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
	// 更新空闲块数目
	availableBlock += t->length;
	int start = t->start;
	int current = start;
	// 将FAT中块清零
	for(int i=0; i<t->length; i++){
		start = fat[current];
		fat[current] = 0;
		current = start;
	}
	// 删除文件目录表中相应表项
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
	// 只有一个逻辑块，则将文件删除
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
		if(trim(v[0])=="help"){
			printOrder();
			return;
		}
		if(trim(v[0])=="exit"){
			exit(0);
		}
		printf("Input error!\n");
		return;
	}
	string filename;
	string functionName =trim(v[0]), body = split(v[1],")")[0];
	
	v = split(body,",");
	if(v.size()>2 || v.size()<1){
		printf("Input error!\n");
		return;
	}
	filename = v[0];
	if(filename.empty()){
		printf("Filename Error!\n");
		return;
	}
	if(v.size()==1){
		if(strcmp(functionName.c_str(),"deleteFile")==0){
				deleteFile(filename);
				return;
		}
		else{
			printf("Invalid Input.\n");
			return;
		}
	}
	else if(v.size()==2){
		if(v[1].empty()){
			printf("Number Empty!\n");
			return;
		}
		int num = atoi(v[1].c_str());

		if(strcmp(functionName.c_str(),"write")==0){
			write(filename, num);
			return;
		}
		else if(strcmp(functionName.c_str(),"insert")==0){
			insert(filename, num);
			return;
		}
		else if(strcmp(functionName.c_str(),"create")==0){
			if(detectFilename(filename)){
				printf("File Name Exist!\n");
				return;
			}
			create(filename, num);
			return;
		}
		else if(strcmp(functionName.c_str(),"deleteBlock")==0){
			deleteBlock(filename, num);
			return;
		}
		else{
			printf("Invalid Input.\n");
			return;
		}
	}
	printf("Can't handle this command.\n");
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
		if(!(order.empty()))
			handle(order);
	}
	return 0;
}