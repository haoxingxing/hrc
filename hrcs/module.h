#ifndef MODULE_H
#define MODULE_H
#include "nlohmann/json.hpp"
#include "helper.h"
typedef std::function<nlohmann::json(const nlohmann::json&)> hfunc;
class pmodule
{
private:
	httplib::Server& srv;
	std::string name;
	std::map < std::string, hfunc> funcs;
protected:
	void insert(const std::string& path, hfunc f)
	{
		httphelper::logger::logstr("Add " + path + "@" + name);
		funcs.insert_or_assign(path, f);
	}
public:
	inline pmodule(const std::string &name, httplib::Server& srv)
		:srv(srv),name(name)
	{
		httphelper::logger::logstr("Load Module " + name );

	};

	virtual inline nlohmann::json call(const std::string& key,const nlohmann::json& data)
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
