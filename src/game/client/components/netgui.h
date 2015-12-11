#ifndef GAME_CLIENT_COMPONENTS_NETGUI_H
#define GAME_CLIENT_COMPONENTS_NETGUI_H

#include <base/tl/sorted_array.h>
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

	// Maxsort by Henritees, not the best one. Just to get stuff into correct render order.
	template<class T>
	void SortNetGuiList(array<T> &elem)
	{
		int num = elem.size();
		if(num < 2)
			return;
		int max = 0;
		T temp;
		for(int i = 0; i < num; i++)
		{
			max = i;
			for(int j = i; i < num; j++)
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

};

#endif
