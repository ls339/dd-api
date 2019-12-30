#ifndef DATADOG_DATADOG_H
#define DATADOG_DATADOG_H
#include <string>

class Datadog {
private:
    std::string api_key_header, app_key_header, dd_base_url;
public:
    Datadog(std::string api_key, std::string app_key);

    bool validate();
};

#endif //DATADOG_DATADOG_H
