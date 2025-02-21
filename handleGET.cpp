#include "CGI.hpp"

string getScriptLocation(const string& rootDir, const string& scriptDir) {
    string result;
    size_t pos = scriptDir.find("?");
    string noArguments = (pos != string::npos) ? scriptDir.substr(0, pos) : scriptDir;

    // Handle ./ + /cgi-bin/script.py (double '/')
    if (rootDir[rootDir.length() - 1] == '/' && noArguments[0] == '/') {
        result = rootDir;
        result.erase(result.length() - 1, result.length());
        result += noArguments;
    // Handle no '/'
    } else if (rootDir[rootDir.length() - 1] != '/' && noArguments[0] != '/') {
        result = rootDir + "/" + noArguments;
    // Handle normal
    } else {
        result = rootDir + noArguments;
    }

    return result;
}

void setEnvironments(string query) {
    size_t pos = query.find_first_of("?");
    if (pos != std::string::npos) {
        string queryString = query.substr(pos + 1);
        setenv("QUERY_STRING", queryString.c_str(), 1);
    } else {
        // Handle no query string
        cout << "Error!\n";
    }
}

void CGI::handleGET() {
    string scriptLocation = getScriptLocation(this->_rootDir, this->_request.url);

    setEnvironments(this->_request.url);
    cout << "Trying to access: " << scriptLocation << endl;
    int output = open("cgi_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (output < 0) {
        // Throw an error later
        cout << "Something went wrong!\n";
    } else {
        dup2(output, STDOUT_FILENO);
    }
    if (access(scriptLocation.c_str(), F_OK) == 0) {
        const char *args[] = {"/usr/bin/python3", scriptLocation.c_str(), NULL};
        extern char **environ;
        execve(args[0], (char* const*)args, environ);
    } else {
        // Page 404, script not found
        cout << "File not found." << endl;
    }
}
