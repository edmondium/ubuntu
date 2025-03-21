// main.cpp - CLI Implementation
#include "IUbuntuImageFetcher.h"
#include "UbuntuImageFetcher.cpp"
#include <iostream>

int main(int argc, char* argv[]) {
    UbuntuImageFetcher fetcher;

    if (argc < 2) {
        std::cout << "Usage: ./UbuntuFetcher <option> [release]" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    if (option == "--list") {
        auto releases = fetcher.getSupportedReleases();
        for (const auto& release : releases) {
            std::cout << release << std::endl;
        }
    } else if (option == "--latest-lts") {
        std::cout << "Latest LTS: " << fetcher.getLatestLTSVersion() << std::endl;
    } else if (option == "--sha256" && argc == 3) {
        std::cout << "SHA256: " << fetcher.getSHA256Checksum(argv[2]) << std::endl;
    } else {
        std::cout << "Invalid option" << std::endl;
    }
    return 0;
}
