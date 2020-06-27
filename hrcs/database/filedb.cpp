#include "filedb.h"

void filedb::Init()
{
	std::ifstream i;
	i.open("datastorage.json");
	if (i.is_open())
		i >> data;
	i.close();
	o.open("datastorage.json");
}

filedb::filedb(std::string name) : db(name)
{}

nlohmann::json& filedb::get(const std::string& key)
{
	o.clear();
	o << data;
	return data[table][key];
}

void filedb::save(const std::string& key, const nlohmann::json& value)
{
	data[table][key] = value;
	o.clear();
	o << data;
}

std::ofstream filedb::o;
nlohmann::json filedb::data;
