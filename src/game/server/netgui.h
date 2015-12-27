// Copyright (c) 2015 Henritees

#ifndef GAME_SERVER_NETGUI_H
#define GAME_SERVER_NETGUI_H

#include <base/tl/array.h>
#include <base/tl/sorted_array.h>
#include <game/server/gamecontroller.h>
#include <game/server/gamecontext.h>
#include <engine/shared/protocol.h>
#include <engine/server.h>

#include "player.h"

#define GUISET(name, id) void CreateGui_##name(int ClientID, int GuiID=id); void RemoveGui_##name(int ClientID, int GuiID=id);\
		enum { GUIID_##name = id };
#define GUIDEFINE(name, netmsgname, args...) \
		public: \
			void Do##name(int ClientID, int NetGuiElemID, vec4 Dimensions, args); \
		private: \
			array<CNetMsg_Sv_NetGui_##name> m_##name[MAX_CLIENTS]; public:

class CNetGui
{
	CGameContext *m_pGameServer;

	// methods for managing sets of GUIs
	GUISET(ExampleClosed,1)
	GUISET(Example1, 2)
	GUISET(Example2, 4)

public:
	CNetGui(CGameContext *pGameServer) : m_pGameServer(pGameServer) { m_ActiveGuis = 0; }
	void RemoveElement(int ClientID, int Type, int NetGuiElemID);

	void OnClientEnter(int ClientID);
	void OnClientDrop(int ClientID);
	void OnMessage(int MsgID, void *pRawMsg, int ClientID);

	void ListboxItemAdd(int ClientID, int ListboxStartID, int ItemID, const char *pText);
	void ListboxItemRemove(int ClientID, int ListboxID, int ItemID);
	const char *ListboxItemGetText(int ClientID, int ListboxID, int ItemID) { return m_ListboxItems[ClientID][clamp(ListboxID, 0, 1024)][clamp(ItemID, 0, m_ListboxItems[ClientID][clamp(ListboxID, 0, 1024)].size())].m_pText; }
	int ListboxItemsNum(int ClientID, int ListboxID) { return m_ListboxItems[ClientID][ListboxID].size(); }

	// auto-generated declarations of functions
	#include <game/netguidefines.h>
	#undef GUIDEFINE

	bool GuiActive(int GuiID) { return (m_ActiveGuis & GuiID) != 0; }

protected:
	CGameContext *GameServer() const { return m_pGameServer; }

private:

	struct CNetGuiListboxItem
	{
		CNetGuiListboxItem(int ListboxID, int ID, const char* pText) : m_ListboxID(ListboxID), m_ID(ID), m_pText(pText) {};
		CNetGuiListboxItem(){};
		bool operator<(const CNetGuiListboxItem &Other) { return m_ID < Other.m_ID; }
		int m_ListboxID;
		int m_ID;
		const char *m_pText;
	};

	sorted_array<CNetGuiListboxItem> m_ListboxItems[MAX_CLIENTS][1024]; // 1024 -> every listbox has it's own list of elements
	int m_ActiveGuis;

	template<class T>
	void SendNetGui(int ClientID, T Msg);
	void RequestData(int ClientID, int Type, int NetGuiElemID);


};

#endif
