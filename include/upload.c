#include "upload.h"
#include <curl/curl.h>
#include <stdio.h>

double test_upload(const char *url, const char *data_path) {
    CURL *curl; // CURL object
    CURLcode res; // CURL result
    FILE *fp = fopen(data_path, "rb"); // Open file
    double speed;

    if(!fp) {
        perror("Failed to open file");
        return -1.0;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT); // Initialize CURL
    curl = curl_easy_init(); // Initialize CURL easy interface

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url); // Set URL
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L); // Upload
        curl_easy_setopt(curl, CURLOPT_READDATA, fp); // Set file
        res = curl_easy_perform(curl); // Perform request
        if(res !- CURLE_OK) {
            fprintf(stderr, "curl perform failed: %s\n", curl_easy_strerror(res));
            return -1.0;
        }

        curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed); // Get speed
        curl_easy_cleanup(curl);
    } else {
        fclose(fp);
        return -1.0;
    }

    fclose(fp);
    curl_global_cleanup();
    return speed * 8 / 1e6; // Convert to Mbps
}