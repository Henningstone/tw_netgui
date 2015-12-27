// Copyright (c) 2015 Henritees

#include <game/server/gamecontext.h>
#include <game/server/gamecontroller.h>
#include <engine/server.h>

#include "netgui.h"

#define BUILD_INIT(name) \
		CNetMsg_Sv_NetGui_##name Msg;	\
		Msg.m_ID = NetGuiElemID;			\
		Msg.m_Dimension[0] = Dimensions.x;	\
		Msg.m_Dimension[1] = Dimensions.y;	\
		Msg.m_Dimension[2] = Dimensions.a;	\
		Msg.m_Dimension[3] = Dimensions.b

#define BUILD_FINALIZE(name) \
	if(m_##name[ClientID].size() > 1)\
	{\
		for(int i = 0; i < m_##name[ClientID].size(); i++)\
		{\
			if(m_##name[ClientID][i].m_ID == NetGuiElemID)\
				m_##name[ClientID].remove_index(i);\
		}\
	}\
	m_##name[ClientID].add(Msg);\
	SendNetGui(ClientID, Msg)

#define GUI_INIT() m_ActiveGuis ^= GuiID
#define GET_EID(gid, eid) ((eid+1) << ((gid) * 5))


// ----------------------------- [start of GUI managing methods] -----------------------------
void CNetGui::CreateGui_ExampleClosed(int ClientID, int GuiID)
{
	GUI_INIT();

	DoButtonMenu(ClientID, 1, vec4(100-25-5-20, 100-5-5-20, 100-5-10, 100-5), "Open", 0);
}
void CNetGui::RemoveGui_ExampleClosed(int ClientID, int GuiID)
{
	GUI_INIT();

	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 1);
}

void CNetGui::CreateGui_Example1(int ClientID, int GuiID)
{
	GUI_INIT();

	// main rect
	DoUIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(30, 70, 38, 70), 15, 5.0f);

	// labels
	DoLabel(ClientID, 0, vec4(0, 100, 0, 10), ">)^_^)> Welcome to this NetGUI server! :)", vec4(80, 0, 0, 90), 20, 1, 100-0);
	DoLabel(ClientID, 1, vec4(0, 100, 10, 20), "(: Click the button! <(^_^(<", vec4(80, 0, 50, 80), 20, 1, 100-0);
	DoLabel(ClientID, 2, vec4(1, 100, 96, 99), "NetGUI mod (c) 2015 by Henritees :P", vec4(100, 20, 20, 70), 10, 0, 100-1);

	// buttons at the bottom (button IDs must begin with 1, not with 0!)
	DoButtonMenu(ClientID, 0, vec4(100-25-5-20, 100-5-5-20, 100-5-10, 100-5), "Close", 0);
	DoButtonMenu(ClientID, 2, vec4(100-5-20, 100-5, 100-5-10, 100-5), "Page 2 →", 0);

	// listbox 1
	DoListboxHeader(ClientID, 0, vec4(20, 50-2, 17, 60), "Testing Listbox with Header ;)", 20.0f, 2.0f);
	// add some useless test items to the list :D
	// IMPROTANT: add the items before doing "ListboxStart"!!
	for(int i = 0; i < 20; i++)
	{
		char aBuf[64];
		str_format(aBuf, sizeof(aBuf), "Item %i", i+1);
		ListboxItemAdd(ClientID, 0, i, aBuf);
	}
	DoListboxStart(ClientID, 0, vec4(0,0,0,0) /*overridden*/, 0, 20.0f, 1, 2, 0, true);
	DoButtonMenu(ClientID, 12, vec4(50, 60, 20, 30), "»»", 0);

	//DoButtonMenu(ClientID, 14, vec4(50, 60, 30+2, 40+2), "«–»", 0);

	// listbox 2
	DoListboxHeader(ClientID, 1, vec4(60+2, 90, 17, 60), "Listbox 2...", 20.0f, 2.0f);
	for(int i = 20; i >= 0; i--)
	{
		char aBuf[64];
		str_format(aBuf, sizeof(aBuf), "%i metI", i+1);
		ListboxItemAdd(ClientID, 1, i, aBuf);
	}
	DoListboxStart(ClientID, 1, vec4(40+2, 60+2, 20, 60), 0, 20.0f, 1, 2, 1, true);
	DoButtonMenu(ClientID, 13, vec4(50, 60, 40+2+2, 50+2+2), "««", 0);

}
void CNetGui::RemoveGui_Example1(int ClientID, int GuiID)
{
	GUI_INIT();

	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_UIRECT, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LABEL, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 2);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 12);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 13);
	//RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 14);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXHEADER, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXHEADER, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 1);
}

