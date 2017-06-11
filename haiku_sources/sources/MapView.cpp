#include "MapView.h"
#include "country.h"
#include "politic.h"
#include "group.h"
#include "day.h"
#include "SendWindow.h"
#include "my_cursors.h"
#include "W6.h"
#include <Bitmap.h>
#include <Alert.h>
#include <TextView.h>
#include <Application.h>
#include <ScrollView.h>

#include <iostream.h>

const pattern stripes = {0xc7,0x8f,0x1f,0x3e,0x7c,0xf8,0xf1,0xe3};

/**** constructeur ****/
MapView::MapView(BRect frame, long flags)
: BView(frame,"MapView", flags, B_WILL_DRAW | B_ASYNCHRONOUS_CONTROLS)
{
	_jour		= ((W6Application *)be_app)->_jour;
	_country	= ((W6Application *)be_app)->_country;
	_group		= ((W6Application *)be_app)->_group;
	_politic	= ((W6Application *)be_app)->_politic;	

	//pour la première fois..
	old_line_rect = Bounds();

	_scrollView=false;
	country_selected=false;
	_startPoint = BPoint(0,0);
	_destPoint = BPoint(0,0);
	_oldDestPoint = BPoint(0,0);

	SetViewColor(0,0,0);
	
    // taille image 1160/740
	BRect	bitmapRect(0,0,DEF_PIC_X_SIZE- 1,DEF_PIC_Y_SIZE- 1);
	
	//création des images
	final_bitmap = new BBitmap(bitmapRect,B_RGB32,true);//bitmap_rect,B_RGB_32);

	// masque frontiere
	unsigned char	*bts = NULL;
	unsigned char	*dest = NULL;
   	BBitmap			*tmp_bitmap = NULL;
   	uint32			pos=0;
   	uint32			leng = 0;
   	BString			name;	
	
	// masque frontiere
	name = ((W6Application *)be_app)->app_dir(); //trouve le dir actuel de l'application (a ne pas appeler avant de créer la win)
	name << "maps/";
	name << "frontier.tif";			//et le nom du fichier
   
	tmp_bitmap = ((W6Application *)be_app)->LoadBitmap(name.String()); //supporte n'importe quel translator!!!
	frontier_bitmap = new BBitmap(bitmapRect,B_CMAP8,true);

	bts = (unsigned char*)(tmp_bitmap->Bits());   
	dest = (unsigned char*)(frontier_bitmap->Bits());   
   	
   	pos = 0;
   	leng = frontier_bitmap->BitsLength();	
   	for(pos=0;pos<leng;pos++)
	{
        *dest = *bts;
        dest++;
    	bts+=4;
	}	
	delete tmp_bitmap;	

	// masque bump
	name = ((W6Application *)be_app)->app_dir(); //trouve le dir actuel de l'application (a ne pas appeler avant de créer la win)
	name << "maps/";
	name << "bump.tif";			//et le nom du fichier

	tmp_bitmap = ((W6Application *)be_app)->LoadBitmap(name.String()); //supporte n'importe quel translator!!!
	bts = (unsigned char*)(tmp_bitmap->Bits());   

	bump_bitmap = new BBitmap(bitmapRect,B_CMAP8,true);
	dest =	 (unsigned char*)(bump_bitmap->Bits());   
   	
	pos = 0;
	leng=bump_bitmap->BitsLength();	
   	for(pos=0;pos<leng;pos++)
	{
        *dest = *bts;
        dest++;
    	bts+=4;
	}	
	delete tmp_bitmap;	

	//ORDRE ABVR
	set_gray_palette();
	//met du gris dans la fausse palette pic relief (bump)
	//la vraie palette est celle (fixe) du système...

	//recherche limites des pays sur la map 1160x740!
 	Init();

	//MISE A JOUR DE L'image finale via fonction MULTIPLY
	MultiplyAll();

	// selectionner le pays courant
	_currentCountry = _jour->active_country;
}

/**** destructeur ****/
MapView::~MapView()
{
	delete	frontier_bitmap;
	delete	bump_bitmap;
	delete	final_bitmap;
}

