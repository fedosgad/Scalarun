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
    ID_Frequency = 1
};

AmplitudeFrame::AmplitudeFrame()
   : wxFrame(NULL, wxID_ANY, "Amplitude")
	{
	wxStaticText *freqtitle = new wxStaticText(this, wxID_STATIC,
	                         wxT("Enter amplitude"),
	                          wxPoint(50, 50), wxSize(100, 50), wxTE_CENTRE);
	frequency = new wxTextCtrl(this, ID_Frequency, "100", wxPoint(50, 100),
	                            wxSize(100, 50), wxTE_CENTRE | wxTE_PROCESS_ENTER);
	response = new wxStaticText(this, wxID_STATIC,
                             wxT(" "),
                              wxPoint(50, 100), wxSize(100, 50), wxTE_CENTRE);
    
	CreateStatusBar();
	Bind(wxEVT_TEXT_ENTER, &AmplitudeFrame::Frequency_enter, this, ID_Frequency);
	Bind(wxEVT_TEXT, &AmplitudeFrame::Input_control, this, ID_Frequency);

	}

void AmplitudeFrame::Input_control(wxCommandEvent& event){
    wxString temp = frequency->GetValue();
    std::string input = std::string(temp.mb_str());
    for (int i = 0; i < input.length(); ++i){
        if (((input[i] < '0') || (input[i] > '9')) && (input[i] != '.')){
            frequency->Clear();
            SetStatusText("Please, enter number");
            break;
        }
        else {
            SetStatusText(" ");
        }
    }
}
void AmplitudeFrame::Frequency_enter(wxCommandEvent& event){
	unsigned int i = 0;
	std::string input = std::string((frequency->GetValue()).mb_str());
	double num = std::stod(input);
	while((i < xes.size()) && (xes[i] < num) ){
		++i;
	}
	if((i == 0) || (i == xes.size())){
		delete response;
		response = new wxStaticText(this, wxID_STATIC,
                             wxT("No data"),
                              wxPoint(50, 200), wxSize(100, 50), wxTE_CENTRE);
	}
	else {
		double amp = (yes[i] - yes[i - 1])/(xes[i] - xes[i - 1])*(num - xes[i - 1]) + yes[i - 1];
		std::string a = std::to_string(amp);
		delete response;
		response = new wxStaticText(this, wxID_STATIC,
                             a,
                              wxPoint(50, 200), wxSize(100, 50), wxTE_CENTRE);

	}
}