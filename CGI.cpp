#include "CGI.hpp"
#include <complex>
#include <cstdlib>
#include <stdexcept>
#include <unistd.h>

void CGI::setEnvironments() {
    map<string, string>::iterator itb = _req.vars.begin();
    map<string, string>::iterator ite = _req.vars.end();

    while (itb != ite) {
        setenv(itb->first.c_str(), itb->second.c_str(), 1);
        ++itb;
    }

    if ((string)REQ_TYPE == "GET")
        setenv("QUERY_STRING", _req.queryString.c_str(), 1);
}

void handleChild(string scriptPath, string type, int *pipefd) {
    if (type == "POST") {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
    }
    if (access(scriptPath.c_str(), F_OK) == 0) {
        const char *args[] = {"/usr/bin/python3", scriptPath.c_str(), NULL};
        extern char **environ;
        execve(args[0], (char * const *)args, environ);
    } else {
        throw runtime_error("Something went wrong!");
    }
}

void handleParent(string queryString, string type, int *pipefd, pid_t pid) {
    if (type == "POST") {
        close(pipefd[0]);
        write(pipefd[1], queryString.c_str(), queryString.size());
        close(pipefd[1]);
    }
    waitpid(pid, NULL, 0);
}

void CGI::execute() {
    cout << "Trying to access: " << _scriptPath << endl;

    int output = open("cgi_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (output < 0)
        throw runtime_error("Couldn't open a file!");
    else {
        dup2(output, STDOUT_FILENO);
        close(output);
    }

    int pipefd[2];
    if ((string)REQ_TYPE == "POST") {
        pipe(pipefd);
    }
    pid_t pid = fork();
    if (pid < 0) {
        throw runtime_error("Failed to create a fork!");
    } else if (pid == 0) {
        handleChild(_scriptPath, REQ_TYPE, pipefd);
    } else {
        handleParent(_req.queryString, REQ_TYPE, pipefd, pid);
    }
}