/**** Initialisation ****/
void MapView::Init()
{
	unsigned char	the_ctry,val; //pour pointer dans list pays
	BPoint			currentPixel;
	Country 		*ct;
	BString			info;


	BTextView *tmp; //pointeur sur le texte du main_alert win
	tmp = _jour->main_alert->TextView();

	//pas PIC_SIZE-1 sinon il fait pas le dernier
	for(currentPixel.y = 0;currentPixel.y<DEF_PIC_Y_SIZE;currentPixel.y++)
	{
		info = "Finding bounds on line ";
		info << currentPixel.y;
		_jour->main_alert->Lock();
		tmp->SetText(info.String());
		_jour->main_alert->Unlock();
						
		//chaque pixel
		for(currentPixel.x = 0;currentPixel.x<DEF_PIC_X_SIZE;currentPixel.x++)
		{	
			val = SelectCountry(currentPixel); //une fois par point
			for(the_ctry = _jour->country_first;the_ctry<_jour->country_last;the_ctry++) //chaque pixel chaque pays
			{
				//si on est dans le bon pays
				if(val == the_ctry)
				{
					//histoire de faire des lignes courtes
					ct = _country[the_ctry];
					
					if (currentPixel.x < ct->limit.left)
						ct->limit.left = currentPixel.x;
					if (currentPixel.y < ct->limit.top)
						ct->limit.top = currentPixel.y;	
					if (currentPixel.x > ct->limit.right)
						ct->limit.right  = currentPixel.x;
					if (currentPixel.y > ct->limit.bottom)
						ct->limit.bottom = currentPixel.y;
				}
			}
		}
	}

	//on trouve le centre
	the_ctry=_jour->country_first;
	while(the_ctry != (_jour->country_last+1)) //tous les rectangles aux valeurs extremes inverses
	{
		ct = _country[the_ctry]; //histoire de faire des lignes courtes
		ct->center_x = (ct->limit.left + ct->limit.right)  /2 ;
		ct->center_y = (ct->limit.top  + ct->limit.bottom) /2 ;
		the_ctry++;
	}

	//CALCUL TABLE MULTIPLY
	int16 a,b;

	//value=frontier_palette[(*color_ptr *3)+composante];
	//full_ptr = (*gray_ptr * value) / 255;
	for(a=0;a<256;a++)
		for(b=0;b<256;b++)
			tab_multiply[a][b]= (a * b) / 255;

}

/**** frontiere ****/
void MapView::set_frontier_palette(unsigned char which_color,unsigned char rval, unsigned char gval,unsigned char bval)
{
	int32	position;

	// +1 pour gerer l'alpha
	position = (which_color*3)+1;
	frontier_palette[position]		= bval;
	frontier_palette[position+1]	= gval;
	frontier_palette[position+2]	= rval;
}

/**** degrade de gris ****/
void MapView::set_gray_palette()
{
	//met la palette a un bete degrades de gris
	unsigned char gray_val=0;
	
	for(int32 pos_pal=0;pos_pal<768;pos_pal+=3) // 768-3)
	{
		bump_palette[pos_pal]   = gray_val;		//set_R
    	bump_palette[pos_pal+1] = gray_val;		//set_G
    	bump_palette[pos_pal+2] = gray_val;		//set_B
    	gray_val++;
	}
}

/**** dessin ****/
void MapView::Draw(BRect update_rect)
{
	// dessiner la carte
	DrawBitmapAsync(final_bitmap,BPoint(0,0));

	// voir la region selectionnée
	MultiplyCountrySelected();

	// voir l'ennemi et les attaques
	ShowTroops();
	
	// dessine la bitmap et le reste
	Sync();
}

