#include "file.h"
#include "linkList.h"
//////////////////////////////////////////////////////////////
/////////////////// 	Global Variable STA	//////////////////
List * list;
vector<User *> user;
Identifier currentUser;
UserOpenFile * currentUOF;
MainFileDirectory * currentD;
vector<UserOpenFile *> openFile;
vector<pair<string, Identifier>> fd;
vector<MainFileDirectory *> mainMenu;
/////////////////// 	Global Variable END	//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Support Function STA//////////////////
string trim(string s);
void switchCurrentD();
Identifier searchID(string fd);
bool getOP(string s, OPERATION & op);
Memory allocateSpace(Memory numBlock);
void releaseSpace(Memory start, Memory length);
vector<string> split(const string &s,  string c);
/////////////////// 	Support Function END//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Global Function STA	//////////////////
void init();
void close(Identifier fileID);
void deleteFile(string filename);
Identifier open(string filename, OPERATION op);
void read(Identifier fileID, Quantity byte2read);
void write(Identifier fileID, Quantity byte2write);
Identifier create(string filename, Quantity maxlength, PROTECTION protect);
void handle(string order);
/////////////////// 	Global Function END	//////////////////
//////////////////////////////////////////////////////////////

void switchCurrentD(){
	for(int i=0; i<mainMenu.size(); i++){
		if(mainMenu[i]->userID == currentUser){
			currentD = mainMenu[i];
			break;
		}
	}
	for(int i=0; i<openFile.size(); i++){
		if(openFile[i]->userID == currentUser){
			currentUOF = openFile[i];
			break;
		}
	}
}

void init(){
	srand(time(0));
	list = new List();
	currentUser = 0;
	for(int i=0; i<MAXUSER; i++){
		User * u = new User();
		user.push_back(u);
		MainFileDirectory * currentDirectory = new MainFileDirectory(u->userID);
		mainMenu.push_back(currentDirectory);
		for(int i=0; i<MAXFILE/MAXUSER; i++){
			currentDirectory->ufd.push_back(new UserFileDirectory());
		}
		openFile.push_back(new UserOpenFile(u->userID));
	}
	switchCurrentD();
}

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
//{CREATE, OPEN, READ, WRITE, CLOSE, DELETE};
bool getOP(string s, OPERATION & op){
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	if(strcmp(s.c_str(),"read")==0){
		op = READ;
		return true;
	}
	else if(strcmp(s.c_str(),"create")==0){
		op = CREATE;
		return true;
	}
	else if(strcmp(s.c_str(),"open")==0){
		op = OPEN;
		return true;
	}
	else if(strcmp(s.c_str(),"write")==0){
		op = WRITE;
		return true;
	}
	else if(strcmp(s.c_str(),"close")==0){
		op = CLOSE;
		return true;
	}
	else if(strcmp(s.c_str(),"delete")==0){
		op = DELETE;
		return true;
	}
	return false;
}

Identifier searchID(string fdstring){
	int i=0;
	Identifier id;
	for(; i<fd.size(); i++){
		if(strcmp(fd[i].first.c_str(),fdstring.c_str())==0){
			id = fd[i].second;
			break;
		}
	}
	if(i==fd.size()){
		printf("File Descriptor Not Found!\n");
		return -1;
	}
	return id;
}

Memory allocateSpace(Memory numBlock){
	ListNode * tem;
	tem= list->header;
	while( tem!=list->trailer && numBlock > tem->length)
		tem = tem->succ;
	if(tem==list->trailer)
		return (Memory)-1;
	list->insertSingle( tem->start + numBlock, tem->length - numBlock );
	list->removeNode( tem );
	return (Memory)tem->start;
}

void releaseSpace(Memory start, Memory length){
	ListNode * tem = list->header->succ;
	ListNode * aim = list->insertSingle( start, length);
	aim->start = start;
	aim->length = length;
	Flag flag=0;
	while(flag==0){
		flag=1;
		while(tem!=list->trailer){
			if( (tem->start+tem->length) == aim->start ){
				tem->length += aim->length;
				list->removeNode(aim);
				list->insertionSort();
				aim = tem;
				flag=0;
			}
			if( (aim->start+aim->length)==tem->start ){
				tem->length += aim->length;
				tem->start = aim->start;
				list->removeNode( aim);
				list->insertionSort();
				aim = tem;
				flag=0;
			}
			tem = tem->succ;
		}
	}
}

