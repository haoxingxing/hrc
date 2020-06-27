#include "hrc.h"
#include <httplib.h>

#include <helper.h>

using namespace std;
int main(void)
{
    using namespace httplib;
    httplib::Client cli("star-home.top", 4430);
    cli.set_logger(&httphelper::logger::log_handler);
    cli.set_follow_location(true);
    auto res = cli.Get("/");

    if (res && res->status == 200) {
        std::cout << res->body << std::endl;
    }
}