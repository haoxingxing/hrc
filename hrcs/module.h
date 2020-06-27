#ifndef MODULE_H
#define MODULE_H
#include "nlohmann/json.hpp"
#include "helper.h"
#include "database/db.h"
typedef std::function<nlohmann::json(const nlohmann::json&)> hfunc;
class pmodule
{
private:
	httplib::Server& srv;
	std::string name;
	std::map < std::string, hfunc> funcs;
protected:
	db* database = nullptr;
	void insert(const std::string& path,const hfunc& f)
	{
		httphelper::logger::logstr("Add " + path + "@" + name);
		funcs[path] = f;
	}
public:
	inline pmodule(const std::string &name, httplib::Server& srv,db* database)
		:srv(srv),name(name),database(database)
	{
		httphelper::logger::logstr("Load Module " + name );
	};
	virtual ~pmodule()
	{
		delete database;
	};
	virtual nlohmann::json call(const std::string& key,const nlohmann::json& data)
	{
		if (funcs.find(key) == funcs.end())
			return nlohmann::json({
			{"status",404.2 },
			{"reason","Function Not Find"}
				});
		return funcs.at(key)(data);
	};

	
};

	
#endif // MODULE_H
