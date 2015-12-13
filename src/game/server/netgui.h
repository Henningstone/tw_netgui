// Copyright (c) 2015 Henritees

#ifndef GAME_SERVER_NETGUI_H
#define GAME_SERVER_NETGUI_H

#include <base/tl/array.h>
#include <game/server/gamecontroller.h>
#include <game/server/gamecontext.h>
#include <engine/shared/protocol.h>
#include <engine/server.h>
#include <generated/protocol.h>

#include "player.h"

#define GUISET(name) void CreateGui_##name(int ClientID); void RemoveGui_##name(int ClientID);

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
	void UIRect(int ClientID, int NetGuiElemID, vec4 Dimensions, vec4 Color, int Corner, int RoundingX10);
	void Label(int ClientID, int NetGuiElemID, const char *pText, vec4 Dimensions, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth);
	void ButtonMenu(int ClientID, int NetGuiElemID, const char *pText, int Checked, vec4 Dimensions);

	void OnClientEnter(int ClientID);
	void OnClientDrop(int ClientID); // nah
	void OnMessage(int MsgID, void *pRawMsg, int ClientID);

	array<CNetMsg_Sv_NetGui_ButtonMenu> &GetButtonMenu(int ClientID) { return m_ButtonMenu[ClientID]; }

protected:
	CGameContext *GameServer() const { return m_pGameServer; }

private:
	array<CNetMsg_Sv_NetGui_UIRect> m_UIRect[MAX_CLIENTS];
	array<CNetMsg_Sv_NetGui_Label> m_Label[MAX_CLIENTS];
	array<CNetMsg_Sv_NetGui_ButtonMenu> m_ButtonMenu[MAX_CLIENTS];

};

#endif