/**** mettre a _jour la palette ****/
void MapView::update_map_palette()
{
	unsigned char tmp;
	unsigned char grp;
	rgb_color couleur;

	tmp = _jour->country_first;
	set_frontier_palette(COL_SEA,20,40,120); 
	set_frontier_palette(COL_BORDER,0,0,0); 

	for(tmp=_jour->country_first;tmp<=_jour->country_last;tmp++)
	{
		if(_country[tmp]!=NULL)
		{
			grp = _country[tmp]->group; //trouve le groupe à qui appartient le pays
			couleur = _group[grp]->grp_color;  //trouver la couleur du groupe auquel appartient le country
			set_frontier_palette(tmp,couleur.red,couleur.green,couleur.blue); //et l'applique au pays
		}
	}
}

/**** updater le titre ****/
void MapView::UpdateTitle()
{
	BString		title;

	if (_jour->edit_mode==ON)
		title = "W6 - Editing Scenario";
	else
	{
		title = "W6 - playing with ";
		title << _group[_jour->player_group]->Name();
	}
	_jour->mainWin->SetTitle(title.String());
}    
    
/**** on clique ****/    
void MapView::MouseDown(BPoint point)
{
	uint32	buttons;

	agressor=0; // il FAUT une valeur par défaut ... la mer...
	victim=0;

	//on a besoin des buttons après... dans le mousemoved
	GetMouse(&point,&buttons);

	_startPoint = point;
	_destPoint = point;
	_oldDestPoint = point;
	
	switch(buttons)
	{
	case B_SECONDARY_MOUSE_BUTTON:	// on deplace la vue (mousemove)
		_scrollView = true;
		be_app->SetCursor(B_HAND_CURSOR);//curseur par défaut
		break;
	case B_PRIMARY_MOUSE_BUTTON:
		{
			int16	countrySelected = NO_COUNTRY_SELECTED;
			
			countrySelected = SelectCountry(point);
			if(countrySelected != NO_COUNTRY_SELECTED)
			{
				if(countrySelected!=_currentCountry)
				{
					// effacer l'ancienne
					Invalidate(SelectedFrameCountry());
				
					// afficher les infos du pays
					_currentCountry = countrySelected;
					Invalidate(SelectedFrameCountry());
					_jour->active_country = _currentCountry;
					Invalidate(_country[_jour->active_country]->limit);
					_jour->infoWin->PostMessage(DRAW_INFO);
				}
				country_selected = true; 
			}
		}
	}
}

/**** fin clique souris ****/
void MapView::MouseUp(BPoint point)
{
	uint32	buttons;

	//on a besoin des buttons après... dans le mousemoved
	GetMouse(&point,&buttons);

	if(_scrollView==true)
	{
		_scrollView=false;
		be_app->SetCursor(&simple_cross[0]); //pour si on était en _scrollView ==true
	}
	else
	{
		if(country_selected==true)
		{
			int16	countrySelected = NO_COUNTRY_SELECTED;

			// effacer la ligne
			if(_destPoint != _startPoint)
			{
				_destPoint = point;
				ErasePlayerLine();
			}
			
			countrySelected = SelectCountry(point);
			if(countrySelected!=_currentCountry && countrySelected != NO_COUNTRY_SELECTED)
			{
				// attaquer
				Invalidate(SelectedFrameCountry());
				CountriesChosen();
				Invalidate(SelectedFrameCountry());
			}
			// c'est bon on a relache le bouton
			country_selected = false;
			_startPoint = _destPoint;
		}	
	}
}

