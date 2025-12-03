
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "Koreatech_Navigation_2.h"
#include "ChildView.h"
#include <limits>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_bDrawMode = FALSE;
	m_bSelMode = FALSE;
	m_bDeleteMode = FALSE;
	m_bRodeMode = FALSE;
	m_bSel2Point = FALSE;
	m_bShowPathMode = FALSE;
	SelTime = 0;

	setALLNode();

	setList();
	setRoadList1();
	setRoadList2();
	setRoadList3();
	setRoadList4();
	setRoadList5();
	setRoadList6();
	setRoadList7();
	setRoadList8();

	MatchID(m_RoadBlock_List1);
	MatchID(m_RoadBlock_List2);
	MatchID(m_RoadBlock_List3);
	MatchID(m_RoadBlock_List4);
	MatchID(m_RoadBlock_List5);
	MatchID(m_RoadBlock_List6);
	MatchID(m_RoadBlock_List7);
	MatchID(m_RoadBlock_List8);


}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// 비트맵 리소스를 로드한 후 크기 정보를 얻는다.
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	BITMAP bmpinfo;
	bitmap.GetBitmap(&bmpinfo);

	// 메모리 DC를 만든 후 비트맵을 선택해 넣는다.
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	dcmem.SelectObject(&bitmap);

	dc.StretchBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);		//지도 출력

	if (m_bRodeMode)		//길 그리기
	{
		Net_Building_Road(dc);
		
		DrawRoadBlock(m_RoadBlock_List1, dc);
		DrawRoadBlock(m_RoadBlock_List2, dc);
		DrawRoadBlock(m_RoadBlock_List3, dc);
		DrawRoadBlock(m_RoadBlock_List4, dc);
		DrawRoadBlock(m_RoadBlock_List5, dc);
		DrawRoadLine(m_RoadBlock_List6, dc);
		DrawRoadLine(m_RoadBlock_List7, dc);
		DrawRoadLine(m_RoadBlock_List8, dc);

		ResetNodeData();

		//Allign_List_ID(m_Road_List);
	}

	if (m_bShowPathMode)
	{
		DrawRoadLine(shortest_Path_List, dc, 8, 255);
	}

	if (m_bDrawMode)		//기본 점 그리기
	{
		DrawPoint(m_ALLNode, dc);
	}

	if (m_bDeleteMode && m_bRodeMode)		//선택된 점 해제
	{
		DrawPoint(m_ALLNode, dc);		//점 선택 표시 초기화
		DeSelPoint();						//전체 점 선택해제
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!m_bDrawMode)
	{
		m_bDrawMode = TRUE;
		Invalidate(FALSE);
	}
	
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	if (m_bSelMode && m_bRodeMode)
	{
		CClientDC dc(this);

		SelPoint(point, dc);
	}
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x41 && !m_bRodeMode)			// a누를때
	{
		m_bRodeMode = TRUE;
		SelTime = 0;
		Invalidate(FALSE);
	}

	if (nChar == 0x53)							//s누를때
	{
		m_bSelMode = TRUE;
	}

	if (nChar == 0x46)							//f누를때
	{
		m_bDeleteMode = TRUE;
		SelTime = 0;
		Invalidate(FALSE);
	}

	if (nChar == 0x47 && m_bSel2Point)			// g누를때
	{
		// 1. 다익스트라 알고리즘 호출 (최단 거리 맵과 이전 노드 맵 획득)
	// m_StartNodeId와 m_EndNodeId는 CChildView의 멤버 변수라고 가정합니다.
		auto iter = m_ALLNode.begin();

		BOOL BeginPoint = TRUE;

		while (iter != m_ALLNode.end())
		{
			if ((*iter).Sel_Building)
			{
				if (BeginPoint)
				{
					m_StartNodeId = (*iter).ID;

					BeginPoint = FALSE;
				}
				else
				{
					m_EndNodeId = (*iter).ID;

					break;
				}
			}
			++iter;
		}

		auto result = FindShortestPaths(m_StartNodeId);

		

		// std::pair에서 두 맵을 추출
		map<int, double> distances = result.first;
		map<int, int> prev_nodes = result.second;

		double startDistance = distances.at(m_StartNodeId);

		// 2. 경로 역추적 (Path Reconstruction)
		// 노드 ID 리스트를 얻습니다.
		list<int> shortest_node_path = ReconstructPath(m_StartNodeId, m_EndNodeId, prev_nodes);

		auto iter1234 = shortest_node_path.begin();

		while (iter1234 != shortest_node_path.end())
		{
			CString message;
			message.Format(_T("디버그 ID: %d, "), iter1234);

			AfxMessageBox(message);

			iter1234++;
		}

		shortest_Path_List = ConvertPathToNodeStatusList(shortest_node_path);

		m_bShowPathMode = TRUE;

		m_bSel2Point = FALSE;

		// 5. 화면 갱신을 요청하여 OnDraw 함수에서 경로를 빨간색으로 그립니다.
		Invalidate(FALSE);
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);	// s누를때
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 0x53)							// s뗄떼
	{
		m_bSelMode = FALSE;
	}
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}





