#include "GameObject.h"
#include <list>
#include "Quadtree.h"


#include "Quadtree.h"
#include <ios>
#include "GameManager.h"
#include "trace.h"
#include "Camera.h"

int Quadtree::QUADTREE_CREATED = 0;
int Quadtree::QUADTREE_DELETED = 0;
Quadtree::Quadtree()
{
	QUADTREE_CREATED++;
	m_level = 90;
	//m_nodes = new Quadtree*[4]();
	m_region = new RECT();
	m_object_list = new std::list<GameObject*>();
}

Quadtree::Quadtree(int level, RECT* region)
{
	QUADTREE_CREATED++;
	m_level = level;
	m_region = region;
	//m_nodes = new Quadtree*[4]();
	m_object_list = new std::list<GameObject*>();
}


Quadtree::~Quadtree()
{
	QUADTREE_DELETED++;
	//this->Clear();
}

void Quadtree::PrintAll()
{
	if (m_nodes)
	{
		for (int i = 0; i<4; i++)
		{
			if (m_nodes[i] != nullptr)
				this->PrintAll();
		}
		_count_test++;
		return;
	}

}

void Quadtree::Clear()
{
	//Clear all nodes
	if (m_nodes != nullptr)
	{
		for (int i = 0; i<4; i++)
		{
			if (m_nodes[i] != nullptr)
			{
				m_nodes[i]->Clear();
				delete m_nodes[i];
			}
		}
		delete[] m_nodes;
		//clear current quadtree
		for (auto i = m_object_list->begin(); i != m_object_list->end();)
			delete *i;
		m_object_list->clear();
		delete m_object_list;
		delete m_region;
		_count_test++;
	}
}

bool Quadtree::IsContaining(GameObject* gameObject)
{
	return SimpleIntersect(m_region, &gameObject->bounding_box());
}


RECT* initialize(int left, int right, int top, int bottom)
{
	RECT* temp_rect = new RECT();

	temp_rect->left = left;
	temp_rect->right = right;
	temp_rect->bottom = bottom;
	temp_rect->top = top;
	return temp_rect;
}

void Quadtree::Split()
{
	m_nodes = new Quadtree*[4]();
	m_nodes[0] = new Quadtree(m_level + 1, initialize(m_region->left, m_region->right / 2, m_region->top, m_region->bottom / 2));

	m_nodes[1] = new Quadtree(m_level + 1, initialize(m_region->right / 2, m_region->right, m_region->top, m_region->bottom / 2));

	m_nodes[2] = new Quadtree(m_level + 1, initialize(m_region->right / 2, m_region->right, m_region->bottom / 2, m_region->bottom));

	m_nodes[3] = new Quadtree(m_level + 1, initialize(m_region->left, m_region->right / 2, m_region->bottom / 2, m_region->bottom));

}

void Quadtree::Insert(GameObject* gameObject)
{
	//Insert gameobject into corresponding nodes
	if (m_nodes)
	{
		for (int i = 0; i<4; i++)
		{
			//m_nodes[i] = new Quadtree();
			if (m_nodes[i]->IsContaining(gameObject))
				m_nodes[i]->Insert(gameObject);
		}
	}
	else
	{
		//Insert entity into current quadtree
		if (this->IsContaining(gameObject))
			m_object_list->push_back(gameObject);

		//Split and move all objects in list into it’s corresponding nodes
		if (m_object_list->size() > MAX_OBJECTS_IN_REGION && m_level < QT_MAX_LEVEL)
		{
			Split();

			while (!m_object_list->empty())
			{
				if (m_nodes[0]->IsContaining(m_object_list->back()))
					m_nodes[0]->Insert(m_object_list->back());
				if (m_nodes[1]->IsContaining(m_object_list->back()))
					m_nodes[1]->Insert(m_object_list->back());
				if (m_nodes[2]->IsContaining(m_object_list->back()))
					m_nodes[2]->Insert(m_object_list->back());
				if (m_nodes[3]->IsContaining(m_object_list->back()))
					m_nodes[3]->Insert(m_object_list->back());

				m_object_list->pop_back();
			}
		}
	}


}
void Quadtree::Retrieve(std::list<GameObject*>* return_objects_list, GameObject* gameObject)
{
	if (m_nodes)
	{
		for (int i = 0; i<4; i++)
		{
			if (m_nodes[i] != nullptr)
				/*if (m_nodes[i]->IsContaining(gameObject))*/
					m_nodes[i]->Retrieve(return_objects_list, gameObject);
		}
		return;
	}
	//Add all entities in current region into return_objects_list
	if (this->IsContaining(gameObject))
	{
		for (auto i = m_object_list->begin(); i != m_object_list->end(); i++)
		{
			GameObject* gameObject = *i;
			if (SimpleIntersect(&gameObject->bounding_box(), &MyCamera::GetInstance()->bounding_box()))
				if(find(return_objects_list->begin(), return_objects_list->end(), *i)== return_objects_list->end())
					return_objects_list->push_back(*i);
		}

	}

}

Quadtree* Quadtree::CreateQuadtree(int x1, int y1, int x2, int y2)
{
	Quadtree* quadtree = new Quadtree(0, initialize(x1, x2, y1, y2));
	for (auto i = GameManager::GetInstance()->GetCurrentScene()->game_object_list()->begin(); i != GameManager::GetInstance()->GetCurrentScene()->game_object_list()->end(); i++)
	{
		quadtree->Insert(*i);
	}
	return quadtree;
}









