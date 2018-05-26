#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>
#include <iostream>
#include <mathplot.h>

#include "wx/filedlg.h"

#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>
#include "interface.hpp"
enum
{
    ID_Sample = 1
};
enum
{
    ID_Step = 2
};
enum
{
    ID_Attenuator = 3
};
enum
{
    ID_Min = 4
};
enum
{
    ID_Max = 5
};
enum
{
    ID_Repeat = 6
};
enum
{
    ID_Name = 7
};
enum
{
    ID_Comment = 8
};
enum
{
    ID_RADIO_BOX = 9
};
enum
{
	ID_ON_DIALOG = 10
};

SettingsFrame::SettingsFrame()
    : wxFrame(NULL, wxID_ANY, "Settings", wxDefaultPosition, wxSize(700, 500))
{   
    CreateStatusBar();
	std::ifstream setfile("./Settings.txt");

    std::string input, temp;
    getline(setfile, input);
    wxStaticText *samplesnum = new wxStaticText(this, wxID_STATIC,
                             wxT("Number of samples per point"),
                              wxPoint(50, 50), wxSize(100, 50), wxTE_CENTRE);
    samperpoint = new wxTextCtrl(this, ID_Sample, wxEmptyString, wxPoint(50, 100),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    samperpoint->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *freqstep = new wxStaticText(this, wxID_STATIC,
                             wxT("Step of frequency"),
                              wxPoint(50, 150), wxSize(100, 50), wxTE_CENTRE);
    fstep = new wxTextCtrl(this, ID_Step, wxEmptyString, wxPoint(50, 200),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    fstep->ChangeValue(input); 
    getline(setfile, input);
    wxStaticText *attenuator = new wxStaticText(this, wxID_STATIC,
                             wxT("Attenuator"),
                              wxPoint(50, 250), wxSize(100, 50), wxTE_CENTRE);
    attfield = new wxTextCtrl(this, ID_Attenuator, wxEmptyString, wxPoint(50, 300),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER | wxTE_READONLY);
    attfield->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *minfreq = new wxStaticText(this, wxID_STATIC,
                             wxT("Minimum frequency"),
                              wxPoint(50, 350), wxSize(100, 50), wxTE_CENTRE);
    fmin  = new wxTextCtrl(this, ID_Min, wxEmptyString, wxPoint(50, 400),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    fmin->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *maxfreq = new wxStaticText(this, wxID_STATIC,
                             wxT("Maximum frequency"),
                              wxPoint(250, 50), wxSize(100, 50), wxTE_CENTRE);
    fmax = new wxTextCtrl(this, ID_Max, wxEmptyString , wxPoint(250, 100),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    fmax->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *repeats = new wxStaticText(this, wxID_STATIC,
                             wxT("Number of repeats"),
                              wxPoint(250, 150), wxSize(100, 50), wxTE_CENTRE);
    rep = new wxTextCtrl(this, ID_Repeat, wxEmptyString, wxPoint(250, 200),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    rep->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *curvename = new wxStaticText(this, wxID_STATIC,
                             wxT("Name of curve"),
                              wxPoint(250, 250), wxSize(100, 50), wxTE_CENTRE);
    curname = new wxTextCtrl(this, ID_Name, wxEmptyString, wxPoint(250, 300),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    curname->ChangeValue(input);
    getline(setfile, input);
    wxStaticText *comments = new wxStaticText(this, wxID_STATIC,
                             wxT("Commentaries"),
                              wxPoint(250, 350), wxSize(100, 50), wxTE_CENTRE);
    com = new wxTextCtrl(this, ID_Comment, wxEmptyString, wxPoint(250, 400),
                                wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
    com->ChangeValue(input);
    setfile.close();
    wxArrayString names, types;
    names.Add(wxT("OFF"));
    names.Add(wxT("ON"));
    types.Add(wxT("Linear"));

    attenuatortype = new wxRadioBox(this, ID_RADIO_BOX, wxT("Attenuator"), wxPoint(450, 250), wxSize(150, 80), names, 1, wxRA_SPECIFY_COLS);
    interpolationtype = new wxRadioBox(this, wxID_ANY, wxT("Interpolation types"), wxPoint(450, 50), wxSize(150, 50), types, 1, wxRA_SPECIFY_COLS);
    wxButton *filedialog = new wxButton(this, ID_ON_DIALOG, wxT("Choose calibration curve"), wxPoint(450, 400), wxSize(150, 50));
	    
    
    
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Sample_enter, this, ID_Sample);
    Bind(wxEVT_TEXT, &SettingsFrame::Text1_change, this, ID_Sample);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Step_enter, this, ID_Step);
    Bind(wxEVT_TEXT, &SettingsFrame::Text2_change, this, ID_Step);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Attenuator_enter, this, ID_Attenuator);
    Bind(wxEVT_TEXT, &SettingsFrame::Text3_change, this, ID_Attenuator);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Min_freq_enter, this, ID_Min);
    Bind(wxEVT_TEXT, &SettingsFrame::Text4_change, this, ID_Min);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Max_freq_enter, this, ID_Max);
    Bind(wxEVT_TEXT, &SettingsFrame::Text5_change, this, ID_Max);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Repeat_enter, this, ID_Repeat);
    Bind(wxEVT_TEXT, &SettingsFrame::Text6_change, this, ID_Repeat);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Name_enter, this, ID_Name);
    Bind(wxEVT_TEXT_ENTER, &SettingsFrame::Commentary_enter, this, ID_Comment);
    Bind(wxEVT_COMMAND_RADIOBOX_SELECTED, &SettingsFrame::Attenuator_change, this, ID_RADIO_BOX);
    Bind(wxEVT_COMMAND_BUTTON_CLICKED, &SettingsFrame::OnCurvePath, this, ID_ON_DIALOG);


}


