#include "cApp.h"
#include "cMain.h"
wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}

cApp::~cApp() {

}

bool cApp::OnInit() {
	mFrame = new cMain();
	mFrame->Show();
	return true;
}