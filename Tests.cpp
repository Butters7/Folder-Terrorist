#include "Functional/FolderTerrorist.h"
#include <gtest/gtest.h>

using namespace BMSTU;

void createFiles(const std::filesystem::path &path_to_folder);

void addFile(const std::filesystem::path &path_to_folder);

void startTerror(const std::filesystem::path &path_to_folder, int &res) {
    FolderTerror::signalProcessing();
    FolderTerror::getInstance(path_to_folder).startTerror();
    res = FolderTerror::checkTerFiles(path_to_folder);
}

TEST(FirstTest, CheckTerFiles) {
    int res = 0;
    std::filesystem::path path_to_folder = "Terror";
    std::filesystem::remove_all(path_to_folder);
    std::filesystem::create_directory(path_to_folder);
    createFiles(path_to_folder);
    std::thread thread(startTerror, std::ref(path_to_folder), std::ref(res));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    raise(SIGTERM);
    thread.join();
    EXPECT_EQ(res, 99);
}

TEST(SecondTest, ProhibitionOnTheCreationOfASecondInstanceOfTheClass) {
    int res1 = 0, res2 = 0;
    std::filesystem::path path_to_folder_one = "Terror";
    std::filesystem::path path_to_folder_two = "NoTerror";
    std::filesystem::remove_all(path_to_folder_one);
    std::filesystem::remove_all(path_to_folder_two);
    std::filesystem::create_directory(path_to_folder_one);
    std::filesystem::create_directory(path_to_folder_two);
    createFiles(path_to_folder_one);
    createFiles(path_to_folder_two);
    std::thread thread_one(startTerror, std::ref(path_to_folder_one), std::ref(res1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::thread thread_two(startTerror, std::ref(path_to_folder_two), std::ref(res2));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    raise(SIGTERM);
    thread_one.join();
    thread_two.join();
    EXPECT_EQ(res1, 99);
    EXPECT_EQ(res2, 0);
}

TEST(ThirdTest, CheckForTerrorAfterSignal) {
    int res = 0;
    std::filesystem::path path_to_folder = "Terror";
    std::filesystem::remove_all(path_to_folder);
    std::filesystem::create_directory(path_to_folder);
    createFiles(path_to_folder);
    std::thread thread(startTerror, std::ref(path_to_folder), std::ref(res));
    addFile(path_to_folder);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    raise(SIGTERM);
    addFile(path_to_folder);
    thread.join();
    EXPECT_EQ(res, 100);
}
