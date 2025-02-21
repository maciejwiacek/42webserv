#include "CGI.hpp"

// ----- DEV ONLY -----

struct request {
	map<string, string> variables;
	string queryString;
};

request createTestRequest() {
	request req;

	// Example environment variables
	req.variables["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	req.variables["CONTENT_LENGTH"] = "27";
	req.variables["HTTP_USER_AGENT"] = "Mozilla/5.0";
	req.variables["REQUEST_METHOD"] = "POST";
	req.variables["SCRIPT_NAME"] = "/cgi-bin/test.cgi";
	req.variables["SERVER_PROTOCOL"] = "HTTP/1.1";

	// Example query string (simulating form data from a POST request)
	req.queryString = "name=JohnDoe&age=25";

	return req;
}

// --------------------

// --- MULTIPLE ---

void setEnvironments(request req) {
	map<string, string>::iterator itb = req.variables.begin();
	map<string, string>::iterator ite = req.variables.end();

	while (itb != ite) {
		setenv(itb->first.c_str(), itb->second.c_str(), 1);
		++itb;
	}

	setenv("QUERY_STRING", req.queryString.c_str(), 1);
}

void CGI::handlePOST() {
	cout << "Handling POST!\n";
	string scriptLocation = getScriptLocation(this->_rootDir, this->_request.url);
	request req = createTestRequest();
	setEnvironments(req);

	cout << "Trying to access: " << scriptLocation << endl;

	int output = open("cgi_output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (output < 0) {
		throw runtime_error("Couldn't open a file!");
	}

	// Create a pipe for writing POST data
	int pipefd[2];
	if (pipe(pipefd) == -1) {
		throw runtime_error("Pipe failed!");
	}

	pid_t pid = fork();
	if (pid < 0) {
		throw runtime_error("Fork failed!");
	}
	if (pid == 0) {  // Child process
		close(pipefd[1]);  // Close write end (child only reads)
		dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe
		close(pipefd[0]);  // Close pipe read end

		dup2(output, STDOUT_FILENO);
		close(output);

		if (access(scriptLocation.c_str(), F_OK) == 0) {
			const char *args[] = {"/usr/bin/python3", scriptLocation.c_str(), NULL};
			extern char **environ;
			execve(args[0], (char *const *)args, environ);
			_exit(127); // Exit if execve fails
		} else {
			cerr << "File not found." << endl;
			_exit(1);
		}
	} else {  // Parent process
		close(pipefd[0]);  // Close read end (parent only writes)

		// Send POST data to the script
		string postData = req.queryString;  // Simulate actual POST body
		write(pipefd[1], postData.c_str(), postData.size());
		close(pipefd[1]);  // Close pipe write end (EOF for child)

		close(output);
		int status;
		waitpid(pid, &status, 0);  // Wait for the child process
	}
}