/**** on bouge la souris ****/
void MapView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	uint32	buttons;
	BPoint	newPoint;

	if(transit==B_ENTERED_VIEW)
		be_app->SetCursor(&simple_cross[0]);
	
	if(transit==B_EXITED_VIEW)
		be_app->SetCursor(B_HAND_CURSOR);//curseur par défaut

	// rafraichir le point de deplacement
	GetMouse(&newPoint,&buttons); //faut le refaire sinon la ligne reste tirée

	//---------------------------------------------------------------------------------
	//SI BOUTON DROIT (editeur ou game) DRAG DRAG DRAG DRAG DRAG
	//---------------------------------------------------------------------------------
	switch(buttons)
	{
	case B_SECONDARY_MOUSE_BUTTON:	// on deplace la vue (mousemove)
		if(_scrollView==true)
		{ 
		//ATTENTION si je fais
		//end = point, c'est pas comme le getmouse
		//apparement il y a un délai et çA fait tout merder (ca scrolle trop loin)
		//donc bien que dans un mousemoved on refait un getmouse pour les coord
			if(_destPoint != point)
      		{
      			_destPoint = point;
      			delta = _startPoint-_destPoint;      	 	
   	 			delta.x *= _jour->zoom_level;
   	 			delta.y *= _jour->zoom_level;

				//Pour EVITER BLOP quand on essaie de scroller out of limits...
				//si nég et barre tout en haut à gauche on scrolle pas...
				if(delta.x < 0 && (_jour->scroll_hori->Value() ) == 0)
					delta.x=0;
			
				if(delta.y < 0 && (_jour->scroll_verti->Value()) == 0)
					delta.y=0;

				//si pos
				if(delta.x > 0 && (_jour->scroll_hori->Value()) >= DEF_PIC_X_SIZE-(v_rect.right )-B_H_SCROLL_BAR_HEIGHT)
					delta.x=0;
			
				if(delta.y > 0 && (_jour->scroll_verti->Value()) >= DEF_PIC_Y_SIZE-(v_rect.bottom )-B_V_SCROLL_BAR_WIDTH)
					delta.y=0;

   	 			ScrollBy(delta.x,delta.y);
   				_startPoint=_destPoint;
				_startPoint.x += delta.x; //car quand on scrolle le BPoint change aussi!!!
				_startPoint.y += delta.y; //faut le redécaler d'autant
			}
		}
		break;
	case B_PRIMARY_MOUSE_BUTTON:
		if(country_selected==true)
		{			
			// mettre a _jour les coordonees
			_destPoint = point;
			if(_startPoint!=_destPoint)
			{
			    SetDrawingMode(B_OP_INVERT); 
				StrokeLine(BPoint(_startPoint.x,_startPoint.y),BPoint(_oldDestPoint.x,_oldDestPoint.y));
				StrokeLine(BPoint(_startPoint.x,_startPoint.y),BPoint(_destPoint.x,_destPoint.y));
				SetDrawingMode(B_OP_COPY);
				
				// garder les ancienne coordonnees pour effacer
				_oldDestPoint = _destPoint;     
			}
		}
		break;
	default:
		break;// rien
	}
}

/**** Effacer la ligne du joueur ****/
void MapView::ErasePlayerLine()
{
    SetDrawingMode(B_OP_INVERT); 
	StrokeLine(BPoint(_startPoint.x,_startPoint.y),BPoint(_oldDestPoint.x,_oldDestPoint.y));
	SetDrawingMode(B_OP_COPY);
}

/**** Affichage en couleur des pays ****/
void MapView::MultiplyCountrySelected()
{
cout << "select Country" << endl;
	if(_currentCountry==NO_COUNTRY_SELECTED)
		return;

	// recuperer la zone selectionnée
	BRect	selectedFrame = SelectedFrameCountry();

	//pointeurs sur les 3 pics
   	int32	pos_bits;
	
	//avance jusqu'au pixel de départ
   	pos_bits = (int32)(selectedFrame.left + (DEF_PIC_X_SIZE*(selectedFrame.top))); //pixel de départ (haut gauche du rect)
	pos_bits *= 4;
	
	if(pos_bits<0)
		return;
	
	int32 pos_x = 0;
	int32 pos_y = 0;   
	int32 largeur =  (int32)selectedFrame.Width() + 1;
	int32 hauteur =  (int32)selectedFrame.Height() + 1;
	rgb_color color;

	//pour eviter tout problème
	if(largeur<1 || hauteur<1 || largeur>=DEF_PIC_X_SIZE || hauteur>=DEF_PIC_Y_SIZE)
		return;
		
	BPoint	point;
	
	
	SetHighColor(255,255,0);
	for(pos_y=0;pos_y<hauteur;pos_y++)
	{   
		for(pos_x=0;pos_x<largeur;pos_x++)
       	{ 
   	   		//on avance de 1 pixel dans le gris et de 3 en couleur
       		//*full_ptr = tab_multiply[*gray_ptr][frontier_palette[(*color_ptr *3)+composante]];
			color = *((rgb_color *)(((uint8 *)(final_bitmap->Bits()) + pos_bits)));    		

			// pour verifier que ca appartient au pays
			if(color.red == 0 && color.green == 0 && color.blue == 0)
  			{
   				point.x = selectedFrame.left + pos_x;
    			point.y = selectedFrame.top + pos_y;
    			if(PointOfCountry(point))
	    			StrokeRect(BRect(selectedFrame.left + pos_x,selectedFrame.top + pos_y,selectedFrame.left + pos_x,selectedFrame.top + pos_y));
			}
    		pos_bits+=4;
       	}
		pos_bits += (DEF_PIC_X_SIZE-largeur)*4;
	}
}

