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

typedef short		Flag;
typedef int 		Quantity;
typedef unsigned	Memory;
typedef int 		Identifier;

const Quantity MAXOPENFILE 	= 	4;
const Memory BLOCKSIZE 		= 	64;
const Memory MAXNBLOCK		=	1000;
const Memory TOTALSIZE		=	BLOCKSIZE * MAXNBLOCK;
const Quantity MAXUSER		=	3;
const Quantity MAXFILE 		=	9;

Identifier C1 				= 	10;
Quantity numUser			=	0;
Quantity numFile			=	0;

enum OPERATION 		{CREATE, OPEN, READ, WRITE, CLOSE, DELETE};
enum PROTECTION 	{READABLE=1, WRITABLE=2, EXECUTE=3};
enum STATUS 		{INVALID, OCCUPY};
#endif