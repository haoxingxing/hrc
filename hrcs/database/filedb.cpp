#include "filedb.h"

filedb::filedb(std::string name)
{
	i.open(name);
}