/**** Affichage en couleur des pays ****/
void MapView::Multiply(BRect la_zone)
{
	//pointeurs sur les 3 pics
	unsigned char	*gray_ptr;
	unsigned char	*color_ptr;
	unsigned char	*full_ptr;
	int32			pos_bits;
	unsigned char	composante;
	int32 pos_x,pos_y,largeur,hauteur;   

	//3 pointeurs sur les 3 pics
	color_ptr	= (unsigned char *)frontier_bitmap->Bits();
   	gray_ptr	= (unsigned char *)bump_bitmap->Bits(); 
	full_ptr	= (unsigned char *)final_bitmap->Bits(); 

	//met les couleurs des pays sur la palette de la pic frontier
	update_map_palette();

	//avance jusqu'au pixel de départ
   	pos_bits = (int32)((la_zone.left-1)+(DEF_PIC_X_SIZE*(la_zone.top-1))); //pixel de départ (haut gauche du rect)
	if (pos_bits < 0 )
		pos_bits=0;
	
	color_ptr	+= pos_bits;	//avance jusqu'au pixel en question
   	gray_ptr	+= pos_bits;	//avance jusqu'au pixel en question
	full_ptr	+= pos_bits*4;	//RGB+A!!!

	largeur =  (int32)(la_zone.Width()) + 2;
	hauteur =  (int32)(la_zone.Height()) + 2;

	//pour eviter tout problème
	if(largeur<1)				largeur=1;
	if(hauteur<1)				hauteur=1;
	if(largeur>=DEF_PIC_X_SIZE)	largeur=DEF_PIC_X_SIZE;
	if(hauteur>=DEF_PIC_Y_SIZE)	hauteur=DEF_PIC_Y_SIZE;

	for(pos_y=0;pos_y<hauteur;pos_y++)
	{   
		for(pos_x=0;pos_x<largeur;pos_x++)
       	{ 
       	 	for(composante=1;composante<4;composante++)
       	   	{	
       	   		//on avance de 1 pixel dans le gris et de 3 en couleur
	       		*full_ptr = tab_multiply[*gray_ptr][frontier_palette[(*color_ptr *3)+composante]];
	    		full_ptr++;
       		}
            full_ptr++; //on saute l'alpha
			gray_ptr++;
      		color_ptr++;
       	}
		gray_ptr	+= (DEF_PIC_X_SIZE-largeur);
		color_ptr	+= (DEF_PIC_X_SIZE-largeur);
		full_ptr	+= (DEF_PIC_X_SIZE-largeur)*4;
	}
	Invalidate(la_zone);
}

/**** Rafraichir la carte complete ****/
void MapView::MultiplyAll()
{
	BRect	bounds;

	bounds.Set(0,0,DEF_PIC_X_SIZE-1,DEF_PIC_Y_SIZE-1);
	Multiply(bounds);
}

