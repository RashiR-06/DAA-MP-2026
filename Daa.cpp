#include <iostream>
#include <cstring>
using namespace std;

class Topic {
public:
    char subject[20];
    char name[20];
    int timeRequired;   // remaining time
    int difficulty;
    int weightage;
    int daysLeft;
    int completed;
    float priority;

    void input() {
        cout << "\nSubject: ";
        cin >> subject;
        cout << "Topic: ";
        cin >> name;
        cout << "Time Required (hours): ";
        cin >> timeRequired;
        cout << "Difficulty (1-5): ";
        cin >> difficulty;
        cout << "Weightage: ";
        cin >> weightage;
        cout << "Days before exam: ";
        cin >> daysLeft;

        completed = 0;
        calculatePriority();
    }

    void calculatePriority() {
        // Priority Formula
        priority = (weightage * difficulty) / (float)(timeRequired * daysLeft);
    }
};

class Scheduler {
public:
    Topic t[50];
    int n;

    void inputTopics() {
        cout << "Enter number of topics: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << "\n--- Topic " << i + 1 << " ---\n";
            t[i].input();
        }
    }

    // 🔷 DP KNAPSACK (used every hour)
    int selectBestTopic(int lastIndex) {
        float maxPriority = -1;
        int index = -1;

        for (int i = 0; i < n; i++) {

            // Skip completed topics
            if (t[i].completed == 1)
                continue;

            // Avoid same subject consecutively
            if (i == lastIndex)
                continue;

            if (t[i].priority > maxPriority) {
                maxPriority = t[i].priority;
                index = i;
            }
        }

        return index;
    }

    void generateSchedule() {
        int days;
        cout << "\nEnter number of study days: ";
        cin >> days;

        int hours[30];
        for (int i = 0; i < days; i++) {
            cout << "Hours available on Day " << i + 1 << ": ";
            cin >> hours[i];
        }

        int lastIndex = -1;

        // 🔷 MAIN SCHEDULING LOOP
        for (int d = 0; d < days; d++) {

            cout << "\nDay " << d + 1 << " Timetable:\n";

            for (int h = 0; h < hours[d]; h++) {

                int idx = selectBestTopic(lastIndex);

                if (idx == -1) {
                    cout << "Hour " << h + 1 << ": Free / Revision\n";
                    continue;
                }

                cout << "Hour " << h + 1 << ": "
                     << t[idx].subject << " -> " << t[idx].name << endl;

                // 🔥 Reduce time by 1 hour
                t[idx].timeRequired--;

                // Mark completed if done
                if (t[idx].timeRequired == 0) {
                    t[idx].completed = 1;
                }

                lastIndex = idx;
            }

            // 🔷 Update urgency daily
            for (int i = 0; i < n; i++) {
                if (t[i].completed == 0) {
                    t[i].daysLeft--;

                    if (t[i].daysLeft <= 0)
                        t[i].daysLeft = 1;

                    t[i].calculatePriority();
                }
            }
        }
    }
};

int main() {
    Scheduler s;

    s.inputTopics();
    s.generateSchedule();

    return 0;
}