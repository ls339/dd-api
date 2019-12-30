#include <curl/curl.h>
#include "datadog.h"
#include <string>

Datadog::Datadog(std::string api_key, std::string app_key) {
    api_key_header = "DD-API-KEY:" + api_key;
    app_key_header = "DD-APPLICATION-KEY: " + app_key;
    dd_base_url = "https://api.datadoghq.com/";
}

bool Datadog::validate() {
    std:bool valid { true };
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, api_key_header.c_str());
        chunk = curl_slist_append(chunk, app_key_header.c_str());
        curl_easy_setopt (curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_URL, dd_base_url.append("api/v1/validate").c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* Check for errors */
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            return !valid;
        }
    return valid;
    }
}
