#ifndef DB_H
#define DB_H
#include <nlohmann/json.hpp>
class db
{
public:
	virtual ~db(){};
	virtual nlohmann::json get(std::string key){return nlohmann::json();};
	virtual void commit(std::string key,nlohmann::json){};
	
};
#endif // DB_H
