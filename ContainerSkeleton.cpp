#include "ContainerSkeleton.h"

	ContainerSkeleton::ContainerSkeleton() : 
	  NumBones(),
	  BoneTable(),
	  Root(),
	  Preallocated() {};

	  ContainerSkeleton::~ContainerSkeleton()
	  {   
		  NumBones=0;
		  Root=0;              // На случай если вы - псих и реконструируете класс)
		  delete[] BoneTable;
		  delete[] Preallocated;
	  };


	BoneContainer*ContainerSkeleton::GetBoneContainer(const size_t b)const
	{
		return  b <= NumBones ? &Preallocated[b] : 0;
	};

	BoneContainer*ContainerSkeleton::GetRoot()const { return Root; };

bool ContainerSkeleton::BuildHierarchy(IGameSkin*const skinPtr, FILE*log)
{

   int AllBones=0; 

   if(log)fprintf(log, "%s\n", "HIERARCHY BUILDING..");

   NumBones=skinPtr->GetTotalBoneCount();
   fprintf(log, "%d\n", NumBones);

   Preallocated = new(std::nothrow) BoneContainer[NumBones];
   BoneTable    = new(std::nothrow) int [NumBones]();

   if(!Preallocated || !BoneTable) return false;

   for(int nb=0; nb < NumBones; ++nb) if(!Preallocated[nb].Allocate(20)) return false; 

   if(log)fprintf(log, "%s\n", "ESTABILISHING RELATIONS..");
   for(AllBones; AllBones < NumBones; ++AllBones)
   {
       IGameNode* ChildNode  = skinPtr->GetIGameBone(AllBones);
	   IGameNode* ParentNode = ChildNode->GetNodeParent();

	   int sAllBones=0;

	     if(ParentNode)
	     {
		      bool Parent = false;

	          for(sAllBones; sAllBones < NumBones; ++sAllBones)
	          {    
	                if( ParentNode->GetNodeID() == skinPtr->GetIGameBone(sAllBones)->GetNodeID() )
					{  
						if(log)fprintf(log, "PARENT: %d; PARENT_NAME: %s; \n CHILD: %d; CHILD_NAME: %s\n",
						sAllBones,
						ParentNode->GetName(),
						AllBones, 
						ChildNode->GetName()
						);

	                    if(!Preallocated[sAllBones].AttachBone(ChildNode->GetNodeID(), &Preallocated[AllBones])) 
						{
							 if(!Preallocated[sAllBones].Reallocate()) {  return false; }; 
						     Preallocated[sAllBones].AttachBone(ChildNode->GetNodeID(), &Preallocated[AllBones]);
						};

						Parent = true;
					};
	          };

			  if(!Parent) { Root=&Preallocated[AllBones]; Root->SetBone(ChildNode->GetNodeID());
			                if(log)fprintf(log, "ROOT: %d; NAME: %s\n\n", AllBones,ChildNode->GetName()); };
	 } 
	 else
	 {
        Root=&Preallocated[AllBones]; 
		Root->SetBone(ChildNode->GetNodeID()); 
		if(log)fprintf(log, "ROOT: %d; NAME: %s\n\n", AllBones,ChildNode->GetName());
	 };
		 
   };
       if(log)fprintf(log, "%s\n\n", "COMPLETE");

   int mAllBones=0;

    if(log)fprintf(log, "%s\n", "FILLING BONETBLE..");
   for(mAllBones; mAllBones < NumBones; ++mAllBones)
   {
        IGameNode* SkinBone  = skinPtr->GetIGameBone(mAllBones);
		BoneTable[mAllBones] = Root->GetHierarchyIndex(SkinBone->GetNodeID()); 
   };
     if(log)fprintf(log, "%s\n\n", "COMPLETE");

	 if(log)fprintf(log, "%s\n\n", "COMPLETE");
	  return true;
};

int ContainerSkeleton::GetOrder(int index)const
{
	return BoneTable[index];
};