/////////////////////////////////////////////////////////////////////////
//							유저 멤버 함수							   //
/////////////////////////////////////////////////////////////////////////


void CChildView::DrawPoint(list<m_Node_Status>& list, CPaintDC& dc)
{
	auto iter = list.begin();

	CPen dotPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&dotPen);

	CBrush fillBrush(RGB(255, 255, 255));
	CBrush* pOldBrush = dc.SelectObject(&fillBrush);

	while (iter != list.end())
	{
		if ((*iter).is_Building)
		{
			const CPoint& pt = (*iter).C_Building;

			dc.Ellipse(pt.x - 10, pt.y - 10, pt.x + 10, pt.y + 10);
		}
		++iter;
	}

	if (m_bDeleteMode)
	{
		m_bDeleteMode = FALSE;
	}
}

void CChildView::DrawRoadBlock(list<m_Node_Status>&list, CPaintDC& dc, int LineWidth, int R, int G, int B)
{
	DrawRoadLine(list, dc);
	
	CPoint pt[2];
	int Distance;
	int NearNetID;

	pt[0] = list.back().C_Building;
	pt[1] = list.front().C_Building;

	int dx = (int)pt[0].x - (int)pt[1].x;
	int dy = (int)pt[0].y - (int)pt[1].y;

	Distance = (int)(sqrt((dx * dx) + (dy * dy)));

	m_Road_List.push_back({ {list.back().ID, list.front().ID}, (double)Distance });

	dc.Polyline(pt, 2);
}

void CChildView::DrawRoadLine(list<m_Node_Status>& list, CPaintDC& dc, int LineWidth, int R, int G, int B)
{
	auto iter = list.begin();

	CPoint pt[2];
	int i = 0;
	int Distance;
	int NearNetID;

	CPen dotPen(PS_SOLID, LineWidth, RGB(R, G, B));
	CPen* pOldPen = dc.SelectObject(&dotPen);

	while (iter != list.end())
	{
		pt[1] = (*iter).C_Building;
		
		if (i > 0)
		{
			dc.Polyline(pt, 2);

			int dx = (int)pt[0].x - (int)pt[1].x;
			int dy = (int)pt[0].y - (int) pt[1].y;

			Distance = (int) (sqrt((dx * dx) + (dy * dy)));

			m_Road_List.push_back({ {NearNetID, (*iter).ID}, (double)Distance });

			//CString message;

			//message.Format(_T("선택된 노드 ID: %d, %d, %d "), Distance, (m_Road_List.back()).Net_ID, (m_Road_List.back()).Distance);

			//AfxMessageBox(message);
		}
		pt[0] = pt[1];
		NearNetID = (*iter).ID;

		++i;
		++iter;
	}
}

void CChildView::SelPoint(CPoint point, CClientDC& dc)
{
	auto iter = m_ALLNode.begin();

	while (iter != m_ALLNode.end())
	{
		CPoint Origin_point = (*iter).C_Building;
		if (point.x > Origin_point.x - 10 && point.x < Origin_point.x + 10 && point.y > Origin_point.y - 10 && point.y < Origin_point.y + 10)
		{
			if (SelTime == 0)
			{
				SelTime++;
				CPen dotPen(PS_SOLID, 1, RGB(0, 0, 0));
				CPen* pOldPen = dc.SelectObject(&dotPen);

				CBrush fillBrush(RGB(255, 0, 0));
				CBrush* pOldBrush = dc.SelectObject(&fillBrush);

				dc.Ellipse(Origin_point.x - 10, Origin_point.y - 10, Origin_point.x + 10, Origin_point.y + 10);

				(*iter).Sel_Building = TRUE;
				break;
			}
			else if(SelTime == 1)
			{
				if ((*iter).Sel_Building)
				{
					AfxMessageBox(_T("이미 선택된 지점입니다!"));
					break;
				}

				CPen dotPen(PS_SOLID, 1, RGB(0, 0, 0));
				CPen* pOldPen = dc.SelectObject(&dotPen);

				CBrush fillBrush(RGB(0, 0, 255));
				CBrush* pOldBrush = dc.SelectObject(&fillBrush);

				dc.Ellipse(Origin_point.x - 10, Origin_point.y - 10, Origin_point.x + 10, Origin_point.y + 10);

				(*iter).Sel_Building = TRUE;

				AfxMessageBox(_T("두 점을 모두 선택하였습니다!!! \n G키를 눌러 경로를 찾으세요."));
				m_bSelMode = FALSE;
				m_bSel2Point = TRUE;
				break;
			}
		}
		++iter;
	}
}

