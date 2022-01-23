//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
//				3DXI file exporter project template
//				For a more in-depth exemple of a 3DXI exporter,
//				please refer to maxsdk\samples\igame\export.
// AUTHOR:		Jean-Francois Yelle - created Mar.20.2007
//***************************************************************************/

#include "wox.h"

#include "3dsmaxsdk_preinclude.h"
#include "IGame/IGame.h"
#include <IGame\IGameModifier.h>
#include "ContainerSkeleton.h"

#include "Matrix4x3.h"
#include "Quaternion.h"
#include "Vector3.h"

#define wox_CLASS_ID	Class_ID(0x35cf2ddb, 0x76147ce1)



#pragma pack(push,1)


struct vIndex
{
DWORD i[3];
};

struct vVertex
{
	POD_Math::Vector3 Position;
	POD_Math::Vector3 Normal;
	float             tcoords[2];
	unsigned char     bones[4];
	float             weight[4];
};

template <typename T> class darray
{
	public:
		darray():c(),ptr(){};
		~darray(){ c=0; delete[]ptr; ptr=0; };

		bool init(const size_t n)
		{
			ptr = new(std::nothrow) T[n]();

			if(ptr) return true;

			return false;
		};

		void push_back(const T&t)
		{
			ptr[c]=t;
			++c;
		};

		size_t size()const
		{
			return c;	
		};

		T& operator [] (const size_t n)
		{
			return ptr[n];
		};

	private:

	size_t c;
	T *ptr;
};


struct Keyframe
{
	POD_Math::Quaternion Rotation;
	POD_Math::Vector3    Translation;
};

struct vBone
{
	char                Name[31];
	char                Parent;
	POD_Math::Matrix4x3 Inverse;
};

struct Header
{
		unsigned long  magic;
		unsigned long  NumVerts;
		unsigned long  NumInds;
		unsigned short NumBones;   
		unsigned short NumKeyframes;
};


#pragma pack(pop)

vIndex*Indices=0;
vVertex*Vertices=0;
vBone*Bones=0;
Keyframe*Keys=0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float SumWeights(IGameSkin*const skinPtr, const unsigned long v)
{
	int Weights=0;
	float Sum=0;
	int NumBones=skinPtr->GetNumberOfBones(v);
	for(Weights; Weights < NumBones; ++Weights) 
	{
		if(Weights==4) break;
		Sum+=skinPtr->GetWeight(v,Weights);
	};

	return Sum;
}; 

float NormalizeWeight(const float w, const float sum)
{
     return w/sum;
};


class wox : public SceneExport 
{
	public:
		
		virtual int				ExtCount();					// Number of extensions supported
		virtual const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
		virtual const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
		virtual const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
		virtual const TCHAR *	AuthorName();				// ASCII Author name
		virtual const TCHAR *	CopyrightMessage();			// ASCII Copyright message
		virtual const TCHAR *	OtherMessage1();			// Other message #1
		virtual const TCHAR *	OtherMessage2();			// Other message #2
		virtual unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
		virtual void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box

		virtual BOOL SupportsOptions(int ext, DWORD options);
		virtual int	DoExport(const TCHAR *name,ExpInterface *ei,Interface *i, BOOL suppressPrompts=FALSE, DWORD options=0);

		//Constructor/Destructor
		wox();
		virtual ~wox();

	protected:
		int GetSceneNodes(INodeTab& i_nodeTab, INode* i_currentNode =NULL);

	private:
		static HWND hParams;
};



class woxClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new wox(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return wox_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("wox"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetwoxDesc() { 
	static woxClassDesc woxDesc;
	return &woxDesc; 
}





INT_PTR CALLBACK woxOptionsDlgProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) {
	static wox *imp = NULL;

	switch(message) {
		case WM_INITDIALOG:
			imp = (wox *)lParam;
			CenterWindow(hWnd,GetParent(hWnd));
			return TRUE;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			return 1;
	}
	return 0;
}


//--- wox -------------------------------------------------------
wox::wox()
{

}

wox::~wox() 
{

}

int wox::ExtCount()
{
	// Returns the number of file name extensions supported by the plug-in.
	return 1;
}

const TCHAR *wox::Ext(int n)
{		
	#pragma message	(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("WOX");
}

const TCHAR *wox::LongDesc()
{
	#pragma message	(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\""))
	return _T("WOX Exporter");
}
	
const TCHAR *wox::ShortDesc() 
{			
	#pragma message	(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("");
}

const TCHAR *wox::AuthorName()
{			
	#pragma message	(TODO("Return ASCII Author name"))
	return _T("daotheman");
}

const TCHAR *wox::CopyrightMessage() 
{	
	#pragma message	(TODO("Return ASCII Copyright message"))
	return _T("");
}

const TCHAR *wox::OtherMessage1() 
{		
	//TODO: Return Other message #1 if any
	return _T("");
}

const TCHAR *wox::OtherMessage2() 
{		
	//TODO: Return other message #2 in any
	return _T("");
}

unsigned int wox::Version()
{				
	#pragma message	(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}

void wox::ShowAbout(HWND hWnd)
{			
	// Optional
}

BOOL wox::SupportsOptions(int ext, DWORD options)
{
	// TODO Decide which options to support.  Simply return
	// true for each option supported by each Extension 
	// the exporter supports.

	return TRUE;
}

int wox::GetSceneNodes(INodeTab& i_nodeTab, INode* i_currentNode /*=NULL*/)
{
	int i;
	if (i_currentNode == NULL)
	{
		i_currentNode = GetCOREInterface()->GetRootNode();
	}
	else // IGame will crash 3ds Max if it is initialised with the root node.
	{
	    i_nodeTab.AppendNode(i_currentNode);
	}
	for (i = 0; i < i_currentNode->NumberOfChildren(); i++)
	{
		GetSceneNodes(i_nodeTab, i_currentNode->GetChildNode(i));
	}
	return i_nodeTab.Count();
}


int	wox::DoExport(const TCHAR* name,ExpInterface* ei,Interface* i, BOOL suppressPrompts, DWORD options)
{
	// This is where the file export operation occur.

	if(!suppressPrompts)
		DialogBoxParam(hInstance, 
				MAKEINTRESOURCE(IDD_PANEL), 
				GetActiveWindow(), 
				woxOptionsDlgProc, (LPARAM)this);


		FILE*log=fopen("log.txt", "w+t");

	IGameScene * pIgame = GetIGameInterface();


	IGameConversionManager* manager=GetConversionManager();
	manager->SetCoordSystem(IGameConversionManager::IGAME_D3D);

	pIgame->InitialiseIGame();
	pIgame->SetStaticFrame(0);
	
	IGameNode* node  = pIgame->GetIGameNode(i->GetSelNode(0));
	IGameObject*obj  = node->GetIGameObject();
	IGameMesh* mesh  = (IGameMesh*) obj; 

	mesh->InitializeData();

	int NumV = mesh->GetNumberOfVerts();
	int NumF= mesh->GetNumberOfFaces();
	int NumT=mesh->GetNumberOfTexVerts();

	
	fprintf(log,"%s","BEFORE SKIN");
	IGameSkin*skin   = mesh->GetIGameSkin();

	int NumKeyframes = (pIgame->GetSceneEndTime() - pIgame->GetSceneStartTime()) / pIgame->GetSceneTicks();
	
	fprintf(log,"%s","ALLOCATIONS");
	Header         head=Header(); 
	darray<vVertex> Vertices; Vertices.init(mesh->GetNumberOfFaces()*3);

	darray<int> OriginalVertexIndicesForBones; 
	OriginalVertexIndicesForBones.init(mesh->GetNumberOfFaces()*3);

	Indices    =  new(std::nothrow) vIndex    [mesh->GetNumberOfFaces()]();
	Bones      =  new(std::nothrow) vBone     [skin->GetTotalBoneCount()]();
	Keys       =  new(std::nothrow) Keyframe  [skin->GetTotalBoneCount()*NumKeyframes]();

	head.NumKeyframes=NumKeyframes;
	head.NumBones=skin->GetTotalBoneCount();
	head.NumInds=mesh->GetNumberOfFaces();
	head.NumVerts=0;
	head.magic=100;

	fprintf(log,"%s","BUILD HIERARCHY");

	ContainerSkeleton sc; 
	sc.BuildHierarchy(skin,log); 
	
	DWORD Written=0;
	fprintf(log,"%s","CREATE FILE");
	HANDLE file=CreateFile(name,
		                   GENERIC_WRITE,
						   0,
						   0,
						   CREATE_ALWAYS,
						   FILE_ATTRIBUTE_NORMAL,
						   0);
		
		fprintf(log,"%s","FACES");
		for(int i=0; i < mesh->GetNumberOfFaces(); ++i)
		{
			FaceEx * facec=mesh->GetFace(i);

			for(int tt =0; tt < 3; ++tt)
			{
				Point3 V0  = mesh->GetVertex(facec->vert[tt]);
				Point2 tV0 = mesh->GetTexVertex(mesh->GetFaceTextureVertex(i,tt));
				Point3 N0  = mesh->GetNormal(i,tt);

				int u = 0;
				
				for(u;  u < Vertices.size(); ++u)
				{
					if(Vertices[u].tcoords[0] == tV0.x &&
						Vertices[u].tcoords[1] == tV0.y &&
						Vertices[u].Position.x == V0.x &&
						Vertices[u].Position.y == V0.y &&
						Vertices[u].Position.z == V0.z &&
						Vertices[u].Normal.x == N0.x && 
						Vertices[u].Normal.y == N0.y &&
						Vertices[u].Normal.z == N0.z)
						{
							Indices[i].i[tt] = u; 
								break;
						};
				};

				if( u == Vertices.size())
				{
					vVertex v = vVertex();

					v.Position.x = V0.x;
					v.Position.y = V0.y;
					v.Position.z = V0.z;

					v.Normal.x = N0.x;
					v.Normal.y = N0.y;
					v.Normal.z = N0.z;

					v.tcoords[0] = tV0.x;
					v.tcoords[1] = tV0.y;

					Vertices.push_back(v); // put an original vertex
					OriginalVertexIndicesForBones.push_back(facec->vert[tt]); // put the original index 

					Indices[i].i[tt] = Vertices.size()-1;
				};
					
			};

		};

		//*********************************************** special
	for(int v=0; v < OriginalVertexIndicesForBones.size(); ++v)
	{
	
		float Sum=SumWeights(skin,OriginalVertexIndicesForBones[v]);
	
		for(int b=0; b < skin->GetNumberOfBones(OriginalVertexIndicesForBones[v]); ++b)
		{
			if(b==4)break;

			IGameNode* Bone = skin->GetIGameBone(OriginalVertexIndicesForBones[v],b);
			float Weight    = skin->GetWeight(OriginalVertexIndicesForBones[v],b);

			if(Sum!=1.0f) Weight=NormalizeWeight(Weight,Sum);

			if(!Weight)continue;
			
			Vertices[v].bones[b]  = static_cast<unsigned char>(sc.GetOrder(skin->GetBoneIndex(Bone)));
			Vertices[v].weight[b] = Weight;
		};

	};

			
			fprintf(log,"%s","BONES");
		for(int bb=0; bb < skin->GetTotalBoneCount(); ++bb)
		{

			IGameNode* Bone = skin->GetIGameBone(bb);
			IGameNode* Parent = Bone->GetNodeParent();

			GMatrix SpaceMatrix4; 

			SpaceMatrix4=Bone->GetWorldTM(0);
			Matrix3 SpaceMatrix3=SpaceMatrix4.ExtractMatrix3();
			SpaceMatrix3.Invert();

			strcpy(Bones[sc.GetOrder(bb)].Name,Bone->GetName());

			if(Parent) Bones[sc.GetOrder(bb)].Parent=static_cast<char>(sc.GetRoot()->GetHierarchyIndex(Parent->GetNodeID()));
			else Bones[sc.GetOrder(bb)].Parent = -1;


			//***************************************
			//       Инверсия
			//***************************************
			Point3 SMr0=SpaceMatrix3.GetRow(0);
			Point3 SMr1=SpaceMatrix3.GetRow(1);
			Point3 SMr2=SpaceMatrix3.GetRow(2);
			const Point3 Tr=SpaceMatrix3.GetTrans();

			Bones[sc.GetOrder(bb)].Inverse._11= SMr0.x;
			Bones[sc.GetOrder(bb)].Inverse._12= SMr0.y;
			Bones[sc.GetOrder(bb)].Inverse._13= SMr0.z;

			Bones[sc.GetOrder(bb)].Inverse._21= SMr1.x;
			Bones[sc.GetOrder(bb)].Inverse._22= SMr1.y;
			Bones[sc.GetOrder(bb)].Inverse._23= SMr1.z;

			Bones[sc.GetOrder(bb)].Inverse._31= SMr2.x;
			Bones[sc.GetOrder(bb)].Inverse._32= SMr2.y;
			Bones[sc.GetOrder(bb)].Inverse._33= SMr2.z;

			Bones[sc.GetOrder(bb)].Inverse._41= Tr.x;
			Bones[sc.GetOrder(bb)].Inverse._42= Tr.y;
			Bones[sc.GetOrder(bb)].Inverse._43= Tr.z;

			//***************************************
				//MessageBox(0,"BOOM5","",0);
			for(int kKeys=0; kKeys < NumKeyframes; ++kKeys)
			{

            GMatrix SecondKey;

			if(sc.GetRoot()->GetBone() == Bone->GetNodeID())
			{
			    SecondKey = Bone->GetWorldTM(pIgame->GetSceneTicks()*kKeys); 
			}
			else
			{
                 SecondKey = Bone->GetLocalTM(pIgame->GetSceneTicks()*kKeys); 
			};

		    Matrix3 SecondKey3=SecondKey.ExtractMatrix3();
			Quat    SecondKeyQ(SecondKey3);
			const Point3 SecondKeyTrans=SecondKey3.GetTrans();

			int That = sc.GetOrder(bb) * NumKeyframes + kKeys;

			//***************************************

			Keys[ That].Rotation.x=SecondKeyQ.x;
			Keys[ That].Rotation.y=SecondKeyQ.y;
			Keys[ That].Rotation.z=SecondKeyQ.z;
			Keys[ That].Rotation.w=SecondKeyQ.w;

			//***************************************

			Keys[ That].Translation.x=SecondKeyTrans.x;
			Keys[ That].Translation.y=SecondKeyTrans.y;
			Keys[ That].Translation.z=SecondKeyTrans.z;

			//****************************************************
			};
			
		}; 
			//MessageBox(0,"BOOM6","",0);
		head.NumVerts = Vertices.size();
	WriteFile(file,
			      &head,
				  sizeof(Header),
				  &Written,
				  0);

	WriteFile(file,
			      &Vertices[0],
				  sizeof(vVertex)*Vertices.size(),
				  &Written,
				  0);

	WriteFile(file,
			      Indices,
				  sizeof(vIndex)*mesh->GetNumberOfFaces(),
				  &Written,
				  0);
	
			WriteFile(file,
			      Bones,
				  sizeof(vBone)*skin->GetTotalBoneCount(),
				  &Written,
				  0);

		WriteFile(file,
			      Keys,
				  sizeof(Keyframe)*skin->GetTotalBoneCount()*NumKeyframes,
				  &Written,
				  0);
			
   delete[]Indices;
   delete[]Bones;
   delete[]Keys;

            fprintf(log,"\n%f,%f,%f\n",mesh->GetMaxMesh()->getTVert(0).x,
		                               mesh->GetMaxMesh()->getTVert(0).y,
	                                   mesh->GetMaxMesh()->getTVert(0).z);

	        fprintf(log,"\n%f,%f,%f\n",mesh->GetTexVertex(0).x,
		                               mesh->GetTexVertex(0).y
	                                   );

			fprintf(log,"\n NUM_MAP_VERTS: %d, NUM_TEX_VERTS: %d, NUMERTS: %d\n",mesh->GetNumberOfMapVerts(1),
				mesh->GetNumberOfTexVerts(),mesh->GetNumberOfVerts()
	                                   );
			


	pIgame->ReleaseIGame();
   CloseHandle(file);
   fclose(log);

	return FALSE;
}


 
 
