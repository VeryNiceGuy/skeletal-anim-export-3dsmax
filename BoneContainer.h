#ifndef BONECONTAINER_H
#define BONECONTAINER_H

#include<new>   

	class BoneContainer
	{

	public:

	    BoneContainer();
	    ~BoneContainer();

		bool Allocate(size_t size);
		bool Reallocate();
		bool AttachBone(const int bone, BoneContainer*const prealloc);
		int GetHierarchyIndex(const int bone);
		void SetBone(const int bone);
		int GetBone()const;

        private:

		bool GetHierarchyIndexRecursive(const int bone, size_t& count);


	unsigned short NumChildren;
	size_t         MaxChildren; 
	BoneContainer  **Children; 
	int            IBone;   

	};



#endif
