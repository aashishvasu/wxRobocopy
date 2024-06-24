#include "MainFrame.h"

#include <wx/artprov.h>
#include <wx/clipbrd.h>

#include "OptionPanel.h"
#include "data/Enums.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition)
{
	SetBackgroundColour(wxNullColour);
	
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_About, "&About...\tCtrl-A", "Show about dialog");
	menuFile->AppendSeparator();
	menuFile->Append(ID_Quit, "E&xit\tAlt-X", "Quit this program");

	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(menuFile, "&File");

	wxStaticText *srcLabel = new wxStaticText(
			this,
			wxID_ANY,
			"Source"
		);

	wxStaticText *dstLabel = new wxStaticText(
			this,
			wxID_ANY,
			"Target"
		);

	srcDirPicker = new wxDirPickerCtrl(
			this,
			wxID_ANY,
			wxEmptyString,
			"Source",
			wxDefaultPosition,
			wxDefaultSize,
			wxDIRP_DEFAULT_STYLE | wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST,
			wxDefaultValidator,
			"Source"
		);
	dstDirPicker = new wxDirPickerCtrl(
			this,
			wxID_ANY,
			wxEmptyString,
			"Target",
			wxDefaultPosition,
			wxDefaultSize,
			wxDIRP_DEFAULT_STYLE | wxDIRP_USE_TEXTCTRL | wxDIRP_DIR_MUST_EXIST,
			wxDefaultValidator,
			"Target"
		);

	optPanel = new OptionPanel(this);

	rcpCommandText = new wxTextCtrl(
			this,
			wxID_ANY,
			wxEmptyString,
			wxDefaultPosition,
			wxDefaultSize,
			wxTE_READONLY
		);

	clipBtn = new wxBitmapButton(
			this, wxID_ANY,
			wxArtProvider::GetBitmap(wxART_COPY, wxART_BUTTON),
			wxDefaultPosition,
			wxDefaultSize
		);
	clipBtn->SetToolTip("Copy robocopy command");
	
	// Layout nested sizers
	// Flex grid for the source and target pickers
	wxFlexGridSizer *fileSizer = new wxFlexGridSizer(2, 2, wxDefaultSize);
	fileSizer->Add(srcLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	fileSizer->Add(srcDirPicker, 0, wxALL | wxEXPAND, 5);
	fileSizer->Add(dstLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
	fileSizer->Add(dstDirPicker, 0, wxALL | wxEXPAND, 5);
	fileSizer->AddGrowableCol(1, 1);

	// Static box sizer for file locations
	wxStaticBoxSizer *fileBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, "Folders");
	fileBoxSizer->Add(fileSizer, 0, wxALL | wxEXPAND);

	wxFlexGridSizer* commandSizer = new wxFlexGridSizer(1, 2, wxDefaultSize);
	commandSizer->Add(rcpCommandText, 0, wxALL | wxEXPAND, 5);
	commandSizer->Add(clipBtn, 0, wxALL | wxEXPAND, 5);
	commandSizer->AddGrowableCol(0, 1);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(fileBoxSizer, 0, wxALL | wxEXPAND, 5);
	sizer->Add(optPanel, 0, wxALL | wxEXPAND);
	sizer->Add(commandSizer, 0, wxALL | wxEXPAND, 5);
	
	SetSizer(sizer);

	SetMenuBar(menuBar);

	CreateStatusBar(2);
	SetStatusText("Ready");

	BindEvents();
}

void MainFrame::BindEvents()
{
	Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID_Quit);
	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, ID_About);
	Bind(rcEVT_OPTIONS_UPDATED, &MainFrame::OnOptionsChanged, this);

	srcDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::OnSrcDirPicked, this);
	dstDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::OnDstDirPicked, this);
	clipBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRcpCommandCopyClicked, this);
}

void MainFrame::OnSrcDirPicked(wxFileDirPickerEvent& e)
{
	(void)GenerateRobocopyCmd();
}

void MainFrame::OnDstDirPicked(wxFileDirPickerEvent& e)
{
	(void)GenerateRobocopyCmd();
}

void MainFrame::OnOptionsChanged(wxCommandEvent& e)
{
	(void)GenerateRobocopyCmd();
}

void MainFrame::OnRcpCommandCopyClicked(wxCommandEvent& e)
{
	wxString cmd = GenerateRobocopyCmd();
	
	// Here we will add the robocopy command to the OS clipboard
	if(cmd.IsEmpty())
		return;

	// Open clipboard and add data
	if (wxTheClipboard->Open())
	{
		wxTheClipboard->SetData( new wxTextDataObject(cmd) );
		wxTheClipboard->Close();
	}
}

wxString MainFrame::GenerateRobocopyCmd() const
{
	// Here we parse all relevant information into a robocopy command
	wxString src = srcDirPicker->GetPath();
	wxString dst = dstDirPicker->GetPath();

	// If source or destination is empty, then we can ignore
	if(src.IsEmpty() || dst.IsEmpty())
	{
		return wxEmptyString;
	}

	// Get relevant arguments from each option
	const wxString command = "robocopy " + wxString::Format("%s %s %s", src, dst, optPanel->GetOptions());

	rcpCommandText->SetValue(command);

	return command;
}

void MainFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("This is a wxWidgets Hello World example","About Hello World", wxOK | wxICON_INFORMATION, this);
}
