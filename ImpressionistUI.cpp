//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

void ImpressionistUI::cb_dissolve_dialog(Fl_Menu_* o, void* v)
{
	whoami(o)->m_dissolveDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
	whoami(o)->m_dissolveDialog->hide();

}


//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for CS341, Spring 2002");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;


	pDoc->setBrushType(type);
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the brush direction to use to the one chosen in the 
// brush direction choice.  
// Called by the UI when a brush direction is chosen in the 
// brush direction choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	Fl_Choice* brushDirectionChoice = (Fl_Choice*)o;
	int directionIndex = brushDirectionChoice->value();

	pDoc->setBrushDirection(directionIndex);
}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Swaps the content of the paintview and original image.
//------------------------------------------------------------

void ImpressionistUI::cb_swap_content(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	pDoc->swapContent();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the line
// thickness slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineThicknessSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineThickness = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
// Updates the brush size to use from the value of the brush
// angle slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_brushAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nBrushAngle = int(((Fl_Slider*)o)->value());
}

//-----------------------------------------------------------
// Updates the alpha value to use from the value of the alpha
// value slider
// Called by the UI when the alpha value slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_alphaValueSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlphaValue = float(((Fl_Slider*)o)->value());

}

void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	whoami(o)->getDocument()->undo();
}

// Dissolve 2 images
void ImpressionistUI::cb_dissolve(Fl_Widget* o, void* v)
{
	ImpressionistUI* ui =
		static_cast<ImpressionistUI*>(o->user_data());

	char* filename = fl_file_chooser(
		"Choose second image",
		"*.bmp",
		""
	);

	if (filename == NULL)
		return;

	ui->getDocument()->dissolveImage(
		filename,
		static_cast<float>(ui->m_dissolveSlider->value())
	);
}

//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
}

//------------------------------------------------
// Return the line thickness
//------------------------------------------------
int ImpressionistUI::getLineThickness()
{
	return m_nLineThickness;
}

//-------------------------------------------------
// Set the line thickness
//-------------------------------------------------
void ImpressionistUI::setLineThickness(int thickness)
{
	m_nLineThickness = thickness;

	if (thickness <= 40)
		m_LineThicknessSlider->value(m_nLineThickness);
}

//------------------------------------------------
// Return the brush angle
//------------------------------------------------
int ImpressionistUI::getBrushAngle()
{
	return m_nBrushAngle;
}

//-------------------------------------------------
// Set the brush angle
//-------------------------------------------------
void ImpressionistUI::setBrushAngle(int angle)
{
	m_nBrushAngle = angle;

	if (angle <= 360)
		m_BrushAngleSlider->value(m_nBrushAngle);
}

//-------------------------------------------------
// Set the alpha value
//-------------------------------------------------
void ImpressionistUI::setAlphaValue(float alpha)
{
	m_nAlphaValue = alpha;

	if (alpha <= 1.0)
		m_AlphaValueSlider->value(m_nAlphaValue);
}

