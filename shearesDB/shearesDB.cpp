#include "shearesDB.hpp"
#include <vector>
#include <string.h>


shearesDB::shearesDB(){

}

std::vector<char> shearesDB::get(std::string key){
    if(this->dataMapPtr.find(key) != this->dataMapPtr.end()){
        return this->dataMapPtr[key];
    }
};

bool shearesDB::put(std::string key, std::vector<char> value){
    if(this->dataMapPtr.find(key) != this->dataMapPtr.end()){
        return false;
    }
    this->dataMapPtr[key] = value;
    return true;
};