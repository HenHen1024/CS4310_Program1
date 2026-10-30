
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>

struct Job {
    std::string name;
    int burst;
    int remaining;
    int completion = 0;
};

int main() {
    std::ifstream file("job.txt");
    std::vector<Job> jobs;

    std::string name;
    int burst;

    while (file >> name >> burst) {
        jobs.push_back({name, burst, burst, 0});
    }

    if (!file.eof() || jobs.empty() || jobs.size() > 30) {
        std::cout << "Invalid job file\n";
        return 1;
    }

    const int quantum = 2;
    std::queue<int> readyQueue;

    for (int i = 0; i < jobs.size(); i++) {
        readyQueue.push(i);
    }

    int time = 0;

    std::cout << "--- Round Robin (RR-2) ---\n";

    while (!readyQueue.empty()) {
        int i = readyQueue.front();
        readyQueue.pop();

        int start = time;
        int run = std::min(quantum, jobs[i].remaining);

        time += run;
        jobs[i].remaining -= run;

        std::cout << jobs[i].name << ": "
                  << start << " - " << time << " ms";

        if (jobs[i].remaining > 0) {
            std::cout << " (remaining: "
                      << jobs[i].remaining << " ms)";
            readyQueue.push(i);
        }
        else {
            jobs[i].completion = time;
            std::cout << " (completed)";
        }

        std::cout << "\n";
    }

    double total = 0;

    std::cout << "\nTurnaround Times:\n";

    for (const Job& j : jobs) {
        std::cout << j.name << ": "
                  << j.completion << " ms\n";
        total += j.completion;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Turnaround Time: "
              << total / jobs.size() << " ms\n";

    return 0;
}
