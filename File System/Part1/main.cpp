#include "file.h"
#include "linkList.h"

//////////////////////////////////////////////////////////////
/////////////////// 	Global Variable STA	//////////////////
// 管理空间的双向链表全局变量
List * list;
// 管理用户的vector
vector<User *> user;
// 保存当前用户的id
Identifier currentUser;
// 当前用户的打开的文件列表，索引作用
UserOpenFile * currentUOF;
// 当前用户拥有的文件，索引作用
MainFileDirectory * currentD;
// 管理所有用户打开文件列表
vector<UserOpenFile *> openFile;
// 保存文件描述符和对应的文件id
vector< pair<string, Identifier> > fd;
// 保存所有用户及其拥有的文件
vector<MainFileDirectory *> mainMenu;
/////////////////// 	Global Variable END	//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Global Function STA	//////////////////
void init();
void allWriteBack();
void listFD();
void listUOF();
void listFile();
void listOrder();
void close(Identifier id);
void deleteFile(string filename);
Identifier open(string filename, OPERATION op);
void read(Identifier fileID, Quantity byte2read);
void write(Identifier fileID, Quantity byte2write);
Identifier create(string filename, Quantity maxlength, PROTECTION protect);
void handle(string order);
/////////////////// 	Global Function END	//////////////////
//////////////////////////////////////////////////////////////

// 根据当前用户切换缓存变量currentD和currentUOF
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

// 将打开文件中的更改写回到磁盘文件中
void allWriteBack(){
    for(int i=0; i<MAXOPENFILE; i++){
        currentD->writeBack(currentUOF->fileNode[i]);
    }
}

// 初始化，新建随机文件，新建随机用户
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
    listOrder();
    listFile();
}

// 打印命令列表
void listOrder(){
    printf("==================================\n");
    printf("Providing orders: \n");
    printf("0. help \t\t\t\t\t// list all the commands.\n");    
    printf("1. ls \t\t\t\t\t\t// list all the files.\n");
    printf("2. listUOF \t\t\t\t\t// list the opened files.\n");
    printf("3. listFD \t\t\t\t\t// list the file descriptors.\n");
    printf("4. fd=create(filename, maxLength, protectWay); \t// create a file with filename,length and protect way. \n");
    printf("5. write(fd, byteToWrite); \t\t\t// write a file with filename and bytes to write. \n");
    printf("6. fd=open(filename, operation); \t\t// open a file with file name and operation \n");
    printf("7. read(fd, byteToRead); \t\t\t// read a file with filename and bytes to read. \n");
    printf("8. close(fd); \t\t\t\t\t// close the file according to the file descriptor. \n");
    printf("9. delete(filename); \t\t\t\t// delete the file according to file name. \n");
    printf("A. exit \t\t\t\t\t// exit the program.\n");
    printf("==================================\n");
}

// 打印当前打开的文件列表，对应命令listUOF
void listUOF(){
    printf("==================================\n");
    printf("List User Open File:\n");
    UserOpenFileNode * uofn = NULL;
    for(int i=0; i<MAXOPENFILE; i++){
        if(currentUOF->fileNode[i]->status!=INVALID){
            uofn = currentUOF->fileNode[i];
            printf("File ID: %d. \t File name: %s. \t Read Pointer: %d. \t Write Pointer: %d. \t Current Length: %d.\n",uofn->fileID,uofn->filename.c_str(),uofn->readPointer, uofn->writePointer, uofn->currentLength);
        }
    }
    if(uofn==NULL){
        printf("No Open File.\n");
    }
    printf("==================================\n");
}

// 打印所有文件描述符及对应的文件ID，对应命令listFD
void listFD(){
    printf("==================================\n");
    printf("List File Descriptors:\n");
    if(fd.size()==0){
        printf("No file descriptor.\n");
        return;
    }
    for(int i=0; i<fd.size(); i++){
        printf("File descriptor: %s. \t File id: %d.\n",fd[i].first.c_str(), fd[i].second);
    }
    printf("==================================\n");
}

