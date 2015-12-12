// Copyright (c) 2015 Henritees

#include "netgui.h"


void CNetGui::OnReset()
{
	m_NetGuiUIRect.clear();
	m_NetGuiLabel.clear();
	m_NetGuiButtonMenu.clear();
}


void CNetGui::OnMessage(int MsgId, void *pRawMsg)
{
	if(MsgId == NETMSGTYPE_SV_NETGUI_REMOVEELEMENT)
	{
		CNetMsg_Sv_NetGui_RemoveElement *pMsg = (CNetMsg_Sv_NetGui_RemoveElement *)pRawMsg;
		//dbg_msg("NETGUI", "received 'REMOVEELEMENT' with Type:%d and ID:%d", pMsg->m_Type, pMsg->m_ID);

		switch(pMsg->m_Type) // TODO: This seems kinda shitty to me... to much duplicated code :0
		{
		case NETMSGTYPE_SV_NETGUI_UIRECT:
			for(int i = 0; i < m_NetGuiUIRect.size(); i++)
			{
				if(m_NetGuiUIRect[i].m_ID == pMsg->m_ID)
				{
					dbg_msg("NETGUI", "removing UIRect with ID:%d", pMsg->m_ID);
					m_NetGuiUIRect.remove_index(i);
				}
			}
			break;
		case NETMSGTYPE_SV_NETGUI_LABEL:
			for(int i = 0; i < m_NetGuiLabel.size(); i++)
			{

				if(m_NetGuiLabel[i].m_ID == pMsg->m_ID)
				{
					dbg_msg("NETGUI", "removing Label with ID:%d", pMsg->m_ID);
					m_NetGuiLabel.remove_index(i);
				}
			}
			break;
		case NETMSGTYPE_SV_NETGUI_BUTTONMENU:
			for(int i = 0; i < m_NetGuiButtonMenu.size(); i++)
			{
				if(m_NetGuiButtonMenu[i].m_ID == pMsg->m_ID)
				{
					dbg_msg("NETGUI", "removing ButtonMenu with ID:%d", pMsg->m_ID);
					m_NetGuiButtonMenu.remove_index(i);
				}
			}
			break;
		}
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_UIRECT)
	{
		CNetMsg_Sv_NetGui_UIRect *pMsg = (CNetMsg_Sv_NetGui_UIRect *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_UIRect e;
		e.m_ID = pMsg->m_ID;
		e.m_Dimension[0] = pMsg->m_Dimension[0];
		e.m_Dimension[1] = pMsg->m_Dimension[1];
		e.m_Dimension[2] = pMsg->m_Dimension[2];
		e.m_Dimension[3] = pMsg->m_Dimension[3];
		e.m_Color[0] = pMsg->m_Color[0];
		e.m_Color[1] = pMsg->m_Color[1];
		e.m_Color[2] = pMsg->m_Color[2];
		e.m_Color[3] = pMsg->m_Color[3];
		e.m_Corner = pMsg->m_Corner;
		e.m_RoundingX10 = pMsg->m_RoundingX10;

		// check for duplicated IDs and overwrite them
		if(m_NetGuiUIRect.size() > 1)
		{
			for(int i = 0; m_NetGuiUIRect.size(); i++)
			{
				if(m_NetGuiUIRect[i].m_ID == e.m_ID)
					m_NetGuiUIRect.remove_index(i);
			}
		}

		// save the element and resort the list
		m_NetGuiUIRect.add(e);
		SortNetGuiList<CNetMsg_Sv_NetGui_UIRect>(m_NetGuiUIRect);

		dbg_msg("NETGUI", "RECEIVED RECT ID:%d, num=%i", e.m_ID, m_NetGuiUIRect.size());
		for(int i = 0; i < m_NetGuiUIRect.size(); i++)
			dbg_msg("NETGUI", " Rect IDs: %i=%d", i, m_NetGuiUIRect[i].m_ID);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_LABEL)
	{
		CNetMsg_Sv_NetGui_Label *pMsg = (CNetMsg_Sv_NetGui_Label *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_Label e;

		e.m_ID = pMsg->m_ID;
		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;//pString;
		e.m_Dimension[0] = pMsg->m_Dimension[0];
		e.m_Dimension[1] = pMsg->m_Dimension[1];
		e.m_Dimension[2] = pMsg->m_Dimension[2];
		e.m_Dimension[3] = pMsg->m_Dimension[3];
		e.m_Color[0] = pMsg->m_Color[0];
		e.m_Color[1] = pMsg->m_Color[1];
		e.m_Color[2] = pMsg->m_Color[2];
		e.m_Color[3] = pMsg->m_Color[3];
		e.m_FontSize = pMsg->m_FontSize;
		e.m_FontAlign = pMsg->m_FontAlign;

		// check for duplicated IDs and overwrite them
		if(m_NetGuiLabel.size() > 1)
		{
			for(int i = 0; i < m_NetGuiLabel.size(); i++)
			{
				if(m_NetGuiLabel[i].m_ID == e.m_ID)
					m_NetGuiLabel.remove_index(i);
			}
		}

		// save the element and resort the list
		m_NetGuiLabel.add(e);
		dbg_msg("NETGUI", "RECEIVED LABEL ID:%d, num=%i", e.m_ID, m_NetGuiLabel.size());
		SortNetGuiList<CNetMsg_Sv_NetGui_Label>(m_NetGuiLabel);

		for(int i = 0; i < m_NetGuiLabel.size(); i++)
			dbg_msg("NETGUI", " Label IDs: %i=%d", i, m_NetGuiLabel[i].m_ID);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_BUTTONMENU)
	{
		CNetMsg_Sv_NetGui_ButtonMenu *pMsg = (CNetMsg_Sv_NetGui_ButtonMenu *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_ButtonMenu e;

		e.m_ID = pMsg->m_ID;
		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Dimension[0] = pMsg->m_Dimension[0];
		e.m_Dimension[1] = pMsg->m_Dimension[1];
		e.m_Dimension[2] = pMsg->m_Dimension[2];
		e.m_Dimension[3] = pMsg->m_Dimension[3];
		e.m_Checked = pMsg->m_Checked;

		// check for duplicated IDs and overwrite them
		if(m_NetGuiButtonMenu.size() > 1)
		{
			for(int i = 0; i < m_NetGuiButtonMenu.size(); i++)
			{
				if(m_NetGuiButtonMenu[i].m_ID == e.m_ID)
					m_NetGuiButtonMenu.remove_index(i);
			}
		}

		// save the element and resort the list
		m_NetGuiButtonMenu.add(e);
		SortNetGuiList<CNetMsg_Sv_NetGui_ButtonMenu>(m_NetGuiButtonMenu);

		dbg_msg("NETGUI", "RECEIVED BUTTON ID:%d, num=%i", e.m_ID, m_NetGuiButtonMenu.size());
		for(int i = 0; i < m_NetGuiButtonMenu.size(); i++)
			dbg_msg("NETGUI", " Button IDs: %i=%d", i, m_NetGuiButtonMenu[i].m_ID);
	}
}
