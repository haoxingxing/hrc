#ifndef FILEDB_H
#define FILEDB_H
#include <fstream>

#include "db.h"
class filedb : public db
{
	std::ifstream i;
public:
	filedb(std::string name);
	
};
#endif // FILEDB_H