void handle(string order){
	vector<string> v = split(order, "(");
	if(v.size()<2){
		printf("Input error!\n");
		return;
	}
	Identifier currentFile;
	string fdstring;
	string functionName = v[0], body = v[1];
	v =  split(functionName, "=");
	if(v.size()==1){
		functionName = trim(v[0]);
		body = split(body,")")[0];
		v = split(body,",");
		if(v.size()==2){
			currentFile = searchID(v[0]);
			if(currentFile==-1)
				return;
			if(strcmp(functionName.c_str(),"write")==0){
				write(currentFile, atoi( v[1].c_str() ));
			}
			else if(strcmp(functionName.c_str(),"read")==0){
				read(currentFile, atoi( v[1].c_str() ));
			}
		}
		else if(v.size()==1){
			if(strcmp(functionName.c_str(),"close")==0){
				currentFile = searchID(v[0]);
				if(currentFile==-1)
					return;
				close(currentFile);
			}
			else if(strcmp(functionName.c_str(),"delete")==0){
				deleteFile(v[0]);
			}
		}
		else{
			printf("Invalid function Name.\n");
			return;
		}
	}
	else{
		fdstring = trim(v[0]);
		functionName = trim(v[1]);
		body = split(body,")")[0];
		v = split(body,",");
		if(strcmp(functionName.c_str(),"create")==0){
			if(v.size()!=3){
				printf("Parameter error.\n");
				return;
			}
			pair<string, Identifier> p1(fdstring, create(fdstring, atoi(v[1].c_str()), PROTECTION(atoi(v[2].c_str())) ));
			fd.push_back(p1);
		}
		else if(strcmp(functionName.c_str(),"open")==0){
			if(v.size()!=2){
				printf("Parameter error.\n");
				return;
			}
			OPERATION op; 
			if(getOP(v[1], op)==false){
				printf("Operation error.\n");
				return;
			}
			pair<string, Identifier> p1(fdstring, open(fdstring, op));
			fd.push_back(p1);
		}
	}
}

int main(){
	init();
	string order;
	while(1){
		getline(cin, order);
		handle(order);
	}
	return 0;
}


Identifier create(string filename, Quantity maxlength, PROTECTION protect){
	Quantity blocks = ceil(maxlength / BLOCKSIZE);
	Memory startPlace = allocateSpace(blocks);
	UserFileDirectory * ufd = new UserFileDirectory(filename, protect, startPlace, maxlength);
	for(int i=0; i<mainMenu.size(); i++){
		if(mainMenu[i]->userID == currentUser){
			mainMenu[i]->ufd.push_back(ufd);
			break;
		}
	}
	for(int i=0; i<openFile.size(); i++){
		if(openFile[i]->userID == currentUser){
			openFile[i]->openFile(ufd, CREATE);
			break;
		}
	}
	return ufd->fileID;
}

Identifier open(string filename, OPERATION op){
	Identifier id = -1;
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->filename==filename){
			id = currentD->ufd[i]->fileID;
			if(!currentUOF->openFile(currentD->ufd[i] ,op)){
				printf("Open file out of bound.\n");
			}
			break;
		}
	}
	return id;
}

void write(Identifier fileID, Quantity byte2write){
	UserOpenFileNode * node = NULL;
	for(int i=0; i<MAXOPENFILE; i++){
		if(fileID == currentUOF->fileNode[i]->fileID){
			node = currentUOF->fileNode[i];
			break;
		}
	}
	if(node){
		node->writePointer += byte2write;
		node->currentLength += byte2write;
	}
}

void read(Identifier fileID, Quantity byte2read){
	UserOpenFileNode * node = NULL;
	for(int i=0; i<MAXOPENFILE; i++){
		if(fileID == currentUOF->fileNode[i]->fileID){
			node = currentUOF->fileNode[i];
			break;
		}
	}
	if(node)
		node->readPointer += byte2read;
}

void close(Identifier fileID){
	UserOpenFileNode * node = NULL;
	for(int i=0; i<MAXOPENFILE; i++){
		if(fileID == currentUOF->fileNode[i]->fileID){
			node = currentUOF->fileNode[i];
			break;
		}
	}
	if(node){
		currentD->writeBack(node);
		node->status = INVALID;
	}
}

void deleteFile(string filename){
	Identifier id = -1;
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->filename==filename){
			id = currentD->ufd[i]->fileID;
			break;
		}
	}
	if(id == -1){
		printf("File Not Found.\n");
		return;
	}
	close(id);
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->filename == filename){
			releaseSpace(currentD->ufd[i]->startBlock, ceil(currentD->ufd[i]->maxLength*1.0/BLOCKSIZE));
			currentD->ufd.erase(currentD->ufd.begin()+i, currentD->ufd.begin()+i+1);
			break;
		}
	}
}