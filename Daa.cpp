#include <iostream>
#include <fstream>
using namespace std;

// TOPIC CLASS 
class Topic {
public:
    string subject, topic;
    int difficulty, weightage, deadline, timeRequired;
    float priority, ratio, hrstaken;

    void input() {
        cout << "Subject: ";
        cin >> subject;

        cout << "Topic: ";
        cin >> topic;

        cout << "Difficulty(out of 5): ";
        cin >> difficulty;

        cout << "Weightage(out of 5): ";
        cin >> weightage;

        cout << "Deadline(in days): ";
        cin >> deadline;

        cout << "timeRequired (in hrs): ";
        cin >> timeRequired;

        calculatePriority();
        hrstaken = 0;
    }

    void calculatePriority() {
        priority = (0.5 * difficulty + 0.5 * weightage) / deadline;
        ratio = priority / timeRequired;
    }

    void display() {
        if (hrstaken > 0) {
            cout << subject << "-" << topic
                 << " -> " << hrstaken << " hrs\n";
        }
    }
};

// ---------- FILE MANAGER CLASS ----------
class FileManager {
public:
    //to check if user already exits
    bool studentExists(string username) {
        ifstream file("topics.txt");
        if(!file) return false;

        string word;

        while(file >> word) {
            if(word == "Student") {
                string existingName;
                file >> existingName;

                if(existingName == username) {
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        return false;
    }
    // OVERWRITE
    void enterTopics() {
        string username;
        int n;
        cout << "Enter Student User Name: ";
        cin >> username;

        if(studentExists(username)) {
        cout << "Error: Student already exists!\n";
        cout << "Use 'Add Topics' option instead.\n";
        return;
    }
        cout << "Enter number of topics: ";
        cin >> n;

        ofstream file("topics.txt", ios::app);

        file << "Student " << username << endl;

        for(int i = 0; i < n; i++) {
            Topic t;
            cout << "\nTopic " << i+1 << ":\n";
            t.input();

            file << t.subject << " "
                 << t.topic << " "
                 << t.difficulty << " "
                 << t.weightage << " "
                 << t.deadline << " "
                 << t.timeRequired << endl;
        }

        file << "END\n";
        file.close();
        cout << "Saved successfully.\n";
    }

    // APPEND
    void addTopics() {
        string username;
        int m;
        cout << "Enter Student User Name: ";
        cin >> username;

        if(!studentExists(username)) {
            cout << "Error: Student does not exist!\n";
            cout << "Use 'Enter Topics' first.\n";
            return;
        }
        cout << "Enter number of topics to add: ";
        cin >> m;

        ofstream file("topics.txt", ios::app);

        file << "Student " << username << endl;

        for(int i = 0; i < m; i++) {
            Topic t;
            cout << "\nNew Topic:\n";
            t.input();

            file << t.subject << " "
                 << t.topic << " "
                 << t.difficulty << " "
                 << t.weightage << " "
                 << t.deadline << " "
                 << t.timeRequired << endl;
        }
        file << "END\n";
        file.close();
        cout << "Added successfully.\n";
    }
    
    // LOAD
    bool loadTopics(Topic t[], int &n, string username) {
        ifstream file("topics.txt");

        if(!file) return false;

        n = 0;
        string word;

        while(file >> word) {

            if(word == "Student") {
                string currentName;
                file >> currentName;

                if(currentName == username) {

                    while(true) {
                        string sub;
                        file >> sub;

                        if(sub == "END") break;

                        t[n].subject = sub;

                        file >> t[n].topic
                             >> t[n].difficulty
                             >> t[n].weightage
                             >> t[n].deadline
                             >> t[n].timeRequired;

                        t[n].calculatePriority();
                        t[n].hrstaken = 0;
                        n++;
                    }
                }
            }
        }

        file.close();
        return n > 0;
    }
};

// SCHEDULER CLASS
class Scheduler {
private:
    Topic t[50];
    int n;

public:
    // MERGE FUNCTION 
    void merge(int low, int mid, int high) {
        Topic temp[50];

        int i = low;
        int j = mid + 1;
        int k = low;

        while(i <= mid && j <= high) {
            if(t[i].ratio > t[j].ratio) { // descending order
                temp[k++] = t[i++];
            } else {
                temp[k++] = t[j++];
            }
        }
        while(i <= mid) {
            temp[k++] = t[i++];
        }
        while(j <= high) {
            temp[k++] = t[j++];
        }
        for(int i = low; i <= high; i++) {
            t[i] = temp[i];
        }
    }
    //MERGE SORT
    void mergeSort(int low, int high) {
        if(low < high) {
            int mid = (low + high) / 2;

            mergeSort(low, mid);
            mergeSort(mid + 1, high);

            merge(low, mid, high);
        }
    }
    // FRACTIONAL KNAPSACK
    void fractionalKnapsack(int totalHours) {

    // USE MERGE SORT
    mergeSort(0, n - 1);    

    int remaining = totalHours;
    
    for(int i = 0; i < n; i++) {

        if(remaining == 0) break;

        if(t[i].timeRequired <= remaining) {
            t[i].hrstaken = t[i].timeRequired;
                remaining -= t[i].timeRequired;
        } 
        else {
            t[i].hrstaken = remaining;
            remaining = 0;
        }
    }
    }

    // DISPLAY
    void displaySelected() {
        cout << "\nSelected Topics:\n";

        for(int i = 0; i < n; i++) {
            t[i].display();
        }
    }

    // SCHEDULE
    void generateSchedule() {

        int days;
        cout << "Enter number of days: ";
        cin >> days;

        int hoursPerDay[30];
        int totalHours = 0;

        for(int i = 0; i < days; i++) {
            cout << "Hours Day " << i+1 << ": ";
            cin >> hoursPerDay[i];
            totalHours += hoursPerDay[i];
        }

        fractionalKnapsack(totalHours);
        displaySelected();

        int totalSlots = totalHours;
        string schedule[200];

        int index = 0;

        for(int i = 0; i < n; i++) {
            int hrs = (int)t[i].hrstaken;

            for(int h = 0; h < hrs; h++) {
                if(index < totalSlots) {
                    schedule[index++] = t[i].subject + "-" + t[i].topic;
                }
            }
        }

        cout << "\n--- FINAL SCHEDULE ---\n";

        int k = 0;

        for(int d = 0; d < days; d++) {

            cout << "\nDay " << d+1 << ":\n";

            for(int h = 0; h < hoursPerDay[d]; h++) {

                cout << "Hour " << h+1 << " -> ";

                if(k < totalSlots)
                    cout << schedule[k] << endl;
                else
                    cout << "---\n";

                k++;
            }
        }
    }

    // LOAD + RUN
    void run(FileManager &fm) {
        string username;
        cout << "Enter Student Name: ";
        cin >> username;

        if(!fm.loadTopics(t, n, username)) {
            cout << "No data found.\n";
            return;
        }

        generateSchedule();
    }
};

int main() {
    FileManager fm;
    Scheduler scheduler;
    int choice;
    while(true) {

        cout << "\n1. Enter Topics\n"
            << "2. Add Topics\n"
            << "3. Generate Schedule\n"
            << "4. Exit\nChoice: ";
        cin >> choice;

        if(choice == 1)
            fm.enterTopics();

        else if(choice == 2)
            fm.addTopics();

        else if(choice == 3)
            scheduler.run(fm);

        else
            break;
    }
    return 0;
}
