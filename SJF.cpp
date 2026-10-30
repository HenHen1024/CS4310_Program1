
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

struct Job {
    std::string name;
    int burst;
    int completion = 0;
};

int main() {
    std::ifstream file("job.txt");
    std::vector<Job> jobs;

    Job job;
    while (file >> job.name >> job.burst) {
        jobs.push_back(job);
    }

    if (!file.eof() || jobs.empty() || jobs.size() > 30) {
        std::cout << "Invalid job file\n";
        return 1;
    }

    // Sort jobs from shortest to longest burst time
    std::stable_sort(jobs.begin(), jobs.end(),
        [](const Job& a, const Job& b) {
            return a.burst < b.burst;
        });

    int time = 0;
    double total = 0;

    std::cout << "--- SJF Scheduling ---\n";

    for (Job& j : jobs) {
        int start = time;
        time += j.burst;
        j.completion = time;

        std::cout << j.name << ": "
                  << start << " - " << time << " ms\n";

        total += j.completion;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Turnaround Time: "
              << total / jobs.size() << " ms\n";

    return 0;
}
