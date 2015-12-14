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
	Label(ClientID, 0, ">)^_^)> Welcome to this NetGUI server! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 100-0);
	Label(ClientID, 1, "(: Click the button! <(^_^(<", vec4(0, 100, 10, 20), vec4(80, 0, 50, 80), 20, 1, 100-0);
	Label(ClientID, 2, "NetGUI mod (c) 2015 by Henritees :P", vec4(1, 100, 96, 99), vec4(100, 20, 20, 70), 10, 0, 100-1);
	ButtonMenu(ClientID, 0, "Close", 0, vec4(45-10, 45+10, 50-5, 50+5));
	ButtonMenu(ClientID, 2, "Page 2 →", 0, vec4(vec4(100-5-20, 100-5, 100-5-10, 100-5)));
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
	UIRect(ClientID, 1, vec4(0, 100, 0, 100), vec4(70, 30, 38, 70), 15, 50);
	Label(ClientID, 0, ">)^_^)> Welcome to Page 2! :)", vec4(0, 100, 0, 10), vec4(80, 0, 0, 90), 20, 1, 100-0);
	Label(ClientID, 1, "(: Congraz for clicking! <(^_^(<", vec4(0, 100, 10, 20), vec4(50, 0, 80, 80), 20, 1, 100-0);
	Label(ClientID, 2, "NetGUI mod (c) 2015 by Henritees :P", vec4(1, 100, 96, 99), vec4(100, 20, 20, 70), 10, 0, 100-1);
	ButtonMenu(ClientID, 3, "← Page 1", 1, vec4(100-5-20, 100-5, 100-5-10, 100-5));

	ButtonMenu(ClientID, 4, "Kill me", 0, vec4(5, 15, 20+1, 25+1));
	Label(ClientID, 3, "<- This button will kill you", vec4(15+3, 100, 20+1, 25+1), vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	ButtonMenu(ClientID, 5, "Troll me :P", 0, vec4(5, 15, 25+3, 30+3));
	Label(ClientID, 4, "<- This button will print some random shit into the chat ;)", vec4(15+3, 100, 25+3, 30+3), vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	ButtonMenu(ClientID, 6, "F!ck me :P", 0, vec4(5, 15, 30+5, 35+5));
	Label(ClientID, 5, "<- Surprise motherf*ckr! ^(devil)^", vec4(15+3, 100, 30+5, 35+5), vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	ButtonMenu(ClientID, 7, "Print me :P", 0, vec4(5, 15, 35+7, 40+7));
	Label(ClientID, 6, "<- Print your login data (from below ↓) into the chat... public! mehe!", vec4(15+3, 100, 35+7, 40+7), vec4(30, 100, 20, 80), 13, 0, 10);

	UIRect(ClientID, 2, vec4(5, 50, 40+9, 60+15), vec4(0, 0, 40, 85), 15, 30);
	Label(ClientID, 7, "Server Account Login (just as an example ^^)", vec4(5+2, 50-2, 40+9+1, 45+9+1), vec4(100,100,100,100), 10, 1, (50-2)-(5+2));
	EditBox(ClientID, 0, vec4(5+3, 50-3, 45+11, 50+11), "Login name", 50, 16, false);
	EditBox(ClientID, 1, vec4(5+3, 50-3, 50+13, 55+13), "Password", 50, 16, true);

	CheckBox(ClientID, 0, vec4(5, 50, 60+17, 65+17), "Whatever… but hey, I'm a checkbox so YOOO!", 0);
	ButtonMenu(ClientID, 8, "»", 0, vec4(50+3, 55+3, 60+17, 65+17));
}
void CNetGui::RemoveGui_Example2(int ClientID)
{
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_UIRECT, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_UIRECT, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 3);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 4);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 5);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 6);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 7);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 3);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 4);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 5);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 6);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 7);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 8);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_CHECKBOX, 0);
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
	m_EditBox[ClientID].clear();
	m_CheckBox[ClientID].clear();
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
		if(exists)
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
				str_format(aBuf, sizeof(aBuf), "Gob Gob Gob Gob who want some coooookies....? ^-^ Ask %s!", GameServer()->Server()->ClientName(ClientID));
				GameServer()->SendChat(ClientID, 0, aBuf);
				break;
			case 6: // f!ck
				GameServer()->Server()->Kick(ClientID, "haste dich selber gef***t, ne? :P");
				break;
			case 7:
				RequestData(ClientID, 0, NETMSGTYPE_SV_NETGUI_EDITBOX);
				RequestData(ClientID, 1, NETMSGTYPE_SV_NETGUI_EDITBOX);
				break;
			case 8:
				RequestData(ClientID, 0, NETMSGTYPE_SV_NETGUI_CHECKBOX);
			}
		}
	}
	else if(MsgID == NETMSGTYPE_CL_NETGUI_EDITBOX_CONTENT)
	{
		CNetMsg_Cl_NetGui_EditBox_Content *pMsg = (CNetMsg_Cl_NetGui_EditBox_Content *)pRawMsg;

		// a (maybe shitty) example of how multiple EditBoxes can be read at once (though not simultaneously...)
		static int GotIDs;
		static char aLoginName[32];
		static char aLoginPass[32];
		switch(pMsg->m_ID)
		{
		case 0:
			GotIDs |= 1;
			str_copy(aLoginName, pMsg->m_Text, sizeof(aLoginName));
			break;
		case 1:
			GotIDs |= 2;
			str_copy(aLoginPass, pMsg->m_Text, sizeof(aLoginPass));
			break;
		}

		if(GotIDs == (1 | 2))
		{
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' would have logged in with name='%s' and pass='%s'", GameServer()->Server()->ClientName(ClientID), aLoginName, aLoginPass);
			GameServer()->SendChatTarget(-1, aBuf);
			GotIDs = 0;
		}
	}
	else if(MsgID == NETMSGTYPE_CL_NETGUI_CHECKBOX_STATE)
	{
		CNetMsg_Cl_NetGui_CheckBox_State *pMsg = (CNetMsg_Cl_NetGui_CheckBox_State *)pRawMsg;
		char aBuf[128];
		str_format(aBuf, sizeof(aBuf), "'%s' made checkbox being %s! Well done :)", GameServer()->Server()->ClientName(ClientID), pMsg->m_Checked ? "checked" : "unchecked");
		GameServer()->SendChatTarget(-1, aBuf);
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
	case NETMSGTYPE_SV_NETGUI_EDITBOX:
		for(int i = 0; i < m_EditBox[ClientID].size(); i++)
		{
			if(m_EditBox[ClientID][i].m_ID == NetGuiElemID)
				m_EditBox[ClientID].remove_index(i);
		}
		break;
	case NETMSGTYPE_SV_NETGUI_CHECKBOX:
		for(int i = 0; i < m_CheckBox[ClientID].size(); i++)
		{
			if(m_CheckBox[ClientID][i].m_ID == NetGuiElemID)
				m_CheckBox[ClientID].remove_index(i);
		}
		break;
	}

	SendNetGui(ClientID, Msg);
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

	SendNetGui(ClientID, Msg);
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

	SendNetGui(ClientID, Msg);
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

	SendNetGui(ClientID, Msg);
}

