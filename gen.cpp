#include <cctype>
#include<iostream>
#include<cstdlib>
#include <stdint.h>
#include <stdlib.h>
#include<string>
#include<fstream>
#include<cstring>

//idea is that there is a default template. 
//import java.util.*;
void putt(const int,const char** );
void print_menu(void);
int isFile(const char* file);
int isHelp(const char* command);

int main(const int argc, const char** argv) {
    if( argc == 2 && isHelp(argv[1])) {
        print_menu();
        return EXIT_SUCCESS;
    }

    if(argc < 2 || !isFile(argv[1]))  {
        std::cerr << "invalid input. please include file and or commands\n";
        std::cerr << "for more information on what commands can be called run ./gen -h\n";
        return EXIT_FAILURE;
    }   
    putt(argc, argv);
    
    return EXIT_SUCCESS;

}

void print_menu(void) {
    std::cout << "help has arrived\n";
    std::cout << "available commands to add to template\n";
    std::cout << "-i: add extra imports. ex: -i [name]...[name]\n";
    std::cout << "-c: add classes. ex: -c [name]...[name]\n";
    std::cout << "-nm: the generated code will not create a main.";
}

// note... argv[1] = file_name
//there is going to be base code and -i will run right after the base imports.
void putt(const int argc, const char** argv) {
    
    std::string f = argv[1];
    bool print_main = true;    
    std::ofstream file;
    file.open(f);

    if(!file) {
        std::cerr << "Could Not Open File.\n";
        exit(EXIT_FAILURE);
    }
    file << "import java.util.*;\nimport java.io.*;\n";
//    std::cout << file.rdbuf();
    //this loop takes care of all imports that are run in the command line.
    for(int i = 2; i < argc; i++ ) {
        std::string command = argv[i];
        if(command == "-i") {
            int j = i+1;
            
            if(j >= argc) {
                std::cerr << "when running -i please include the imports you want!\n";
                exit(EXIT_FAILURE);
            }


            while(j < argc) {
                if(argv[j] == std::string("-nm")) {print_main = false; j++; continue;} 
                if(argv[j] == std::string("-c") || argv[j] == std::string("-i")) {
                    break;
                }
                file << "import " << argv[j] << ";\n";
                ++j;
            }
            i=j;
        } 
    }
   
    file << "\n";
    //this new line is just to make the code look nicer and less clunky 
    //this loop takes care of the classes that are input by the user
    //relooping kind of sucks but its okay because some people may want to use multiple -i for some reason!
    
    for(int i = 2; i < argc; i++ ) {
        std::string command = argv[i];

        if(command == "-c") {
            int j = i+1;
            if(j >= argc) {
                std::cerr << "when running -c please include the classes you want!\n";
                exit(EXIT_FAILURE);
            }
            
            while(j < argc) {
                if(argv[j] == std::string("-nm")) {print_main = false; j++; continue;} 
                if(argv[j] == std::string("-c") || argv[j] == std::string("-i")) {
                    break;
                }
                file << "class " << argv[j] << " {\n\n";
                file << "}\n\n";
                j++;
            }
            i=j-1;
        } 
    }
        
    //anything that is not after its explicit command will not be written to. just so you know. 
    uint8_t left = 0, right = f.size()-1;
    while(!std::isalpha(f[left]) || f[right] != '.') {
        if(f[right] == '.' && !std::isalpha(f[left])) {
            left++;
            continue;
        } else if(std::isalpha(f[left]) && f[right] != '.') {
            right--;
            continue;
        }
        left++;
        right--;
    }
    f = f.substr(left,right-left);
    if(print_main) {
        file << "public class " << f << " {\n";
        file << "\tpublic static void main(String[] args) throws IOException {\n";
        file << "\n\t\tScanner s = new Scanner(new File(\"" << f << ".dat\"));\n\n"; 
        file << "\t\tint T = s.nextInt();\n";
        file << "\n\t\twhile(T-- > 0) {\n\n\t\t}\n\n\n";
        file << "\n\n\t\ts.close();\n\t}\n}";
    }

    file.close();

    return;
}

//as long as there is a . in the file name we will accept it
int isFile(const char* file) {
    int size = std::strlen(file);
    for(int i = 1; i < size-1; i++ ) {
        if(file[i] == '.') return 1;
    }
    return 0;
} 

int isHelp(const char *command) {
    int size = std::strlen(command);
    if(size!=2) return 0; 
    if(command[0] != '-' || command[1] != 'h') return 0;
    return 1;  
}
