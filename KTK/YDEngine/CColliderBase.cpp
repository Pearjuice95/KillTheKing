
#include "CColliderBase.h"
#include "CObjectBase.h"

CColliderBase::CColliderBase()
{
}

CColliderBase::~CColliderBase()
{
}

bool CColliderBase::BoxColliderCheck(RECT* collider1, RECT* collider2)
{

	float Xlength = (collider1->right - collider1->left) + (collider2->right - collider2->left);
	float Ylength = (collider1->bottom - collider1->top) + (collider2->bottom - collider2->top);

	if (abs((collider1->left + collider1->right) - (collider2->left + collider2->right)) <= Xlength && abs((collider1->bottom + collider1->top) - (collider2->bottom + collider2->top)) <= Ylength)
	{
		return true;
	}
	return false;
}

void CColliderBase::PushCollisionBox(CObjectBase* checkobj, CObjectBase* targetobj, CVector2D centerSize)
{
	/*CVector2D pushDistance;
	pushDistance.x = abs((checkobj->m_pos.x - targetobj->m_pos.x)) / 2;
	pushDistance.y = abs((checkobj->m_pos.y - targetobj->m_pos.y)) / 2;*/

	if (checkobj->m_pos.x <= targetobj->m_pos.x)
	{
		float checkobjx = checkobj->m_pos.x + centerSize.x;
		float targetobjx = targetobj->m_pos.x - centerSize.x;
		float x = (checkobjx - targetobjx) / 2.0f;
		checkobj->m_pos.x -= x;
		targetobj->m_pos.x += x;
	}

	else
	{
		float checkobjx = checkobj->m_pos.x - centerSize.x;
		float targetobjx = targetobj->m_pos.x + centerSize.x;
		int x = (targetobjx - checkobjx) / 2;
		checkobj->m_pos.x += x;
		targetobj->m_pos.x -= x;
	}

	if (checkobj->m_pos.y <= targetobj->m_pos.y)
	{
		float checkobjy = checkobj->m_pos.y + centerSize.y;
		float targetobjy = targetobj->m_pos.y - centerSize.y;
		int y = (checkobjy - targetobjy) / 2;
		checkobj->m_pos.y -= y;
		targetobj->m_pos.y += y;
	}

	else
	{
		float checkobjy = checkobj->m_pos.y - centerSize.y;
		float targetobjy = targetobj->m_pos.y + centerSize.y;
		int y = (targetobjy - checkobjy) / 2;
		checkobj->m_pos.y += y;
		targetobj->m_pos.y -= y;
	}
}

void CColliderBase::WallCollision(CObjectBase* checkobj, CObjectBase* targetobj, CVector2D centerSize)
{
	/*RECT rect;
	rect = checkobj->GetRECT();

	CVector2D temppos;
	temppos.x = rect.left + ((rect.right - rect.left) / 2);
	temppos.y = rect.top + ((rect.bottom - rect.top) / 2);*/

	/*if (targetobj->m_totalStatus == eToTalStatus::DASH)
	{*/
		/*if (checkobj->m_pos.x <= targetobj->m_pos.x)
		{
			float checkobjx = checkobj->m_pos.x + wallSize.x;
			float targetobjx = targetobj->m_pos.x - centerSize.x;
			float x = (checkobjx - targetobjx);

			if (checkobj->m_pos.y <= targetobj->m_pos.y)
			{
				float checkobjy = checkobj->m_pos.y + wallSize.y;
				float targetobjy = targetobj->m_pos.y - centerSize.y;
				int y = (checkobjy - targetobjy);


				if (y > x)
				{
					targetobj->m_pos.x = checkobjx + centerSize.x + 1;
				}

				else
				{
					targetobj->m_pos.y =  checkobjy + centerSize.y + 1;
				}
			}

			else
			{
				float checkobjy = checkobj->m_pos.y - wallSize.y;
				float targetobjy = targetobj->m_pos.y + centerSize.y;
				int y = (targetobjy - checkobjy);

				if (y > x)
				{
					targetobj->m_pos.x = checkobjx + centerSize.x +1;
				}

				else
				{
					targetobj->m_pos.y = checkobjy - 1 - centerSize.y;
				}
			}
		}

		else
		{
			float checkobjx = checkobj->m_pos.x - wallSize.x;
			float targetobjx = targetobj->m_pos.x + centerSize.x;
			int x = (targetobjx - checkobjx);

			if (checkobj->m_pos.y <= targetobj->m_pos.y)
			{
				float checkobjy = checkobj->m_pos.y + wallSize.y;
				float targetobjy = targetobj->m_pos.y - centerSize.y;
				int y = (checkobjy - targetobjy);


				if (y > x)
				{
					targetobj->m_pos.x = checkobjx - 1 - centerSize.x;
				}

				else
				{
					targetobj->m_pos.y =  checkobjy + 1 + centerSize.y;
				}
			}

			else
			{
				float checkobjy = checkobj->m_pos.y - wallSize.y;
				float targetobjy = targetobj->m_pos.y + centerSize.y;
				int y = (targetobjy - checkobjy);

				if (y > x)
				{
					targetobj->m_pos.x = checkobjx - 1 - centerSize.x;
				}

				else
				{
					targetobj->m_pos.y -= checkobjy - 1 - centerSize.y;
				}
			}
		}*/
		/*if (targetobj->m_DashPos.x < targetobj->m_pos.x)
		{
			CVector2D temp;
			temp.x = targetobj->m_pos.x - targetobj->m_DashPos.x;

			if (targetobj->m_DashPos.y < targetobj->m_pos.y)
			{
				temp.y = targetobj->m_pos.y - targetobj->m_DashPos.y;
			}

			else
			{
				temp.y = targetobj->m_DashPos.y - targetobj->m_pos.y;
			}
		}

		else
		{
			CVector2D temp;
			temp.x = targetobj->m_DashPos.x - targetobj->m_pos.x;

			if (targetobj->m_DashPos.y < targetobj->m_pos.y)
			{
				temp.y = targetobj->m_pos.y - targetobj->m_DashPos.y;
			}

			else
			{
				temp.y = targetobj->m_DashPos.y - targetobj->m_pos.y;
			}
		}

		targetobj->m_pos = targetobj->m_DashPos;
	}*/

	/*else
	{*/
		targetobj->m_pos = targetobj->m_prevPos;
	//}

}

//CVector2D CColliderBase::LineBoxCollision(CVector2D* start, CVector2D* end, CObjectBase* box, CVector2D boxSize)
//{
//	//CVector2D result;
//
//	//if (end->x < start->x)
//	//{
//	//	if (end->y < start->y)
//	//	{
//	//		if (end->x < (box->m_pos.x + boxSize.x))
//	//		{
//	//			if (end->y < (box->m_pos.y + boxSize.y))
//	//			{
//	//				result.x = 
//	//			}
//	//		}
//	//		//yDistance = start->y - end->y;
//	//	}
//
//	//	else
//	//	{
//	//		yDistance = end->y - start->y;
//	//	}
//	//}
//
//	//else
//	//{
//	//	xDistance = end->x - start->x;
//
//	//	if (end->y < start->y)
//	//	{
//	//		yDistance = start->y - end->y;
//	//	}
//
//	//	else
//	//	{
//	//		yDistance = end->y - start->y;
//	//	}
//	//}
//
//
//}