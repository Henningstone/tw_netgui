#ifndef GAME_NETGUI_H
#define GAME_NETGUI_H

#include <base/tl/sorted_array.h>
#include <game/server/gamecontext.h>
#include <game/server/gamecontroller.h>
#include <generated/protocol.h>

class CNetGui
{
	enum
	{
		e_UIRect = 0,
		e_Label,
	};

	class CGameContext *m_pGameServer;

public:
	CNetGui(CGameContext *pGameServer) { m_pGameServer = pGameServer; }
	void RemoveElement(int ClientID, int Type, int NetGuiElemID);
	void UIRect(int ClientID, int NetGuiElemID, vec4 Dimensions, vec4 Color, int Corner, int RoundingX10);
	void Label(int ClientID, int NetGuiElemID, const char *pText, vec2 Pos, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth);
	void ButtonMenu(int ClientID, int NetGuiElemID, const char *pText, int Checked, vec4 Dimensions);

protected:
	CGameContext *GameServer() const { return m_pGameServer; }

private:
	array<CNetMsg_Sv_NetGui_UIRect> m_UIRect;
	array<CNetMsg_Sv_NetGui_Label> m_Label;
public:	array<CNetMsg_Sv_NetGui_ButtonMenu> m_ButtonMenu; private:

};

#endif
