#include "CGI.hpp"

int main() {
    CGI cgi;
    cgi.fillDevData();
    cgi.setEnvironments();
    cgi.execute();
    return (0);
}
