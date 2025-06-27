#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
#include "json.hpp"

namespace fs=std::filesystem;

std::pair<int,std::vector<std::string>> search(fs::path path,std::string ext,std::string out){
    std::string app_path;
    std::vector<std::string> app_name;
    int found = 0;
    try{
        for(const auto &entry : fs::recursive_directory_iterator(path)){
            if(entry.is_regular_file() && entry.path().extension() == ext){
                app_path = "\"" + fs::absolute(entry.path()).string() +  "\"" + "\n" ;
                app_name.push_back(entry.path().filename().string());
                std::ofstream file(out,std::ios::app);
                file << app_path;
                found++;
                // std::cout << "Total File Found(s): " << found++ << std::endl;
            }
        }
    }catch(const fs::filesystem_error e){
        std::cerr << "Filesystem Error: " << e.what() << std::endl;
    }
    return{found,app_name};
}


int main(int argc,char *argv[]){

    if(argc < 1 || argc == 1){
        std::cout << "Type -help for more information " << std::endl;
        return 0;
    }

    std::string path_input = argv[1];
    std::string extension = argv[2];
    std::string path_output = argv[3];
    fs::path path_as_file_system(path_input);
    auto [total_founds,names] = search(path_as_file_system,extension,path_output);
    for(const auto name : names){
        std::cout << "Found: " << name << std::endl;
    }
    std::cout << "File Found(s): " << total_founds << std::endl;

    return 0;
}