#pragma once
#ifndef _QUADTREE_H
#define _QUADTREE_H
//06-11 chipu
#include <wincon.h>
#include <list>
#include "GameObject.h"

#define QT_MAX_LEVEL 6
#define MAX_OBJECTS_IN_REGION 3

class Quadtree
{
private:
	int m_level;
	RECT* m_region;
	std::list<GameObject*>* m_object_list;

public:

	std::list<GameObject*>* object_list() const
	{
		return m_object_list;
	}

	void set_object_list(std::list<GameObject*>* game_objects)
	{
		m_object_list = game_objects;
	}

private:
	Quadtree** m_nodes;
	bool IsContaining(GameObject* gameObject);
	void Split();


public:
	static Quadtree* CreateQuadtree(int, int, int, int);
	Quadtree();
	Quadtree(int level, RECT* region);
	~Quadtree();
	int _count_test;
	void PrintAll();
	void Clear();
	void Insert(GameObject* gameObject);
	void Retrieve(std::list<GameObject*>* return_objects_list, GameObject* gameObject);
	static int QUADTREE_CREATED;
	static int QUADTREE_DELETED;


};
#endif
