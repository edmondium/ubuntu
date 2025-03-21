// IUbuntuImageFetcher.h - Interface definition
#ifndef IUBUNTUIMAGEFETCHER_H
#define IUBUNTUIMAGEFETCHER_H

#include <string>
#include <vector>

class IUbuntuImageFetcher {
public:
    virtual ~IUbuntuImageFetcher() = default;
    virtual std::vector<std::string> getSupportedReleases() = 0;
    virtual std::string getLatestLTSVersion() = 0;
    virtual std::string getSHA256Checksum(const std::string& release) = 0;
};

#endif // IUBUNTUIMAGEFETCHER_H