void CNetGui::CreateGui_Example2(int ClientID, int GuiID)
{
	GUI_INIT();

	DoUIRect(ClientID, 0, vec4(0, 100, 0, 100), vec4(70, 30, 38, 70), 15, 5.0f);
	DoLabel(ClientID, 0, vec4(0, 100, 0, 10), ">)^_^)> Welcome to Page 2! :)", vec4(80, 0, 0, 90), 20, 1, 100-0);
	DoLabel(ClientID, 1, vec4(0, 100, 10, 20), "(: Congraz for clicking! <(^_^(<", vec4(50, 0, 80, 80), 20, 1, 100-0);
	DoLabel(ClientID, 2, vec4(1, 100, 96, 99), "NetGUI mod (c) 2015 by Henritees :P", vec4(100, 20, 20, 70), 10, 0, 100-1);
	DoButtonMenu(ClientID, 3, vec4(100-5-20, 100-5, 100-5-10, 100-5), "← Page 1", 0);

	DoButtonMenu(ClientID, 4, vec4(5, 15, 20+1, 25+1), "Kill me", 0);
	DoLabel(ClientID, 3, vec4(15+3, 100, 20+1, 25+1), "<- This button will kill you", vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	DoButtonMenu(ClientID, 5, vec4(5, 15, 25+3, 30+3), "Troll me :P", 0);
	DoLabel(ClientID, 4, vec4(15+3, 100, 25+3, 30+3), "<- This button will print some random shit into the chat ;)", vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	DoButtonMenu(ClientID, 6, vec4(5, 15, 30+5, 35+5), "F!ck me :P", 0);
	DoLabel(ClientID, 5, vec4(15+3, 100, 30+5, 35+5), "<- Surprise motherf*ckr! ^(devil)^", vec4(30, 100, 20, 80), 13, 0, 100-(15+3));

	DoButtonMenu(ClientID, 7, vec4(5, 15, 35+7, 40+7), "Print me :P", 0);
	DoLabel(ClientID, 6, vec4(15+3, 100, 35+7, 40+7), "<- Print your login data (from below ↓) into the chat... public! mehe!", vec4(30, 100, 20, 80), 13, 0, 10);

	DoUIRect(ClientID, 2, vec4(5, 50, 40+9, 60+15), vec4(0, 0, 40, 85), 15, 3.0f);
	DoLabel(ClientID, 7, vec4(5+2, 50-2, 40+9+1, 45+9+1), "Server Account Login (just as an example ^^)", vec4(100,100,100,100), 10, 1, (50-2)-(5+2));
	DoEditBox(ClientID, 0, vec4(5+3, 50-3, 45+11, 50+11), "Login name", 50, 16, false);
	DoEditBox(ClientID, 1, vec4(5+3, 50-3, 50+13, 55+13), "Password", 50, 16, true);

	DoInfoBox(ClientID, 0, vec4(50+3, 90-3, 45+11, 50+11), "Infobox 1", "this is an info.");
	DoInfoBox(ClientID, 1, vec4(50+3, 90-3, 50+13, 55+13), "Infobox 2", "hm. <(ø_ø(<");

	DoCheckBox(ClientID, 0, vec4(5, 50, 60+17, 65+17), "Whatever… but hey, I'm a checkbox so YOOO!", 0);
	DoButtonMenu(ClientID, 8, vec4(50+3, 55+3, 60+17, 65+17), "»", 0);

	DoCheckBoxNumber(ClientID, 0, vec4(5, 50, 65+19, 70+19), "Amazing Number-Checkbox ;)", 0, 16, 2);
	DoButtonMenu(ClientID, 9, vec4(50+3, 55+3, 65+19, 70+19), "»", 0);

	DoScrollbarOption(ClientID, 0, vec4(5, 50, 70+21, 75+21), "Scroooool-me-bar", 55.0f, 0, 100, false);
	DoButtonMenu(ClientID, 10, vec4(50+3, 55+3, 70+21, 75+21), "»", 0);

	DoScrollbar(ClientID, 0, vec4(90, 95, 5, 50), true);
	DoButtonMenu(ClientID, 11, vec4(90, 95, 50+5, 60+5), "»", 0);

}
void CNetGui::RemoveGui_Example2(int ClientID, int GuiID)
{
	GUI_INIT();

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
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 9);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 10);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_BUTTONMENU, 11);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 1);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_CHECKBOX, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_CHECKBOXNUMBER, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_SCROLLBAR, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_SCROLLBAROPTION, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_INFOBOX, 0);
	RemoveElement(ClientID, NETMSGTYPE_SV_NETGUI_INFOBOX, 1);
}

