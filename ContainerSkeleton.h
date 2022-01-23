#ifndef CONTAINERSKELETON_H
#define CONTAINERSKELETON_H

#include "BoneContainer.h"
#include <IGame\IGame.h>
#include <IGame\IGameModifier.h>

class ContainerSkeleton
{

public:

	ContainerSkeleton();
	~ContainerSkeleton();


	BoneContainer*GetBoneContainer(const size_t b)const;
	BoneContainer*GetRoot()const;

bool BuildHierarchy(IGameSkin*const skinPtr, FILE*log);
int GetOrder(int index)const;

	protected:

		BoneContainer*Preallocated;
		BoneContainer*Root;
		int NumBones;
		int *BoneTable;

	};

#endif