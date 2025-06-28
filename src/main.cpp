#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "json.hpp"
#include <chrono>

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
                std::ofstream file(out);
                file << result.dump(4);
                file.close();
                std::cout << "App Found(s): "<<found++ << std::endl;
            }
        }
    }catch(const fs::filesystem_error e){
        std::cerr << "Filesystem Error: " << e.what() << std::endl;
    }
    return found;
}


int main(int argc,char *argv[]){

    if(argc < 2){
        std::cout << "Type -help for more information " << std::endl;
        return 0;
    }

    std::string path_input = argv[1];
    std::string extension = argv[2];
    std::string path_output = argv[3];
    fs::path path_as_file_system(path_input);
    auto start = std::chrono::high_resolution_clock::now();
    int output = search(path_as_file_system,extension,path_output);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end-start;
    std::cout <<"Total App Found(s): "<< output << std::endl;
    std::cout <<"Time Taken: " << duration.count() << " Seconds" << std::endl;
    return 0;
}