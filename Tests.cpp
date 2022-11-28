#include "Functional/FolderTerrorist.h"
#include <gtest/gtest.h>

using namespace BMSTU;

void createFiles(const std::filesystem::path &path_to_folder);

int checkTerFiles(const std::filesystem::path &path_to_folder);

void addFile(const std::filesystem::path &path_to_folder);

void startTerror(const std::filesystem::path &path_to_folder) {
    FolderTerror::signalProcessing();
    FolderTerror::getInstance(path_to_folder).startTerror();
}

TEST(FirstTest, CheckTerFiles) {
    std::filesystem::path path_to_folder = "Terror";
    std::filesystem::path::remove_all(path_to_folder);
    std::filesystem::create_directory(path_to_folder);
    createFiles(path_to_folder);
    std::thread thread(startTerror, std::ref(path_to_folder));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    raise(SIGTERM);
    thread.join();
}

TEST(SecondTest, ProhibitionOnTheCreationOfASecondInstanceOfTheClass) {
    std::filesystem::path path_to_folder_one = "Terror";
    std::filesystem::path path_to_folder_two = "NoTerror";
    std::filesystem::path::remove_all(path_to_folder_one);
    std::filesystem::path::remove_all(path_to_folder_two);
    std::filesystem::create_directory(path_to_folder_one);
    std::filesystem::create_directory(path_to_folder_two);
    createFiles(path_to_folder_one);
    createFiles(path_to_folder_two);
    std::thread thread_one(startTerror, std::ref(path_to_folder_one));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread thread_two(startTerror, std::ref(path_to_folder_two));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    raise(SIGTERM);
    thread_one.join();
    thread_two.join();
}
