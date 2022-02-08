#ifndef RESOURCES_REPOSITORY_H
#define RESOURCES_REPOSITORY_H

// класс предназначен для ханения ресурсов различного типа
#include <type_traits>

#include "ResourcesFile.hpp"
#include "SingleThreaded.hpp"
#include <algorithm>
#include <map>

namespace Resource
{
    //-------------------------------------------------------------------------------
    template <bool B, class T = void>
    struct KeyType;

    template <class T>
    struct KeyType<false, T>
    {
        typedef T value;
    };

    template <class T>
    struct KeyType<true, T>
    {
        typedef const T& value;
    };
    //-------------------------------------------------------------------------------

    template<typename Key, class ResourceItem, template <class> class ThreadingModel = SingleThreaded >
    class CResourcesRepository : public ThreadingModel<CResourcesRepository<Key, ResourceItem, ThreadingModel> >

    {
    public:
        typedef typename KeyType<std::is_class<Key>::value, Key >::value                    TKeyType;
        typedef std::shared_ptr<ResourceItem> ResourceItemPtr;
        typedef std::map<Key, ResourceItemPtr >                                                TResourcesMap;
        typedef ThreadingModel<CResourcesRepository<Key, ResourceItem, ThreadingModel> >    MyThreadingModel;

        //-------------------------------------------------------------------------------
        CResourcesRepository(){}
        //-------------------------------------------------------------------------------
        ~CResourcesRepository()
        {
        }

        //-------------------------------------------------------------------------------
        ResourceItemPtr    getResource(TKeyType key) const
        {
            typename MyThreadingModel::Lock lock(*this);
            typename TResourcesMap::const_iterator citer = mResources.find(key);
            if(citer == mResources.end())
                return NULL;
            return citer->second;
        }

        //-------------------------------------------------------------------------------
        void    deleteResource(TKeyType key)
        {
            typename MyThreadingModel::Lock lock(*this);
            typename TResourcesMap::iterator iter = mResources.find(key);
            if(iter != mResources.end())
            {
                mResources.erase(iter);
            }
        }

        //-------------------------------------------------------------------------------
        void    readFromFile(const std::string& NameFile)
        {
            Private::ResourcesFile<ResourceItem> ResFile(NameFile);
            typename Private::ResourcesFile<ResourceItem>::iterator iter = ResFile.begin();
            while(iter.valid())
            {
                insertResource(std::make_shared<ResourceItem>(*iter));
                iter = iter.next();
            }
        }

    private:
        TResourcesMap        mResources;

        //-------------------------------------------------------------------------------
        void    insertResource(ResourceItemPtr item)
        {
            typename MyThreadingModel::Lock lock(*this);
            mResources[item->key()] = item;
        }
    };

}

#endif // RESOURCES_REPOSITORY_H

