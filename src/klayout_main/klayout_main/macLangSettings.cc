/*
  File: macLangSettings.cc
  Description: To detect the user's language preference and set the LANG environment variable on the Mac
  Related ticket: https://github.com/KLayout/klayout/issues/1213
  Reference: macLangSettings-ChatGPTLecture.txt
  Author: Kazzz-S + ChatGPT
  Last modified: 2023-11-02
*/

#include <cstring>
#include <iostream>
#include <string>

// Prototypes
extern "C" const char* GetUserPreferredLanguage(void);
std::string            getMacLANG(void);
void                   setMacLANG(std::string);
int                    getsetMacLANG(void);

/**
 * @brief Detect the "LANG" environment variable on the Mac
 *
 * @return the value of "LANG" environment variable (can be "")
*/
std::string
getMacLANG(void)
{
    const char* ENV_VAR = "LANG";
    const char* tmp = getenv(ENV_VAR);
    std::string env_var(tmp ? tmp : "");
    return env_var;
}

/**
 * @brief Set the "LANG" environment variable
 *
 * @param[in] env_var   user's language preference, such as "ja-JP"
 *
 * @return void
*/
void
setMacLANG(std::string env_var)
{
    std::string userlang = env_var.replace(2, 1, "_") + ".UTF-8";
    char* cstr = new char[userlang.size() + 1];
    std::strcpy(cstr, userlang.c_str());
    setenv( "LANG", cstr, 1 ); // overwrite if exists
    delete[] cstr;
}

/**
 * @brief Get and set the "LANG" environment variable
 *
 * @return 0 on success; -1 on failure
*/
int
getsetMacLANG(void)
{
    std::string env_var = getMacLANG();
    // If LANG is already set, don't touch it.
    if ( !env_var.empty() ) {
        std::cout << "Info: getsetMacLANG() found LANG=" << env_var << std::endl;
        return 0;
    } else {
        const char* userLanguage = GetUserPreferredLanguage();
        if (userLanguage) {
            setMacLANG(userLanguage);
            std::string env_var = getMacLANG();
            std::cout << "Info: getsetMacLANG() set and found LANG=" << env_var << std::endl;
        } else {
            std::cerr << "Error: getsetMacLANG() failed to retrieve user language settings." << std::endl;
            return -1;
        }
    }
    return 0;
}

// EOF
