#include "download.h"
#include <curl/curl.h>
#include <stdio.h>

size_t null_write(void *ptr, size_t size, size_t nmemb, void *userdata) { 
    return size * nmemb; 
}

double test_download(const char *url) {
    CURL *curl; // CURL object
    CURLcode res; // CURL result
    double speed;

    curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize CURL
    curl = curl_easy_init(); // Initialize CURL easy interface

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url); // Set URL
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, null_write); // Discard data
        res = curl_easy_perform(curl); // Perform request
        if(res != CURLE_OK) {
            fprintf(stderr, "curl perform failed: %s\n", curl_easy_strerror(res));
            return -1.0;
        }

        curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &speed); // Get speed
        curl_easy_cleanup(curl);
    } else {
        return -1.0;
    }

    curl_global_cleanup();
    return speed * 8 / 1e6; // Convert to Mbps
}
