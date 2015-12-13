// Copyright (c) 2015 Henritees

#include <game/server/gamecontext.h>
#include <game/server/gamecontroller.h>
#include <engine/server.h>

#include "netgui.h"


// ----------------------------- [start of GUI managing methods] -----------------------------
void CNetGui::CreateGui_ExampleClosed(int ClientID)
{
	ButtonMenu(ClientID, 1, "Open", 0, vec4(45-10, 45+10, 50-5, 50+5));
}
void CNetGui::RemoveGui_ExampleClosed(int ClientID)
{
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 1);
}

void CNetGui::CreateGui_Example1(int ClientID)
{
	UIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(30, 70, 38, 70), 15, 50);
	Label(ClientID, 0, ">)^_^)> Welcome to this NetGUI server! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 500);
	Label(ClientID, 1, "(: Click the button! <(^_^(<", vec4(0, 100, 10, 20), vec4(80, 0, 50, 80), 20, 1, 500);
	Label(ClientID, 2, "NetGUI mod (c) 2015 by Henritees :P", vec4(1, 100, 96, 99), vec4(100, 20, 20, 70), 10, 0, 500);
	ButtonMenu(ClientID, 0, "Close", 0, vec4(45-10, 45+10, 50-5, 50+5));
	ButtonMenu(ClientID, 2, "Page 2 >", 0, vec4(55-10+15, 55+10+15, 50-5, 50+5));
}
void CNetGui::RemoveGui_Example1(int ClientID)
{
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_UIRECT, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 2);

}

void CNetGui::CreateGui_Example2(int ClientID)
{
	UIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(70, 30, 38, 70), 15, 50);
	Label(ClientID, 0, ">)^_^)> Welcome to Page 2! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 500);
	Label(ClientID, 1, "(: Click the button! <(^_^(<", vec4(0, 100, 10, 20), vec4(50, 0, 80, 80), 20, 1, 500);
	Label(ClientID, 2, "NetGUI mod (c) 2015 by Henritees :P", vec4(1, 100, 96, 99), vec4(100, 20, 20, 70), 10, 0, 500);
	ButtonMenu(ClientID, 3, "< Page 1", 1, vec4(55-10+15, 55+10+15, 50-5, 50+5));
	ButtonMenu(ClientID, 4, "Kill me :P", 0, vec4(5, 15, 20+1, 25+1));
	ButtonMenu(ClientID, 5, "Troll me :P", 0, vec4(5, 15, 25+3, 30+3));
	ButtonMenu(ClientID, 6, "F!ck me :P", 0, vec4(5, 15, 30+5, 35+5));
}
void CNetGui::RemoveGui_Example2(int ClientID)
{
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_UIRECT, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 3);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 4);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 5);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 6);
}
// ------------------------------ [end of GUI managing methods] -----------------------------

void CNetGui::OnClientEnter(int ClientID)
{
	// send an example GUI to every entering client
	CreateGui_Example1(ClientID);
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
		bool exists = false;
		for(int i = 0; i < GetButtonMenu(ClientID).size(); i++)
		{
			if(GetButtonMenu(ClientID)[i].m_ID == pMsg->m_ID)
				exists = true;
		}
		if(exists == true)
		{
			// handle button presses
			switch(pMsg->m_ID)
			{
			case 0: // close
				RemoveGui_Example1(ClientID);
				CreateGui_ExampleClosed(ClientID);
				break;
			case 1: // open page 1
				RemoveGui_ExampleClosed(ClientID);
				CreateGui_Example1(ClientID);
				break;
			case 2: // switch to page 2
				RemoveGui_Example1(ClientID);
				CreateGui_Example2(ClientID);
				break;
			case 3: // switch back to page 1
				RemoveGui_Example2(ClientID);
				CreateGui_Example1(ClientID);
				break;
			case 4: // kill
				GameServer()->m_apPlayers[ClientID]->KillCharacter(0);
				break;
			case 5: // troll
				char aBuf[128];
				str_format(aBuf, sizeof(aBuf), "%s is such an NetGUI abuser ey, dat gibbet nich! GRR!! CHATSPAM!!!", GameServer()->Server()->ClientName(ClientID));
				GameServer()->SendChatTarget(-1, aBuf);
				break;
			case 6: // f!ck
				GameServer()->Server()->Kick(ClientID, "haste dich selber gef***t, ne? :P");
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
