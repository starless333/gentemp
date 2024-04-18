#include <cctype>
#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<cstring>
#include<set>
#include<vector>
//idea is that there is a default template.
//import java.util.*;
const std::set<std::string> commands = {"-h","-m","-nm","-CArr","-bCl","-S","-i", "-c"};
void putt(const int,const char**);
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
    std::string command = "nvim ";
    command.append(argv[1]);
    const char* ptr = command.c_str();

    system(ptr);

    return EXIT_SUCCESS;

}


void print_menu(void) {
    std::cout << "help has arrived\n";
    std::cout << "available commands to add to template\n";
    std::cout << "-i: add extra imports. ex: -i [name]...[name]\n";
    std::cout << "-bCl: add unlimited blank classes. ex: -bCl [name]...[name]\n";
    std::cout << "-nm: the generated code will not create a main.\n";
    std::cout << "-S <Implements>: creates sort method necessary for sorting Objects\n";
    std::cout << "-c: implements a class with given class variables\n";
    //class sort implements Comparator<> {}
    std::cout << "-CArr <Name><Type>: Creates an ArrayList<Object> that picks up n test cases\n";
    //int n = s.nextInt();
    //ArrayList<Type> <Name> = new ArrayList<>();
    //for(int i = 0; i < n; ++i) {<Name>.add(s.next<Type>());}
    std::cout << "-m <Name> <Return Type> <Parameter> + <Name>...: will create a method with given return types and parameters;\n";
}
bool isCommand(const std::string word) {
    return commands.count(word) != 0;
}

// note... argv[1] = file_name
//there is going to be base code and -i will run right after the base imports.
void putt(const int argc, const char** argv) {

    std::string f = argv[1];
    bool print_main = true;
    std::ofstream file;
    file.open(f);
    bool print_cin = false;
    if(!file) {
        std::cerr << "Could Not Open File.\n";
        exit(EXIT_FAILURE);
    }
    file << "import java.util.*;\nimport java.io.*;\n";
//    std::cout << file.rdbuf();
    //this loop takes care of all imports that are run in the command line.
    std::string name, type;
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
                if(commands.count(argv[j])  != 0) break;
                file << "import " << argv[j] << ";\n";
                ++j;
            }
            i=j;
        } else if(command == "-CArr")  {
            print_cin = true;
            if(i+1 >= argc || isCommand(argv[i+1])) continue;
            if(i+2 >= argc || isCommand(argv[i+2])) {name = argv[i+1]; continue;}
            if(!isCommand(argv[i+1]) && !isCommand(argv[i+2])) {name=argv[i+1]; type=argv[i+2]; i+=2; continue;}
        } else if(command == "-nm") {print_main =false;}
    }


    file << "\n";
    //this new line is just to make the code look nicer and less clunky
    //this loop takes care of the classes that are input by the user
    //relooping kind of sucks but its okay because some people may want to use multiple -i for some reason!
    //-S <Implements>
    for(int i = 2; i < argc; i++ ) {
        if(argv[i] == std::string("-S")) {
            int j = i+1;
            if(j == argc || isCommand(argv[j])) {
                // no parameters;
                file << "\nclass Sort {}\n";
                break;
            }
            file << "\nclass Sort implements " << argv[j] << "<> {\n\tpublic static int compare(Object o";
            file << ", Object k) {\n\n\t}\n}\n\n\n";
        }
    }

    for(int i = 2; i < argc; i++ ) {
        std::string command = argv[i];
        std::vector<std::string> list;
        if(command == "-c")
        {
            std::string cl_name;
            file << "class ";
            int j = i+1;
            while(j < argc-1 && !isCommand(argv[j])) {
                if(j == i+1) {
                    cl_name = argv[j];
                    file << argv[j] << " {\n";
                    j++; continue;
                }
                std::string type = argv[j];
                std::string name = argv[j+1];
                list.push_back(type);
                list.push_back(name);
                file << "\t" << type << " " << name <<";\n";
                j+=2;
            }
            file<<"\tpublic " << cl_name << "(";
            for(int k = 0; k < list.size()-1; k+=2 ) {
                file << list[k] << " " << list[k+1];
                if(k != list.size()-2) file << ", ";
            }
            file << ") {\n";
            for(int k = 1; k < list.size(); k+=2) {
                file << "\t\tthis." << list[k] << " = " << list[k] << ";\n";
            }
            file << "\t}\n";
            file << "}\n\n";
        }
    }

    for(int i = 2; i < argc; i++ ) {
        std::string command = argv[i];

        if(command == "-bCl") {
            int j = i+1;
            if(j >= argc) {
                std::cerr << "when running -c please include the classes you want!\n";
                exit(EXIT_FAILURE);
            }

            while(j < argc) {
                if(argv[j] == std::string("-nm")) {print_main = false; j++; continue;}
                if( isCommand(argv[j]) ||argv[j] == std::string("-c") || argv[j] == std::string("-i")) {
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
        file << "\n\t\twhile(T-- > 0) {\n";
        if(print_cin) {
            file << "\t\t\tint n = s.nextInt();\n";
            if(name.size() == 0) {std::cerr << "please provide name for CArr\n"; exit(EXIT_FAILURE);}
            if(type.size() == 0) {
                file <<"\t\t\tArrayList<Object> " << name << " = new ArrayList<Object> ();\n";
            }
            else file << "\t\t\tArrayList<" << type << "> " << name << " = new ArrayList<" << type<< "> ();\n";
            file << "\t\t\t" << "for(int i = 0; i < n; i++) {\n\t\t\t\t" << name << ".add(";
            file << "s.next" <<  "());\n\t\t\t}\n";
        } else {
            file << "\n";
        }
        file << "\t\t}";
        file << "\n\n\t\ts.close();\n\t}\n";
    }
    //<Name> <Return Type> <Parameters...>
    for(int i = 2; i < argc; i++ ) {
        if(argv[i] == std::string("-m")) {
            int j = i+1;
            std::vector<std::string> vec;
            while(j < argc && !isCommand(argv[j])) {
                vec.push_back(argv[j++]);
            }
            file << "\n//------------------------------------------\n";
            file << "public static " << vec[1] << " " << vec[0] <<"(";
            for(int k = 2; k < vec.size()-1; k+=2 ) {
                if(k == vec.size()-2) {file << vec[k] << " " << vec[k+1]; break;}
                file << vec[k] << " " << vec[k+1] << ", ";
            }
            file << ") {\n\n\n\treturn " << "null;\n}\n";
            i=j-1;
        }

    }
    if(print_main)file << "\n}";
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
