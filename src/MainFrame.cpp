#include "MainFrame.h"

#include <wx/artprov.h>
#include <wx/clipbrd.h>

#include "OptionPanel.h"
#include "RobocopyHandler.h"

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
	rcpCommandText->Disable();

	clipBtn = new wxBitmapButton(
			this, wxID_ANY,
			wxArtProvider::GetBitmap(wxART_COPY, wxART_BUTTON),
			wxDefaultPosition,
			wxDefaultSize
		);
	clipBtn->SetToolTip("Copy robocopy command");

	rcpRunBtn = new wxButton(
			this,
			ID_Run_Button,
			"Run Robocopy"
		);
	rcpRunBtn->Disable();

	rcpStopBtn = new wxButton(
			this,
			ID_Run_Button,
			"Abort"
		);
	rcpStopBtn->Hide();

	rcpOutput = new wxTextCtrl(
			this,
			wxID_ANY,
			"",
			wxDefaultPosition,
			wxDefaultSize,
			wxTE_MULTILINE | wxTE_READONLY
		);
	rcpOutput->Hide();
	
	rcpHandler = new RobocopyHandler(this, rcpOutput);	
	
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
	sizer->Add(commandSizer, 0, wxALL | wxEXPAND);
	sizer->Add(rcpRunBtn, 0, wxALL | wxEXPAND, 5);
	sizer->Add(rcpStopBtn, 0, wxALL | wxEXPAND, 5);
	sizer->Add(rcpOutput, 1, wxALL | wxEXPAND, 5);
	
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
	Bind(rcEVT_THREAD_STARTED, &MainFrame::OnRcpThreadStarted, this);
	Bind(rcEVT_THREAD_STOPPED, &MainFrame::OnRcpThreadStopped, this);

	srcDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::OnSrcDirPicked, this);
	dstDirPicker->Bind(wxEVT_DIRPICKER_CHANGED, &MainFrame::OnDstDirPicked, this);
	clipBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRcpCommandCopyClicked, this);
	rcpRunBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRcpRunBtnClicked, this);
	rcpStopBtn->Bind(wxEVT_BUTTON, &MainFrame::OnRcpStopBtnClicked, this);
	
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
	const wxString cmd = GenerateRobocopyCmd();
	
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

void MainFrame::OnRcpRunBtnClicked(wxCommandEvent& e)
{
	if(!rcpHandler)
		return;

	const wxString cmd = GenerateRobocopyCmd();
	rcpOutput->Clear();
	rcpHandler->Execute(cmd);
}

void MainFrame::OnRcpStopBtnClicked(wxCommandEvent& e)
{
	if(!rcpHandler)
		return;

	rcpHandler->Stop();
}

void MainFrame::OnRcpThreadStarted(wxCommandEvent& e)
{
	SetStatusText("Running...");
	rcpRunBtn->Disable();
	rcpStopBtn->Show();
	rcpOutput->Show();
	Layout();
}

void MainFrame::OnRcpThreadStopped(wxCommandEvent& e)
{
	SetStatusText("Ready");
	rcpStopBtn->Hide();
	rcpRunBtn->Enable();
	Layout();
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

	// If command is not empty, then enable the robocopy button
	if(!command.IsEmpty())
		rcpRunBtn->Enable();

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
