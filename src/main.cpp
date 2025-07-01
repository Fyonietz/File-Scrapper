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
#else
int search_linux(fs::path path, std::string out) {
    nlohmann::json result;
    result["app_lists"] = nlohmann::json::array();

    int found = 0;
    int skipped_dirs = 0;
    
    try {
        std::error_code ec;
        
        // Use error_code version to handle permission errors gracefully
        for (const auto &entry : fs::recursive_directory_iterator(path, 
                                    fs::directory_options::skip_permission_denied, ec)) {
            
            if (ec) {
                // Skip this entry and continue
                std::cout << "Skipping directory due to permission: " << ec.message() << std::endl;
                skipped_dirs++;
                ec.clear();
                continue;
            }
            
            std::error_code file_ec;
            
            // Check if it's a regular file with error handling
            if (entry.is_regular_file(file_ec) && !file_ec) {
                // Check if file is executable
                if (access(entry.path().c_str(), X_OK) == 0) {
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
            }
        }
        
        if (skipped_dirs > 0) {
            std::cout << "Note: Skipped " << skipped_dirs << " directories due to permission restrictions." << std::endl;
        }

        std::ofstream file(out);
        file << result.dump(4);
        file.close();

    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem Error: " << e.what() << std::endl;
        std::cerr << "Path: " << e.path1() << std::endl;
        std::cerr << "Try running with more specific directory or with appropriate permissions." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
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
    
    // Check if command line arguments are provided as fallback
    if (argc >= 3) {
        std::cout << "Using command-line arguments..." << std::endl;
        Input_folder = argv[1];
        output_json = argv[2];
        
        // Validate paths
        if (!fs::exists(Input_folder)) {
            std::cerr << "Error: Input folder '" << Input_folder << "' does not exist!" << std::endl;
            return 1;
        }
        
        std::cout << "Input folder: " << Input_folder << std::endl;
        std::cout << "Output file: " << output_json << std::endl;
    } else {
        std::cout << "Opening file dialogs..." << std::endl;
        std::cout << "Note: If dialogs don't appear, you can use command line:" << std::endl;
        std::cout << "Usage: " << argv[0] << " <input_folder> <output.json>" << std::endl;
        std::cout << std::endl;
        
        Input_folder = tinyfd_selectFolderDialog(
            "Select Input Folder",nullptr
        );
        if(!Input_folder){
            std::cerr << "No folder selected or dialog failed." << std::endl;
            std::cerr << "Try using command line: " << argv[0] << " <input_folder> <output.json>" << std::endl;
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
        
        if(!output_json){
            std::cerr << "No output file selected or dialog failed." << std::endl;
            return 1;
        }
    }    
    std::cout << Input_folder <<std::endl;
    #ifdef _WIN32
    std::cout << extension << std::endl;
    #endif
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