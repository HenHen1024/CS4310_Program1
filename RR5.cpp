
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <iomanip>


//job variable to hold all the info for the job
struct Job {
    std::string name;
    int burst;
    int remaining;
    int completion = 0;
};

int main() {
    //open the file and read in the jobs
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

    const int quantum = 5;
    std::queue<int> readyQueue;

    for (int i = 0; i < jobs.size(); i++) {
        readyQueue.push(i);
    }

    int time = 0;

    std::cout << "--- Round Robin (RR-5) ---\n";
    //run the jobs in the ready queue until all jobs are completed
    while (!readyQueue.empty()) {
        int i = readyQueue.front();
        readyQueue.pop();

        int start = time;
        int run = std::min(quantum, jobs[i].remaining);

        time += run;
        jobs[i].remaining -= run;

        //print the job name, start time, end time, and remaining time
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

    //print out the turnaround times and average turnaround time
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