void CChildView::DeSelPoint()
{
	auto iter = m_Building_List.begin();
	while (iter != m_Building_List.end())
	{
		if ((*iter).Sel_Building)
		{
			(*iter).Sel_Building = FALSE;
		}
		++iter;
	}
}

void CChildView::Net_Building_Road(CPaintDC& dc)
{
	auto iter = m_ALLNode.begin();
	while (iter != m_ALLNode.end())
	{
		if ((*iter).is_Building)
		{
			CPoint pt[2];
			int NearNetID;

			pt[0] = (*iter).C_Building;

			auto Roaditer = m_ALLNode.begin();

			int Distance = 0;
			int MinDistance = 9999999999999;
			
			while (Roaditer != m_ALLNode.end())
			{
				if (!(*Roaditer).is_Building)
				{
					int dx = (int)(*iter).C_Building.x - (int)(*Roaditer).C_Building.x;
					int dy = (int)(*iter).C_Building.y - (int)(*Roaditer).C_Building.y;

					Distance = sqrt( (dx*dx) +(dy*dy) );

					if (Distance < MinDistance)
					{
						MinDistance = Distance;
						pt[1] = (*Roaditer).C_Building;
						NearNetID = (*Roaditer).ID;
					}
				}
				++Roaditer;
			}

			CPen dotPen(PS_SOLID, 4, RGB(0, 0, 0));
			CPen* pOldPen = dc.SelectObject(&dotPen);

			m_Road_List.push_back({ {(*iter).ID, NearNetID}, (double)Distance});


			/*CString message;

			message.Format(_T("노드 - 거리 디버그 %d, %d, %d "), (*iter).ID, NearNetID, Distance);

			AfxMessageBox(message);*/

			dc.Polyline(pt, 2);
			//return Distance;
		}
		++iter;
	}
	//return -1;
}

void CChildView::MatchID(list<m_Node_Status> list)			//ID를 바꿀 리스트를 괄호안에 넣는다.
{
	auto Target_iter = list.begin();
	auto Data_iter = m_ALLNode.begin();

	while (Target_iter != list.end())
	{
		while (Data_iter != m_ALLNode.end())
		{
			if ((*Target_iter).C_Building == (*Data_iter).C_Building)
			{
				(*Target_iter).ID = (*Data_iter).ID;
			}
			Data_iter++;
		}
		Target_iter++;
	}
}

void CChildView::ResetNodeData()
{

	// m_Net_Data_Map은 std::map<int, std::list<m_Net_Data>> 타입의 멤버 변수라고 가정합니다.
	m_Net_Data_Map.clear(); // 기존 데이터 초기화

	// m_ALLNode는 무시하고, m_Road_List만 순회합니다. (가장 효율적)
	auto Road_iter = m_Road_List.begin();

	while (Road_iter != m_Road_List.end())
	{
		// Net_ID[0] (시작점)을 키로 사용하여 해당 리스트에 바로 접근
		m_Net_Data_Map[(*Road_iter).Net_ID[0]].emplace_back(
			(*Road_iter).Net_ID[1], // 끝 노드 ID
			(*Road_iter).Distance   // 거리
		);

		Road_iter++;
	}

	CString message;
	message.Format(_T("디버그 ID: %d, %d"), m_Net_Data_Map.rbegin());

	AfxMessageBox(message);
	// m_ALLNode의 모든 노드가 맵에 키로 등록되기를 원한다면, m_Road_List 순회 후 
	// m_ALLNode를 순회하며 맵에 없는 키를 빈 리스트로 추가하는 별도 작업이 필요합니다.
}

