#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <fstream>
namespace fs=std::filesystem;

int main(int argc,char *argv[]){

    if(argc < 1 || argc == 1){
        std::cout << "Type -help for more information " << std::endl;
        return 0;
    }

    std::string path_input = argv[1];
    std::string extension = argv[2];
    std::string path_output = argv[3];
    std::string file;
    int found = 0;
    fs::path path_as_file_system(path_input);
    
    try {
        for(const auto &entry : fs::recursive_directory_iterator(path_as_file_system)){
            if(entry.is_regular_file() && entry.path().extension() == extension){
                std::string file = "\"" + fs::absolute(entry.path()).string() +  "\"" + "\n" ;
                std::ofstream file_output(path_output,std::ios::app);
                file_output << file;
                found++;
                std::cout << "File Found(s): " << found << std::endl;
            }
        }
    } catch(const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    std::cout << "Total File Found(s): " << found << std::endl;
    return 0;
}