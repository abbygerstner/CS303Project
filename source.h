#ifndef WEBHISTORY_H
#define WEBHISTORY_H

#include <string>

class WebPage {
public:
    std::string url;
    WebPage* next;

    WebPage(const std::string& link);
};

class WebHistory {
public:
    WebPage* head;
    int count;

    WebHistory();
    ~WebHistory();

    void addPage(const std::string& link);
    void removePage(const std::string& link);
    void displayHistory();
    void showRecentWebsites();
    void goToWebsite(const std::string& link);
    void clearHistory();
    int getCount() const;
};

#endif // WEBHISTORY_H
