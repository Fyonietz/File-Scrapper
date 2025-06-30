#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include <chrono>
#include "tinyfiledialogs.h"


namespace fs=std::filesystem;

int search(fs::path path,std::string ext,std::string out){
    nlohmann::json result;
    result["app_lists"] = nlohmann::json::array();

    int found = 0;
    try{
        for(const auto &entry : fs::recursive_directory_iterator(path)){
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
        }
                std::ofstream file(out);
                file << result.dump(4);
                file.close();

    }catch(const fs::filesystem_error e){
        std::cerr << "Filesystem Error: " << e.what() << std::endl;
    }
    return found;
}


int main(int argc,char *argv[]){
    char const *Input_folder;
    char const *output_json;

    Input_folder = tinyfd_selectFolderDialog(
        "Select Input Folder",nullptr
    );
    if(!Input_folder){
        tinyfd_messageBox("error","Select Folder Name Is NULL","ok","error",1);
    };
    const char *filter[1]={"*.json"};
    output_json = tinyfd_saveFileDialog(
        "Save File To",
        NULL,
        1,
        filter,
        NULL
    );    
    std::cout << Input_folder <<std::endl;
    fs::path path_as_file_system(Input_folder);
    auto start = std::chrono::high_resolution_clock::now();
    int output = search(path_as_file_system,".exe",output_json);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end-start;
    std::cout <<"Total App Found(s): "<< output << std::endl;
    std::cout <<"Time Taken: " << duration.count() << " Seconds" << std::endl;

    return 0;
}