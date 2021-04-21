#include "Octree.h"
using namespace Simplex;

// Simplex
uint Octree::octantCount = 0;
uint Octree::maxLvl = 3;
uint Octree::idealEntCount = 5;

// Creates the root of the tree and begins the tree
Simplex::Octree::Octree(uint octantLevels, uint maxSub)
{
	// Initializes the tree's fields and clears all previous data
	maxLvl = 0;
	m_pEntMgr = MyEntityManager::GetInstance();
	m_pMeshMgr = MeshManager::GetInstance();

	center = vector3(0.0f);
	min = vector3(0.0f);
	max = vector3(0.0f);
	size = 0;
	numOfChildren = 0;
	octantCount = 0;
	maxLvl = octantLevels;
	myId = octantCount;

	root = nullptr;
	parent = nullptr;

	idealEntCount = maxSub;

	// Set the root and clear the nodes
	root = this;
	nodes.clear();

	std::vector<vector3> Maxmin;

	// Get the number of entities and the entity to add its locations to a list
	uint numObj = m_pEntMgr->GetEntityCount();
	for (uint i = 0; i < numObj; i++)
	{
		MyEntity* tempEnt = m_pEntMgr->GetEntity(i);
		MyRigidBody* tempbody = tempEnt->GetRigidBody();
		Maxmin.push_back(tempbody->GetMinGlobal());
		Maxmin.push_back(tempbody->GetMaxGlobal());
	}

	MyRigidBody* tempbody = new MyRigidBody(Maxmin);

	vector3 hWidth = tempbody->GetHalfWidth();
	Maxmin.clear();

	float sizeMax = hWidth.x;
	for (int i = 0; i < 3; i++)
	{
		if (sizeMax < hWidth[i])
		{
			sizeMax = hWidth[i];
		}
	}

	// Get its center and update max and min values
	vector3 mycenter = tempbody->GetCenterLocal();
	Maxmin.clear();
	SafeDelete(tempbody);

	size = sizeMax * 2;
	center = mycenter;
	min = center - vector3(sizeMax);
	max = center + vector3(sizeMax);

	octantCount++;

	FormTree(maxLvl);
}

// Creates the nodes within the tree
Simplex::Octree::Octree(vector3 tempCent, float tempSize)
{
	m_pEntMgr = MyEntityManager::GetInstance();
	m_pMeshMgr = MeshManager::GetInstance();

	center = vector3(0.0f);
	min = vector3(0.0f);
	max = vector3(0.0f);
	size = 0;
	numOfChildren = 0;
	myId = octantCount;

	center = tempCent;
	size = tempSize;

	min = center - (vector3(size / 2));
	max = center + (vector3(size / 2));

	octantCount++;
}

void Simplex::Octree::Display(uint octreeID)
{
	if (myId == octreeID)
	{
		m_pMeshMgr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, center) * glm::scale(vector3(size)), C_YELLOW, RENDER_WIRE);

		return;
	}
	for (uint i = 0; i < numOfChildren; i++)
	{
		children[i]->Display(octreeID);
	}
}

void Simplex::Octree::Display(vector3 color)
{
	for (uint i = 0; i < numOfChildren; i++)
	{
		children[i]->Display(color);
	}
	m_pMeshMgr->AddWireCubeToRenderList(glm::translate(IDENTITY_M4, center) * glm::scale(vector3(size)), color, RENDER_WIRE);
}