// 打印所有文件，对应命令ls
void listFile(){
    printf("==================================\n");
    printf("List Files:\n");
    vector<UserFileDirectory *> u = currentD->ufd;
    if(u.size()==0){
        printf("No File.\n");
        return;
    }
    allWriteBack();
    for(int i=0; i<u.size(); i++){
        printf("File ID: %d. \tFile name: %s. \t Current Length: %d. \t Max Length: %d.\n",u[i]->fileID,u[i]->filename.c_str(),u[i]->currentLength, u[i]->maxLength);
    }
    printf("==================================\n");
}

// 辅助函数，将字符串根据一个字符串进行分割，返回字符串列表
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

// 辅助函数，去除字符串前后的空格
string trim(string s){
	if(s.empty())
		return s;
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ")+1);
	return s;
}

// 将用户输入的操作字符串映射到枚举变量中
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

// 判断用户操作是否符合文件支持的操作
bool detectPortect(Identifier id, Flag way){
	PROTECTION protect = READABLE;
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->fileID==id){
			protect = currentD->ufd[i]->protectWay;
			break;
		}
	}
	printf("Protect:%d\n",protect);
	if( way == 0 ){
		if( !( protect==READABLE || protect == EXECUTE)){
			printf("ProtectWay unspport. This file isn't readable.\n");
			return false;
		}
	}
	else if(way == 1){
		if( !( protect==WRITABLE || protect == EXECUTE)){
			printf("ProtectWay unspport. This file isn't writable.\n");
			return false;
		}
	}
	return true;
}

// 根据文件id删除文件描述符
void removeFD(Identifier id){
	for(int i=0; i<fd.size(); i++){
		if(fd[i].second == id){
			fd.erase(fd.begin()+i, fd.begin()+i+1);
			break;
		}
	}
}

// 根据文件描述符找到id， 若mode==1，则找到后将该文件描述符删除
Identifier searchID(string fdstring, int mode){
	Identifier id = -1;
	for(int i=0; i<fd.size(); i++){
		if(fd[i].first == fdstring){
			id = fd[i].second;
			if(mode == 1)
				fd.erase(fd.begin()+i, fd.begin()+i+1);
			break;
		}
	}
	if(id == -1)
		printf("File Descriptor Not Found!\n");
	return id;
}

// 辅助函数，根据要分配的块数在磁盘中找到连续的空间分配，返回起始块号
Memory allocateSpace(Memory numBlock){
	ListNode * tem;
	tem= list->header;
	Memory start;
	while(tem!=list->trailer && numBlock > tem->length)
		tem = tem->succ;
	if(tem==list->trailer)
		return (Memory)-1;
	list->insertSingle( tem->start + numBlock, tem->length - numBlock );
	start = tem->start;
	list->removeNode( tem );
	return start;
}

