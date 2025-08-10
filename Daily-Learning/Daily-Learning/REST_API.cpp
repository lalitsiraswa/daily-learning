#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <curl/curl.h>

namespace fs = std::filesystem;

// Callback function to write downloaded data directly into a file stream
size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    size_t totalSize = size * nmemb;
    std::ofstream *out = static_cast<std::ofstream *>(userp);
    out->write(static_cast<char *>(contents), totalSize);
    return totalSize;
}

// Function to download a file from a URL and save it to outputPath
bool downloadFile(const std::string &url, const std::string &outputPath, const std::string &caCertPath){
    std::cout << "[LOG] Downloading from URl: " << url << "\n";
    std::cout << "[LOG] Saving to: " << outputPath << "\n";
    
    // Ensure output directory exists
    fs::path outpathFilePath = outputPath;
    fs::path outputDirPath = outpathFilePath.parent_path();
    if(!outputDirPath.empty()){
        try{
            fs::create_directory(outputDirPath);
            std::cout << "[LOG] Ensured output directory exists: " << outputDirPath << "\n";
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "[ERROR] Filed to create output directory: " << outputDirPath << "\n"
            << "Error: " << e.what() << "\n";
            return false;
        }
    }
    // Initialize libcurl
    CURL *curl = curl_easy_init();
    if(!curl){
        std::cerr << "[ERROR] curl_easy_init() failed.\n";
        return false;
    }
    // Open the file to write downloaded content
    std::ofstream outFile(outputPath, std::ios::binary);
    if(!outFile){
        std::cerr << "[ERROR] Failed to open " << outputPath << " for writing.\n";
        curl_easy_cleanup(curl);
        return false;
    }
    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &outFile);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    
    // Use CA certificate if provided
    if(!caCertPath.empty()){
        curl_easy_setopt(curl, CURLOPT_CAINFO, caCertPath.c_str());
        std::cout << "[LOG] Using CA Certificate: " << caCertPath << "\n";
    }
    
    // Perform the file download
    CURLcode res = curl_easy_perform(curl);
    
    // Close file and cleanup CURL resources
    outFile.close();
    curl_easy_cleanup(curl);
    
    // Check for errors during download
    if (res != CURLE_OK)
    {
        std::cerr << "[ERROR] Download failed: " << curl_easy_strerror(res) << "\n";
        // Optionally remove incomplete file
        try { fs::remove(outputPath); } catch (...) {}
        return false;
    }

    std::cout << "[LOG] Download successful!\n";
    return true;
}

// Main program demonstrating how to use the downloadFile function
int main()
{
    std::string url = "https://www.example.com/index.html"; // Change to the actual URL you want to download
    std::string outputPath = "/Users/lavik/Downloads/index.html";        // Path where the file will be saved
    std::string caCertPath = "";                             // Path to CA cert file or empty if you want to skip
    bool success = downloadFile(url, outputPath, caCertPath);
    if (success)
    {
        std::cout << "File downloaded successfully to '" << outputPath << "'\n";
    }
    else
    {
        std::cout << "Download failed.\n";
    }

    return 0;
}
