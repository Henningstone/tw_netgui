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
	// automatically make a storage array for everything
	#define GUIDEFINE(name, netmsgname, args...) array<CNetMsg_Sv_NetGui_##name> m_NetGui##name;
	#include <game/netguidefines.h>
	#undef GUIDEFINE

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

	void SendEvent(int Type, int NetGuiElementID)
	{
		CNetMsg_Cl_NetGui_TriggerEvent Msg;
		Msg.m_Type = Type;
		Msg.m_ID = NetGuiElementID;
		Client()->SendPackMsg(&Msg, MSGFLAG_VITAL);
	}

};

#endif
