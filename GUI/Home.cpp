#include "Home.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUI::Home form;
	Application::Run(%form);
}

System::Void GUI::Home::asterixPosText_TextChanged(System::Object^  sender, System::EventArgs^  e) {



}

void GUI::Home::toggleMainUIElements() {

	this->asterixPosText->Enabled = !this->asterixPosText->Enabled;
	this->asterixPosSet->Enabled = !this->asterixPosSet->Enabled;
	// this->asterixAltText->Enabled = !this->asterixAltText->Enabled;
	// this->asterixAltSet->Enabled = !this->asterixAltSet->Enabled;

	this->obelixPosText->Enabled = !this->obelixPosText->Enabled;
	this->obelixPosSet->Enabled = !this->obelixPosSet->Enabled;
	// this->obelixAltText->Enabled = !this->obelixAltText->Enabled;
	// this->obelixAltSet->Enabled = !this->obelixAltSet->Enabled;

	this->idefixPosText->Enabled = !this->idefixPosText->Enabled;
	this->idefixPosSet->Enabled = !this->idefixPosSet->Enabled;
	// this->idefixAltText->Enabled = !this->idefixAltText->Enabled;
	// this->idefixAltSet->Enabled = !this->idefixAltSet->Enabled;

}