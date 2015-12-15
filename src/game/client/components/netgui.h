// Copyright (c) 2015 Henritees

#ifndef GAME_CLIENT_COMPONENTS_NETGUI_H
#define GAME_CLIENT_COMPONENTS_NETGUI_H

#include <base/tl/array.h>
#include <game/client/component.h>

class CNetGui : public CComponent
{
	virtual void OnReset();
	virtual void OnMessage(int MsgId, void *pRawMsg);

public:
	array<CNetMsg_Sv_NetGui_UIRect> m_NetGuiUIRect;
	array<CNetMsg_Sv_NetGui_Label> m_NetGuiLabel;
	array<CNetMsg_Sv_NetGui_ButtonMenu> m_NetGuiButtonMenu;
	array<CNetMsg_Sv_NetGui_EditBox> m_NetGuiEditBox;
	array<CNetMsg_Sv_NetGui_CheckBox> m_NetGuiCheckBox;
	array<CNetMsg_Sv_NetGui_CheckBoxNumber> m_NetGuiCheckBoxNumber;
	char m_aNetGuiEditBoxContent[1024][1024]; // necessary because it cannot be stored into the NetMsg (CONST char...)

	// maxsort to get stuff into correct render order.
	template<class T>
	void SortNetGuiList(array<T> &elem)
	{
		int num = elem.size();
		if(num < 2)
			return;
		int max = 0;
		T temp;
		for(int i = 0; i < max; i++)
		{
			max = i;
			for(int j = i; j < num; j++)
			{
				if(elem[i].m_ID > elem[max].m_ID)
					max = i;
			}

			if(max == i)
				continue;
			temp = elem[i];
			elem[i] = elem[max];
			elem[max] = temp;
		}
	}

	template<class T>
	void NetGui_ButtonPressed(int NetGuiElementID)
	{
		T Msg;
		Msg.m_ID = NetGuiElementID;
		Client()->SendPackMsg(&Msg, MSGFLAG_VITAL);
	}

};

#endif
