#include "auth.h"
#include "../tools.h"
#include "nlohmann/json.hpp"

auth::auth(httplib::Server& srv) : pmodule("auth", srv)
{
	insert("Login", [&](nlohmann::json data) -> nlohmann::json
		{
			auto x = auth::login(data.at("user"), data.at("password"));
			save();
			return
				nlohmann::json({
					{"status", x.first ? 200 : 400.1},
					{"usr_key", x.second}
					});
		});
	insert("GetMchKey", [&](nlohmann::json data) -> nlohmann::json
	{
		auto x = auth::GetMachineKey(data.at("usr_id"));
		save();
		return
			nlohmann::json({
				{"status", x.first ? 200 : 400.1},
				{"mch_key", x.second}
				});
	});
	insert("ChkMchKey", [&](nlohmann::json data) -> nlohmann::json
		{
			auto x = auth::VerifyMachineKey(data.at("mch_key"));
			save();
			return
				nlohmann::json({
					{"status", x ? 200 : 400.2},
					});
		});
	std::ifstream i("users.json");
	i >> users;
	std::ifstream i2("machines.json");
	i2 >> machines;

}

void auth::save()
{
	std::ofstream o("users.json");
	o <<  users << std::endl;
	std::ofstream o2("machines.json");
	o2 << machines << std::endl;
}


std::pair<bool, std::string> auth::login(std::string usr, std::string pwd)
{
	if (users[usr]["password"] == pwd) {
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
	machines[x] = { {"status",101}, {"status_str" ,"Pending For First Sign"} };
	return std::make_pair(true, x);
}

bool auth::VerifyMachineKey(std::string pwd)
{
	return machines.contains(pwd);
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
