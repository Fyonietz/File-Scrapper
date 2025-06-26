#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
namespace fs=std::filesystem;
int main(int argc,char *argv[]){

    if(argc < 1 || argc == 1){
        std::cout << "Type -help for more information " << std::endl;
        return 0;
    }

    std::string path_input = argv[1];
    fs::path path_as_file_system(path_input);



    std::cout << path_as_file_system << std::endl;
    return 0;
}