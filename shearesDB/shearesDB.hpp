#include<unordered_map>
#include <vector>
#include <string>
#include <stdlib.h>

class shearesDB{
    std::string name;
    std::unique_ptr<std::unordered_map<std::string, std::vector<char>>> dataMapPtr;

public:
    shearesDB();
    ~shearesDB();
   std::vector<char> get(std::string key);
   bool put(std::string key, std::vector<char>);
};