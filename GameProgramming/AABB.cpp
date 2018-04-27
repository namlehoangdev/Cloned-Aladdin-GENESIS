#include "AABB.h"
#include <limits>
#include "game.h"
#include "trace.h"
//new 02-11 chipu

RECT getSweptBroadphaseRect(const GameObject* MovingObj)
{
	RECT rect;

	rect.left = (MovingObj->vx()) > 0 ? MovingObj->bounding_box().left : MovingObj->bounding_box().left + (MovingObj->vx()*FIXED_TIME);
	rect.top = (MovingObj->vy()) > 0 ? MovingObj->bounding_box().top : MovingObj->bounding_box().top + (MovingObj->vy()*FIXED_TIME);
	rect.right = (MovingObj->vx())>0 ? (MovingObj->vx()*FIXED_TIME) + MovingObj->width() + MovingObj->bounding_box().left : MovingObj->bounding_box().left + MovingObj->width();
	rect.bottom = (MovingObj->vy()) > 0 ? MovingObj->bounding_box().top + MovingObj->height() + (MovingObj->vy()*FIXED_TIME) : MovingObj->bounding_box().top + MovingObj->height();
	return rect;
}

bool SimpleIntersect(RECT* rect1, RECT* rect2)
{
	RECT temp_rect;
	IntersectRect(&temp_rect, rect1, rect2);
	return (temp_rect.top != 0 || temp_rect.bottom != 0 || temp_rect.right != 0 || temp_rect.left != 0);

}

RECT CalculateBoundingBox(float x, float y, int width, int height, AnchorPoint anchor)
{
	RECT temp_rect;
	switch (anchor)
	{
	case TOP_LEFT:
	{
		temp_rect.left = x;
		temp_rect.right = x + width;
		temp_rect.top = y;
		temp_rect.bottom = y + height;
	}; break;
	case TOP_MID:
	{
		temp_rect.left = x - width / 2;
		temp_rect.right = x + width / 2;
		temp_rect.top = y;
		temp_rect.bottom = y + height;

	}; break;
	case TOP_RIGHT:
	{
		temp_rect.left = x - width;
		temp_rect.right = x;
		temp_rect.top = y;
		temp_rect.bottom = y + height;
	}; break;
	case MID_LEFT:
	{
		temp_rect.left = x;
		temp_rect.right = x + width;
		temp_rect.top = y - height / 2;
		temp_rect.bottom = y + height / 2;
	}; break;
	case MIDDLE:
	{
		temp_rect.left = x - width / 2;
		temp_rect.right = x + width / 2;
		temp_rect.top = y - height / 2;
		temp_rect.bottom = y + height / 2;

	}; break;
	case MID_RIGHT:
	{
		temp_rect.left = x - width;
		temp_rect.right = x;
		temp_rect.top = y;
		temp_rect.bottom = y + height;

	}; break;
	case BOTTOM_LEFT:
	{
		temp_rect.left = x;
		temp_rect.right = x + width;
		temp_rect.top = y - height / 2;
		temp_rect.bottom = y + height / 2;
	}; break;

	case BOTTOM_MID:
	{
		temp_rect.left = x - width / 2;
		temp_rect.right = x + width / 2;
		temp_rect.top = y - height;
		temp_rect.bottom = y;

	}; break;
	case BOTTOM_RIGHT:
	{
		temp_rect.left = x - width;
		temp_rect.right = x;
		temp_rect.top = y - height;
		temp_rect.bottom = y;

	}; break;
	}
	return temp_rect;
}

