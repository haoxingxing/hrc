#ifndef DB_H
#define DB_H
#include <nlohmann/json.hpp>
#include <utility>

class db
{
protected:
	std::string table;
public:
	db(std::string table):table(std::move(table)){};
	virtual ~db(){};
	virtual nlohmann::json& get(const std::string& key) { return *(new nlohmann::json); };
	virtual void save(const std::string&,const nlohmann::json&){};
	
};
#endif // DB_H
