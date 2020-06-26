#include "hrc.h"
#include <httplib.h>

#include <helper.h>

using namespace std;
int main(void)
{
    using namespace httplib;
    httplib::Client cli("localhost", 1234);
    cli.set_logger(&httphelper::logger::log_handler);
    auto res = cli.Get("/hi");
    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
}