// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-25
#ifndef INC_COMMON_HPP_
#define INC_COMMON_HPP_
#include <iostream>
#include <string>
#include <filesystem>

#ifndef ROOT_PATH_KEY_DIR
#define ROOT_PATH_KEY_DIR "build"
#endif // !ROOT_PATH_KEY_DIR


namespace beiklive{

    namespace filesystem{
        std::string getProjectRootDirectory() {
            const std::string keyDir = ROOT_PATH_KEY_DIR;
            std::string separator = "/";
        #ifdef _WIN32
            separator = "\\";
        #endif
            const std::string keyDirWithSeparator = separator + keyDir;
            const std::string currentFilePath = std::filesystem::current_path().string();
            const std::size_t found = currentFilePath.rfind(keyDirWithSeparator);

            if (found != std::string::npos) {
                return currentFilePath.substr(0, found);
            }

            return "";
        }
    }
}




#endif  // INC_COMMON_HPP_
