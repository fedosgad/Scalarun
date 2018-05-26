//header
#pragma once
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
#include <fstream>
#include "wx/filedlg.h"

#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>

extern std::vector<double> xes, yes;


struct settings{
	int sample, step, max_freq, min_freq, attenuator, repeat;
	std::string name, comment, path;
	bool is_attenuator;
} typedef;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};
class MyFrame : public wxFrame
{
public:
    MyFrame();
    wxFrame *SettingFrame = NULL, *Amplitude = NULL;
    mpWindow *plot;
    mpFXYVector *lay;
    bool is_set = false;
    settings setting;
    wxString pathtoplot;
private:
    void OnExit(wxCommandEvent& event);
//    void OnButtonUP(wxCommandEvent& event);
//    void OnButtonDOWN(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSettings(wxCommandEvent& event);
    void OnDefautSettings(wxCommandEvent& event);
    void OnGet(wxCommandEvent& event);
    void OnAmplitude(wxCommandEvent& event);
    void OnCalibration(wxCommandEvent& event);
};
class SettingsFrame : public wxFrame
{
public:
    SettingsFrame();
    wxRadioBox *attenuatortype, *interpolationtype;
    wxTextCtrl *samperpoint, *fstep, *attfield, *fmin, *fmax, *rep, *curname, *com;
    wxString *pathtocurve;
private:
    void Sample_enter(wxCommandEvent& event);
    void Step_enter(wxCommandEvent& event);
    void Max_freq_enter(wxCommandEvent& event);
    void Min_freq_enter(wxCommandEvent& event);
    void Attenuator_enter(wxCommandEvent& event);
    void Repeat_enter(wxCommandEvent& event);
    void Commentary_enter(wxCommandEvent& event);
    void Name_enter(wxCommandEvent& event);
    void Onchangedirectory(wxCommandEvent& event);
    void Attenuatorturn(wxCommandEvent& event);
    void Attenuator_change(wxCommandEvent& event);
    void Text1_change(wxCommandEvent& event);
    void Text2_change(wxCommandEvent& event);
    void Text3_change(wxCommandEvent& event);
    void Text4_change(wxCommandEvent& event);
    void Text5_change(wxCommandEvent& event);
    void Text6_change(wxCommandEvent& event);
    void OnCurvePath(wxCommandEvent& event);
};
class AmplitudeFrame : public wxFrame
{
public:
    AmplitudeFrame();
    wxTextCtrl *frequency;
    wxStaticText *response;
private:
    void Input_control(wxCommandEvent& event);
    void Frequency_enter(wxCommandEvent& event);
};
