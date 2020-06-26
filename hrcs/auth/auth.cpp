#include "auth.h"
#include "../tools.h"
#include "nlohmann/json.hpp"

auth::auth(httplib::Server& srv) : pmodule("auth", srv)
{
	insert("GetMchKey", [&](nlohmann::json data) -> nlohmann::json
	{
		auto x = auth::GetMachineKey(data.at("usr_id").get<std::string>());
		return
			nlohmann::json({
				{"status", x.first ? 200 : 400.1},
				{"mch_key", x.second}
				});
	});
	insert("ChkMchKey", [&](nlohmann::json data) -> nlohmann::json
		{
			auto x = auth::VerifyMachineKey(data.at("mch_key").get<std::string>());
			return
				nlohmann::json({
					{"status", x ? 200 : 400.2},
					});
		});

}



std::pair<bool, std::string> auth::login(std::string usr, std::string pwd)
{
	auto x = "usr_key_" + tools::random_string(8);
	usr_ssids.push_back(x);
	return std::make_pair(true, x);
}

std::pair<bool, std::string> auth::GetMachineKey(std::string ssid)
{
	auto x = "mch_key_" + tools::random_string(12);
	mch_ssids.push_back(x);
	return std::make_pair(true, x);
}

bool auth::VerifyMachineKey(std::string pwd)
{
	for (const auto& element : mch_ssids)
	{
		if (element == pwd)
			return true;
	}
	return false;
}
