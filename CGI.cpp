#include "CGI.hpp"

CGI::CGI(const string &config, const string &header) {
    parseCGIConfig(config, this->_rootDir, this->_exec);
    parseRequest(header, this->_request);
    if (this->_request.method == "GET") {
		try {
			handleGET();
		} catch (std::exception& e) {
			cout << e.what() << endl;
		}
    } else if (this->_request.method == "POST") {
	    try {
		    handlePOST();
	    } catch (std::exception& e) {
		    cout << e.what() << endl;
	    }
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