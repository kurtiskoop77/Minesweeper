#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, ButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MINESWEEPER", wxPoint(400, 100), wxSize(960, 760)) {
	button = new wxButton* [gridWidth * gridHeight];
	wxGridSizer* grid = new wxGridSizer(gridWidth, gridHeight, 0, 0);

	mineField = new int[gridWidth * gridHeight];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
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
				mineField[randy * gridWidth + randy] = -1;
				mines--;
			}
		}
		firstClick = false;
	}
	//Disable Button
	button[y * gridWidth + x]->Enable(false);
	if (mineField[y * gridWidth + x] == -1) {
		wxMessageBox("KABOOM!!!! - GAME OVER");

		//reset game
		firstClick = true;
		for (int x = 0; x < gridWidth; x++) {
			for (int y = 0; y < gridWidth; y++) {
				mineField[y * gridWidth + x] = 0;
				button[y * gridWidth + x]->SetLabel("");
				button[y * gridWidth + x]->Enable(true);
			}
		}
	}
	else {
		//count neighboring mines
		int mCount = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight) {
					if (mineField[(y + j) * gridWidth + (x + i)] == -1) {
						mCount++;
					}
				}
			}
		}

		//update button label to show mine count if > 0
		if (mCount > 0) {
			button[y * gridWidth + x]->SetLabel(std::to_string(mCount));
		}
	}
	event.Skip();
}
