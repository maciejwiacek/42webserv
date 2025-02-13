#include "CGI.hpp"

// Create a map from two space separated strings
// s1 = "a b c", s2 = "1 2 3"
// map = {"a", "1"}, {"b", "2"}, {"c", "3"}
map<string, string> createMap(const string& s1, const string& s2) {
    map<string, string> result;
    istringstream stream1(s1);
    istringstream stream2(s2);

    string key, value;

    while (stream1 >> key && stream2 >> value) {
        result[key] = value;
    }
    return result;
}

// Returns a value
// s1 = "key value value value"
// result = "value value value"
// s1 = "       key      value     value      value      "
// result = "value value value"
string getValue(const string& str) {
    string key, value, result;
    istringstream stream(str);
    stream >> key;
    while (stream >> value) {
        result.append(value);
        result.append(" ");
    }
    result.erase(result.length() - 1, result.length());
    return result;
}

void parseCGIConfig(const string& config, string& rootDir, map<string, string>& exec) {
    istringstream stream(config);
    string paths, execs;

    // Make error handling
    // Root - cannot be empty, cannot have multiple values (no spaces after getValue)
    // Paths/execs - cannot be empty
    // Config - cannot be empty
    // Possibly make the function throw an error
    getline(stream, rootDir);
    rootDir = getValue(rootDir);
    getline(stream, paths);
    paths = getValue(paths);
    getline(stream, execs);
    execs = getValue(execs);
    exec = createMap(paths, execs);
}

void parseRequest(const string& request, reqStruct& req) {
    istringstream reqStream(request);

    reqStream >> req.method >> req.url >> req.standard;
}