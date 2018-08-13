#ifndef FILE_H
#define FILE_H

#include "common.h"

struct File
{

	File(){}
	~File(){}
};

// 用户类，记录用户id和用户名
struct User
{

	Identifier userID;
	string userName;
	User();
	~User(){}
};

// 一个单独的用户文件节点，记录各种信息
struct UserFileDirectory
{
	Identifier fileID;
	string filename;
	PROTECTION protectWay;
	Quantity currentLength;
    Quantity maxLength;
	File* address;
	Memory startBlock;

	UserFileDirectory();
	UserFileDirectory(string fname, PROTECTION protect, Memory startB, Quantity maxl);
	~UserFileDirectory();
	
};

// 一个用户打开文件节点，除基本信息外还记录读写指针
struct UserOpenFileNode
{

	Identifier fileID;
	string filename;
	OPERATION operation;
	Quantity readPointer;
	Quantity writePointer;
	Quantity currentLength;
	File * address;
	STATUS status;

	UserOpenFileNode();
	UserOpenFileNode(UserFileDirectory * ufd, OPERATION op);
	~UserOpenFileNode(){}
	
};

// 文件目录节点，记录一个用户及其拥有的文件列表
struct MainFileDirectory
{
	Identifier userID;
	vector<UserFileDirectory *> ufd;

	MainFileDirectory(){}
	MainFileDirectory(Identifier user)
	: userID(user){ }
	void writeBack(UserOpenFileNode * node);
	~MainFileDirectory(){}
};

// 用户打开文件列表节点，记录一个用户及其打开文件列表
struct UserOpenFile
{
	UserOpenFileNode *fileNode[MAXOPENFILE];
	Identifier userID;
	Quantity openFileCounter;
	void init();

	UserOpenFile();
	UserOpenFile(Identifier user);
	bool openFile(UserFileDirectory *ud, OPERATION op);
	~UserOpenFile(){}
	
};

// 随机初始化用户
User::User(){
	stringstream stream;
	userID = numUser++;
	stream<<"User "<<(char)(userID+'A'-1)<<userID;
	userName = stream.str();
}

// 随机初始化文件，默认读写方式为可读可写可执行
UserFileDirectory::UserFileDirectory(){
	stringstream stream;
    fileID = numFile++;
    stream<<"File"<<(char)(fileID+'A')<<fileID;
	filename = stream.str();
	protectWay = PROTECTION(3);
	currentLength = rand()%1000;
	maxLength = ceil((rand()%2000+1000)*1.0/BLOCKSIZE)*BLOCKSIZE;
	address = new File();
	startBlock = allocateSpace(maxLength/BLOCKSIZE);
}

// 带条件的构造函数
UserFileDirectory::UserFileDirectory(string fname, PROTECTION protect, Memory startB, Quantity maxl){
    fileID = numFile++;
	filename = fname;
	protectWay = protect;
	startBlock = startB;
	maxLength = maxl;
    currentLength = 0;
	address = new File();
}

// 将打开文件的信息写回到磁盘文件信息
void MainFileDirectory::writeBack(UserOpenFileNode * node){
    if(node->status==INVALID)
        return;
	UserFileDirectory * u;
	for(int i=0; i<ufd.size(); i++){
		if(ufd[i]->fileID == node->fileID){
            ufd[i]->currentLength = node->currentLength;
            return;
		}
	}
}

UserFileDirectory::~UserFileDirectory(){
	delete address;
}

void UserOpenFile::init(){
	openFileCounter = 0;
	for(Quantity i=0; i<MAXOPENFILE; i++){
		fileNode[i] = new UserOpenFileNode();
	}
}

UserOpenFile::UserOpenFile(){
	init();
}

UserOpenFile::UserOpenFile(Identifier user){
	init();
	userID = user;
}

bool UserOpenFile::openFile(UserFileDirectory * ud, OPERATION op){
	if(openFileCounter>=MAXOPENFILE)
		return false;
	UserOpenFileNode *file = new UserOpenFileNode(ud, op);
	for(int i=0; i<MAXOPENFILE; i++)
		if( fileNode[i]->status == INVALID ){
			delete fileNode[i] ;
			fileNode[i] = file;
			file->status = OCCUPY;
			++openFileCounter;
			break;
		}
	return true;
}

UserOpenFileNode::UserOpenFileNode(){
	status = INVALID;
}

UserOpenFileNode::UserOpenFileNode(UserFileDirectory * ufd, OPERATION op){
	fileID =  ufd->fileID;
	filename = ufd->filename;
	currentLength = ufd->currentLength;
	operation = op;
	readPointer = 1;
	writePointer = currentLength;
	address = ufd->address;
	status = OCCUPY;
}

#endif
