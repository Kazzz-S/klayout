/*
  File: macUserPreferredLanguage.mm
  Description: To detect the user's language preference with Objective-C++ on the Mac
  Related ticket: https://github.com/KLayout/klayout/issues/1213
  Reference: macLangSettings-ChatGPTLecture.txt
  Author: Kazzz-S + ChatGPT
  Last modified: 2023-11-02
*/

#import <Foundation/Foundation.h>

// Prototype
extern "C" const char* GetUserPreferredLanguage(void);

/**
 * @brief Get the user preferred language
 *
 * @return the user preferred language, such as "ja-JP"
*/
extern "C" const char* GetUserPreferredLanguage(void) {
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    NSArray* languages = [[NSUserDefaults standardUserDefaults] objectForKey:@"AppleLanguages"];
    NSString* userPreferredLanguage = [languages objectAtIndex:0];
    const char* lang = [userPreferredLanguage UTF8String];
    [pool release];
    return lang;
}

// EOF
