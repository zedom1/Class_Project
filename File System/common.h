#ifndef COMMON_H
#define COMMON_H 

#include <string>
#include <algorithm>
#include <vector>

typedef short		Flag;
typedef int 		Quantity;
typedef unsigned	Memory;
typedef int 		Identifier;

const Memory BLOCKSIZE 	= 	64;
const Memroy MAXNBLOCK	=	1000;
const Memroy TOTALSIZE	=	BLOCKSIZE * MAXNBLOCK;
Identifier C1 			= 	10;

enum OPERATION 		{CREATE, OPEN, READ, WRITE, CLOSE, DELETE};
enum PROTECTION 	{READ, WRITE, EXECUTE};

#endif