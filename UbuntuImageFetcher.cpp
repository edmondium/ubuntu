// UbuntuImageFetcher.cpp - Implementation using libcurl and nlohmann/json
#include "IUbuntuImageFetcher.h"
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

class UbuntuImageFetcher : public IUbuntuImageFetcher {
private:
    const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string fetchJSON() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        
        return readBuffer;
    }

public:
    std::vector<std::string> getSupportedReleases() override {
        std::string jsonData = fetchJSON();
        auto json = nlohmann::json::parse(jsonData);
        std::vector<std::string> releases;

        for (auto& item : json["products"].items()) {
            releases.push_back(item.key());
        }
        return releases;
    }

    std::string getLatestLTSVersion() override {
        std::string jsonData = fetchJSON();
        auto json = nlohmann::json::parse(jsonData);
        std::string latestLTS;
        
        for (auto& item : json["products"].items()) {
            std::string releaseKey = item.key();
            std::string releaseTitle = item.value().value("release_title", "");
            std::string arch = item.value().value("arch", "");

            if (releaseTitle.find("LTS") != std::string::npos && arch == "amd64") {
                latestLTS = releaseKey;
            }
        }
        
        if (!latestLTS.empty()) {
            size_t secondLastColon = latestLTS.rfind(":", latestLTS.rfind(":") - 1);
            size_t lastColon = latestLTS.rfind(":");

            if (secondLastColon != std::string::npos && lastColon != std::string::npos) {
                return latestLTS.substr(secondLastColon + 1, lastColon - secondLastColon - 1); // Extract version
            }
        }
        return "Unknown";
    }

    std::string getSHA256Checksum(const std::string& release) override {
        std::string jsonData = fetchJSON();
        auto json = nlohmann::json::parse(jsonData);
        
        for (auto& item : json["products"].items()) {
            std::string productKey = item.key();
            std::string releaseCodename = item.value().value("release", "");

            if (releaseCodename == release) {
                try {
                    for (auto& version : item.value()["versions"].items()) { 
                        if (version.value()["items"].contains("disk1.img") && 
                            version.value()["items"]["disk1.img"].contains("sha256")) {
                            return version.value()["items"]["disk1.img"]["sha256"].get<std::string>();
                        }
                    }
                } catch (...) {
                    return "SHA256 not available";
                }
            }
        }
        return "Not found";
    }
};
