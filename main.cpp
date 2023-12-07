// Morgan Sansone, Abby Gerstner, Lars Yarkosky, Semyon Tsyrenov
// CS303 Group Project
// Due Date: December 8, 2023
// 3 additional functionalities: 
// Most recent 3 websites
// Go to website
// Clear search history

#include <QApplication>
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>
#include "source.h"

class WebPage {
public:
    std::string url;
    WebPage* next;

    WebPage(const std::string& link) : url(link), next(nullptr) {}
};

class WebHistory {
public:
    WebPage* head;
    int count;

    WebHistory() : head(nullptr), count(0) {}

    ~WebHistory() {
        clearHistory();
    }

    void addPage(const std::string& link) {
        WebPage* newPage = new WebPage(link);
        newPage->next = head;
        head = newPage;
        count++;
    }

    void removePage(const std::string& link) {
        if (head == nullptr)
            return;

        if (head->url == link) {
            WebPage* temp = head;
            head = head->next;
            delete temp;
            count--;
            return;
        }

        WebPage* current = head;
        while (current->next != nullptr) {
            if (current->next->url == link) {
                WebPage* temp = current->next;
                current->next = current->next->next;
                delete temp;
                count--;
                return;
            }
            current = current->next;
        }
    }

    void displayHistory() {
        WebPage* current = head;
        std::cout << "Search History:" << std::endl;
        while (current != nullptr) {
            std::cout << current->url << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }

    void showRecentWebsites() {
        int counter = 0;
        WebPage* current = head;
        std::cout << "Most Recent Websites:" << std::endl;
        while (current != nullptr && counter < 3) {
            std::cout << current->url << std::endl;
            current = current->next;
            counter++;
        }
        std::cout << std::endl;
    }

    void goToWebsite(const std::string& link) {
        WebPage* current = head;
        while (current != nullptr) {
            if (current->url == link) {
                std::cout << "Navigating to: " << current->url << std::endl;
                return;
            }
            current = current->next;
        }
        std::cout << "Website not found in history!" << std::endl;
    }

    void clearHistory() {
        while (head != nullptr) {
            WebPage* temp = head;
            head = head->next;
            delete temp;
        }
        count = 0;
        std::cout << "Search history cleared." << std::endl;
    }

    int getCount() const {
        return count;
    }
};

class WebHistoryWidget : public QWidget {
    Q_OBJECT

public:
    WebHistoryWidget(WebHistory& history, QWidget* parent = nullptr) : QWidget(parent), history(history) {
        QVBoxLayout* layout = new QVBoxLayout(this);

        listWidget = new QListWidget(this);
        layout->addWidget(listWidget);

        QPushButton* clearButton = new QPushButton("Clear History", this);
        connect(clearButton, &QPushButton::clicked, this, &WebHistoryWidget::clearHistory);
        layout->addWidget(clearButton);

        setLayout(layout);
        updateListWidget();

        setWindowTitle("Web History");
    }

public slots:
    void updateListWidget() {
        listWidget->clear();
        WebPage* current = history.head;
        while (current != nullptr) {
            listWidget->addItem(QString::fromStdString(current->url));
            current = current->next;
        }
    }

    void clearHistory() {
        history.clearHistory();
        updateListWidget();
    }

private:
    WebHistory& history;
    QListWidget* listWidget;
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    WebHistory history;

    history.addPage("www.example.com");
    history.addPage("www.testsite.com");
    history.addPage("www.openai.com");
    history.addPage("www.github.com");

    QMainWindow mainWindow;
    WebHistoryWidget* historyWidget = new WebHistoryWidget(history, &mainWindow);
    mainWindow.setCentralWidget(historyWidget);

    mainWindow.show();

    return app.exec();
}
