#include "ResourcesRepository.hpp"
#include "Threaded.hpp"

template<class Res>
class Loader;

class Test
{
    friend class Loader<Test>;
public:
    int key() const { return mKey; }
private:
    int mKey = {0};
    int mValue = {0};
};

template<>
class Loader<Test>
{
public:
    static bool load(std::ifstream* file, Test* res)
    {
        if(!file || !file->is_open() || file->eof())
            return false;
        
        file->read((char*)&res->mKey, sizeof(res->mKey));
        
        if(file->eof())
            return false;
        
        file->read((char*)&res->mValue, sizeof(res->mValue));
        
        if(file->eof())
            return false;
        
        return true;
    }
};

int main()
{
    Resource::CResourcesRepository<int, Test, Threaded> tmp;
    tmp.readFromFile("test");
    
    return 0;
}


