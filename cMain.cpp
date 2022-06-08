#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, ButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MINESWEEPER", wxPoint(400, 100), wxSize(960, 760)) {
	button = new wxButton* [gridWidth * gridHeight];
	wxGridSizer* grid = new wxGridSizer(gridWidth, gridHeight, 0, 0);

	mineField = new int[gridWidth * gridHeight];

	for (int x = 0; x < gridWidth; x++) {
		for (int y = 0; y < gridHeight; y++) {
			button[y * gridWidth + x] = new wxButton(this, 10000 + (y * gridWidth + x));
			grid->Add(button[y * gridWidth + x], 1, wxEXPAND | wxALL);

			button[y * gridWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::ButtonClicked, this);
			mineField[y * gridWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}
cMain::~cMain() {

}
void cMain::ButtonClicked(wxCommandEvent& event) {
	// get coordinate of button clicked
	int x = (event.GetId() - 10000) % gridWidth;
	int y = (event.GetId() - 10000) / gridWidth;

	if (firstClick == true) {
		int mines = 30;
		while (mines) {
			int randx = rand() % gridWidth;
			int randy = rand() % gridHeight;
			if (mineField[randy * gridWidth + randx] == 0 && randx != x && randy != y) {

			}
		}
	}
	event.Skip();
}
