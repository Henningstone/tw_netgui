// Copyright (c) 2015 Henritees

#include "netgui.h"

#define GUI_BUILDRESPONSE(name, type) \
		int index = -1;\
		for(int i = 0; i < m_NetGui##name.size(); i++)\
		{\
			if(m_NetGui##name[i].m_ID == pMsg->m_ID)\
				index = i;\
		}\
		if(index < 0)\
			break;\
		CNetMsg_Cl_NetGui_Response##type Reply;\
		Reply.m_ID = pMsg->m_ID;\
		Reply.m_Type = pMsg->m_Type

#define GUIRECEIVE_INIT(name) \
		CNetMsg_Sv_NetGui_##name *pMsg = (CNetMsg_Sv_NetGui_##name *)pRawMsg;\
		CNetMsg_Sv_NetGui_##name e;\
		e.m_ID = pMsg->m_ID;\
		e.m_Dimension[0] = pMsg->m_Dimension[0];\
		e.m_Dimension[1] = pMsg->m_Dimension[1];\
		e.m_Dimension[2] = pMsg->m_Dimension[2];\
		e.m_Dimension[3] = pMsg->m_Dimension[3]

#define GUIRECEIVE_FINALIZE(name) \
		if(m_NetGui##name.size() > 1)\
		{\
			for(int i = 0; i < m_NetGui##name.size(); i++)\
			{\
				if(m_NetGui##name[i].m_ID == e.m_ID)\
					m_NetGui##name.remove_index(i);\
			}\
		}\
		m_NetGui##name.add(e);\
		SortNetGuiList<CNetMsg_Sv_NetGui_##name>(m_NetGui##name)


void CNetGui::OnReset()
{
	// auto-generated clear's
	#define GUIDEFINE(name, netmsgname, args...) m_NetGui##name.clear();
	#include <game/netguidefines.h>
	#undef GUIDEFINE
}

void CNetGui::OnMessage(int MsgId, void *pRawMsg)
{
	if(MsgId == NETMSGTYPE_SV_NETGUI_REMOVEELEMENT)
	{
		CNetMsg_Sv_NetGui_RemoveElement *pMsg = (CNetMsg_Sv_NetGui_RemoveElement *)pRawMsg;

		// remove handler; the "args..." thingy is just for compatiblity and will be dropped
		#define GUIDEFINE(name, netmsgname, args...) \
			case NETMSGTYPE_SV_NETGUI_##netmsgname: \
				for(int i = 0; i < m_NetGui##name.size(); i++) \
				{ \
					if(m_NetGui##name[i].m_ID == pMsg->m_ID) \
						m_NetGui##name.remove_index(i); \
				} \
				break;

		switch(pMsg->m_Type)
		{
			// auto-generated remove handlers
			#include <game/netguidefines.h>
			#undef GUIDEFINE
		}
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_REQUESTDATA)
	{
		CNetMsg_Sv_NetGui_RequestData *pMsg = (CNetMsg_Sv_NetGui_RequestData *)pRawMsg;
		switch(pMsg->m_Type)
		{
		case NETMSGTYPE_SV_NETGUI_EDITBOX:
		{
			GUI_BUILDRESPONSE(EditBox, String);
			Reply.m_Text = m_aNetGuiEditBoxContent[index];
			Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_CHECKBOX:
		{
			GUI_BUILDRESPONSE(CheckBox, Int);
			Reply.m_Value = m_NetGuiCheckBox[index].m_Checked;
			Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_CHECKBOXNUMBER:
		{
			GUI_BUILDRESPONSE(CheckBoxNumber, Int);
			Reply.m_Value = m_NetGuiCheckBoxNumber[index].m_Value;
			Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_SCROLLBAR:
		{
			GUI_BUILDRESPONSE(Scrollbar, Int);
			Reply.m_Value = m_NetGuiScrollbar[index].m_ValueX100;
			Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
		}
		break;
		case NETMSGTYPE_SV_NETGUI_SCROLLBAROPTION:
		{
			GUI_BUILDRESPONSE(ScrollbarOption, Int);
			Reply.m_Value = m_NetGuiScrollbarOption[index].m_Value;
			Client()->SendPackMsg(&Reply, MSGFLAG_VITAL);
		}
		break;

		}
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_UIRECT)
	{
		GUIRECEIVE_INIT(UIRect);

		e.m_Color[0] = pMsg->m_Color[0];
		e.m_Color[1] = pMsg->m_Color[1];
		e.m_Color[2] = pMsg->m_Color[2];
		e.m_Color[3] = pMsg->m_Color[3];
		e.m_Corner = pMsg->m_Corner;
		e.m_RoundingX10 = pMsg->m_RoundingX10;

		GUIRECEIVE_FINALIZE(UIRect);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_LABEL)
	{
		GUIRECEIVE_INIT(Label);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Color[0] = pMsg->m_Color[0];
		e.m_Color[1] = pMsg->m_Color[1];
		e.m_Color[2] = pMsg->m_Color[2];
		e.m_Color[3] = pMsg->m_Color[3];
		e.m_FontSize = pMsg->m_FontSize;
		e.m_FontAlign = pMsg->m_FontAlign;

		GUIRECEIVE_FINALIZE(Label);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_BUTTONMENU)
	{
		GUIRECEIVE_INIT(ButtonMenu);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Selected = pMsg->m_Selected;

		GUIRECEIVE_FINALIZE(ButtonMenu);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_EDITBOX)
	{
		GUIRECEIVE_INIT(EditBox);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Title);
		e.m_Title = aBuf;
		e.m_SplitValue = pMsg->m_SplitValue;
		e.m_MaxTextWidth = pMsg->m_MaxTextWidth;
		e.m_Password = pMsg->m_Password;

		GUIRECEIVE_FINALIZE(EditBox);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_CHECKBOX)
	{
		GUIRECEIVE_INIT(CheckBox);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Checked = pMsg->m_Checked;

		GUIRECEIVE_FINALIZE(CheckBox);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_CHECKBOXNUMBER)
	{
		GUIRECEIVE_INIT(CheckBoxNumber);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Value = pMsg->m_Value;
		e.m_MinValue = pMsg->m_MinValue;
		e.m_MaxValue = pMsg->m_MaxValue;
		e.m_StepValue = pMsg->m_StepValue;

		GUIRECEIVE_FINALIZE(CheckBoxNumber);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_SCROLLBAR)
	{
		GUIRECEIVE_INIT(Scrollbar);
		GUIRECEIVE_FINALIZE(Scrollbar);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_SCROLLBAROPTION)
	{
		GUIRECEIVE_INIT(ScrollbarOption);

		char* aBuf = (char*)mem_alloc(512, 0);
		str_format(aBuf, 512, "%s", pMsg->m_Text);
		e.m_Text = aBuf;
		e.m_Value = pMsg->m_Value;
		e.m_MinValue = pMsg->m_MinValue;
		e.m_MaxValue = pMsg->m_MaxValue;
		e.m_VSplitValX10 = pMsg->m_VSplitValX10;

		GUIRECEIVE_FINALIZE(ScrollbarOption);
	}
	else if(MsgId == NETMSGTYPE_SV_NETGUI_INFOBOX)
	{
		GUIRECEIVE_INIT(InfoBox);

		char* aBufLabel = (char*)mem_alloc(512, 0);
		str_format(aBufLabel, 512, "%s", pMsg->m_Label);
		e.m_Label = aBufLabel;
		char* aBufValue = (char*)mem_alloc(512, 0);
		str_format(aBufValue, 512, "%s", pMsg->m_Value);
		e.m_Value = aBufValue;

		GUIRECEIVE_FINALIZE(InfoBox);
	}
}
