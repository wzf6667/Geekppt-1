#pragma once

// macro defines to determine the platform
#define WINDOWS 0
#define UNIX 1
#if defined(_WIN32)
#define PLATFORM WINDOWS
#define popen _popen
#define pclose _pclose
#else
#define PLATFORM UNIX
#endif

#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include <vector>
#include <filesystem>
#include <algorithm>


enum LanguageType {
    CPP,
    JAVA,
    PYTHON
};


class CodeEvaluation {
private:
    std::string code_;
    LanguageType language_;
    std::string address_;
    std::string filename_;
    std::string compiler_;  // This private member added by qianhao, which indicates the compiler used.

public:
    /* constructors */
    CodeEvaluation(LanguageType language, std::string const& address) :
        language_(language), address_(address) {
        code_ = readTxt(address_);
        filename_ = extractFilename(address_);
        // Qianhao, Default compiler
        if (language == CPP) {
            compiler_ = "g++";
        }
        else if (language == JAVA) {
            compiler_ = "javac";
        }
        else {
            compiler_ = "";
        }
    }

    /* overloading constructors */
    CodeEvaluation(LanguageType language, std::string const& address, std::string const& compiler) :
        language_(language), address_(address), compiler_(compiler) {
        code_ = readTxt(address_);
        filename_ = extractFilename(address_);
    }

    /* helper func by HH,
       extract from absolute address the filename without suffix
       e.g. ./home/Admin/lecture_related/source.txt -> source */
    std::string extractFilename(std::string const& address);


    /**
     * used to read TXT format file and store the information in string
     *
     * @param file address
     *
     * @return string which store the content of the input txt file
    */
    std::string readTxt(std::string address) const;

    /**
    * create a file with a certain language type suffix
      and write code_ inside the file
    *
    * @return the filename of the file
    */
    std::string createAndWriteFile();

    /**
    * used to change the suffix of the given file which in txt format
    *
    * @param the wanted language such as python and java
    *
    * @return the filename of the file
    */
    std::string changeSuffix(LanguageType language);
    // todo 2 Hao Huang

    /* if not use cmake, generate compile command from a certain language and compiler
    e.g. compiler = "g++" should return "g++ filename.cpp -o filename"
    */
    std::string generateCompileCommand(std::string const& compiler);

    /* This is for unix env (defined by macro)
    e.g. filename = "main", input = "ZhaiQianhao"
    should generate "./main < &ZhaiQianhao"
     */
    std::string generateRunCommand(std::string const& filename, std::string const& input);

    /* This function is to generate input for different platforms. */
    std::string generateInputCommand(std::string const& input);


    // todo 3 Luo Wenxiang
    // /* if use cmake, HH's cmake is poor, Luo will write this */ 
    static void generateCmakeFile(const std::string& project_name,
        const std::string& main_file,
        const std::string& output_cmake_path,
        std::vector<std::string>& libs,
        const int cpp_standard = 20,
        const std::string& cmake_mini_version = "3.20");


    /* done!
       execute certain command in command line */
    void executeInCmdLine(std::string const& cmd);

    /* already finished by Zhou */
    std::string executeAndGetFromCmd(std::string const& cmd);


    // sets
    void set_address(std::string const& address) { address_ = address; }
    void set_language(LanguageType language) { language_ = language; }

    // gets
    std::string get_filename() { return filename_; }


    // todo 4 Qianhao Zhai
    /* use the above methods
       accept input and return output
       an overload function is needed for the user to specify the code to be run (addresss) */
    std::string runCode(std::string const& input);
    std::string runCode(std::string const& address, std::string const& input);
};