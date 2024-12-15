#ifndef APIMANAGERTEST_APIMANAGER_H
#define APIMANAGERTEST_APIMANAGER_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <json/json.h>
#include <vector>
#include <unordered_map>
class APIManager {
private:
    std::string baseUrl;
    std::string token;

    // Static callback function to handle response data
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);

public:
    APIManager(const std::string& baseUrl);

    std::string get(const std::string& endpoint);
    std::string post(const std::string& endpoint, const std::string& data);
    std::string put(const std::string& endpoint, const std::string& data);
    std::string del(const std::string& endpoint);



    bool login(const std::string& username, const std::string& password);
    void ping();
    bool secure();
    bool addInstrument(const std::string& isin, const std::string& mic,
                       const std::string& currency, const std::string& status);
    bool modifyInstrument(const std::string& isin, const std::string& mic,
                                  const std::string& currency, const std::string& status);

    bool dellInstrument(const std::string& isin);
    std::vector<std::unordered_map<std::string, std::string>> getInstruments();

};

#endif //APIMANAGERTEST_APIMANAGER_H
