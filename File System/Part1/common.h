#ifndef COMMON_H
#define COMMON_H 

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

//////////////////////////////////////////////////////////////
/////////////////// 	Typedef STA 		//////////////////
typedef short		Flag;
typedef int 		Quantity;
typedef int			Memory;
typedef int 		Identifier;
/////////////////// 	Typedef END 		//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Constant STA 		//////////////////
const Quantity MAXOPENFILE 	= 	4;							// 最大支持的打开文件数目
const Memory BLOCKSIZE 		= 	64;							// 一个块的字节大小
const Memory MAXNBLOCK		=	1000;						// 块的数目
const Memory TOTALSIZE		=	BLOCKSIZE * MAXNBLOCK;		// 模拟磁盘的大小
const Quantity MAXUSER		=	3;							// 最大用户数
const Quantity MAXFILE 		=	9;							// 初始最大文件数
/////////////////// 	Constant END 		//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Variable STA 		//////////////////
Identifier C1 				= 	10;							// 开始分配块号
Quantity numUser			=	0;							// 用户计数器
Quantity numFile			=	0;							// 文件计数器
/////////////////// 	Variable END 		//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	ENUM STA 			//////////////////
enum OPERATION 		{CREATE, OPEN, READ, WRITE, CLOSE, DELETE};	// 打开文件要进行的操作的枚举变量
enum PROTECTION 	{READABLE=1, WRITABLE=2, EXECUTE=3};		// 文件操作方式
enum STATUS 		{INVALID, OCCUPY};							// 文件在打开文件列表中的状态
/////////////////// 	ENUM end 			//////////////////
//////////////////////////////////////////////////////////////
/////////////////// 	Support Function STA//////////////////
string trim(string s);
void switchCurrentD();
void removeFD(Identifier id);
Identifier searchID(string fd, int mode=0);
bool getOP(string s, OPERATION & op);
Memory allocateSpace(Memory numBlock);
bool detectPortect(Identifier id, Flag way);
void releaseSpace(Memory start, Memory length);
vector<string> split(const string &s,  string c);
/////////////////// 	Support Function END//////////////////
//////////////////////////////////////////////////////////////
#endif