#ifndef HANDLER_H
#define HANDLER_H
#include "httplib.h"
#include "module.h"

class v1_handler
{
private:
	httplib::Server& srv;
	std::map<std::string, pmodule*> mods;
public:
	v1_handler(httplib::Server& srv);
	~v1_handler() {


	};
	void handleRequest(const httplib::Request& req, httplib::Response& res);
};

#endif // HANDLER_H
