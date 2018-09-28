#ifndef EXCEPT_H
#define EXCEPT_H

#include <string>

class Except {
public:
    Except(const std::string& desc);
    Except(const Except& orig);
    virtual ~Except();
    
    std::string getDesc() const { return description; }
private:
    std::string description;
};

#endif /* EXCEPT_H */

