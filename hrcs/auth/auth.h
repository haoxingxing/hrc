#ifndef AUTH_H
#define AUTH_H
#include <string>
#include <helper.h>
#include <vector>
#include "../module.h"

//
//
//    USERS
//   |      |
//  login   register
//   |        |  
//  usid <----|
//   |
//   |
//   ---> userid <-- usid
//		     |---------------|
//	  GetNewMachineKey     AccessControl
//
//
//    Machines
//    |
//    | register with machine key
//    | (mch_key)
//

class auth : public pmodule
{
private:
	std::map<std::string, std::string> usid;
		
public:
	auth(httplib::Server& srv, db* database);
	std::pair<bool, std::string> login(std::string usr,std::string pwd);
	std::pair<bool, std::string> reg(std::string usr, std::string pwd);
	std::pair<bool, std::string> GetMachineKey(std::string ssid);
	bool DelMachineKey(std::string usr, std::string pwd);
	bool VerifyMachineKey( std::string pwd) const;
	bool VerifyUsrKey(std::string pwd);
	

};
#endif // AUTH_H
