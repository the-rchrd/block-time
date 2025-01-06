#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>

namespace tr
{
    typedef std::chrono::time_point<std::chrono::steady_clock> time;

    struct TimePeriod
    {
        time begin, end;

        const time difference() { return time(begin - end); }
    };

    class ITime
    {
        public:
            ~ITime() {};

            virtual void set() = 0;
            virtual void clear() = 0;
            virtual void print() = 0;
    };

    class BlockTime : public ITime
    {
        public:
            BlockTime(const std::string& file_path) : path(file_path) {}

            void set()
            {
                if (time_period.empty())
                {
                    time_period.resize(time_period.size() + 1);
                    time_period[time_period.size() - 1].begin = std::chrono::steady_clock::now();
                }
                else
                {
                    time_period[time_period.size() - 1].end = std::chrono::steady_clock::now();
                    time_period.resize(time_period.size() + 1);
                    time_period[time_period.size() - 1].begin = std::chrono::steady_clock::now();
                }
            }

            void clear() { time_period.clear(); }

            void print()
            {
                std::cout << '\n';
                
                for (int i = 0; i < time_period.size() - 1; i++)
                {
                    auto diff = time_period[i].end - time_period[i].begin;
                    if (std::chrono::duration<double, std::milli>(diff).count() <= 0.001)
                        std::cout << "\033[0;37m";
                    else if ((std::chrono::duration<double, std::milli>(diff).count() > 0.001)
                            && (std::chrono::duration<double, std::milli>(diff).count() < 0.1))
                        std::cout << "\033[0;32m";
                    else if ((std::chrono::duration<double, std::milli>(diff).count() >= 0.1
                            && (std::chrono::duration<double, std::milli>(diff).count() < 1.0)))
                        std::cout << "\033[0;33m";
                    else if ((std::chrono::duration<double, std::milli>(diff).count() >= 1.0))
                        std::cout << "\033[0;31m";
                    
                    std::ifstream in(path);
                    std::string line;
                    std::string output;
                    int found = -1;

                    while (!in.eof() && found != i)
                    {
                        in >> line;
                        if (line == "block_time.set();")
                            found++;
                    }
                    while(getline(in, line))
                    {
                        int words = 0;
                        std::stringstream ls(line);
                        std::string word;
                        while (ls >> word && found != i + 1)
                        {
                            if (word == "block_time.set();")
                                found++;
                        }
                        if (found != i + 1 && word.length() != 0)
                            std::cout << std::endl << "│" << line;
                    }
                    in.close();

                    std::cout << "\033[1m";
                    std::cout << "\n├──";
                    std::cout << "\033[4m";
                    std::cout << "execution time: " << std::setprecision(2) << std::chrono::duration<double, std::milli>(diff).count() << "ms";
                    std::cout << "\033[0m";
                }

                std::cout << '\n';
            }

        private:
            std::vector<TimePeriod> time_period;

            std::string path;

            std::ifstream in;
    };
}
