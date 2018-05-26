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

#include <mathplot.h>

#include "wx/filedlg.h"

#include <wx/image.h>
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/log.h>
#include <wx/intl.h>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class FX : public mpFX
{
public:
    int multiplier = 1;
    FX() : mpFX(wxT("Trial function")){};

    FX(const int& a) : mpFX(wxT("Trial function")), multiplier(a){};

    virtual double GetY(double x){
        return multiplier * x;
    }
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
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
/*
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
*/
class SettingsFrame : public wxFrame
{
public:
    SettingsFrame();
    wxRadioBox *attenuatortype, *interpolationtype;
    wxTextCtrl *samperpoint, *fstep, *attfield, *fmin, *fmax, *rep, *curname, *com;
    wxString *pathtocurve;
private:
    
};

enum
{
    ID_DOWN = 1
};
enum
{
    ID_UP = 2
};
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
enum
{
    ID_SettingFrame = 10
};
enum
{
    ID_RADIO_BOX = 11
};
mpWindow *plot;
mpLayer *lay;
int tangens = 0;

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Test app")
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

    wxButton *Button1 = new wxButton(this, ID_UP, wxT("UP"), wxPoint(1000, 200)); 
    wxButton *Button2 = new wxButton(this, ID_DOWN, wxT("DOWN"), wxPoint(1000, 300)); 

    plot = new mpWindow(this, -1, wxPoint(0, 0), wxSize(1000, 1000), wxSUNKEN_BORDER);

    plot->AddLayer(new mpScaleX( wxT("Frequency, Hz")));
    plot->AddLayer(new mpScaleY( wxT("Amplitude, V")));
    plot->AddLayer(lay = new FX(tangens));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuMeasure, "&Measure");
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MyFrame::OnButtonUP, this, ID_UP);
    Bind(wxEVT_BUTTON, &MyFrame::OnButtonDOWN, this, ID_DOWN);
    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, ID_Open);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, ID_Save);
    Bind(wxEVT_MENU, &MyFrame::OnSettings, this, ID_Settings);
    Bind(wxEVT_MENU, &MyFrame::OnDefautSettings, this, ID_DefaultSettings);
    Bind(wxEVT_MENU, &MyFrame::OnGet, this, ID_Get);
    Bind(wxEVT_MENU, &MyFrame::OnAmplitude, this, ID_Amplitude);
    Bind(wxEVT_MENU, &MyFrame::OnCalibration, this, ID_Calibration);

}

SettingsFrame::SettingsFrame()
    : wxFrame(NULL, wxID_ANY, "Settings", wxDefaultPosition, wxSize(500, 500))
{   
    wxStaticText *samplesnum = new wxStaticText(this, wxID_STATIC,
                             wxT("Number of samples per point"),
                              wxPoint(50, 50), wxSize(100, 50), wxTE_CENTRE);
    samperpoint = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(50, 100),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *freqstep = new wxStaticText(this, wxID_STATIC,
                             wxT("Step of frequency"),
                              wxPoint(50, 150), wxSize(100, 50), wxTE_CENTRE);
    fstep = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(50, 200),
                                wxSize(100, 50), wxTE_CENTRE); 
wxStaticText *attenuator = new wxStaticText(this, wxID_STATIC,
                             wxT("Attenuator"),
                              wxPoint(50, 250), wxSize(100, 50), wxTE_CENTRE);
    attfield = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(50, 300),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *minfreq = new wxStaticText(this, wxID_STATIC,
                             wxT("Minimum frequency"),
                              wxPoint(50, 350), wxSize(100, 50), wxTE_CENTRE);
    fmin  = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(50, 400),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *maxfreq = new wxStaticText(this, wxID_STATIC,
                             wxT("Maximum frequency"),
                              wxPoint(250, 50), wxSize(100, 50), wxTE_CENTRE);
    fmax = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(250, 100),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *repeats = new wxStaticText(this, wxID_STATIC,
                             wxT("Number of repeats"),
                              wxPoint(250, 150), wxSize(100, 50), wxTE_CENTRE);
    rep = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(250, 200),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *curvename = new wxStaticText(this, wxID_STATIC,
                             wxT("Name of curve"),
                              wxPoint(250, 250), wxSize(100, 50), wxTE_CENTRE);
    curname = new wxTextCtrl(this, wxID_ANY, "100", wxPoint(250, 300),
                                wxSize(100, 50), wxTE_CENTRE);
    wxStaticText *comments = new wxStaticText(this, wxID_STATIC,
                             wxT("Commentaries"),
                              wxPoint(250, 350), wxSize(100, 50), wxTE_CENTRE);
    com = new wxTextCtrl(this, wxID_ANY, "Lorem ipsum", wxPoint(250, 400),
                                wxSize(100, 50), wxTE_CENTRE);
    wxArrayString names, types;
    names.Add(wxT("ON"));
    names.Add(wxT("OFF"));
    types.Add(wxT("Linear"));

    attenuatortype = new wxRadioBox(this, ID_RADIO_BOX, wxT("Attenuator"), wxPoint(450, 250), wxSize(150, 50), names, 1, wxRA_SPECIFY_COLS);
    interpolationtype = new wxRadioBox(this, ID_RADIO_BOX, wxT("Interpolation types"), wxPoint(450, 50), wxSize(150, 50), types, 1, wxRA_SPECIFY_COLS);
    wxString caption = wxT("Choose a file");
    wxString wildcard = wxT("BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif");
    wxString defaultDir = wxT("~");
    wxString defaultFilename = wxEmptyString;

    wxFileDialog *setpath = new wxFileDialog(this, caption, defaultDir, defaultFilename, wildcard, wxFD_SAVE);
    setpath->Show(true);
}   

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
void MyFrame::OnButtonUP(wxCommandEvent& event){
    tangens+= 1;
    plot->DelLayer(lay);
    plot->AddLayer(lay = new FX(tangens));
}
void MyFrame::OnButtonDOWN(wxCommandEvent& event){
    tangens-= 1;
    plot->DelLayer(lay);
    plot->AddLayer(lay = new FX(tangens));
}
void MyFrame::OnOpen(wxCommandEvent& event){

}
void MyFrame::OnSave(wxCommandEvent& event){

}
void MyFrame::OnSettings(wxCommandEvent& event){
    wxFrame* SettingFrame = new SettingsFrame();
    SettingFrame->Show(true);
}
void MyFrame::OnDefautSettings(wxCommandEvent& event){

}
void MyFrame::OnGet(wxCommandEvent& event){

}
void MyFrame::OnAmplitude(wxCommandEvent& event){

}
void MyFrame::  OnCalibration(wxCommandEvent& event){

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
            Aplly calculation curve Ctrl+C(default off in case of no curve open big window)
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