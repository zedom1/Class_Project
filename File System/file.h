#ifndef FILE_H
#define FILE_H

#include "common.h"

class File
{
public:
	File();
	~File();
	
};

class UserFileDirectory
{
	String filename;
	PROTECTION protectWay;
	Quantity currentLength;
	Quantity maxLength;
	File* address;

public:
	UserFileDirectory();
	~UserFileDirectory();
	
};

class MainFileDirectory
{
private:
	String userName;
	UserFileDirectory * ufd;

public:
	MainFileDirectory();
	~MainFileDirectory();
	
};

class UserOpenFile
{
private:
	String filename;
	Flag operation;
	Quantity readPointer;
	Quantity writePointer;
	Quantity currentLength;
	File * address;
	Flag status;

public:
	UserOpenFile();
	~UserOpenFile();
	
};

#endif