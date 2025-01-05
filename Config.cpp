#include <fstream>
#include <iostream>
#include <string>

#include "Config.h"

Config::Config()
    : hitDuration(20), paintBlobLimit(30), 
    rockLowerBound(10), rockUpperBound(20),
    fogLowerBound(5), fogUpperBound(10), longRangeLimit(30) {};

Config::Config(std::string url) {
    std::ifstream inputFile(url);
    if (!inputFile.is_open()) {
        throw std::invalid_argument("Error opening file");
    }
    std::string line;

    while (std::getline(inputFile, line)){
        /* Skip lines starting with # */
        if (line.empty() || line.at(0) == '#') continue; 
        std::string key;
        std::string val;
        int value;

        /* Split line with 'key = value'*/
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos){
            key = line.substr(0,delimiterPos);
            val = line.substr(delimiterPos+1);

            /* Trim white space */
            key = key.erase(key.find_last_not_of(" \n\r\t")+1);
            val = val.erase(val.find_last_not_of(" \n\r\t")+1);

            /* get value */
            try {
                value = std::stoi(val);
            } catch(const std::invalid_argument&) {
                std::cerr << "invalid value" << std::endl;
            } catch(const std::out_of_range&){
                std::cerr << "invalid value" << std::endl;
            }
            if (value < 0){ throw std::invalid_argument("Negative Config Value");}

        } else {
            throw std::invalid_argument("Missing Delimiter '=' in config file");
        }
        
        /* Key and Value are correctly formatted */
        if (key.find("HIT_DURATION") != std::string::npos){
               hitDuration = value;}
        else if (key.find("PAINTBLOB_LIMIT") != std::string::npos){
            paintBlobLimit = value;}
        else if (key.find("ROCK_LOWER_BOUND") != std::string::npos){
            rockLowerBound = value;}
        else if (key.find("ROCK_UPPER_BOUND") != std::string::npos){
            rockUpperBound = value;}
        else if (key.find("FOG_LOWER_BOUND") != std::string::npos){
            fogLowerBound = value;}
        else if (key.find("FOG_UPPER_BOUND") != std::string::npos){
            fogUpperBound = value;}
        else if (key.find("LONG_RANGE_LIMIT") != std::string::npos){
            longRangeLimit = value;}
    }

    /* If missing parameters, set to default */
    if(!hitDuration) { hitDuration = 28;}
    if(!paintBlobLimit) { paintBlobLimit = 30;}
    if(!longRangeLimit) { longRangeLimit = 26;}
    if(!rockLowerBound) { rockLowerBound = 10;}
    if(!rockUpperBound) { rockUpperBound = 12;}
    if(!fogLowerBound) { fogLowerBound = 2;}
    if(!fogUpperBound) { fogUpperBound = 8;}

    /* if upper < lower, swap them */
    if(fogUpperBound < fogLowerBound){
        int temp = fogUpperBound;
        fogUpperBound = fogLowerBound;
        fogLowerBound = temp;
    }
    if(rockUpperBound < rockLowerBound){
        int temp = rockUpperBound;
        rockUpperBound = rockLowerBound;
        rockLowerBound = temp;
    }

}

int Config::getFogLowerBound() const{return fogLowerBound;}
int Config::getFogUpperBound() const{return fogUpperBound;}
int Config::getRockUpperBound() const{return rockUpperBound;}
int Config::getRockLowerBound() const{return rockLowerBound;}
int Config::getLongRangeLimit() const{return longRangeLimit;}
int Config::getPaintBlobLimit() const{return paintBlobLimit;}
int Config::getHitDuration() const{return hitDuration;}