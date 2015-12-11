#include <game/server/gamecontext.h>
#include <game/server/gamecontroller.h>

#include "netgui.h"

void CNetGui::RemoveElement(int ClientID, int Type, int NetGuiElemID)
{
	CNetMsg_Sv_NetGui_RemoveElement Msg;
	Msg.m_Type = Type;
	Msg.m_ID = NetGuiElemID;

	switch(Type) // TODO: This seems kinda shitty to me... to much duplicated code :0
	{
	case NETMSGTYPE_SV_NETGUI_UIRECT:
		for(int i = 0; i < m_UIRect.size(); i++)
		{
			if(m_UIRect[i].m_ID == NetGuiElemID)
				m_UIRect.remove_index(i);
		}
		break;
	case NETMSGTYPE_SV_NETGUI_LABEL:
		for(int i = 0; i < m_Label.size(); i++)
		{
			if(m_Label[i].m_ID == NetGuiElemID)
				m_Label.remove_index(i);
		}
		break;
	case NETMSGTYPE_SV_NETGUI_BUTTONMENU:
		for(int i = 0; i < m_ButtonMenu.size(); i++)
		{
			if(m_ButtonMenu[i].m_ID == NetGuiElemID)
				m_ButtonMenu.remove_index(i);
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

	m_UIRect.add_unsorted(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}

void CNetGui::Label(int ClientID, int NetGuiElemID, const char *pText, vec2 Pos, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth)
{
	dbg_msg("NETGUI", "CREATING LABEL");
	CNetMsg_Sv_NetGui_Label Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Text = pText;
	Msg.m_Dimension[0] = Pos.x;
	Msg.m_Dimension[1] = Pos.y;
	Msg.m_Dimension[2] = 0;
	Msg.m_Dimension[3] = 0;
	Msg.m_Color[0] = Color.r;
	Msg.m_Color[1] = Color.g;
	Msg.m_Color[2] = Color.b;
	Msg.m_Color[3] = Color.a;
	Msg.m_FontSize = FontSize;
	Msg.m_FontAlign = FontAlign;
	Msg.m_MaxTextWidth = MaxTextWidth;

	m_Label.add_unsorted(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}

void CNetGui::ButtonMenu(int ClientID, int NetGuiElemID, const char *pText, int Checked, vec4 Dimensions)
{
	dbg_msg("NETGUI", "CREATING BUTTON");
	CNetMsg_Sv_NetGui_ButtonMenu Msg;
	Msg.m_ID = NetGuiElemID;
	Msg.m_Text = pText;
	Msg.m_Checked = Checked;
	Msg.m_Dimension[0] = Dimensions.x;
	Msg.m_Dimension[1] = Dimensions.y;
	Msg.m_Dimension[2] = Dimensions.a;
	Msg.m_Dimension[3] = Dimensions.b;

	m_ButtonMenu.add_unsorted(Msg);

	GameServer()->SendNetGui(ClientID, Msg);
}
