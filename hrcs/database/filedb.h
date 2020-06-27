#ifndef FILEDB_H
#define FILEDB_H
#include <fstream>
#include "db.h"

class filedb : public db
{
	static 	std::ofstream o;
	static nlohmann::json data;
public:
	static void Init();
	filedb(std::string name);
	nlohmann::json& get(const std::string& key) override;
	void save(const std::string&, const nlohmann::json&) override;
};
#endif // FILEDB_H
