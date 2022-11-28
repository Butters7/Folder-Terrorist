#include <filesystem>
#include <fstream>

void createFiles(const std::filesystem::path &path_to_folder) {
    const std::string slash = std::filesystem::current_path().root_directory().string();
    const std::filesystem::path path_to_new_directory = path_to_folder.string() + slash + "HW3_1";
    std::filesystem::create_directory(path_to_new_directory);
    const std::string random_string = "gkrfegoqiy3r7g9y59g8hirhfvlkdac'[ 0i2-   cr92ru9ruc 14r438ru";
    for (size_t i = 1; i < 100; i++) {
        std::ostringstream ost;
        ost << i;
        std::filesystem::path path_to_file = path_to_new_directory.string() + slash + "in_" + ost.str() + ".txt";
        std::ofstream record(path_to_file, std::ios::out);
        record << random_string;
        record.close();
    }
}

void addFile(const std::filesystem::path &path_to_folder) {
    const std::string slash = std::filesystem::current_path().root_directory().string();
    std::filesystem::path path_to_file = path_to_folder.string() + slash + "in_a.txt";
    const std::string random_string = "gkrfegoqiy3r7g9y59g8hirhfvlkdac'[ 0i2-   cr92ru9ruc 14r438ru";
    std::ofstream record(path_to_file, std::ios::out);
    record << random_string;
    record.close();
}