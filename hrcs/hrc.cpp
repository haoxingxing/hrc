#include "hrc.h"
#include <httplib.h>
#include "v1_handler.h"
#include <helper.h>
#include <nlohmann/json.hpp>
using namespace std;
using namespace httplib;
#define DEFAULT_ADDRESS "0.0.0.0"
#define DEFAULT_PORT    4096
int main(void)
{
    Server svr;
    svr.set_logger(&httphelper::logger::log_handler);
    v1_handler h(svr);
	
    svr.listen(DEFAULT_ADDRESS, DEFAULT_PORT);
}