/**** Timer ****/	
void MapView::Pulse()
{
	//CE PULSE A PAS BESOIN D'ETRE PAUSE VU QUE il n'y a que dans Running quon modifie
	//avec des daypassed, ici on update juste la pic... si nécessaire
	if(_jour->game_started==ON) //pour pas qu'on voie la pause s'afficher dans draw alors qu'on choisit son groupe au début
	{
	if (_jour->pause==OFF)
	{
		;// on doit invalider le deplacement des troupes
	}				
	else //pour pas qu'on voie la pause s'afficher dans draw alors qu'on choisit son groupe au début
	{
		BPoint center = BPoint(DEF_PIC_X_SIZE/2,DEF_PIC_Y_SIZE/2);
		BRect update_it = BRect(center,center);
		update_it.InsetBy(-216,-216);
		Draw(update_it);	//on efface
		SetDrawingMode(B_OP_MAX); 
	
		if (pause_angle >=359)
			pause_angle=0;
		else
			pause_angle++;
			
		BFont font; 
		SetFontSize(32);
		SetHighColor(255,255,255);
   	
		pause_angle++;
		font.SetRotation(pause_angle); 
		SetFont(&font, B_FONT_ROTATION); 
   		DrawString("Game paused",center); 
	
		SetDrawingMode(B_OP_COPY); //Restaure l'ancien
	}//fin if game started
	}
}

/**** afficher la ligne d'action du joueur ****/
/*void MapView::ShowLineAndName()
{
	if(_destPoint==_startPoint)
		return;

	unsigned char ct1,ct2;
	unsigned int distance=0;
 
	SetFont(be_bold_font);
	SetFontSize(10);
    SetPenSize(1);

	ForceFontAliasing(false);

	SetLowColor(0,0,0);
    SetHighColor(255,255,0); //couleur du texte

    SetDrawingMode(B_OP_INVERT); 
	StrokeLine(BPoint(floor(_startPoint.x/ _jour->zoom_level),floor(_startPoint.y/ _jour->zoom_level)),BPoint(floor(_destPoint.x/ _jour->zoom_level),floor(_destPoint.y/ _jour->zoom_level)),stripes);
	SetDrawingMode(B_OP_COPY); //restaure le mode normal pour restaurer l'image
    	   		
	//Ca prend les valeurs de start et end...
	ct1=SelectCountry(_startPoint);	
	ct2=SelectCountry(_destPoint);

	_SrcName = _country[ct1]->name;
	DrawString(_SrcName.String(),BPoint(floor(_startPoint.x/ _jour->zoom_level),floor(_startPoint.y/ _jour->zoom_level)));  //affiche le nom attaquant
            
    if(ct1!=COL_BORDER && ct2!=COL_BORDER && ct1!=COL_SEA && ct2!=COL_SEA)
    {
		distance = _country[ct1]->FindDistance(_country[ct1],_country[ct2]);			
    	_DestName = _country[ct2]->name;
    	_DestName << ", " << distance << " km";
    }
    
    SetDrawingMode(B_OP_INVERT); 
	StrokeLine(BPoint(floor(_startPoint.x/ _jour->zoom_level),floor(_startPoint.y/ _jour->zoom_level)),BPoint(floor(_destPoint.x/ _jour->zoom_level),floor(_destPoint.y/ _jour->zoom_level)),stripes);
	SetDrawingMode(B_OP_COPY); //restaure le mode normal pour restaurer l'image

    DrawString(_DestName.String(),BPoint(floor(_destPoint.x/ _jour->zoom_level),floor(_destPoint.y/ _jour->zoom_level)));		//affiche nom victime

	ForceFontAliasing(true);
}*/

