// Copyright (c) 2015 Henritees
#ifndef GAME_NETGUIDEFINES_H
#define GAME_NETGUIDEFINES_H
#undef GAME_NETGUIDEFINES_H // this file will be included several times

#ifdef GUIDEFINE
GUIDEFINE(UIRect, UIRECT, vec4 Color, int Corner, float Rounding);
GUIDEFINE(Label, LABEL, const char *pText, vec4 Color, int FontSize, int FontAlign, int MaxTextWidth);
GUIDEFINE(ButtonMenu, BUTTONMENU, const char *pText, bool Selected);
GUIDEFINE(EditBox, EDITBOX, const char *pTitle, int SplitValue, int MaxTextWidth, bool Password);
GUIDEFINE(CheckBox, CHECKBOX, const char *pText, bool Checked);
GUIDEFINE(CheckBoxNumber, CHECKBOXNUMBER, const char *pText, int MinValue, int MaxValue, int StepValue);
GUIDEFINE(Scrollbar, SCROLLBAR, bool Vertical = false);
GUIDEFINE(ScrollbarOption, SCROLLBAROPTION, const char *pText, float VSplitVal, int Min, int Max, bool Infinite);
GUIDEFINE(InfoBox, INFOBOX, const char *pLabel, const char* pValue);
GUIDEFINE(ListboxHeader, LISTBOXHEADER, const char *pTitle, float Height, float Spacing);
GUIDEFINE(ListboxStart, LISTBOXSTART, const char *pBottomText, float RowHeight, int ItemsPerRow, int SelectedIndex, int HeaderID=-1, bool Background=true);
#endif

#endif
