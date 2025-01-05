#pragma once
#include <string>

class Config {
    int hitDuration;
    int paintBlobLimit;
    int rockLowerBound;
    int rockUpperBound;
    int fogLowerBound;
    int fogUpperBound;
    int longRangeLimit;
    public:
        Config();
        Config(std::string);
        int getHitDuration() const;
        int getPaintBlobLimit() const;
        int getRockLowerBound() const;
        int getRockUpperBound() const;
        int getFogLowerBound() const;
        int getFogUpperBound() const;
        int getLongRangeLimit() const;
};