#include "Config.h"
#include <iostream>

int defaultConstructor(const Config& p);
int validConfigFile(const Config& p);               //all good
void badFileName();                                 //invalid.txt
void missingParameters();             //hit_duration not present
void missingDelimiters();             //hit_duration 22
void extraParameters();               //robot_speed = 10
void incorrectBoundaryParameters();   //lowerbound = 10 upperboud = 8
void negativeParameters();            //hit_duration = -10
void incorrectComments();             // / this is a comment
void incorrectParameterNames();       // dit_Huration


int main(int argc, char const *argv[])
{
    Config default_settings;

    std::cout << "Checking Default Constructor: ";
    if(defaultConstructor(default_settings)){
        std::cout << "\t\tPASS\n";
    } else { std::cout << "\t\tFAIL\n"; }

    Config *settings = new Config("config.txt");

    std::cout << "Checking Valid Configuration file: ";
    if (validConfigFile(*settings)){
        std::cout << "\tPASS\n";
    } else { std::cout << "\t\tFAIL\n";}
    delete settings;

    badFileName();
    missingParameters();
    missingDelimiters();
    extraParameters();
    incorrectBoundaryParameters();
    negativeParameters();
    incorrectComments();
    incorrectParameterNames();
    


    return 0;
}

int isValid(int x) {
    return (x > 0);
}

//all good
int defaultConstructor(const Config& settings) {
    try
    {
        return isValid(settings.getFogLowerBound()) &&
        isValid(settings.getFogUpperBound()) && 
        isValid(settings.getHitDuration()) && 
        isValid(settings.getLongRangeLimit()) && 
        isValid(settings.getPaintBlobLimit()) &&
        isValid(settings.getRockLowerBound()) &&
        isValid(settings.getRockUpperBound());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
};


//all good
int validConfigFile(const Config& settings) {
    try
    {
        return isValid(settings.getFogLowerBound()) &&
        isValid(settings.getFogUpperBound()) && 
        isValid(settings.getHitDuration()) && 
        isValid(settings.getLongRangeLimit()) && 
        isValid(settings.getPaintBlobLimit()) &&
        isValid(settings.getRockLowerBound()) &&
        isValid(settings.getRockUpperBound());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
};               

//invalid.txt
void badFileName() {
    std::cout << "Checking Bad file Name: ";
    try {
        Config *test = new Config("Invalid.txt");
        std::cout << "\t\tFAIL : no error thrown\n";
    }
    catch(const std::invalid_argument& e) {
        std::cout << "\t\tPASS\n";
    }
};                   

//hit_duration not present
void missingParameters() { 
    std::cout << "Checking missing parameters: ";
    try
    {
        Config *test = new Config("missingParams.txt");
        // Rock limits have been removed
        if (isValid(test->getRockLowerBound()) 
        && isValid(test->getRockUpperBound())){
            std::cout << "\t\tPASS\n";
        }
        else { std::cout << "\t\tFAIL\n";}
        delete test;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
};             

//hit_duration 22
void missingDelimiters() {
    std::cout << "Checking missing delimiters: ";
    try
    {
        Config *test = new Config("missingDelim.txt");
        std::cout << "\tFAIL : no error caught\n";
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "\t\tPASS\n";
    }
    
};

//robot_speed = 10
void extraParameters() {
    std::cout << "Checking extra parameters: ";
    try
    {
        Config *settings = new Config("extraParams.txt");
        if (isValid(settings->getFogLowerBound()) &&
        isValid(settings->getFogUpperBound()) && 
        isValid(settings->getHitDuration()) && 
        isValid(settings->getLongRangeLimit()) && 
        isValid(settings->getPaintBlobLimit()) &&
        isValid(settings->getRockLowerBound()) &&
        isValid(settings->getRockUpperBound())){
            std::cout << "\t\tPASS\n";
        }
        else { std::cout << "\t\tFAIL\n";}
        delete settings;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cout << "FAIL\n";
    }
    
};

//lowerbound = 10 upperboud = 8
void incorrectBoundaryParameters() {
    std::cout << "Checking Boundary Parameters: ";
    try
    {
        Config *settings = new Config("bounds.txt");
        if (settings->getFogLowerBound() <= settings->getFogUpperBound()
        && settings->getRockLowerBound() <= settings->getRockUpperBound()){
            std::cout << "\t\tPASS\n";
        }
        else { std::cout << "\t\tFAIL\n";}
        delete settings;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
};

//hit_duration = -10
void negativeParameters() {
    std::cout << "Checking negative parameters: ";
    try
    {
        Config *settings = new Config("negative.txt");
        std::cout << "\t\tFAIL : no error thrown\n";
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "\t\tPASS\n";
    }
    
};

// / this is a comment
void incorrectComments() {
    std::cout << "Checking bad formatting: ";
    try
    {
        Config *settings = new Config("badformat.txt");
        std::cout << "\t\tFAIL : no error thrown\n";
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "\t\tPASS\n";
    }
    
};

// dit_Huration
void incorrectParameterNames() {
    std::cout << "Checking misspelled names: ";
    try
    {
        Config *settings = new Config("misspelled.txt");
        /* it should just set to default parameter */
        if (isValid(settings->getFogLowerBound()) &&
        isValid(settings->getFogUpperBound()) && 
        isValid(settings->getHitDuration()) && 
        isValid(settings->getLongRangeLimit()) && 
        isValid(settings->getPaintBlobLimit()) &&
        isValid(settings->getRockLowerBound()) &&
        isValid(settings->getRockUpperBound())){
            std::cout << "\t\tPASS\n";
        }
        else { std::cout << "\t\tFAIL\n";}
        delete settings;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
};