/**** dessiner les troupes ****/
void MapView::ShowTroops()
{
	unsigned char tmp_ct=_jour->country_first; //unsigned char tmp_ct=_jour->country_first
	
	while(tmp_ct!=_jour->country_last+1)
	{
		BRect rect1;
		Country *ctry=_country[tmp_ct]; 

		//rect en haut à droite
		rect1.Set(ctry->center_x-(_jour->sq_size/2),ctry->center_y-(_jour->sq_size/2),ctry->center_x+(_jour->sq_size/2),ctry->center_y+(_jour->sq_size/2));

		//on ne voit que le premier agresseur		 
		if (ctry->agressor_01!=NULL)
		{
			SetHighColor(_group[ctry->agressor_01->group]->grp_color);
			FillRect(rect1,B_SOLID_HIGH); //B_SOLID_HIGH pour du plein pattern
			SetHighColor(0,0,0);
			StrokeRect(rect1,B_SOLID_HIGH); 
		}

		SetDrawingMode(B_OP_OVER);       
		if(ctry->move_01!=OFF && ctry->victim_01!=NULL)
		{
			SetHighColor(_group[ctry->group]->grp_color);
			StrokeLine(BPoint(ctry->center_x,ctry->center_y),BPoint(ctry->victim_01->center_x,ctry->victim_01->center_y),stripes);
		}

		if(ctry->move_02!=OFF && ctry->victim_02!=NULL)
		{
			SetHighColor(_group[ctry->group]->grp_color);
			StrokeLine(BPoint(ctry->center_x,ctry->center_y),BPoint(ctry->victim_02->center_x,ctry->victim_02->center_y),stripes);
		}

		if(ctry->move_03!=OFF && ctry->victim_03!=NULL)
		{
			SetHighColor(_group[ctry->group]->grp_color);
			StrokeLine(BPoint(ctry->center_x,ctry->center_y),BPoint(ctry->victim_03->center_x,ctry->victim_03->center_y),stripes);
		}

		if(ctry->move_04!=OFF && ctry->victim_04!=NULL)
		{
			SetHighColor(_group[ctry->group]->grp_color);
			StrokeLine(BPoint(ctry->center_x,ctry->center_y),BPoint(ctry->victim_04->center_x,ctry->victim_04->center_y),stripes);
		}
		tmp_ct++;
		SetDrawingMode(B_OP_COPY);      
	} 
}

/**** Selectionner un pays ****/
int16 MapView::SelectCountry(BPoint point)
{
	int16			val = NO_COUNTRY_SELECTED;
	unsigned char	*bits = NULL;

	point.x = floor(point.x / _jour->zoom_level);
	point.y = floor(point.y / _jour->zoom_level);

	unsigned long pos_bits;
	pos_bits=(long unsigned int)(point.x+(DEF_PIC_X_SIZE*point.y));

	//pour accèder aux pixels directement
 	bits = (unsigned char *)(frontier_bitmap->Bits());
	bits += pos_bits;//avance jusqu'au pixel en question
	val = *bits;
	
	if(val!=COL_BORDER && val!=COL_BORDER && val!=COL_SEA && val!=COL_SEA)
		return val;

	return NO_COUNTRY_SELECTED;
}

/**** recalculer la zone selectionnée ****/
BRect MapView::SelectedFrameCountry()
{
	BRect	selectedFrame;
	
	selectedFrame = _country[_currentCountry]->limit;
	selectedFrame.InsetBy(-1,-1);

	//frame du pays selectionné
	return selectedFrame;
}

