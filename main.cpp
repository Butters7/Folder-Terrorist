#include "Functional/FolderTerrorist.h"

using namespace BMSTU;

void createFiles(const std::filesystem::path &path_to_folder);

void addFile(const std::filesystem::path &path_to_folder);

void startTerror(const std::filesystem::path &path_to_folder) {
    FolderTerror::signalProcessing();
    FolderTerror::getInstance(path_to_folder).startTerror();
}

int main(int argc, char **argv) {
    std::filesystem::path path_to_folder = argv[1];
    std::thread thread(startTerror, std::ref(path_to_folder));
    thread.join();
    return 0;
}