#pragma once
#include "wx/wx.h"
class cMain : public wxFrame
{
public:
	cMain();
	~cMain();
public:
	int gridWidth = 10;
	int gridHeight = 10;
	wxButton** button;
	int* mineField = nullptr;
	bool firstClick = true;

	void ButtonClicked(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