// Divides the larger cube into smaller sub-divisions
void Simplex::Octree::Divide(void)
{
	if (myLvl >= maxLvl)
	{
		return;
	}

	if (numOfChildren != 0)
	{
		return;
	}

	numOfChildren = 8;

	// Calculates location of each quadrants center
	float mySize = size / 4.0f;
	float mySizeSec = mySize * 2;

	vector3 curCenter;

	curCenter = center;
	curCenter.x -= mySize;
	curCenter.y -= mySize;
	curCenter.z -= mySize;
	children[0] = new Octree(curCenter, mySizeSec);

	curCenter.x += mySizeSec;
	children[1] = new Octree(curCenter, mySizeSec);

	curCenter.z += mySizeSec;
	children[2] = new Octree(curCenter, mySizeSec);

	curCenter.x -= mySizeSec;
	children[3] = new Octree(curCenter, mySizeSec);

	curCenter.y += mySizeSec;
	children[4] = new Octree(curCenter, mySizeSec);

	curCenter.z -= mySizeSec;
	children[5] = new Octree(curCenter, mySizeSec);

	curCenter.x += mySizeSec;
	children[6] = new Octree(curCenter, mySizeSec);

	curCenter.z += mySizeSec;
	children[7] = new Octree(curCenter, mySizeSec);

	for (uint i = 0; i < 8; i++)
	{
		children[i]->root = root;
		children[i]->parent = this;
		children[i]->myLvl = myLvl + 1;
		if(children[i]->HasMore(idealEntCount))
		{
			children[i]->Divide();
		}
	}

}

// Checks the current entity for collisions
bool Simplex::Octree::HasMore(uint Entities)
{

	m_pEntMgr = MyEntityManager::GetInstance();
	m_pMeshMgr = MeshManager::GetInstance();

	uint currentNum = 0;
	uint objCount = m_pEntMgr->GetEntityCount();

	for (uint i = 0; i < objCount; i++)
	{
		if (Collide(i))
		{
			currentNum++;
		}
		if (currentNum > Entities)
		{
			return true;
		}
	}

	return false;
}
// Creates tree
void Simplex::Octree::FormTree(uint maxlevels)
{
	if (myLvl != 0)
	{
		return;
	}

	maxLvl = maxlevels;

	octantCount = 1;
	
	// Clear previous lists 
	ListOfEnt.clear();

	ClearBranch();
	nodes.clear();

	
	if (HasMore(idealEntCount))
	{
		Divide();
	}
	
	// Assign the children to the list and construct the list of their children
	AddChild();
	ConstList();

}
// Adds to list
void Simplex::Octree::AddChild(void)
{ 
	for (uint i = 0; i < numOfChildren; i++)
	{
		children[i]->AddChild();
	}
	if (numOfChildren == 0) //Finds a leaf
	{
		uint numEnt = m_pEntMgr->GetEntityCount(); // Gets the number of entities and checks for collision
		for (uint i = 0; i < numEnt; i++)
		{
			// If so, add it to that quadrants list
			if (Collide(i)) 
			{
				ListOfEnt.push_back(i);
				m_pEntMgr->AddDimension(i, myId);
			}
		}
	}
}

// Creates a list for each child
void Simplex::Octree::ConstList(void)
{
	for (uint i = 0; i < numOfChildren; i++)
	{
		children[i]->ConstList();
	}
	if (ListOfEnt.size() < 0)
	{
		root->nodes.push_back(this);
	}
}

// Clears the nodes on the branch
void Simplex::Octree::ClearBranch(void)
{
	for (uint i = 0; i < numOfChildren; i++)
	{
		children[i]->ClearBranch();
		delete children[i];
		children[i] = nullptr;
	}

	numOfChildren = 0;
}

// Checks Collision
bool Simplex::Octree::Collide(uint curNum)
{
	uint objCount = m_pEntMgr->GetEntityCount();

	if (curNum >= objCount)
	{
		return false;
	}

	MyEntity* tempEnt = m_pEntMgr->GetEntity(curNum);
	MyRigidBody* tempBody = tempEnt->GetRigidBody();

	vector3 objmin = tempBody->GetMinGlobal();
	vector3 objmax = tempBody->GetMaxGlobal();

	//Check along each axis for collision, return true if there's a collision
	if (max.x < objmin.x)
	{
		return false;
	}
	if (min.x > objmax.x)
	{
		return false;
	}

	if (max.y < objmin.y)
	{
		return false;
	}
	if (min.y > objmax.y)
	{
		return false;
	}

	if (max.z < objmin.z)
	{
		return false;
	}
	if (min.z > objmax.z)
	{
		return false;
	}

	return true;
}


