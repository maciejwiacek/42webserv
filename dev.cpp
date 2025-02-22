#include "CGI.hpp"

request fillRequest() {
    request res;

    res.vars["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
    res.vars["CONTENT_LENGTH"] = "27";
    res.vars["HTTP_USER_AGENT"] = "Mozilla/5.0";
    res.vars["SCRIPT_NAME"] = "/cgi-bin/script.py";
    res.vars["SERVER_PROTOCOL"] = "HTTP/1.1";

    res.queryString = "name=Henry&age=18";
    return res;
}

void CGI::fillDevData() {
    this->_scriptPath = "./cgi-bin/script.py";
    this->_req = fillRequest();
}