// ------------------------------ [end of GUI managing methods] -----------------------------

void CNetGui::OnClientEnter(int ClientID)
{
	// send an example GUI to every entering client
	CreateGui_Example1(ClientID);
}

void CNetGui::OnClientDrop(int ClientID)
{
	// auto-generated clear's
	#define GUIDEFINE(name, netmsgname, args...) m_##name[ClientID].clear();
	#include <game/netguidefines.h>
	#undef GUIDEFINE
}


void CNetGui::OnMessage(int MsgID, void *pRawMsg, int ClientID)
{
	CPlayer *pPlayer = GameServer()->m_apPlayers[ClientID];

	if (MsgID == NETMSGTYPE_CL_NETGUI_TRIGGEREVENT)
	{
		CNetMsg_Cl_NetGui_TriggerEvent *pMsg = (CNetMsg_Cl_NetGui_TriggerEvent *)pRawMsg;

		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_BUTTONMENU:
			bool exists = false;
			for(int i = 0; i < m_ButtonMenu[ClientID].size(); i++)
			{
				if(m_ButtonMenu[ClientID][i].m_ID == pMsg->m_ID)
					exists = true;
			}
			if(exists)
			{
				// TODO: handle button presses
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
					GameServer()->Server()->Kick(ClientID, "You just got fckd up by yourself :P");
					break;
				case 7: // print
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 0);
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_EDITBOX, 1);
					break;
				case 8: // checkbox
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_CHECKBOX, 0);
					break;
				case 9: // numbercheckbox
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_CHECKBOXNUMBER, 0);
					break;
				case 10: // option-scrollbar
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_SCROLLBAROPTION, 0);
					break;
				case 11: // (vertical) scrollbar
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_SCROLLBAR, 0);
					break;
				case 12: // listbox1 -> listbox2
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 0);
					break;
				case 13: // listbox2 -> listbox1
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 1);
					break;
			/*	case 14: // listbox1 <-> listbox2
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 0);
					RequestData(ClientID, NETMSGTYPE_SV_NETGUI_LISTBOXSTART, 1);
					break;*/
				}
			}
			break;
		}
	}
	else if(MsgID == NETMSGTYPE_CL_NETGUI_RESPONSESTRING) // TODO: handle string responses
	{
		CNetMsg_Cl_NetGui_ResponseString *pMsg = (CNetMsg_Cl_NetGui_ResponseString *)pRawMsg;

		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_EDITBOX:
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
			break;
		}
	}
	else if(MsgID == NETMSGTYPE_CL_NETGUI_RESPONSEINT) // TODO: handle integer responses
	{
		CNetMsg_Cl_NetGui_ResponseInt *pMsg = (CNetMsg_Cl_NetGui_ResponseInt *)pRawMsg;

		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_CHECKBOX:
		{
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' made checkbox being %s! Well done :)", GameServer()->Server()->ClientName(ClientID), pMsg->m_Value ? "checked" : "unchecked");
			GameServer()->SendChatTarget(-1, aBuf);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_CHECKBOXNUMBER:
		{
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' set the number-checkbox to %i! Nice :)", GameServer()->Server()->ClientName(ClientID), pMsg->m_Value);
			GameServer()->SendChatTarget(-1, aBuf);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_SCROLLBAR:
		{
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' slided the sliding scroooollbar %i%! Wuhu :)", GameServer()->Server()->ClientName(ClientID), pMsg->m_Value);
			GameServer()->SendChatTarget(-1, aBuf);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_SCROLLBAROPTION:
		{
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' scrooolled the bar to value %i! Great :)", GameServer()->Server()->ClientName(ClientID), pMsg->m_Value);
			GameServer()->SendChatTarget(-1, aBuf);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_LISTBOXSTART:
			char aBuf[128];
			str_format(aBuf, sizeof(aBuf), "'%s' selected item no %i from listbox ID:%d. It's text is '%s'", GameServer()->Server()->ClientName(ClientID), pMsg->m_Value, pMsg->m_ID, ListboxItemGetText(ClientID, pMsg->m_ID, pMsg->m_Value));
			GameServer()->SendChatTarget(-1, aBuf);
			ListboxItemAdd(ClientID, 1-pMsg->m_ID, ListboxItemsNum(ClientID, 1-pMsg->m_ID), ListboxItemGetText(ClientID, pMsg->m_ID, pMsg->m_Value));
		}
	}
}

void CNetGui::RemoveElement(int ClientID, int Type, int NetGuiElemID)
{
	CNetMsg_Sv_NetGui_RemoveElement Msg;
	Msg.m_Type = Type;
	Msg.m_ID = NetGuiElemID;

	// remove handler; the "args..." thingy is just for compatiblity and will be dropped
	#define GUIDEFINE(name, netmsgname, args...) \
		case NETMSGTYPE_SV_NETGUI_##netmsgname: \
			for(int i = 0; i < m_##name[ClientID].size(); i++) \
			{ \
				if(m_##name[ClientID][i].m_ID == NetGuiElemID) \
					m_##name[ClientID].remove_index(i); \
			} \
			break;


	switch(Type)
	{
		// auto-generated remove handlers
		#include <game/netguidefines.h>
		#undef GUIDEFINE
	}

	SendNetGui(ClientID, Msg);
}


void CNetGui::DoUIRect(int ClientID, int NetGuiElemID, vec4 Dimensions, vec4 Color, int Corner, float Rounding)
{
	BUILD_INIT(UIRect);

	Msg.m_Color[0] = Color.r;
	Msg.m_Color[1] = Color.g;
	Msg.m_Color[2] = Color.b;
	Msg.m_Color[3] = Color.a;
	Msg.m_Corner = Corner;
	Msg.m_RoundingX10 = (int)(Rounding*10.0f);

	BUILD_FINALIZE(UIRect);
}

void CNetGui::DoLabel(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth)
{
	BUILD_INIT(Label);

	Msg.m_Text = pText;
	Msg.m_Color[0] = Color.r;
	Msg.m_Color[1] = Color.g;
	Msg.m_Color[2] = Color.b;
	Msg.m_Color[3] = Color.a;
	Msg.m_FontSize = FontSize;
	Msg.m_FontAlign = FontAlign;
	Msg.m_MaxTextWidth = MaxTextWidth;

	BUILD_FINALIZE(Label);
}

void CNetGui::DoButtonMenu(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, bool Selected)
{
	BUILD_INIT(ButtonMenu);

	Msg.m_Text = pText;
	Msg.m_Selected = Selected ? 1 : 0;

	BUILD_FINALIZE(ButtonMenu);
}

void CNetGui::DoEditBox(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pTitle, int SplitValue, int MaxTextWidth, bool Password)
{
	BUILD_INIT(EditBox);

	Msg.m_Title = pTitle;
	Msg.m_SplitValue = SplitValue;
	Msg.m_MaxTextWidth = MaxTextWidth;
	Msg.m_Password = Password ? 1 : 0;

	BUILD_FINALIZE(EditBox);
}

void CNetGui::DoCheckBox(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, bool Checked)
{
	BUILD_INIT(CheckBox);

	Msg.m_Text = pText;
	Msg.m_Checked = Checked ? 1 : 0;

	BUILD_FINALIZE(CheckBox);
}

void CNetGui::DoCheckBoxNumber(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, int MinValue, int MaxValue, int StepValue)
{
	BUILD_INIT(CheckBoxNumber);

	Msg.m_Text = pText;
	Msg.m_Value = MinValue;
	Msg.m_MinValue = MinValue;
	Msg.m_MaxValue = MaxValue;
	Msg.m_StepValue = StepValue;

	BUILD_FINALIZE(CheckBoxNumber);
}

void CNetGui::DoScrollbar(int ClientID, int NetGuiElemID, vec4 Dimensions, bool Vertical)
{
	BUILD_INIT(Scrollbar);

	Msg.m_Vertical = Vertical ? 1 : 0;

	BUILD_FINALIZE(Scrollbar);
}

void CNetGui::DoScrollbarOption(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pText, float VSplitVal, int Min, int Max, bool Infinite)
{
	BUILD_INIT(ScrollbarOption);

	Msg.m_Text = pText;
	Msg.m_VSplitValX10 = (int)(VSplitVal*10.0f);
	Msg.m_MinValue = Min;
	Msg.m_MaxValue = Max;
	Msg.m_Infinite = Infinite ? 1 : 0;

	BUILD_FINALIZE(ScrollbarOption);
}

void CNetGui::DoInfoBox(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pLabel, const char* pValue)
{
	BUILD_INIT(InfoBox);

	Msg.m_Label = pLabel;
	Msg.m_Value = pValue;

	BUILD_FINALIZE(InfoBox);
}

void CNetGui::DoListboxHeader(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pTitle, float Height, float Spacing)
{
	BUILD_INIT(ListboxHeader);

	Msg.m_Title = pTitle;
	Msg.m_HeightX10 = (int)(Height * 10);
	Msg.m_SpacingX10 = (int)(Spacing * 10);

	BUILD_FINALIZE(ListboxHeader);
}

void CNetGui::DoListboxStart(int ClientID, int NetGuiElemID, vec4 Dimensions, const char *pBottomText, float RowHeight, int ItemsPerRow, int SelectedIndex, int HeaderID, bool Background)
{
	BUILD_INIT(ListboxStart);
	Msg.m_BottomText = pBottomText ? pBottomText : " ";
	Msg.m_RowHeightX10 = (int)(RowHeight * 10);
	Msg.m_ItemsPerRow = ItemsPerRow;
	Msg.m_SelectedIndex = SelectedIndex;
	Msg.m_HeaderID = HeaderID;
	Msg.m_Background = Background ? 1 : 0;

	BUILD_FINALIZE(ListboxStart);
}

// not a gui element
void CNetGui::ListboxItemAdd(int ClientID, int ListboxStartID, int ItemID, const char *pText)
{
	CNetMsg_Sv_NetGui_ListboxItemAdd Msg;
	Msg.m_ID = ItemID;
	Msg.m_ListboxID = ListboxStartID;
	Msg.m_Text = pText;
	SendNetGui(ClientID, Msg);

	char *pNewText = (char *)mem_alloc(sizeof(pText), 0);
	str_copy(pNewText, pText, sizeof(pNewText));

	CNetGuiListboxItem Item(ListboxStartID, ItemID, pNewText);
	m_ListboxItems[ClientID][ListboxStartID].add(Item);

}

// not a gui element
void CNetGui::ListboxItemRemove(int ClientID, int ListboxID, int ItemID)
{
	CNetMsg_Sv_NetGui_ListboxItemRemove Msg;
	Msg.m_ID = ItemID;
	Msg.m_ListboxID = ListboxID;
	SendNetGui(ClientID, Msg);

	// go though all elements and find the one to remove
	sorted_array<CNetGuiListboxItem> *pItems = &m_ListboxItems[ClientID][ListboxID];
	for(int i = 0; i < pItems->size(); i++)
	{
		if((*pItems)[i].m_ID == ItemID)
			pItems->remove_index(i);
	}
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

void CNetGui::RequestData(int ClientID, int Type, int NetGuiElemID)
{
		CNetMsg_Sv_NetGui_RequestData Msg;
		Msg.m_ID = NetGuiElemID;
		Msg.m_Type = Type;
		GameServer()->Server()->SendPackMsg(&Msg, MSGFLAG_VITAL, ClientID);
}
