// wxWidgets "Hello World" Program
// For compilers that support precompilation, includes "wx/wx.h".
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
/*
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class FX : public mpFX
{
    mpFXYVector container;
public:
    
    FX(std::vector<double> yvec, std::vector<double> xvec) : mpFX(wxT("Trial function")){
        container.SetData(xvec, yvec);
    };

    FX(const int& a) : mpFX(wxT("Trial function"));

    virtual double GetY(double x){
        for (unsigned int i = 0; i < container.m_xs.size() - 1; ++i){
            if ((container.m_xs[i + 1] > x) && (container.m_xs[i] <= x)){
                return container.m_ys[i] + (x - container.m_xs[i])*(container.m_ys[i + 1] - container.m_ys[i])/(container.m_xs[i + 1] - container.m_xs[i]); 
            }
        }
    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
    wxFrame *SettingFrame = NULL, *Amplitude = NULL;
    mpWindow *plot;
    mpFXYVector *lay;
    bool is_set = false;
private:
    void OnExit(wxCommandEvent& event);
    void OnButtonUP(wxCommandEvent& event);
    void OnButtonDOWN(wxCommandEvent& event);
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
    void Text1_change(wxCommandEvent& event);
    void Text2_change(wxCommandEvent& event);
    void Text3_change(wxCommandEvent& event);
    void Text4_change(wxCommandEvent& event);
    void Text5_change(wxCommandEvent& event);
    void Text6_change(wxCommandEvent& event);
};

*/
enum
{
    ID_Open = 3
};
enum
{
    ID_Save = 4
};
enum
{
    ID_Settings = 5
};
enum
{
    ID_DefaultSettings = 6
};
enum
{
    ID_Get = 7
};
enum
{
    ID_Amplitude = 8
};
enum
{
    ID_Calibration = 9
};

