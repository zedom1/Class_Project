#ifndef FILE_H
#define FILE_H

#include "common.h"

struct File
{

	File(){}
	~File(){}
};

struct User
{

	Identifier userID;
	string userName;
	User();
	~User(){}
};

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


User::User(){
	stringstream stream;
	userID = numUser++;
	stream<<"User "<<(char)(userID+'A'-1)<<userID;
	userName = stream.str();
}

UserFileDirectory::UserFileDirectory(){
	stringstream stream;
	fileID = numFile++;
	stream<<"File "<<(char)(fileID+'A'-1)<<fileID;
	filename = stream.str();
	protectWay = PROTECTION(rand()%3+1);
	currentLength = rand()%1000;
	maxLength = rand()%3000+1000;
	address = new File();
}

UserFileDirectory::UserFileDirectory(string fname, PROTECTION protect, Memory startB, Quantity maxl){
	fileID = numFile++;
	filename = fname;
	protectWay = protect;
	startBlock = startB;
	maxLength = maxl;
	address = new File();
}

void MainFileDirectory::writeBack(UserOpenFileNode * node){
	UserFileDirectory * u;
	for(int i=0; i<ufd.size(); i++){
		if(ufd[i]->fileID == node->fileID){
			u = ufd[i];
			break;
		}
	}
	u->currentLength = node->currentLength;
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