//------------------------------------------------
// Return the alpha value
//------------------------------------------------
float ImpressionistUI::getAlphaValue()
{
	return m_nAlphaValue;
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Dissolve...", 0, (Fl_Callback*)ImpressionistUI::cb_dissolve_dialog },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas},
		{ "&Undo", FL_ALT + 'z', (Fl_Callback*)ImpressionistUI::cb_undo},
		{"&Swap Content", 0, (Fl_Callback*)ImpressionistUI::cb_swap_content, 0, FL_MENU_DIVIDER  },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Triangles",			FL_ALT+'t',	(Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_TRIANGLES},
  {"Rings",				FL_ALT+'r',	(Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_RINGS},
  {"Stars",				FL_ALT+'s',	(Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_STARS},
  {"Blur", 0, (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_BLUR},
  {"Sharpen", 0, (Fl_Callback*)ImpressionistUI::cb_brushChoice, (void*)BRUSH_SHARPEN},
  {0}
};

// Brush direction choice menu definition
Fl_Menu_Item ImpressionistUI::brushDirectionMenu[NUM_BRUSH_DIRECTION + 1] = {
  {"Slider"},
  {"Right Mouse"},
  {"Cursor"},
  {"Gradient"},
  {0}
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineThickness = 1;
	m_nBrushAngle = 0;
	m_nAlphaValue = 1.0;


	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 375, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add a brush direction choice to the dialog
		m_BrushDirectionChoice = new Fl_Choice(110, 50, 150, 25, "&Brush Direction");
		m_BrushDirectionChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushDirectionChoice->menu(brushDirectionMenu);
		m_BrushDirectionChoice->callback(cb_brushDirectionChoice);
		m_BrushDirectionChoice->value(BRUSH_DIRECTION_SLIDER); // Set default value to "Slider"


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 90, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add line thickness slider to the dialog
		m_LineThicknessSlider = new Fl_Value_Slider(10, 130, 300, 20, "Line Thickness");
		m_LineThicknessSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineThicknessSlider->type(FL_HOR_NICE_SLIDER);
        m_LineThicknessSlider->labelfont(FL_COURIER);
        m_LineThicknessSlider->labelsize(10);
		m_LineThicknessSlider->minimum(1);
		m_LineThicknessSlider->maximum(40);
		m_LineThicknessSlider->step(1);
		m_LineThicknessSlider->value(m_nLineThickness);
		m_LineThicknessSlider->align(FL_ALIGN_RIGHT);
		m_LineThicknessSlider->callback(cb_lineThicknessSlides);

		// Add brush angle slider to the dialog
		m_BrushAngleSlider = new Fl_Value_Slider(10, 170, 300, 20, "Brush Angle");
		m_BrushAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushAngleSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushAngleSlider->labelfont(FL_COURIER);
        m_BrushAngleSlider->labelsize(12);
		m_BrushAngleSlider->minimum(0);
		m_BrushAngleSlider->maximum(360);
		m_BrushAngleSlider->step(1);
		m_BrushAngleSlider->value(m_nBrushAngle);
		m_BrushAngleSlider->align(FL_ALIGN_RIGHT);
		m_BrushAngleSlider->callback(cb_brushAngleSlides);

		// Add alpha value slider to the dialog
		m_AlphaValueSlider = new Fl_Value_Slider(10, 210, 300, 20, "Alpha Value");
		m_AlphaValueSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaValueSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaValueSlider->labelfont(FL_COURIER);
		m_AlphaValueSlider->labelsize(12);
		m_AlphaValueSlider->minimum(0.0);
		m_AlphaValueSlider->maximum(1.0);
		m_AlphaValueSlider->step(0.01);
		m_AlphaValueSlider->value(m_nAlphaValue);
		m_AlphaValueSlider->align(FL_ALIGN_RIGHT);
		m_AlphaValueSlider->callback(cb_alphaValueSlides);

		// Add RGB channels
		const char* rgbLabels[3] = { "Red", "Green", "Blue" };

		for (int channel = 0; channel < 3; channel++)
		{
			m_rgbSliders[channel] = new Fl_Value_Slider(
				10, 250 + channel * 40, 300, 20,
				rgbLabels[channel]
			);

			m_rgbSliders[channel]->type(FL_HOR_NICE_SLIDER);
			m_rgbSliders[channel]->labelfont(FL_COURIER);
			m_rgbSliders[channel]->labelsize(12);
			m_rgbSliders[channel]->minimum(0.0);
			m_rgbSliders[channel]->maximum(2.0);
			m_rgbSliders[channel]->step(0.01);
			m_rgbSliders[channel]->value(1.0);
			m_rgbSliders[channel]->align(FL_ALIGN_RIGHT);
		}

	m_brushDialog->end();

	// Dissolve has its own dialog, opened from the File menu.
	m_dissolveDialog = new Fl_Window(400, 120, "Dissolve");
		m_dissolveSlider = new Fl_Value_Slider(
			10, 20, 300, 20, "Amount"
		);

		m_dissolveSlider->type(FL_HOR_NICE_SLIDER);
		m_dissolveSlider->minimum(0.0);
		m_dissolveSlider->maximum(1.0);
		m_dissolveSlider->step(0.01);
		m_dissolveSlider->value(0.5);
		m_dissolveSlider->align(FL_ALIGN_RIGHT);

		Fl_Button* dissolveButton = new Fl_Button(
			10, 65, 300, 30,
			"Load BMP and Dissolve..."
		);

		dissolveButton->user_data(this);
		dissolveButton->callback(cb_dissolve);

	m_dissolveDialog->end();

}
