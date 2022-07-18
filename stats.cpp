#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <chrono>
#include <thread>

typedef struct Country {
    std::string name;
    std::string code;
    Country(std::string s, std::string c): name(s), code(c) {}
} Country;

/*!
 * Compute population percentage per blood group for a given country.
 *
 * @param country The country for which stats will be computed. Its code is
 *                used to determine which file data will be read from.
 * @param stats A map where the stats will be stored.
 */
std::map<std::string, float> generate_stats(const Country &country)
{
    std::ifstream in("./data/" + country.code + ".txt");
    std::map<std::string, int> m;
    std::string group;
    int pop = 0;

    while (in >> group) {
        ++m[group];
        ++pop;
    }

    std::map<std::string, float> stats;
    for (const auto &[k, v]: m) {
        double p = static_cast<double>(v) / pop * 100;
        stats[k] = p;
    }

    return stats;
}

/*!
 * Print the stats for a country to stardard output.
 *
 * @param country The country.
 * @param stats A map containing the stats.
 */
void print_stats(const Country &country, const std::map<std::string, float> &m)
{
    std::cout << "Stats for " << country.name << std::endl;
    std::cout << std::setprecision(2);
    for (const auto &[k, v]: m) {
        std::cout << std::setw(2) << k << std::setw(0) << ": ";
        std::cout << std::fixed << v << "%" << std::endl;
    }
    std::cout << std::endl;
}

/*!
 * Show an animation.
 *
 * The function is heavily based on the solution give for this question
 * on StackOverflow: https://stackoverflow.com/questions/72175072.
 *
 * @param should_animate A handle used to know if the animation should stop.
 */
void animate(bool *should_animate)
{
    // Using this namespace lets us use the "100ms" time literal in
    // the sleep_for() function argument.
    using namespace std::chrono_literals;

    std::string symbols = "|/-\\";

    std::cout << "Crunching data...\x20\x20";
    std::cout.flush(); 
    while (*should_animate) {
        for (size_t i = 0; i < symbols.length(); ++i) {
            std::cout << "\b" << symbols[i];
            // I had to flush cout so that the animation would show up.
            std::cout.flush();
            // I added some delay here so that the animation is more visible.
            std::this_thread::sleep_for(120ms);
        }
    }

    // For pretty print and remove animation char.
    std::cout << "\b" << " " << std::endl;
    std::cout << "Done." << std::endl << std::endl;
}

int main()
{
    std::vector<Country> countries{
        Country("Benin", "bj"),
        Country("Burkina Faso", "bf"),
        Country("Niger", "ne"),
        Country("Togo", "tg")
    };
    std::vector<std::map<std::string, float>> stats;
    bool should_animate = true;
    std::thread thread_animate(animate, &should_animate);

    for (const auto &country: countries) {
        auto m = generate_stats(country);
        stats.push_back(m);
    }

    should_animate = false;
    thread_animate.join();

    for (size_t i = 0; i < std::size(countries); ++i) {
        print_stats(countries[i], stats[i]);
    }

    return 0;
}

