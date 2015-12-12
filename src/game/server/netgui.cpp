// Copyright (c) 2015 Henritees

#include <game/server/gamecontext.h>
#include <game/server/gamecontroller.h>

#include "netgui.h"

void CNetGui::OnClientEnter(int ClientID)
{
	// send NetGui
	UIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(30, 70, 38, 70), 15, 50);
	Label(ClientID, 0, ">)^_^)> Welcome to Henritee's NetGUI Testserver! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 500);
	Label(ClientID, 1, "(: Click the button! <(^_^(<", vec4(0, 100, 10, 20), vec4(80, 0, 50, 80), 20, 1, 500);
	ButtonMenu(ClientID, 0, "Close", 0, vec4(50-10, 50+10, 50-5, 50+5));
}

void CNetGui::OnClientDrop(int ClientID)
{
	m_UIRect[ClientID].clear();
	m_Label[ClientID].clear();
	m_ButtonMenu[ClientID].clear();
}

void CNetGui::OnMessage(int MsgID, void *pRawMsg, int ClientID)
{
	CPlayer *pPlayer = GameServer()->m_apPlayers[ClientID];

	if (MsgID == NETMSGTYPE_CL_NETGUI_BUTTONMENU_PRESSED)
	{
		CNetMsg_Cl_NetGui_ButtonMenu_Pressed *pMsg = (CNetMsg_Cl_NetGui_ButtonMenu_Pressed *)pRawMsg;
		//dbg_msg("NETGUI", "ClientID=%d sended 'BUTTONMENU_PRESSES' with m_ID:%d", pPlayer->GetCID(), pMsg->m_ID);
		bool exists = false;
		for(int i = 0; i < GetButtonMenu(ClientID).size(); i++)
		{
			if(GetButtonMenu(ClientID)[i].m_ID == pMsg->m_ID)
				exists = true;
		}
		if(exists == true)
		{
			// DO THE WANTED ACTIONS HERE
			switch(pMsg->m_ID)
			{
			case 0:
				RemoveElement(pPlayer->GetCID(), NETMSGTYPE_SV_NETGUI_UIRECT, 0);
				RemoveElement(pPlayer->GetCID(), NETMSGTYPE_SV_NETGUI_LABEL, 0);
				RemoveElement(pPlayer->GetCID(), NETMSGTYPE_SV_NETGUI_LABEL, 1);
				RemoveElement(pPlayer->GetCID(), NETMSGTYPE_SV_NETGUI_BUTTONMENU, 0);
				ButtonMenu(ClientID, 1, "Open", 0, vec4(50-10, 50+10, 50-5, 50+5));
				break;
			case 1:
				UIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(30, 70, 38, 70), 15, 50);
				Label(ClientID, 0, ">)^_^)> Welcome to Henritee's NetGUI Testserver! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 500);
				Label(ClientID, 1, "(: Congraz for using it! <(^_^(<", vec4(0, 100, 10, 20), vec4(80, 50, 0, 80), 20, 1, 500);
				RemoveElement(pPlayer->GetCID(), NETMSGTYPE_SV_NETGUI_BUTTONMENU, 1);
				ButtonMenu(ClientID, 0, "Close", 0, vec4(50-10, 50+10, 50-5, 50+5));
				break;
			}
		}
	}
}

void CNetGui::RemoveElement(int ClientID, int Type, int NetGuiElemID)
{
	CNetMsg_Sv_NetGui_RemoveElement Msg;
	Msg.m_Type = Type;
	Msg.m_ID = NetGuiElemID;

	switch(Type)
	{
	case NETMSGTYPE_SV_NETGUI_UIRECT:
		for(int i = 0; i < m_UIRect[ClientID].size(); i++)
		{
			if(m_UIRect[ClientID][i].m_ID == NetGuiElemID)
				m_UIRect[ClientID].remove_index(i);
		}
		break;
	case NETMSGTYPE_SV_NETGUI_LABEL:
		for(int i = 0; i < m_Label[ClientID].size(); i++)
		{
			if(m_Label[ClientID][i].m_ID == NetGuiElemID)
				m_Label[ClientID].remove_index(i);
		}
		break;
	case NETMSGTYPE_SV_NETGUI_BUTTONMENU:
		for(int i = 0; i < m_ButtonMenu[ClientID].size(); i++)
		{
			if(m_ButtonMenu[ClientID][i].m_ID == NetGuiElemID)
				m_ButtonMenu[ClientID].remove_index(i);
		}
		break;
	}

	GameServer()->SendNetGui(ClientID, Msg);
}

void CNetGui::UIRect(int ClientID, int NetGuiElemID, vec4 Dimensions, vec4 Color, int Corner, int RoundingX10)
{
	dbg_msg("NETGUI", "CREATING UIRECT");
	CNetMsg_Sv_NetGui_UIRect Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;
	Msg.m_Color[0] = Color.r;
	Msg.m_Color[1] = Color.g;
	Msg.m_Color[2] = Color.b;
	Msg.m_Color[3] = Color.a;
	Msg.m_Corner = Corner;
	Msg.m_RoundingX10 = RoundingX10;

	m_UIRect[ClientID].add(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}

void CNetGui::Label(int ClientID, int NetGuiElemID, const char *pText, vec4 Dimensions, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth)
{
	CNetMsg_Sv_NetGui_Label Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Text = pText;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;
	Msg.m_Color[0] = Color.r;
	Msg.m_Color[1] = Color.g;
	Msg.m_Color[2] = Color.b;
	Msg.m_Color[3] = Color.a;
	Msg.m_FontSize = FontSize;
	Msg.m_FontAlign = FontAlign;
	Msg.m_MaxTextWidth = MaxTextWidth;

	m_Label[ClientID].add(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}

void CNetGui::ButtonMenu(int ClientID, int NetGuiElemID, const char *pText, int Checked, vec4 Dimensions)
{
	CNetMsg_Sv_NetGui_ButtonMenu Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Text = pText;
	Msg.m_Checked = Checked;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;

	m_ButtonMenu[ClientID].add(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}
