
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include <list>
#include "Location.h"
#include <cmath>
#include <map>
#include <queue>

using namespace std;

// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

	int SelTime;

	int m_StartNodeId = -1;
	int m_EndNodeId = -1;

	BOOL m_bDrawMode;
	BOOL m_bSelMode;
	BOOL m_bSel2Point;
	BOOL m_bDeleteMode;
	BOOL m_bRodeMode;
	BOOL m_bShowPathMode;

	list<m_Node_Status> m_ALLNode;

	list<m_Location_Status> m_Building_List;
	list<m_Node_Status> m_RoadBlock_List1;
	list<m_Node_Status> m_RoadBlock_List2;
	list<m_Node_Status> m_RoadBlock_List3;
	list<m_Node_Status> m_RoadBlock_List4;
	list<m_Node_Status> m_RoadBlock_List5;
	list<m_Node_Status>	m_RoadBlock_List6;
	list<m_Node_Status>	m_RoadBlock_List7;
	list<m_Node_Status>	m_RoadBlock_List8;
	list<m_Node_Status> shortest_Path_List;

	list<m_Road_id> m_Road_List;

	map<int, list<m_Net_Data>>m_Net_Data_Map;

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	void DrawPoint(list<m_Node_Status>& list, CPaintDC& dc);
	void DrawRoadBlock(list<m_Node_Status>&list, CPaintDC& dc, int LineWidth = 4, int R = 0, int G = 0, int B = 0);
	void DrawRoadLine(list<m_Node_Status>& list, CPaintDC& dc, int LineWidth = 4, int R = 0, int G = 0, int B = 0);

	void SelPoint(CPoint point, CClientDC& dc);
	void DeSelPoint();

	void Net_Building_Road(CPaintDC& dc);

	void MatchID(list<m_Node_Status> list);

	pair<map<int, double>, map<int, int>> FindShortestPaths(int startNodeId);
	list<int> ReconstructPath(int startNodeId, int endNodeId, const std::map<int, int>& prev_nodes);
	list<m_Node_Status> ConvertPathToNodeStatusList(const list<int>& shortest_node_path);

	//void Allign_List_ID(list<m_Road_id> list);

	void setALLNode()
	{
		list<CPoint> Sublist = { 직장어린이집, 산학협력관, 캠퍼스컴퍼니, 스마트팩토리, 창업보육관, 나우리인성관, 소울관, 공학4관_A동, 공학4관_B동, 새롬관, 참빛쪽, 솔빛한울, 해울예지관리동, 체육관, 운동장, 테니스장, 미학관, 복지관, 다산, 학생회관, 학생통합지원센터, 공학3관, 강당, 국제교육센터, 인경, 공학1관, 대학본부, 담헌, 공학2관, 나래돔, 케이팩토리앞, 산학협력관앞, 직장어린이집앞, 캠퍼스컴퍼니앞, 창업보육관앞, 공학4관3거리, 공학4관A동앞, 소울관3거리, 나우리인성관앞, 참빛새롬커브길, 참빛새롬앞, 솔빛앞, 솔빛3거리, 공학4관B동3거리, 소울관앞, 소울관커브, 미학관앞, 미학관3거리, 복지관3거리, 복지관앞, 다산앞3거리, GEC앞, 인경앞, 대학본부앞, 학생지원센터앞, 테니스장3거리, 생활관입구3거리, 생활관앞, 운동장앞3거리, 운동장커브1, 운동장앞, 운동장커브2, 운동장커브3, 체육관앞, 강당앞커브, 공학3관앞커브, 공학3관앞, 공학3관뒷3거리, 공학1관뒷커브, 공학12관앞, 담헌앞, 담헌3거리, 나래돔삼거리, 나래돔앞 };
		auto iter = Sublist.begin();
		int i = 0;
		while (iter != Sublist.end())
		{
			if (i < 30)
			{
				m_ALLNode.push_back({ i, CPoint (*iter), TRUE });
			}
			else
			{
				m_ALLNode.push_back({ i, CPoint (*iter), FALSE});
			}
			++iter;
			++i;
		}
	}

	void ResetNodeData();

	void setList()
	{
		m_Building_List.push_back({ 직장어린이집, FALSE });
		m_Building_List.push_back({ 산학협력관, FALSE });
		m_Building_List.push_back({ 캠퍼스컴퍼니, FALSE });
		m_Building_List.push_back({ 스마트팩토리, FALSE });
		m_Building_List.push_back({ 창업보육관, FALSE });
		m_Building_List.push_back({ 나우리인성관, FALSE });
		m_Building_List.push_back({ 소울관, FALSE });
		m_Building_List.push_back({ 공학4관_A동, FALSE });
		m_Building_List.push_back({ 공학4관_B동, FALSE });
		m_Building_List.push_back({ 새롬관, FALSE });
		m_Building_List.push_back({ 참빛쪽, FALSE });
		m_Building_List.push_back({ 솔빛한울, FALSE });
		m_Building_List.push_back({ 해울예지관리동, FALSE });
		m_Building_List.push_back({ 체육관, FALSE });
		m_Building_List.push_back({ 운동장, FALSE });
		m_Building_List.push_back({ 테니스장, FALSE });
		m_Building_List.push_back({ 미학관, FALSE });
		m_Building_List.push_back({ 복지관, FALSE });
		m_Building_List.push_back({ 다산, FALSE });
		m_Building_List.push_back({ 학생회관, FALSE });
		m_Building_List.push_back({ 학생통합지원센터, FALSE });
		m_Building_List.push_back({ 공학3관, FALSE });
		m_Building_List.push_back({ 강당, FALSE });
		m_Building_List.push_back({ 국제교육센터, FALSE });
		m_Building_List.push_back({ 인경, FALSE });
		m_Building_List.push_back({ 공학1관, FALSE });
		m_Building_List.push_back({ 대학본부, FALSE });
		m_Building_List.push_back({ 담헌, FALSE });
		m_Building_List.push_back({ 공학2관, FALSE });
		m_Building_List.push_back({ 나래돔, FALSE });
	}

	void setRoadList1()
	{
		m_RoadBlock_List1.push_back({0,  케이팩토리앞, FALSE });
		m_RoadBlock_List1.push_back({0,  산학협력관앞 , FALSE });
		m_RoadBlock_List1.push_back({0,  직장어린이집앞, FALSE });
		m_RoadBlock_List1.push_back({0,  캠퍼스컴퍼니앞, FALSE });
		m_RoadBlock_List1.push_back({0,  창업보육관앞	, FALSE });
		m_RoadBlock_List1.push_back({0,  공학4관3거리, FALSE });
		m_RoadBlock_List1.push_back({0,  공학4관A동앞, FALSE });
		m_RoadBlock_List1.push_back({0,  소울관3거리, FALSE });
		m_RoadBlock_List1.push_back({0,  나우리인성관앞, FALSE });
	}								
									
	void setRoadList2()				
	{								
		m_RoadBlock_List2.push_back({0,  참빛새롬커브길, FALSE });		
		m_RoadBlock_List2.push_back({0,  참빛새롬앞, FALSE });		
		m_RoadBlock_List2.push_back({0,  솔빛앞, FALSE });		
		m_RoadBlock_List2.push_back({0,  솔빛3거리, FALSE });		
		m_RoadBlock_List2.push_back({0,  공학4관B동3거리, FALSE });	
		m_RoadBlock_List2.push_back({0,  소울관커브, FALSE });		
		m_RoadBlock_List2.push_back({0,  소울관앞, FALSE });
		m_RoadBlock_List2.push_back({0,  소울관3거리, FALSE });
		m_RoadBlock_List2.push_back({0,  공학4관A동앞, FALSE });
		m_RoadBlock_List2.push_back({0,  공학4관3거리, FALSE });
	}								
									
	void setRoadList3()				
	{								
		m_RoadBlock_List3.push_back({0,  솔빛3거리, FALSE });
		m_RoadBlock_List3.push_back({0,  미학관앞, FALSE });
		m_RoadBlock_List3.push_back({0,  미학관3거리, FALSE });
		m_RoadBlock_List3.push_back({0,  복지관3거리, FALSE });
		m_RoadBlock_List3.push_back({0,  공학4관B동3거리, FALSE });
	}								
									
	void setRoadList4()				
	{								
		m_RoadBlock_List4.push_back({0,  미학관3거리, FALSE });
		m_RoadBlock_List4.push_back({0,  복지관3거리, FALSE });
		m_RoadBlock_List4.push_back({0,  복지관앞, FALSE });
		m_RoadBlock_List4.push_back({0,  다산앞3거리, FALSE });
		m_RoadBlock_List4.push_back({0,  GEC앞, FALSE });
		m_RoadBlock_List4.push_back({0,  인경앞, FALSE });
		m_RoadBlock_List4.push_back({0,  대학본부앞, FALSE });
		m_RoadBlock_List4.push_back({0,  학생지원센터앞, FALSE });
		m_RoadBlock_List4.push_back({0,  테니스장3거리, FALSE });
		m_RoadBlock_List4.push_back({0,  생활관입구3거리, FALSE });
	}								
									
	void setRoadList5()				
	{								
		m_RoadBlock_List5.push_back({0,  다산앞3거리, FALSE });
		m_RoadBlock_List5.push_back({0,  강당앞커브, FALSE });	
		m_RoadBlock_List5.push_back({0,  공학3관앞커브, FALSE });	
		m_RoadBlock_List5.push_back({0,  공학3관앞, FALSE });	
		m_RoadBlock_List5.push_back({0,  공학3관뒷3거리, FALSE });	
		m_RoadBlock_List5.push_back({0,  공학1관뒷커브, FALSE });	
		m_RoadBlock_List5.push_back({0,  공학12관앞, FALSE });	
		m_RoadBlock_List5.push_back({0,  담헌앞, FALSE });	
		m_RoadBlock_List5.push_back({0,  담헌3거리, FALSE });	
		m_RoadBlock_List5.push_back({0,  인경앞, FALSE });
		m_RoadBlock_List5.push_back({0,  GEC앞, FALSE });
	}								
									
	void setRoadList6()				
	{								
		m_RoadBlock_List6.push_back({0,  담헌3거리, FALSE });
		m_RoadBlock_List6.push_back({0,  나래돔삼거리, FALSE });
		m_RoadBlock_List6.push_back({0,  나래돔앞, FALSE });
	}								 
									 
	void setRoadList7()				 
	{								 
		m_RoadBlock_List7.push_back({0,  생활관입구3거리, FALSE });
		m_RoadBlock_List7.push_back({0,  생활관앞, FALSE });
	}								
									
	void setRoadList8()				
	{								
		m_RoadBlock_List8.push_back({0,  테니스장3거리, FALSE });
		m_RoadBlock_List8.push_back({0,  운동장앞3거리, FALSE });
		m_RoadBlock_List8.push_back({0,  운동장커브1, FALSE });
		m_RoadBlock_List8.push_back({0,  운동장앞, FALSE });
		m_RoadBlock_List8.push_back({0,  운동장커브2, FALSE });
		m_RoadBlock_List8.push_back({0,  운동장커브3, FALSE });
		m_RoadBlock_List8.push_back({0,  체육관앞, FALSE });
	}		

	
																	
	DECLARE_MESSAGE_MAP()											
};																	




