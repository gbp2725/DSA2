#pragma once

#include <vector>

#include "MyEntityManager.h"

namespace Simplex
{
	class Octree
	{
	private:
		std::vector<Octree*> nodes; // Nodes within the tree

		static uint octantCount;
		static uint maxLvl;
		static uint idealEntCount;

		uint myId = 0;
		uint myLvl = 0;
		uint numOfChildren = 0;

		float size = 0.0f;

		MeshManager* m_pMeshMgr = nullptr;
		MyEntityManager* m_pEntMgr = nullptr;

		vector3 center = vector3(0.0f); // Center point
		vector3 min = vector3(0.0f);
		vector3 max	= vector3(0.0f);

		Octree* root = nullptr; // Root of tree
		Octree* parent = nullptr; // Parent of octant
		Octree* children[8]; // Children of octant

		std::vector<uint> ListOfEnt; // List of entities
	public:
		// Octree construct
		Octree(uint octantLevels, uint maxSub);  
		Octree(vector3 tempCent, float tempSize);
		Model* model;

		// Display octree
		void Display(uint octreeID); 

		// Show the starting box
		void Display(vector3 color);
		// Divides the larger cube into smaller sub-divisions
		void Divide(void);
		// Checks the current entity for collisions
		bool HasMore(uint Entities);
		// Creates tree
		void FormTree(uint maxlevels);
		// Adds to list
		void AddChild(void);
		// Creates a list for each child
		void ConstList(void);
		// Clears the nodes on the branch
		void ClearBranch(void);
		// Checks for collision 
		bool Collide(uint curNum);
	};
}
