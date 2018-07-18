#include "file.h"

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