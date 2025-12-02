#pragma once

#include "pch.h"
#include "framework.h"

#include <list>
#include "ChildView.h"

#define 직장어린이집 		CPoint (166, 106)
#define 산학협력관 			CPoint (230, 97)
#define 캠퍼스컴퍼니 		CPoint (220, 165)
#define 스마트팩토리 		CPoint (284, 117)
#define 창업보육관 			CPoint (273, 201)
#define 나우리인성관 		CPoint (351, 165)
#define 소울관 				CPoint (410, 214)
#define 공학4관_A동 		CPoint (324, 213)
#define 공학4관_B동 		CPoint (367, 270)
#define 새롬관 				CPoint (286, 250)
#define 참빛쪽 				CPoint (211, 325)
#define 솔빛한울 			CPoint (304, 368)
#define 해울예지관리동 		CPoint (360, 510)
#define 체육관 				CPoint (182, 646)
#define 운동장 				CPoint (435, 663)
#define 테니스장 			CPoint (506, 512)
#define 미학관 				CPoint (461, 361)
#define 복지관 				CPoint (536, 326)
#define 다산 				CPoint (610, 284)
#define 학생회관 			CPoint (540, 390)
#define 학생통합지원센터	CPoint (604, 422)
#define 공학3관 			CPoint (772, 207)
#define 강당 				CPoint (738, 248)
#define 국제교육센터 		CPoint (700, 300)
#define 인경 				CPoint (805, 359)
#define 공학1관 			CPoint (887, 275)
#define 대학본부 			CPoint (748, 434)
#define 담헌 				CPoint (926, 427)
#define 공학2관 			CPoint (1049, 351)
#define 나래돔 				CPoint (1091, 478)

#define 케이팩토리앞 		CPoint (282, 97)
#define 산학협력관앞 		CPoint (233, 133)
#define 직장어린이집앞 		CPoint (181, 155)
#define 캠퍼스컴퍼니앞		CPoint (217, 193)
#define 창업보육관앞		CPoint (250, 220)
#define 공학4관3거리		CPoint (278, 241)
#define 공학4관A동앞		CPoint (325, 218)
#define 소울관3거리			CPoint (386, 182)
#define 나우리인성관앞		CPoint (333, 164)

#define 참빛새롬커브길		CPoint (243, 270)
#define 참빛새롬앞			CPoint (272, 330)
#define 솔빛앞				CPoint (323, 326)
#define 솔빛3거리			CPoint (351, 325)
#define 공학4관B동3거리		CPoint (410, 295)
#define 소울관앞			CPoint (414, 214)
#define 소울관커브			CPoint (463, 250)

#define 미학관앞			CPoint (420, 405)
#define 미학관3거리			CPoint (458, 428)
#define 복지관3거리			CPoint (525, 377)
#define 복지관앞			CPoint (567, 351)
#define 다산앞3거리			CPoint (633, 305)
#define GEC앞				CPoint (677, 332)
#define 인경앞				CPoint (757, 388)
#define 대학본부앞			CPoint (713, 417)
#define 학생지원센터앞		CPoint (651, 468)
#define 테니스장3거리		CPoint (571, 526)
#define 생활관입구3거리		CPoint (475, 449)
#define 생활관앞			CPoint (368, 528)
#define 운동장앞3거리		CPoint (570, 619)
#define 운동장커브1			CPoint (521, 580)
#define 운동장앞			CPoint (432, 580)
#define 운동장커브2			CPoint (347, 591)
#define 운동장커브3			CPoint (267, 631)
#define 체육관앞			CPoint (217, 634)
#define 강당앞커브			CPoint (729, 245)
#define 공학3관앞커브		CPoint (776, 273)
#define 공학3관앞			CPoint (825, 236)
#define 공학3관뒷3거리		CPoint (853, 226)
#define 공학1관뒷커브		CPoint (997, 298)
#define 공학12관앞			CPoint (948, 332)
#define 담헌앞				CPoint (889, 396)
#define 담헌3거리			CPoint (835, 436)
#define 나래돔삼거리		CPoint (1077, 566)
#define 나래돔앞			CPoint (1133, 511)	

struct m_Location_Status
{
	CPoint C_Building;
	BOOL Sel_Building = FALSE;
};

struct m_Node_Status
{
	int ID;
	CPoint C_Building;
	BOOL is_Building;
	BOOL Sel_Building = FALSE;

};

struct m_Road_id
{
	int Net_ID[2];
	double Distance;
};

struct m_Net_Data
{
	int ID;
	double Distance;

	// 명시적인 생성자 정의 (두 인수를 받음)
	m_Net_Data(int id, double dist) : ID(id), Distance(dist) {}

	// 기본 생성자도 명시적으로 추가하는 것이 좋습니다.
	m_Net_Data() : ID(0), Distance(0.0) {}
};

struct NodeDistance
{
	int nodeID;    // 노드의 고유 ID
	double distance; // 시작점에서 이 노드까지의 거리 (가중치)

	// 우선순위 큐가 최소값(Min-Heap)을 선택하도록 돕는 비교 연산자 오버로딩
	// "현재 객체의 거리가 다른 객체보다 크다" == "우선순위가 낮다"
	bool operator>(const NodeDistance& other) const
	{
		return distance > other.distance;
	}
};
