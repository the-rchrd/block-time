#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <sstream>

namespace tr
{
    typedef std::chrono::time_point<std::chrono::steady_clock> time;    // DEFINING CHRONO'S STEADY_CLOCK WITH SMTHNG SHORTER

    struct TimePeriod
    {
        int line_begin, line_end;

        time begin, end;
    };

    class ITime
    {
        public:
            ~ITime() {};

            virtual void set(const int& str) = 0;
            virtual void clear() = 0;
            virtual void print() const = 0;

            std::vector<TimePeriod> time_period;
    };

    class BlockTime : public ITime
    {
        public:
            BlockTime(const std::string& path) : path(path) {} // INTITALIZE ONLY WITH FILE_PATH (THAT CONTAINS THIS BLOCKS)

            void set(const int& line)
            {
                if (time_period.empty())    // THERE WAS NO ONE SETTER BEFORE
                {
                    TimePeriod t_p;
                    time_period.push_back(t_p);
                    time_period.back().begin = std::chrono::steady_clock::now();    // SET BEGIN OF NEW PERIOD      //
                    time_period.back().line_begin = line;
                }
                else                        // THERE WAS SETTER BEFORE
                {
                    time_period.back().end = std::chrono::steady_clock::now();      // SET END OF PREVIOUS PERIOD   //
                    time_period.back().line_end = line;

                    TimePeriod t_p;
                    time_period.push_back(t_p);
                    time_period.back().begin = std::chrono::steady_clock::now();    // SET BEGIN OF NEW PERIOD      //
                    time_period.back().line_begin = line;
                }
            }

            void clear() { time_period.clear(); }

            void print() const
            {
                std::cout << "\n.";
                
                for (std::size_t i = 0; i < time_period.size() - 1; i++)
                {
                    auto diff = time_period[i].end - time_period[i].begin;                          // COUNT DIFF IN BLOCK TIME

                    if (std::chrono::duration<double, std::milli>(diff).count() <= 0.001)           /* <VERY FAST> ~white~~~*/
                        std::cout << "\033[0;37m";                                                  //                      */
                    else if ((std::chrono::duration<double, std::milli>(diff).count() > 0.001)      // <FAST>               */
                            && (std::chrono::duration<double, std::milli>(diff).count() < 0.1))     // ~green~              */
                        std::cout << "\033[0;32m";                                                  //                      */
                    else if ((std::chrono::duration<double, std::milli>(diff).count() >= 0.1        // <NORMAL/NOT FAST>    */
                            && (std::chrono::duration<double, std::milli>(diff).count() < 1.0)))    // ~yellow~             */
                        std::cout << "\033[0;33m";                                                  //                      */
                    else if ((std::chrono::duration<double, std::milli>(diff).count() >= 1.0))      /* <SLOW> ~red~~~~~~~~~~*/
                        std::cout << "\033[0;31m";
                    
                
                    int line = 0;
                    std::string str;
                    std::ifstream in(path); // IN ~open~
                    while(getline(in, str))                                                
                    {              
                        line++;                                                                                     
                                                                                       
                        if (line > time_period[i].line_begin && line < time_period[i].line_end)
                            std::cout << std::endl << "│" << str;
                    }
                    in.close();             // IN ~close~

                    if (i == time_period.size() - 2)
                        std::cout << "\n└──";   // LAST BRANCH
                    else
                        std::cout << "\n├──";   // NOT LAST BRANCH
                    std::cout << "\033[1m";     // SET OUTPUT ~bold~
                    std::cout << "\033[4m";     // SET OUTPUT ~underline~
                    std::cout << "execution time: " << std::setprecision(2) << std::chrono::duration<double, std::milli>(diff).count() << "ms";
                    std::cout << "\033[0m";     // RESET OUTPUT STYLE
                }

                std::cout << '\n';
            }

        private:
            std::string path;
    };
}
