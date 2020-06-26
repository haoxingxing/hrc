#include "v1_handler.h"

#include "auth/auth.h"


v1_handler::v1_handler(httplib::Server& srv) : srv(srv)
{
	mods["auth"] = new auth(srv);
	srv.Post("/v1/.*", [&](const httplib::Request& req, httplib::Response& res)
	{
		this->handleRequest(req, res);
	});
}

void v1_handler::handleRequest(const httplib::Request& req, httplib::Response& res)
{
	auto x = nlohmann::json::parse(req.body);
	std::vector<std::string> levels;
	std::string s = req.path;
	size_t pos = 0;
	std::string classname;
	if ((pos = s.find("/v1/")) != std::string::npos)
	{
		s.erase(0, pos + 4);
	}
	if ((pos = s.find('/')) != std::string::npos)
	{
		classname = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	else
	{
		classname = s;
	}
	if (classname != "auth")
	{
		if (x.contains("mch_key"))
		{
			if (mods["auth"]->call("ChkMchKey", x).at("status") != 200.0)
			{
				res.set_content(nlohmann::json({
					                {"status", 401.0},
					                {"reason", "Unauthorized"}
				                }).dump(), "text/json"
				);
				return;
			}
		}
		else
		{
			res.set_content(nlohmann::json({
					{"status", 401.0},
					{"reason", "Unauthorized"}
				}).dump(), "text/json"
			);
			return;
		}
	}
	if (mods.find(classname) == mods.end())
	{
		res.set_content(nlohmann::json({
			                {"status", 404.1},
			                {"reason", "Module Not Find"}
		                }).dump(), "text/json"
		);
		return;
	}
	res.set_content(mods[classname]->call(s, x).dump(),
	                "text/json");
}