CollisionResult CheckCollision(GameObject* MovingObj, GameObject* SubMoving)
{
	CollisionResult result;
	result._collisionIndex = 1.0f;
	result._collisionSide = NONE;
	
		float dxEntry, dxExit, txEntry, txExit;
		float dyEntry, dyExit, tyEntry, tyExit;
		float tEntry, tExit;
		float movingX1 = MovingObj->bounding_box().left;
		float movingX2 = movingX1 + MovingObj->width();
		float movingY1 = MovingObj->bounding_box().top;
		float movingY2 = movingY1 + MovingObj->height();
		float staticX1 = SubMoving->bounding_box().left + SubMoving->vx();
		float staticX2 = staticX1 + SubMoving->width();
		float staticY1 = SubMoving->bounding_box().top + SubMoving->vy();
		float staticY2 = staticY1 + SubMoving->height();

		int fixedVx = MovingObj->vx()*FIXED_TIME;
		int fixedVy = MovingObj->vy()*FIXED_TIME;
		RECT dst_rect;
		IntersectRect(&dst_rect, &getSweptBroadphaseRect(MovingObj), &SubMoving->bounding_box());
		if (dst_rect.bottom == 0 && dst_rect.top == 0 && dst_rect.right == 0 && dst_rect.left == 0)
		{
			return result;
		}
		//to edit later
		if (SubMoving->get_name() == "HorizontalBar" || SubMoving->get_name() == "Rope")
		{
			IntersectRect(&dst_rect, &MovingObj->bounding_box(), &SubMoving->bounding_box());
			if (dst_rect.bottom == 0 && dst_rect.top == 0 && dst_rect.right == 0 && dst_rect.left == 0)
			{
				return result;
			}
			else
			{
				result._collisionIndex = 0;
				return result;
			}
		}

	
		if (fixedVy == 0.0f)
		{
			tyEntry = -std::numeric_limits<float>::infinity();
			tyExit = -std::numeric_limits<float>::infinity();
			if (staticY1 > movingY2 || staticY2 < movingY1)
			{
				/*movingX1 += MovingObj->vx();*/
				return result;
			}
		}
		if (fixedVx == 0.0f)
		{
			txEntry = -std::numeric_limits<float>::infinity();
			txExit = -std::numeric_limits<float>::infinity();
			if (staticX1 > movingX2 || staticX2 < movingX1)
			{
				return result;
			}
		}

		if (fixedVx > 0)
		{
			//distance of near side with fixedVx > 0
			dxEntry = staticX1 - movingX2;
			//distance of far side with fixedVx > 0
			dxExit = staticX2 - movingX1;
			//time moving enter static
			txEntry = dxEntry / fixedVx;
			txExit = dxExit / fixedVx;
			if (txEntry < 0)
			{
				txEntry = 0;
			}

		}
		if (fixedVx < 0)
		{
			dxEntry = movingX1 - staticX2;
			dxExit = movingX2 - staticX1;

			txEntry = dxEntry / fixedVx;
			txExit = dxExit / fixedVx;
			if (txEntry > 0)
			{
				txEntry = 0;
			}

		}
		if (fixedVy > 0)
		{
			//distance of near side with fixedVx > 0
			dyEntry = staticY1 - movingY2;
			//distance of far side with fixedVx > 0
			dyExit = staticY2 - movingY1;
			//time moving enter static
			tyEntry = dyEntry / fixedVy;
			tyExit = dyExit / fixedVy;
			if (tyEntry < 0)
			{
				tyEntry = 0;
			}
		}
		if (fixedVy < 0)
		{
			//distance of near side with fixedVx > 0
			dyEntry = movingY1 - staticY2;
			//distance of far side with fixedVx > 0
			dyExit = movingY2 - staticY1;
			//time moving enter static
			tyEntry = dyEntry / fixedVy;
			tyExit = dyExit / fixedVy;
			if (tyEntry > 0)
			{
				tyEntry = 0;
			}
		}

		if (tyEntry != -std::numeric_limits<float>::infinity() && txEntry != -std::numeric_limits<float>::infinity())
			tEntry = max(fabs(txEntry), fabs(tyEntry));
		else tEntry = (txEntry == -std::numeric_limits<float>::infinity()) ? tyEntry : txEntry;
		if (tyExit != std::numeric_limits<float>::infinity() && txEntry != std::numeric_limits<float>::infinity())
			tExit = min(fabs(tyExit), fabs(txExit));
		else tExit = (txExit == std::numeric_limits<float>::infinity()) ? tyExit : txExit;
		if (fabs(tEntry) < 1.0f && fabs(tEntry) < fabs(tExit))
		{
			result._collisionIndex = tEntry;
			if (MovingObj->vx() != 0)
			{
				if (MovingObj->vx()>0)
				{
					if (movingX2 + fixedVx*tEntry >= staticX1)
						result._collisionSide = LEFT;
				}
				else
					if (movingX1 + fixedVx*tEntry <= staticX2)
						result._collisionSide = RIGHT;
			}
			if (MovingObj->vy() != 0)
			{
				if (MovingObj->vy() > 0)
				{
					if (movingY2 + fixedVy*tEntry == staticY1)
						result._collisionSide = UPTOP;
					return result;
				}
			}
			return result;
		}

	return result;

	 
}

CollisionPair::CollisionPair(GameObject* Obj1, GameObject* Obj2)
{
	_obj1 = Obj1;
	_obj2 = Obj2;
	_collisionResult = CheckCollision(Obj1, Obj2);

}
CollisionPair::~CollisionPair()
{
	delete _obj1, _obj2;
}

bool CollisionPair::IsIndentical(CollisionPair* cp1, CollisionPair* cp2)
{
	return ((cp1->obj1() == cp2->obj1() && cp1->obj2() == cp2->obj2()) || (cp1->obj1() == cp2->obj2() && cp1->obj1() == cp2->obj2()));
}

float CalculateY(float x, float a, float b , float c)
{

	return a*pow(x, 2) + b*x + c;
}

int CalculateParabolVy(int vx, D3DXVECTOR3 startposition, int max_x, int max_y , float curPosX)
{
	float vy;
	float a, b, c;
	if (vx < 0)
		max_x = -max_x;

	a = (-max_y) / pow(max_x / 2, 2);
	b = -2 * a*(startposition.x + max_x / 2);
	c = startposition.y - a* pow(startposition.x, 2) - b*startposition.x;

	vy = abs((CalculateY(curPosX, a, b, c) - CalculateY(curPosX + vx, a, b, c)));

	if (curPosX > startposition.x - abs(max_x / 2) && curPosX < startposition.x + abs(max_x / 2))
		vy = -vy;

	//`trace(L"\n%.4f", vy);
	return (int)vy;

}
