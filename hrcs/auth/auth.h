#ifndef AUTH_H
#define AUTH_H
#include <string>
#include <helper.h>
#include <vector>
#include "../module.h"
class auth : public pmodule
{
private:
	std::vector<std::string> usr_ssids;
	std::vector<std::string> mch_ssids;

public:
	auth(httplib::Server& srv);
	std::pair<bool, std::string> login(std::string usr,std::string pwd);
	std::pair<bool, std::string> regter(std::string usr, std::string pwd);
	std::pair<bool, std::string> GetMachineKey(std::string ssid);
	bool DelMachineKey(std::string usr, std::string pwd);
	bool VerifyMachineKey( std::string pwd);
	

};
#endif // AUTH_H
