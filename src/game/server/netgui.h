// Copyright (c) 2015 Henritees

#ifndef GAME_SERVER_NETGUI_H
#define GAME_SERVER_NETGUI_H

#include <base/tl/array.h>
#include <game/server/gamecontroller.h>
#include <game/server/gamecontext.h>
#include <engine/shared/protocol.h>
#include <engine/server.h>

#include "player.h"

#define NETGUIMAGICNUMBER1 1883
#define NETGUIMAGICNUMBER2 5397

#define GUISET(name) void CreateGui_##name(int ClientID); void RemoveGui_##name(int ClientID);
#define GUIDEFINE(name, netmsgname, args...) \
		public: \
			void Do##name(int ClientID, int NetGuiElemID, vec4 Dimensions, args); \
		private: \
			array<CNetMsg_Sv_NetGui_##name> m_##name[MAX_CLIENTS]; public:

class CNetGui
{
	CGameContext *m_pGameServer;

	// methods for managing sets of GUIs
	GUISET(ExampleClosed)
	GUISET(Example1)
	GUISET(Example2)

public:
	CNetGui(CGameContext *pGameServer) : m_pGameServer(pGameServer){}
	void RemoveElement(int ClientID, int Type, int NetGuiElemID);

	void OnClientEnter(int ClientID);
	void OnClientDrop(int ClientID);
	void OnClientCompatible(int ClientID);
	void OnMessage(int MsgID, void *pRawMsg, int ClientID);

	bool IsNetGuiClient(int ClientID) { return m_NetGuiClients[ClientID]; }

	// // auto-generated declarations of functions
	#include <game/netguidefines.h>
	#undef GUIDEFINE

protected:
	CGameContext *GameServer() const { return m_pGameServer; }

private:
	bool m_NetGuiClients[MAX_CLIENTS]; // could have been put into CPlayer as well, but I want to keep stuff together

	template<class T>
	void SendNetGui(int ClientID, T Msg);
	void RequestData(int ClientID, int Type, int NetGuiElemID);


};

#endif