/**** choix du pays ****/
void MapView::CountriesChosen()
{
	agressor=SelectCountry(_startPoint); 
	victim=SelectCountry(_destPoint);
	
	//SI ON A TIRE UNE LIGNE d'un pays à un autre
	if(agressor!=victim && agressor!=COL_SEA && agressor!=COL_BORDER && victim!=COL_SEA && victim!=COL_BORDER) 
	{
		//RETRAITE
		//si celui d'ou tu pars ("agressor") n'est pas a toi
		//et celui ou tu arrives ("victim") l'est, c'est une retraite
		if(_group[_country[agressor]->group]->player==COMPUTER && _group[_country[victim]->group]->player!=COMPUTER && _country[agressor]->war==ON)							
		{
		  	char str[255];
		  	sprintf (str,"Do you really wish to retreat to ");
		  	strcat (str,_country[victim]->Name());
		  	strcat (str,"?\nYou'll lose about 10% of your troops in this operation.");
		  	BAlert *alert = new BAlert("", str, "No", "Yes!"); 
		   	
		   	int32 button_index;
  		 	//les boutons ont tou_jours les valeurs 0,1,2 (trois boutons max)
  		 	switch(button_index = alert->Go())
  		 	{
 			case 1:	//en fait la victim c'est l'agressor... mais c'est une sorte de victime puisqu'il fuit!
		   		_country[agressor]->Retreat(_country[victim]);
   				break;
			}//fin switch
			result = 0; //on va pas plus loin ensuite	
		}
		else 
		{
  	    	if(_group[_country[agressor]->group]->player!=COMPUTER)
			{
				result=0;

				//y a-t-il quatre attaquants déja?
				if (_country[victim]->agressor_01!=NULL) result++;
				if (_country[victim]->agressor_02!=NULL) result++;
				if (_country[victim]->agressor_03!=NULL) result++;
				if (_country[victim]->agressor_04!=NULL) result++;
	
				//si c'est le meme attaquant c'est bon, il continue
				if (_country[agressor]==_country[victim]->agressor_01) result--; 
				if (_country[agressor]==_country[victim]->agressor_02) result--; //si c'est le meme attaquant c'est bon, il continue
				if (_country[agressor]==_country[victim]->agressor_03) result--; //si c'est le meme attaquant c'est bon, il continue
				if (_country[agressor]==_country[victim]->agressor_04) result--; //si c'est le meme attaquant c'est bon, il continue
		
				if (_country[agressor]->group==_country[victim]->group) result=0; //si renforts
		
				if (result>=4) //si plus de 3 attaquants
				{
					BAlert *alert = new BAlert("","Country already suffers from four different attacks","Shame");
			 		alert->Go();
				
					_currentCountry = SelectCountry(_startPoint);
					_jour->active_country = _currentCountry;
					_jour->active_group=_country[_jour->active_country]->group;
					
					agressor=victim; //pour skipper le menu envoi des troupes
				}

				if(result<4) //si moins de 3 attaquants
				{
					unsigned char a,b,c,d;

					a=_country[victim]->attacked_by;
					b=_country[agressor]->group;
					c=_country[victim]->group;
					d=_country[agressor]->group;

					if(_country[agressor]->victim_04==NULL) //seulement si pas déjà 4 attaques
					{
						if(_country[victim]->war==ON && a!= b && c!= d)
						{
		  					BAlert *alert = new BAlert("","Country already under attack by another party! Your troops won't be able to attack unless the other have finished fighting...","Go on !", "Sorry..."); 
							int32 button_index;
   
							//les boutons ont tou_jours les valeurs 0,1,2 (trois boutons max)
   							switch(button_index = alert->Go())
   							{
   							case 0: //on attaque quand même
								sendWindow = new SendWindow(_country[agressor],_country[victim],_jour);

								_currentCountry = victim;
								_jour->active_country = _currentCountry;
								_jour->active_group=_country[_jour->active_country]->group;

	    						sendWindow ->Lock();		
	    						sendWindow ->Show();	
	    						sendWindow ->Unlock();	
   								break;
    						}
						}
						else
						{ //donc si le pays est pas déjà en guerre		
							sendWindow = new SendWindow(_country[agressor],_country[victim],_jour);

							_currentCountry = victim;
							_jour->active_country = _currentCountry;
							_jour->active_group=_country[_jour->active_country]->group;

							sendWindow->Lock();
	    					sendWindow ->Show();		
							sendWindow ->Unlock();	
						}		
					}//fin if result<4
				}
			}
		}//fin else retraite
	}//fin else not computer

	if (agressor==victim && agressor!=COL_SEA && agressor!=COL_BORDER)
	{
		_currentCountry = SelectCountry(_startPoint);
		_jour->active_country = _currentCountry; 
		_jour->active_group=_country[_jour->active_country]->group;
	}
}

/**** verifier si un des point autour du point appartient a la country ****/
bool MapView::PointOfCountry(BPoint point)
{
	BPoint	pointTest;
	int8	i;
	int8	j;

	for(i=-1;i<2;i++)
		for(j=-1;j<2;j++)
			{
    			pointTest.x = point.x + i;
    			pointTest.y = point.y + j;
    			if(SelectCountry(pointTest) == _currentCountry)
					return true;
			}

	return false;
}