void CNetGui::EditBox(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pTitle, int SplitValue, int MaxTextWidth, bool Password)
{
	CNetMsg_Sv_NetGui_EditBox Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;
	Msg.m_Title = pTitle;
	Msg.m_SplitValue = SplitValue;
	Msg.m_MaxTextWidth = MaxTextWidth;
	Msg.m_Password = Password ? 1 : 0;

	m_EditBox[ClientID].add(Msg);

	SendNetGui(ClientID, Msg);
}

void CNetGui::CheckBox(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, int Checked)
{
	CNetMsg_Sv_NetGui_CheckBox Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Text = pText;
	Msg.m_Checked = Checked;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;

	m_CheckBox[ClientID].add(Msg);

	SendNetGui(ClientID, Msg);
}

template<class T>
void CNetGui::SendNetGui(int ClientID, T Msg)
{
	if(ClientID < 0)
	{
		for(int i = 0; i < MAX_CLIENTS; ++i)
		{
			if(!GameServer()->m_apPlayers[i] /*|| !Server()->ClientIngame(i)*/)
				continue;

			GameServer()->Server()->SendPackMsg(&Msg, MSGFLAG_VITAL, i);
		}
	}
	else
		GameServer()->Server()->SendPackMsg(&Msg, MSGFLAG_VITAL, ClientID);
}

void CNetGui::RequestData(int ClientID, int NetGuiElemID, int Type)
{
		CNetMsg_Sv_NetGui_RequestContent Msg;
		Msg.m_ID = NetGuiElemID;
		Msg.m_Type = Type;
		GameServer()->Server()->SendPackMsg(&Msg, MSGFLAG_VITAL, ClientID);
}
