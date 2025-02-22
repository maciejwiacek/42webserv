#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define REQ_TYPE "GET"

using namespace std;

struct request {
    map<string, string> vars;
    string queryString;
};

class CGI {
    private:
        string _scriptPath;
        request _req;
    public:
        void fillDevData();
        void setEnvironments();
        void execute();
};
