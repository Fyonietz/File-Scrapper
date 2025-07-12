#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include <chrono>
#include "tinyfiledialogs.h"
#ifdef __unix__
#include <unistd.h>
#endif

namespace fs=std::filesystem;
#ifdef _WIN32
int search_windows(fs::path path,std::string ext,std::string out){
    nlohmann::json result;
    result["app_lists"] = nlohmann::json::array();

    int found = 0;
    try {
        for(const auto &entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)){
            try{
                if(entry.is_regular_file() && entry.path().extension() == ext){
                    std::string app_path = fs::absolute(entry.path()).string();
                    std::string app_name = entry.path().filename().string();
                    std::string app_image = "/Assets/icon/" +  entry.path().filename().stem().string() + ".png"; 
                    nlohmann::json app;
                    app[app_name.substr(0,app_name.find_last_of('.'))]={
                        {"app_location",app_path},
                        {"app_image",app_image}
                    };
                    result["app_lists"].push_back(app);
                    std::cout << "App Found(s): "<<++found << std::endl;
                }
            }catch(const fs::filesystem_error& e){
                std::cerr << "Filesystem Error: " << e.what() << std::endl;
                continue;
            }
        }
    } catch(const fs::filesystem_error& e) {
        std::cerr << "Fatal Filesystem Error: " << e.what() << std::endl;
    }
    std::ofstream file(out);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open " << out << " for writing." << std::endl;
    } else {
        file << result.dump(4);
        file.close();
    }

    return found;
}
#else
int search_linux(fs::path path, std::string out) {
    nlohmann::json result;
    result["app_lists"] = nlohmann::json::array();

    int found = 0;
    try {
        for (const auto &entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            try {
                if (entry.is_regular_file() && access(entry.path().c_str(), X_OK) == 0) {
                    std::string app_path = fs::absolute(entry.path()).string();
                    std::string app_name = entry.path().filename().string();
                    std::string app_image = "/Assets/icon/" +  entry.path().filename().stem().string() + ".png"; 

                    nlohmann::json app;
                    app[app_name] = {
                        {"app_location", app_path},
                        {"app_image", app_image}
                    };
                    result["app_lists"].push_back(app);
                    std::cout << "App Found(s): " << ++found << std::endl;
                }
            } catch (const fs::filesystem_error &e) {
                std::cerr << "Filesystem Error: " << e.what() << std::endl;
                continue;
            }
        }
    } catch(const fs::filesystem_error& e) {
        std::cerr << "Fatal Filesystem Error: " << e.what() << std::endl;
    }

    std::ofstream file(out);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open " << out << " for writing." << std::endl;
    } else {
        file << result.dump(4);
        file.close();
    }

    return found;
}
#endif

int main(int argc,char *argv[]){
    char const *Input_folder;
    char const *output_json;
    #ifdef _WIN32
    char const *extension;
    #endif
    Input_folder = tinyfd_selectFolderDialog(
        "Select Input Folder",nullptr
    );
    if(!Input_folder){
        tinyfd_messageBox("error","Select Folder Name Is NULL","ok","error",1);
        return 1;
    };
    #ifdef _WIN32
    extension = tinyfd_inputBox(
        "Input Extension","Please Input Extension like \n .exe,.json,etc",".exe"
    );
    #endif
    const char *filter[1]={"*.json"};
    output_json = tinyfd_saveFileDialog(
        "Save File To",
        NULL,
        1,
        filter,
        NULL
    );    
    std::cout << Input_folder <<std::endl;
    std::cout << extension << std::endl;
    std::cout << output_json << std::endl;
    fs::path path_as_file_system(Input_folder);
    auto start = std::chrono::high_resolution_clock::now();
    #ifdef _WIN32
    int output = search_windows(path_as_file_system,extension,output_json);
    #else
    int output = search_linux(path_as_file_system,output_json); 
    #endif
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end-start;
    std::cout <<"Total App Found(s): "<< output << std::endl;
    std::cout <<"Time Taken: " << duration.count() << " Seconds" << std::endl;

    return 0;
}