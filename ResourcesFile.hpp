#ifndef RESOURCES_FILE_H
#define RESOURCES_FILE_H

#include <fstream>

template<class Res>
class Loader
{
public:
	static bool load(std::ifstream* file, Res* res){ return true;}
};

namespace Resource
{

namespace Private
{

	template<class ResourceType>
	class ResourcesFile
	{
	public:

		template <class ResType>
		class ResourcesFileIterator
		{
		public:
			ResourcesFileIterator(std::ifstream* file):
				mFile(file)
			{
				mValid = Loader<ResType>::load(file, &mNode);
			}
            
            ResType& operator * ()
            {
                return mNode;
            }

			bool operator == (ResourcesFileIterator const& i)
			{
				return mNode == i.mNode;
			}

			bool operator != (ResourcesFileIterator const& i)
			{
				return !(*this == i);
			}

			ResourcesFileIterator next()
			{
				return ResourcesFileIterator(mFile);
			}
			
			bool valid() const
			{
				return mValid;
			}

		private:
			ResType	        mNode;
            std::ifstream*	mFile = {nullptr};
            bool			mValid = {false};
		};

		typedef ResourcesFileIterator<ResourceType> iterator;

		//-------------------------------------------------------------------------------
		ResourcesFile(const std::string& FileName)
		{
			mpStream.open( FileName.c_str(), std::ios_base::in );
		}

		//-------------------------------------------------------------------------------
		iterator begin()
		{
			return iterator(&mpStream);
		}

		//-------------------------------------------------------------------------------
		iterator end()
		{
			return iterator(NULL, NULL);
		}

		//-------------------------------------------------------------------------------
		~ResourcesFile()
		{
			if(mpStream.is_open())
				mpStream.close();
		}

	private:
		std::ifstream mpStream;
	};
}

}

#endif // RESOURCES_FILE_H
