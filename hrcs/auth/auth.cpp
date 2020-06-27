#include "auth.h"
#include "../tools.h"
#include "nlohmann/json.hpp"

auth::auth(httplib::Server& srv,db* database) : pmodule("auth", srv,database)
{
	insert("Login", [&](nlohmann::json data) -> nlohmann::json
		{
			auto x = auth::login(data.at("user"), data.at("password"));
			return
				nlohmann::json({
					{"status", x.first ? 200 : 400.1},
					{"usr_key", x.second}
					});
		});
	insert("GetMchKey", [&](nlohmann::json data) -> nlohmann::json
	{
		auto x = auth::GetMachineKey(data.at("usr_id"));
		return
			nlohmann::json({
				{"status", x.first ? 200 : 400.1},
				{"mch_key", x.second}
				});
	});
	insert("ChkMchKey", [&](nlohmann::json data) -> nlohmann::json
		{
			auto x = auth::VerifyMachineKey(data.at("mch_key"));
			return
				nlohmann::json({
					{"status", x ? 200 : 400.2},
					});
		});
}


std::pair<bool, std::string> auth::login(std::string usr, std::string pwd)
{
	if (database->get("users")[usr]["password"] == pwd) {
		auto x = "usr_key_" + tools::random_string(8);
		usid[x] = usr;
		return std::make_pair(true, x);
	}
	else
	{
		return std::make_pair(false, "");
	}
	
}


std::pair<bool, std::string> auth::GetMachineKey(std::string ssid)
{
	if (!VerifyUsrKey(ssid))
		return std::make_pair(false, "");;
	auto x = "mch_key_" + tools::random_string(12);
	database->get("machines")[x] = { {"status",101}, {"status_str" ,"Pending"} };
	return std::make_pair(true, x);
}

bool auth::VerifyMachineKey(std::string pwd) const
{
	return database->get("machines").contains(pwd);
}

bool auth::VerifyUsrKey(std::string pwd)
{
	for (const auto& element : usid)
	{
		if (element.first == pwd)
			return true;
	}
	return false;
}
