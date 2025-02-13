#include "CGI.hpp"

CGI::CGI(const std::string &config, const std::string &header) {
    parseCGIConfig(config, this->_rootDir, this->_exec);
    parseRequest(header, this->_request);
    if (this->_request.method == "GET") {
        handleGET();
    } else if (this->_request.method == "POST") {
        cout << "POST\n";
    } else if (this->_request.method == "DELETE") {
        cout << "DELETE\n";
    } else {
        cout << "Error!\n";
    }
}

CGI::~CGI() {}

int main() {
    CGI cgi(SAMPLE_CONFIG, SAMPLE_HEADER);
}