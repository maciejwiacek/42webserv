#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

// temporary config, later take it from config file
#define SAMPLE_CONFIG "root ./\n" \
                       "cgi_path /usr/bin/python3 /bin/shell\n" \
                       "cgi_ext .py .sh"

#define SAMPLE_HEADER "POST /cgi-bin/script.py?name=Test&age=20 HTTP/1.1"

struct reqStruct {
    string method;
    string url;
    string standard;
};

class CGI {
private:
    string _rootDir;
    map<string, string> _exec;
    reqStruct _request;

    CGI();
public:
    CGI(const string& config, const string& header);
    ~CGI();
    void handleGET();
	void handlePOST();
};

// CGIHelpers.cpp
map<string, string> createMap(const string& s1, const string& s2);
string getValue(const string& str);
void parseCGIConfig(const string& config, string& rootDir, map<string, string>& exec);
void parseRequest(const string& request, reqStruct& req);

// TO SORT
string getScriptLocation(const string& rootDir, const string& scriptDir);