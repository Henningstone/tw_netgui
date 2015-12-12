#ifndef GAME_CLIENT_COMPONENTS_NETGUI_H
#define GAME_CLIENT_COMPONENTS_NETGUI_H

#include <base/tl/array.h>
#include <generated/protocol.h>
#include <game/client/component.h>

class CNetGui : public CComponent
{
	virtual void OnReset();
	virtual void OnMessage(int MsgId, void *pRawMsg);

public:
	array<CNetMsg_Sv_NetGui_UIRect> m_NetGuiUIRect;
	array<CNetMsg_Sv_NetGui_Label> m_NetGuiLabel;
	array<CNetMsg_Sv_NetGui_ButtonMenu> m_NetGuiButtonMenu;

	// Minsort by Henritees, not the best one. Just to get stuff into correct render order.
	template<class T>
	void SortNetGuiList(array<T> &elem)
	{
		int num = elem.size();
		if(num < 2)
			return;
		int min = 0;
		T temp;
		for(int i = 0; i < num; i++)
		{
			min = i;
			for(int j = i; j < num; j++)
			{
				if(elem[i].m_ID > elem[min].m_ID)
					min = i;
			}

			if(min == i)
				continue;
			temp = elem[i];
			elem[i] = elem[min];
			elem[min] = temp;
		}
	}

};

#endif
