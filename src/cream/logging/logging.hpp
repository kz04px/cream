#ifndef LOGGING_HPP_INCLUDED
#define LOGGING_HPP_INCLUDED

#include <fstream>
#include <memory>
#include <string>

// TODO:
// -- Mirror log writing to the console
//   -- Use colours
// -- Filter depending on debug level
// -- stringstream each level to one write() function

namespace cream {

class Logger {
   public:
    Logger(const std::string filename);
    ~Logger();
    static Logger &get_instance();
    void debug(const std::string text);
    void info(const std::string text);
    void warning(const std::string text);
    void error(const std::string text);

   private:
    std::ofstream file_;
};

}  // namespace cream

#endif
