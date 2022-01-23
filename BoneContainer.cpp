#include "BoneContainer.h"


	    BoneContainer::BoneContainer():
	    Children(),
	    NumChildren(),
		MaxChildren(),
		IBone(){};

	    BoneContainer::~BoneContainer(){ delete[] Children; }; 

		bool BoneContainer::Allocate(size_t size)
		{
		   
           Children = new(std::nothrow) BoneContainer*[size];
		   if(!Children) return false;
		   MaxChildren=size;

		   return true;
		};


		bool BoneContainer::Reallocate()
		{
		   int Ch=0;
           BoneContainer**tmp = new(std::nothrow) BoneContainer*[MaxChildren*2];
		   if(!tmp) return false;

		   if(Children)
		   {
                for(Ch; Ch < NumChildren; ++Ch)
				{
                   tmp[Ch]=Children[Ch];
				};

				MaxChildren*=2;
		   };

		   delete[]Children;
		   Children=tmp;

		   return true;
		};


		bool BoneContainer::AttachBone(const int bone,          
		                BoneContainer*const prealloc) 
		{
		    if(NumChildren==MaxChildren) return false;

			    Children[NumChildren]=prealloc;
				Children[NumChildren]->SetBone(bone);

		    ++NumChildren;

			return true;
		};

		
		int BoneContainer::GetHierarchyIndex(const int bone)
		{
            size_t OrderIndex=0; 
			return GetHierarchyIndexRecursive(bone,OrderIndex) ? OrderIndex : -1;
		};

		void BoneContainer::SetBone(const int bone)
		{
		    IBone=bone;
		};

		int BoneContainer::GetBone()const
		{
		    return IBone;
		};

		bool BoneContainer::GetHierarchyIndexRecursive(const int bone, size_t& count)
		{
		   int Ch=0;

		   if(GetBone()==bone) return true; 

		   if(NumChildren)                 
		   {

               for(Ch; Ch < NumChildren; ++Ch)
		       {   
		           ++count;  
		           bool Result=Children[Ch]->GetHierarchyIndexRecursive(bone,count);
			       if  (Result) return Result;  
		       };

		   };

		   return false;    
		};