#include <string>
#include <iostream>
#include <fstream>

void settingUpEnvironment(const std::string &filetype)
{
    if(filetype == "cpp" || filetype == "hpp"){
        //init keyword/token detection for c++
        std::cout << "C++ extension detected" << std::endl;
    }
}

void openFile(const std::string &filename){
    if (filename.length() == 0) return;
	// Open file 
    std::string filetype = filename.substr(filename.find('.', filename.length()-5)+1);
    std::ifstream file;
    file.open(filename, std::ios::binary | std::ios::in);
    std::string str;
    
    std::cout << filetype << std::endl;
    
    settingUpEnvironment(filetype);
        
    while(true){
        getline(file, str);
        if(file.fail()) break;
        std::cout << str << std::endl;
    }
}

int main(int argc, char* argv[]){
    std::cout << "Welcome to YATE" << std::endl;
    if(argv[1]){
        std::cout << "Open file" << std::endl;
        std::string filename = argv[1];
        openFile(filename);
        std::cout << "File opened.." << std::endl;
    }
    while(true){
        std::cout << "Check for incoming character.." << std::endl;
        char in;
        std::cin.get(in);
        std::cin.clear();
        while(in != '\n'){
            std::cin.get(in);
            std::cin.clear();
        }
    }
	return 0;
}
