#ifndef JSONBRIDGE_H
#define JSONBRIDGE_H

class JsonBridge {
    std::string m_file_path;
    public:
        nlohmann::json data;

        bool load(const std::string& filePath);
        bool saveCurrentState();
        const std::string getFilePath();
};

#endif
