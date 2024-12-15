#include "APIManager.h"
#include <sstream>

size_t APIManager::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

APIManager::APIManager(const std::string& baseUrl) : baseUrl(baseUrl) {}

std::string APIManager::get(const std::string& endpoint) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = baseUrl + endpoint;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add Authorization header if token is set
        if (!token.empty()) {
            struct curl_slist* headers = nullptr;
            std::string authHeader = "Authorization: " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "GET request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

std::string APIManager::post(const std::string& endpoint, const std::string& data) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = baseUrl + endpoint;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add Authorization header if token is set
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        if (!token.empty()) {
            std::string authHeader = "Authorization: " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    return response;
}

std::string APIManager::put(const std::string& endpoint, const std::string& data) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        std::string url = baseUrl + endpoint;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT"); // Set HTTP method to PUT
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add Authorization header if token exists
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        if (!token.empty()) {
            std::string authHeader = "Authorization: " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "PUT request failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return response;
}


bool APIManager::login(const std::string& username, const std::string& password) {
    Json::Value requestBody;
    requestBody["username"] = username;
    requestBody["password"] = password;

    Json::StreamWriterBuilder writer;
    std::string jsonBody = Json::writeString(writer, requestBody);

    CURL* curl = curl_easy_init();
    std::string response;
    long httpCode = 0;

    if (curl) {
        std::string url = baseUrl + "/loginadmin";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Add Content-Type header
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);

        // Get HTTP response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return false;
    }

    if (httpCode == 200) {
        Json::CharReaderBuilder reader;
        Json::Value responseBody;
        std::string errors;
        std::istringstream responseStream(response);

        if (Json::parseFromStream(reader, responseStream, &responseBody, &errors)) {
            if (responseBody.isMember("token")) {
                token = responseBody["token"].asString();
                std::cout << "Login successful. Token: " << token << std::endl;
                return true;
            } else {
                std::cerr << "Error: Response does not contain a token." << std::endl;
            }
        } else {
            std::cerr << "Failed to parse response: " << errors << std::endl;
        }
    } else if (httpCode == 401) {
        std::cerr << "Unauthorized: HTTP 401. Invalid username or password." << std::endl;
    } else {
        std::cerr << "Unexpected HTTP code: " << httpCode << ". Response: " << response << std::endl;
    }

    return false;
}

void APIManager::ping() {
    std::string response = get("/ping");
    std::cout << "Ping response: " << response << std::endl;
}

bool APIManager::secure() {
    if (token.empty()) {
        std::cerr << "Error: No token available. Please log in first." << std::endl;
        return false;
    }

    CURL* curl = curl_easy_init();
    std::string response;
    long httpCode = 0;

    if (curl) {
        std::string url = baseUrl + "/secure";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        struct curl_slist* headers = nullptr;
        std::string authHeader = "Authorization: " + token;
        headers = curl_slist_append(headers, authHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

        if (res != CURLE_OK) {
            std::cerr << "CURL error: " << curl_easy_strerror(res) << std::endl;
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return false;
    }

    return httpCode == 200;
}

std::vector<std::unordered_map<std::string, std::string>> APIManager::getInstruments() {
    std::vector<std::unordered_map<std::string, std::string>> instrumentsList;

    // Call the GET /instruments endpoint
    std::string response = get("/instruments");

    Json::CharReaderBuilder reader;
    Json::Value jsonData;
    std::string errors;

    std::istringstream responseStream(response);

    // Parse the JSON response
    if (Json::parseFromStream(reader, responseStream, &jsonData, &errors)) {
        const Json::Value& instruments = jsonData["instruments"];
        if (instruments.isArray()) {
            for (const auto& instrument : instruments) {
                if (instrument.isObject()) {
                    std::unordered_map<std::string, std::string> instrumentData;

                    for (const auto& key : instrument.getMemberNames()) {
                        instrumentData[key] = instrument[key].asString();
                    }

                    instrumentsList.push_back(instrumentData);
                }
            }
        }
    } else {
        std::cerr << "Failed to parse instruments data: " << errors << std::endl;
    }

    return instrumentsList;
}

bool APIManager::addInstrument(const std::string& isin, const std::string& mic,
                               const std::string& currency, const std::string& status) {
    Json::Value requestBody;
    requestBody["isin"] = isin;
    requestBody["mic"] = mic;
    requestBody["currency"] = currency;
    requestBody["status"] = status;

    Json::StreamWriterBuilder writer;
    std::string jsonBody = Json::writeString(writer, requestBody);

    std::string response = post("/instruments", jsonBody);

    // Simple success check
    if (response.find("successfully") != std::string::npos) {
        std::cout << "Instrument added successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to add instrument. Response: " << response << std::endl;
        return false;
    }
}
bool APIManager::modifyInstrument(const std::string& isin, const std::string& mic,
                                  const std::string& currency, const std::string& status) {
    // Ensure ISIN is provided
    if (isin.empty()) {
        std::cerr << "ISIN is required to modify an instrument." << std::endl;
        return false;
    }

    // Prepare JSON body with fields that are not empty
    Json::Value requestBody;
    requestBody["isin"] = isin; // ISIN is mandatory

    if (!mic.empty()) {
        requestBody["mic"] = mic;
    }
    if (!currency.empty()) {
        requestBody["currency"] = currency;
    }
    if (!status.empty()) {
        requestBody["status"] = status;
    }

    // Serialize JSON body
    Json::StreamWriterBuilder writer;
    std::string jsonBody = Json::writeString(writer, requestBody);

    // Endpoint for modifying the instrument
    std::string endpoint = "/modifyinstrument";
    std::string response = put(endpoint, jsonBody); // Use PUT method

    // Simple success check
    if (response.find("updated successfully") != std::string::npos) {
        std::cout << "Instrument updated successfully." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to update instrument. Response: " << response << std::endl;
        return false;
    }
}