void SettingsFrame::Text1_change(wxCommandEvent& event){
    wxString temp = samperpoint->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            samperpoint->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    } 
}
void SettingsFrame::Text2_change(wxCommandEvent& event){
    wxString temp = fstep->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            fstep->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void SettingsFrame::Text3_change(wxCommandEvent& event){
    wxString temp = attfield->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            attfield->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void SettingsFrame::Text4_change(wxCommandEvent& event){
    wxString temp = fmin->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            fmin->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void SettingsFrame::Text5_change(wxCommandEvent& event){
    wxString temp = fmax->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            fmax->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void SettingsFrame::Text6_change(wxCommandEvent& event){
    wxString temp = rep->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if ((input[i] < '0') || (input[i] > '9')){
            rep->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void SettingsFrame::Sample_enter(wxCommandEvent& event){
    
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 0){
    		output += input + '\n';
    	}
    	else{ 
    		output += samperpoint->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Step_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 1){
    		output += input + '\n';
    	}
    	else{ 
    		output += fstep->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Max_freq_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 4){
    		output += input + '\n';
    	}
    	else{ 
    		output += fmax->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Min_freq_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 3){
    		output += input + '\n';
    	}
    	else{ 
    		output += fmin->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Attenuator_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 2){
    		output += input + '\n';
    	}
    	else{ 
    		output += attfield->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Repeat_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 5){
    		output += input + '\n';
    	}
    	else{ 
    		output += rep->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Commentary_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 7){
    		output += input + '\n';
    	}
    	else{ 
    		output += com->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Name_enter(wxCommandEvent& event){
    std::ifstream getfile("Settings.txt");
    std::string input, output;
    int i = 0;
    while(getline(getfile, input)){
    	if(i != 6){
    		output += input + '\n';
    	}
    	else{ 
    		output += curname->GetValue() + '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
    setfile.close();
}
void SettingsFrame::Attenuator_change(wxCommandEvent& event){
	std::string input, output, temp;
	std::ifstream getfile("Settings.txt");
    int i = 0;
    while(getline(getfile, input)){
    	if (i == 2){
    		temp = input;
    	}
    	if(i != 9){
    		output += input + '\n';
    	}
    	else{ 
    		output += attenuatortype->GetSelection();
    		output += '\n';
    	}
    	++i;
    }
    getfile.close();
    std::ofstream setfile("Settings.txt");
    setfile << output;
	if (attenuatortype->GetSelection() == 0){
		attfield = new wxTextCtrl(this, ID_Attenuator, wxString(temp), wxPoint(50, 300),
        wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER | wxTE_READONLY);

	}
	else {
		attfield = new wxTextCtrl(this, ID_Attenuator, wxString(temp), wxPoint(50, 300),
        wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
	
	}
	setfile.close();
}
void SettingsFrame::OnCurvePath(wxCommandEvent& event){
	wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("*");
    wxString defaultDir = wxT("~");
    wxString defaultFilename = wxEmptyString;
    wxFileDialog *setpath = new wxFileDialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_OPEN);
    setpath->Show(true);
    if (setpath->ShowModal() == wxID_OK){
    	std::string input, output;
		std::ifstream getfile("Settings.txt");
	    int i = 0;
	    while(getline(getfile, input)){
	    	if(i != 8){
	    		output += input + '\n';
	    	}
	    	else{ 
	    		output += setpath->GetPath();
	    		output += '\n';
	    	}
	    	++i;
	    }
	    getfile.close();
	    std::ofstream setfile("Settings.txt");
	    setfile << output;
    }
}