// 辅助函数，根据块的起始位置和长度释放磁盘空间
void releaseSpace(Memory start, Memory length){
	ListNode * tem = list->header->succ;
	ListNode * aim = list->insertSingle( start, length);
	aim->start = start;
	aim->length = length;
	Flag flag=0;
	// 拼接可能的连续块
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

// 解析用户输入的命令并进行处理
void handle(string order){
	vector<string> v = split(order, "(");
	if(v.size()<2){
        if(v[0]=="ls"){
            listFile();
            return;
        }
        else if(v[0]=="listUOF"){
            listUOF();
            return;
        }
        else if(v[0]=="listFD"){
            listFD();
            return;
        }
        else if(v[0]=="help"){
        	listOrder();
        	return;
        }
        else if(v[0]=="exit"){
        	exit(0);
        }
		printf("Input error!\n");
		return;
	}
	Identifier currentFile;
	string fdstring;
	string functionName = trim(v[0]), body = trim(v[1]);
	v =  split(functionName, "=");
	if(v.size()==1){
		functionName = trim(v[0]);
		body = split(body,")")[0];
		v = split(body,",");
		if(v.size()==2){
			currentFile = searchID(trim(v[0]));
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
				Identifier fileID = searchID(trim(v[0]),1);
				if( fileID == -1){
					printf("File Not Found.\n");
					return;
				}
				close(fileID);
			}
			else if(strcmp(functionName.c_str(),"delete")==0){
				deleteFile(trim(v[0]));
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
			Identifier id = create(trim(v[0]), atoi(v[1].c_str()), PROTECTION(atoi(v[2].c_str())) );
            if(id != -1){
            	pair<string, Identifier> p1(fdstring, id);
				fd.push_back(p1);
            }
		}
		else if(strcmp(functionName.c_str(),"open")==0){
			if(v.size()!=2){
				printf("Parameter error.\n");
				return;
			}
			OPERATION op; 
			if(getOP(trim(v[1]), op)==false){
				printf("Operation error.\n");
				return;
			}
            int id = open(trim(v[0]), op);
            if(id==-1){
                printf("File name not found.\n");
                return;
            }
            pair<string, Identifier> p1(fdstring, id);
			fd.push_back(p1);
		}
	}
}

int main(){
	init();
	string order;
	while(1){
        printf("Input your order: ");
		getline(cin, order);
		if(!(order.empty()))
			handle(order);
	}
	return 0;
}

// 根据文件名、最大长度和保护方式创建一个新的文件
Identifier create(string filename, Quantity maxlength, PROTECTION protect){
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->filename==filename){
			printf("FileName Exist.\n");
			return -1;
		}
	}
	Quantity blocks = ceil(maxlength*1.0 / BLOCKSIZE);
	Memory startPlace = allocateSpace(blocks);
	UserFileDirectory * ufd = new UserFileDirectory(filename, protect, startPlace, blocks*BLOCKSIZE);
	// 将创建的文件放入用户拥有文件的列表中
	for(int i=0; i<mainMenu.size(); i++){
		if(mainMenu[i]->userID == currentUser){
			mainMenu[i]->ufd.push_back(ufd);
			break;
		}
	}
	// 将文件放入当前打开文件列表中
	for(int i=0; i<openFile.size(); i++){
		if(openFile[i]->userID == currentUser){
			openFile[i]->openFile(ufd, CREATE);
			break;
		}
	}
	printf("Create Success.\n");
	return ufd->fileID;
}

// 根据文件名和操作打开文件，返回文件的id
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

// 根据文件id和要写的字节写入文件
void write(Identifier fileID, Quantity byte2write){
	// 该文件不支持写入操作
	if(!detectPortect(fileID, 1))
		return;
	// 当前长度+要写长度大于最大长度
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->fileID==fileID){
			if(currentD->ufd[i]->currentLength + byte2write > currentD->ufd[i]->maxLength){
				printf("Byte To Write Too Large.\n");
				return;
			}
			break;
		}
	}
	// 写入文件
	UserOpenFileNode * node = NULL;
	for(int i=0; i<MAXOPENFILE; i++){
		if(fileID == currentUOF->fileNode[i]->fileID){
            printf("Write file name : %s.\n",currentUOF->fileNode[i]->filename.c_str());
			node = currentUOF->fileNode[i];
            node->writePointer += byte2write;
            node->currentLength += byte2write;
			break;
		}
    }
}

// 对给定的文件id进行读操作
void read(Identifier fileID, Quantity byte2read){
	// 检测该文件支不支持读操作
	if(!detectPortect(fileID, 0))
		return;
	UserOpenFileNode * node = NULL;
	// 在打开文件列表中找到该节点
	for(int i=0; i<MAXOPENFILE; i++){
		if(fileID == currentUOF->fileNode[i]->fileID){
			node = currentUOF->fileNode[i];
			break;
		}
	}
	if(node){
		// 判断数字是否合法
		if(node->readPointer+byte2read > node->currentLength){
			printf("Byte To Read Too Large.\n");
			return;
		}
		node->readPointer += byte2read;
	}
}

// 根据文件id关闭文件，将其在打开文件列表中的状态设置为invalid，并将文件写回到磁盘
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

// 根据文件名删除文件
void deleteFile(string filename){
	Identifier id = -1;
	// 获取文件id
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
	// 关闭文件及移除文件描述符（文件可能被打开）
	close(id);
	removeFD(id);
	for(int i=0; i<currentD->ufd.size(); i++){
		if(currentD->ufd[i]->filename == filename){
			releaseSpace(currentD->ufd[i]->startBlock, currentD->ufd[i]->maxLength/BLOCKSIZE);
			currentD->ufd.erase(currentD->ufd.begin()+i, currentD->ufd.begin()+i+1);
			break;
		}
	}
	printf("Delete File %s Success!\n",filename.c_str());
}
