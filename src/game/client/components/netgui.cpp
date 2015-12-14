// Copyright (c) 2015 Henritees

#include "netgui.h"


void CNetGui::OnReset()
{
	m_NetGuiUIRect.clear();
	m_NetGuiLabel.clear();
	m_NetGuiButtonMenu.clear();
	m_NetGuiEditBox.clear();
	m_NetGuiCheckBox.clear();
}

void CNetGui::OnMessage(int MsgId, void *pRawMsg)
{
	if(MsgId == NETMSGTYPE_SV_NETGUI_REMOVEELEMENT)
	{
		CNetMsg_Sv_NetGui_RemoveElement *pMsg = (CNetMsg_Sv_NetGui_RemoveElement *)pRawMsg;

		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_UIRECT:
			for(int i = 0; i < m_NetGuiUIRect.size(); i++)
			{
				if(m_NetGuiUIRect[i].m_ID == pMsg->m_ID)
					m_NetGuiUIRect.remove_index(i);
			}
			break;
		case NETMSGTYPE_SV_NETGUI_LABEL:
			for(int i = 0; i < m_NetGuiLabel.size(); i++)
			{

				if(m_NetGuiLabel[i].m_ID == pMsg->m_ID)
					m_NetGuiLabel.remove_index(i);
			}
			break;
		case NETMSGTYPE_SV_NETGUI_BUTTONMENU:
			for(int i = 0; i < m_NetGuiButtonMenu.size(); i++)
			{
				if(m_NetGuiButtonMenu[i].m_ID == pMsg->m_ID)
					m_NetGuiButtonMenu.remove_index(i);
			}
			break;
		case NETMSGTYPE_SV_NETGUI_EDITBOX:
			for(int i = 0; i < m_NetGuiEditBox.size(); i++)
			{
				if(m_NetGuiEditBox[i].m_ID == pMsg->m_ID)
					m_NetGuiEditBox.remove_index(i);
			}
			break;
		case NETMSGTYPE_SV_NETGUI_CHECKBOX:
			for(int i = 0; i < m_NetGuiCheckBox.size(); i++)
			{
				if(m_NetGuiCheckBox[i].m_ID == pMsg->m_ID)
					m_NetGuiCheckBox.remove_index(i);
			}
			break;
		}
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_REQUESTCONTENT)
	{
		CNetMsg_Sv_NetGui_RequestContent *pMsg = (CNetMsg_Sv_NetGui_RequestContent *)pRawMsg;
		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_EDITBOX:
		{
			int index = -1;
			for(int i = 0; i < m_NetGuiEditBox.size(); i++)
			{
				if(m_NetGuiEditBox[i].m_ID == pMsg->m_ID)
					index = i;
			}
			if(index >= 0)
			{
				CNetMsg_Cl_NetGui_EditBox_Content Reply;
				Reply.m_ID = pMsg->m_ID;
				Reply.m_Text = m_aNetGuiEditBoxContent[index];
				Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
			}
			else
				dbg_msg("NetGUI", "dropped wired EditBox_ContentRequest with index=%d", index);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_CHECKBOX:
			int index = -1;
			for(int i = 0; i < m_NetGuiCheckBox.size(); i++)
			{
				if(m_NetGuiCheckBox[i].m_ID == pMsg->m_ID)
					index = i;
			}
			if(index >= 0)
			{
				CNetMsg_Cl_NetGui_CheckBox_State Reply;
				Reply.m_ID = pMsg->m_ID;
				Reply.m_Checked = m_aNetGuiCheckBoxState[index];
				Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
			}
			else
				dbg_msg("NetGUI", "dropped wired CheckBox_ContentRequest with index=%d", index);
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
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_LABEL)
	{
		CNetMsg_Sv_NetGui_Label *pMsg = (CNetMsg_Sv_NetGui_Label *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_Label e;

		e.m_ID = pMsg->m_ID;
		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
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
		SortNetGuiList<CNetMsg_Sv_NetGui_Label>(m_NetGuiLabel);
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
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_EDITBOX)
	{
		CNetMsg_Sv_NetGui_EditBox *pMsg = (CNetMsg_Sv_NetGui_EditBox *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_EditBox e;

		e.m_ID = pMsg->m_ID;
		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Title);
		e.m_Title = aBuf;
		e.m_Dimension[0] = pMsg->m_Dimension[0];
		e.m_Dimension[1] = pMsg->m_Dimension[1];
		e.m_Dimension[2] = pMsg->m_Dimension[2];
		e.m_Dimension[3] = pMsg->m_Dimension[3];
		e.m_SplitValue = pMsg->m_SplitValue;
		e.m_MaxTextWidth = pMsg->m_MaxTextWidth;
		e.m_Password = pMsg->m_Password;

		// check for duplicated IDs and overwrite them
		if(m_NetGuiEditBox.size() > 1)
		{
			for(int i = 0; i < m_NetGuiEditBox.size(); i++)
			{
				if(m_NetGuiEditBox[i].m_ID == e.m_ID)
					m_NetGuiEditBox.remove_index(i);
			}
		}

		// save the element and resort the list
		m_NetGuiEditBox.add(e);
		SortNetGuiList<CNetMsg_Sv_NetGui_EditBox>(m_NetGuiEditBox);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_CHECKBOX)
	{
		CNetMsg_Sv_NetGui_CheckBox *pMsg = (CNetMsg_Sv_NetGui_CheckBox *)pRawMsg;

		// setup a new element for our list
		CNetMsg_Sv_NetGui_CheckBox e;

		e.m_ID = pMsg->m_ID;
		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Checked = pMsg->m_Checked;
		e.m_Dimension[0] = pMsg->m_Dimension[0];
		e.m_Dimension[1] = pMsg->m_Dimension[1];
		e.m_Dimension[2] = pMsg->m_Dimension[2];
		e.m_Dimension[3] = pMsg->m_Dimension[3];

		// check for duplicated IDs and overwrite them
		if(m_NetGuiCheckBox.size() > 1)
		{
			for(int i = 0; i < m_NetGuiCheckBox.size(); i++)
			{
				if(m_NetGuiCheckBox[i].m_ID == e.m_ID)
					m_NetGuiCheckBox.remove_index(i);
			}
		}

		// save the element and resort the list
		m_NetGuiCheckBox.add(e);
		SortNetGuiList<CNetMsg_Sv_NetGui_CheckBox>(m_NetGuiCheckBox);
	}
}