std::vector<double> xes, yes;

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Test app", wxPoint(0, 0), wxSize(1500, 800))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Open, "&Open response\tCtrl-O");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Save, "&Save response\tCtrl-S");
    menuFile->AppendSeparator();
    menuFile->Append(ID_Settings, "&Settings\tCtrl-P");
    menuFile->AppendSeparator();
    menuFile->Append(ID_DefaultSettings, "&Default Settings\tCtrl-Alt-P");
    menuFile->Append(wxID_EXIT);
    wxMenu *menuMeasure = new wxMenu;
    menuMeasure->Append(ID_Get, "&Get response\tCtrl-Z");
    menuFile->AppendSeparator();
    menuMeasure->Append(ID_Amplitude, "&Amplitude\tCtrl-M");
    menuFile->AppendSeparator();
    menuMeasure->Append(ID_Calibration, "&Apply calculation curve\tCtrl-C");

    //wxButton *Button1 = new wxButton(this, ID_UP, wxT("UP"), wxPoint(1000, 200)); 
    //wxButton *Button2 = new wxButton(this, ID_DOWN, wxT("DOWN"), wxPoint(1000, 300)); 

    plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(1000, 1000), wxSUNKEN_BORDER);

    plot->AddLayer(new mpScaleX( wxT("Frequency, Hz")));
    plot->AddLayer(new mpScaleY( wxT("Amplitude, V")));
    plot->AddLayer(lay = new mpFXYVector("Curve"));
    plot->Fit();

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuMeasure, "&Measure");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    //Bind(wxEVT_BUTTON, &MyFrame::OnButtonUP, this, ID_UP);
    //Bind(wxEVT_BUTTON, &MyFrame::OnButtonDOWN, this, ID_DOWN);
    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &MyFrame::OnSettings, this, ID_Settings);
    Bind(wxEVT_MENU, &MyFrame::OnDefautSettings, this, ID_DefaultSettings);
    Bind(wxEVT_MENU, &MyFrame::OnGet, this, ID_Get);
    Bind(wxEVT_MENU, &MyFrame::OnAmplitude, this, ID_Amplitude);
    Bind(wxEVT_MENU, &MyFrame::OnCalibration, this, ID_Calibration);
}

   

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
    if (Amplitude != NULL){
        Amplitude->Close(true);
    }
    if (SettingFrame != NULL){
        SettingFrame->Close(true);
    }
}
/*void MyFrame::OnButtonUP(wxCommandEvent& event){

}
void MyFrame::OnButtonDOWN(wxCommandEvent& event){

}*/
void MyFrame::OnOpen(wxCommandEvent& event){
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("*");
    wxString defaultDir = wxT("~");
    wxString defaultFilename = wxEmptyString;
    wxFileDialog *setpath = new wxFileDialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_OPEN);
    setpath->Show(true);
    if (setpath->ShowModal() == wxID_OK){
        wxString dialogresponse = setpath->GetPath();
        std::string pathtoresponse = dialogresponse.ToStdString(), input;
        std::ifstream getfile(pathtoresponse);
        xes.clear();
        yes.clear();
        while (getline(getfile, input)){
            auto k = input.find(',');
            std::string first = input.substr(0, k), second = input.substr(k+1);
            xes.push_back(std::stod(first));
            yes.push_back(std::stod(second));
        }
        getfile.close();
        lay->SetData(xes,yes);
        lay->SetContinuity(true);
        plot->Fit();
    }
}
void MyFrame::OnSave(wxCommandEvent& event){
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif");
    wxString defaultDir = wxT("~");
    wxString defaultFilename = wxEmptyString;
    //wxButton *filedialog = new wxButton(this, ID_ON_DIALOG, wxT("Choose save path"), wxPoint(450, 400), wxSize(100, 50));
    wxFileDialog *setpath = new wxFileDialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_SAVE);
    setpath->Show(true);
    if (setpath->ShowModal() == wxID_OK){
        wxString dialogresponse = setpath->GetPath();
        std::string pathtoresponse = dialogresponse.ToStdString();
        std::ofstream getfile(pathtoresponse);
        for (auto j = xes.begin(), k = yes.begin(); j < xes.end(); ++k, ++j){
            getfile << *j << ',' << *k << std::endl;
        }
        getfile.close();
    }
}
void MyFrame::OnSettings(wxCommandEvent& event){
    std::ifstream setfile("./Settings.txt");
    std::string input;
    int i = 0;
    getline(setfile, input);
    setting.sample = std::stoi(input);
    getline(setfile, input);
    setting.step = std::stoi(input);
    getline(setfile, input);
    setting.attenuator = std::stoi(input);
    getline(setfile, input);
    setting.min_freq = std::stoi(input);
    getline(setfile, input);
    setting.max_freq = std::stoi(input);
    getline(setfile, input);
    setting.repeat = std::stoi(input);
    getline(setfile, input);
    setting.name = input;
    getline(setfile, input);
    setting.comment = input;
    getline(setfile, input);
    setting.path = input;
    getline(setfile, input);
    setting.is_attenuator = (input == '1');
    setfile.close();
    SettingFrame = new SettingsFrame();
    SettingFrame->Show(true);
    is_set = true;
}
void MyFrame::OnDefautSettings(wxCommandEvent& event){
    //settings applied
    std::ifstream setfile("./Settings.txt");
    std::string input;
    int i = 0;
    getline(setfile, input);
    setting.sample = std::stoi(input);
    getline(setfile, input);
    setting.step = std::stoi(input);
    getline(setfile, input);
    setting.attenuator = std::stoi(input);
    getline(setfile, input);
    setting.min_freq = std::stoi(input);
    getline(setfile, input);
    setting.max_freq = std::stoi(input);
    getline(setfile, input);
    setting.repeat = std::stoi(input);
    getline(setfile, input);
    setting.name = input;
    getline(setfile, input);
    setting.comment = input;
    getline(setfile, input);
    setting.path = input;
    getline(setfile, input);
    setting.is_attenuator = (input == '1');
    setfile.close();
    is_set = true;

}
void MyFrame::OnGet(wxCommandEvent& event){
    if (!is_set){
        SettingFrame = new SettingsFrame();
        SettingFrame->Show(true);
        is_set = true;
    }
    
    /*for (auto j = xes.begin(), k = yes.begin(); k < yes.end(); ++k, ++j){
        std::cout << *j << ' ' << *k << std::endl;
    }*/
    lay->SetData(xes,yes);
    lay->SetContinuity(true);
    plot->Fit();
}
void MyFrame::OnAmplitude(wxCommandEvent& event){
    Amplitude = new AmplitudeFrame();
    Amplitude->Show(true);
}
void MyFrame::  OnCalibration(wxCommandEvent& event){
    if(!is_set){
        SettingFrame = new SettingsFrame();
        SettingFrame->Show(true);
        is_set = true;
    }
    
}


/*
Settings:
    BIG WINDOW OF SETTINGS
        number of samples per point(field)
        step of frequency(field)
        type of interpolation(ticks)
        attenuator(tick with field)
        beginning and end of frequency(two fields)
        sample rate(not priority)
        calibration curve(path to file with memory)
        number of repeats(field, maybe arrows)
        name of curve(char field)
        commentaries(char field)
    UPPER MENU
        File
            Open response Ctrl+O(path)
            Save response Ctrl+S(path in case of none)
            Settings Ctrl+P(big window mentioned earlier)
            Default settings Ctrl+Alt+P
            Quit Ctrl+Q
        Measure
            Get response Ctrl+Z(plot graph and in case of no settings open big window)
            Amplitude Ctrl+M(open window with field)
            Apply calculation curve Ctrl+C(default off in case of no curve open big window)
    STATUS LINE
        Progress of response
        Status of calibration
        Name of curve
        Pointer coordinates
    GRAPH
        Axises in angles

            
    SAVE FORMAT
        .response
            main curve
            calibration curve(on/off)
        .settings
            format
            name
            commentaries
            path to calibration curve
*/