// 함수 시그니처를 이렇게 변경해야 합니다.
// map<int, double> (거리 맵)과 map<int, int> (이전 노드 맵)을 함께 반환
pair<map<int, double>, map<int, int>> CChildView::FindShortestPaths(int startNodeId)
{
	// **최단 경로 추적을 위한 맵** (Key: 현재 노드, Value: 최단 경로로 오기 직전 노드)
	map<int, int> prev_nodes;

	// 1. 초기화: 모든 노드의 거리를 '무한대'로 설정합니다.
	map<int, double> distances;
	const double Max_Value = DBL_MAX;

	// 맵에 존재하는 모든 노드 ID를 가져와 거리를 초기화합니다.
	for (const auto& pair : m_Net_Data_Map) {
		distances[pair.first] = Max_Value;
		prev_nodes[pair.first] = -1; // -1: 초기화 값 (아직 경로를 찾지 못함)
	}

	// 시작 노드 거리는 0으로 설정합니다.
	distances[startNodeId] = 0.0;
	prev_nodes[startNodeId] = startNodeId; // 시작 노드의 이전 노드는 자기 자신으로 설정

	// 2. 우선순위 큐 생성
	priority_queue<NodeDistance, vector<NodeDistance>, greater<NodeDistance>> pq;

	// 시작 노드를 큐에 추가합니다.
	pq.push({ startNodeId, 0.0 });

	// 3. 메인 루프 (Dijkstra 탐색)
	while (!pq.empty())
	{
		// 현재 탐색할 노드와 그까지의 현재 거리
		NodeDistance current = pq.top();
		pq.pop();

		int u = current.nodeID;
		double d = current.distance;

		// 이미 더 짧은 경로를 찾았다면 건너뜁니다.
		if (d > distances[u]) {
			continue;
		}

		// 현재 노드 u에 인접한 모든 노드(v)를 탐색합니다.
		auto it = m_Net_Data_Map.find(u);
		if (it != m_Net_Data_Map.end())
		{
			// u에 연결된 엣지 리스트를 순회합니다.
			for (const auto& edge : it->second)
			{
				// 주의: 사용자의 코드에 맞춰 edge.ID를 사용했습니다.
				// m_Net_Data 구조체의 멤버 이름이 Connected_ID라면 edge.Connected_ID로 변경해야 합니다.
				int v = edge.ID;
				double weight = edge.Distance;

				// 릴렉세이션(Relaxation): 더 짧은 경로를 찾았는지 확인
				if (distances[u] + weight < distances[v])
				{
					distances[v] = distances[u] + weight;

					// 📌 경로 추적 추가: 노드 v의 최단 경로 이전 노드를 u로 기록합니다.
					prev_nodes[v] = u;

					pq.push({ v, distances[v] }); // 큐에 업데이트된 노드를 추가
				}
			}
		}
	}

	// 4. 최단 거리 맵과 이전 노드 맵을 묶어 반환합니다.
	return { distances, prev_nodes };
}


// prev_nodes 맵을 사용하여 도착 노드에서 시작 노드까지의 경로를 역추적합니다.
list<int> CChildView::ReconstructPath(int startNodeId, int endNodeId, const std::map<int, int>& prev_nodes)
{
	list<int> path;
	int current = endNodeId;

	// 도착 노드까지 도달했는지 확인
	if (prev_nodes.count(endNodeId) == 0 || prev_nodes.at(endNodeId) == -1) {
		return path; // 도달 불가능
	}

	// 시작 노드에 도달할 때까지 역추적
	while (current != startNodeId)
	{
		if (prev_nodes.count(current) == 0) {
			path.clear(); // 오류: 경로가 끊어짐
			break;
		}
		path.push_front(current); // 리스트의 맨 앞에 추가하여 순서를 정방향으로 만듭니다.
		current = prev_nodes.at(current);
	}
	path.push_front(startNodeId); // 마지막으로 시작 노드 추가

	return path;
}

list<m_Node_Status> CChildView::ConvertPathToNodeStatusList(const list<int>& shortest_node_path)
{
	list<m_Node_Status> path_status_list;

	// 1. 최단 경로 ID 리스트를 순회합니다.
	for (int nodeId : shortest_node_path)
	{
		// 2. 전체 노드 목록(m_ALLNode)에서 해당 ID를 가진 노드를 찾습니다.
		auto it_all = m_ALLNode.begin();
		bool found = FALSE;

		while (it_all != m_ALLNode.end())
		{
			if ((*it_all).ID == nodeId)
			{
				// 3. 일치하는 노드를 찾았을 경우
				path_status_list.push_back(*it_all); // 해당 m_Node_Status 객체를 새 리스트에 추가
				found = TRUE;
				break; // m_ALLNode 순회 중지
			}
			++it_all;
		}



		// 경로에 포함된 노드 ID가 m_ALLNode에 존재하지 않을 경우를 대비
		if (!found)
		{
			// 오류 처리 또는 경고 로직 추가 가능
			// (예: cout << "Error: Node ID not found in m_ALLNode: " << nodeId << endl;)
		}
	}

	return path_status_list;
}

/*
void CChildView::Allign_List_ID(list<m_Road_id> list)
{
	auto iter = list.begin();

	int i = 0;

	while (iter != list.end())
	{
		(*iter).Net_ID = i;
		i++;
		iter++;
	}
}
*/