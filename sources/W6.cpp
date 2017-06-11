#include "W6.h"
#include "day.h"
#include "country.h"
#include "group.h"
#include "Running.h"
#include "MapView.h"
#include "W6Window.h"
#include "ChooseWindow.h"
#include "InfoWindow.h"
#include <TextView.h>
#include <Alert.h>
#include <Bitmap.h>
#include <File.h>
#include <TranslationUtils.h>
#include <Roster.h>
#include <Path.h>

#include <iostream.h>

int main()
{	
	W6Application	myApplication; 
	myApplication.Run();

	return(0);
}

//-----------------------------------------------------------------------
// W6Application constructor
W6Application::W6Application()
: BApplication("application/x-vnd.slema-w6")
{
	_jour = new Day(1970); //année de départ
	_jour->pause=ON;

	// initialser les donnees
	InitWeapon();
	InitGroup();
	Init();

	_jour->main_alert = new BAlert("","Startup process... please wait.", "Crash it!"); 
	BTextView *tmp; //pointeur sur le texte du main_alert win
	tmp=_jour->main_alert->TextView();
    _jour->main_alert->Go(NULL); //NULL pour run asynchrone (on attend pas la réponse)

  	BRect aRect;
  	unsigned char temp_ctry;
   			
	//Fenetre principale
	aRect.Set(8, 24, WIN_X_SIZE+8,WIN_Y_SIZE+24);
	mainWindow = new W6Window(aRect);
	
	aRect.Set(32, 100, 32+INFO_X_SIZE, 100+INFO_Y_SIZE);
	infoWindow = new InfoWindow(aRect,_country,_group,_politic,_jour);
	
	//day passed_FAKE jusqu'au futur
	//day_passed_FAKE est _beaucoup_ plus rapide car il fait que la population 
   	_jour->main_alert->Lock();
    tmp->SetText("Warping countries' data from 1970 to 2066...");
	_jour->main_alert->Unlock();

	
	//données de 1970 faut avancer dans le temps
	unsigned long jump_to_future;
   	
   	for(jump_to_future=0;jump_to_future<(2066-1970)*365;jump_to_future++)
    {
		for(temp_ctry = _jour->country_first;temp_ctry<_jour->country_last+1;temp_ctry++)
			_country[temp_ctry]->day_passed_fake();
		_jour->next();
	}
	_jour->main_alert->Lock();
	_jour->main_alert->Close();

	mainWindow->SetTitle("What Went Wrong? It's a World Wide War!"); //pour la barre à droite meme si on voit plus le titre
	mainWindow->Zoom();

	_jour->infoWin=infoWindow; //pour pouvoir envoyer des messages depuis
	_jour->mainWin=mainWindow; //pour pouvoir envoyer des messages depuis
	
	mainWindow->inside_view->MultiplyAll();
	mainWindow->Lock();	
	mainWindow->Show();
 	mainWindow->Unlock();	

	infoWindow->Lock();	
	infoWindow->Show();
 	infoWindow->Unlock();	
 	
 	
 	//classe qui tourne en permanence et qui fait les daypassed (et par conséquent, les battle etc. 
	run_me = new Running(_country,_group,_politic,_weapon,_jour);
	runWin = new BWindow(BRect(0,0,0,0), "W6 time run", B_TITLED_WINDOW,  B_NOT_RESIZABLE); 
	runWin->AddChild(run_me); //sinon le pulse fonctionne pas...					  
	runWin->Lock();  
	runWin->Show(); //faut faire show pour lancer le pulse dans les views
	runWin->Hide(); //quitte à hider la window ensuite
	runWin->Unlock();  
						  
	ChooseWindow *firstWindow = new ChooseWindow(_country,_group,_jour);
	firstWindow->Lock();  
	firstWindow->Show();  
	firstWindow->Unlock();   
	_jour->PlaySoundFile("startup.aiff");
}//fin mainappplication

bool W6Application::QuitRequested()
{//c'est le QuitRequested de W6Application qui reçoit les raccourcis clavier (CMD+Q)
	BAlert	*alert = new BAlert("","Hey you! Not so fast! Don't you even wish to Save Game before quitting?","Cancel", "Quit", "Save");
	int32	button_index;

 	button_index = alert->Go();
   	switch(button_index)
   	{
   	case 1:
		return true;
		break;
	case 2:
		{
			BAlert *alert = new BAlert("","In fact, you cannot save","Yurgl?"); 
			alert->Go();
		}
		break;
	default:
		;// on fait rien on retourne au jeu !    
	}
	return false;
}


void W6Application::MessageReceived(BMessage *message)
{
	// Print the message to see its contents
	message->PrintToStream();
	
 	switch(message->what)
 	{
	case B_SAVE_REQUESTED://le load est dans RefsReceived()
		{	//**************************************************************
			// SAVE
			//**************************************************************
			entry_ref ref;
			message->FindRef("refs", &ref); //cherche s'il y a nom file dans msg et le met dans ref
			BEntry entry(&ref); 
			
			char txt[255];
  			entry.GetName(txt);
			BAlert *xlert = new BAlert("",txt,"Alors?"); 
  		    xlert->Go();
  		
   			BMessage msg_dat; 
   			BBitmap *tmp_bitmap = new BBitmap(BRect(0,0,320,200),B_CMAP8);
   
			//*********************************************************
			//ON SAUVE L'OBJET DANS UN MESSAGE
			tmp_bitmap->Archive(&msg_dat);
	
			//faut faire ces deux a l'enregistrement et au chargement (ici on fait qu'une fois pour l'essai)
			long size = msg_dat.FlattenedSize();
			char *flat_buffer= (char*) malloc(size); //on alloue de la ram pour stocker l'objet à sauver

			msg_dat.Flatten(flat_buffer,size); //Faut aplatir avant de pouvoir sauver...
  
			//on enregistre le fichier (on le crée au besoin)
			// sprintf(txt,"daube.dab");
			BFile fich= BFile(txt, B_CREATE_FILE | B_WRITE_ONLY);
 
			//si erreur d'écriture ou lecture retour est négatif donc erreur
			if(fich.Write(flat_buffer, size) < 0) 
			{
				BAlert *alert = new BAlert("","Erreur d'enregistrement","oops..."); 
				alert->Go();	
			} 
			}
		default:
			BApplication::MessageReceived(message);
	   }

}//fin message received


void W6Application::RefsReceived(BMessage *message)
{

	if (_jour->is_flag_load==ON)
	{	
		//load du drapeau
		entry_ref ref;
		message->FindRef("refs", &ref);
		BEntry entry(&ref); 
		char txt[255];
		entry.GetName(txt);


		//BAlert * alert = new BAlert("",txt,"Do it"); alert->Go();
    				
		//le dossier app et scenar sont rajoutes dans load_bmp
		sprintf(_group[_jour->active_group]->flag_file_name,txt);
		_group[_jour->active_group]->load_bmp();
			
		_jour->editWin->Show();	_jour->edit_grpWin->Show(); //parce-qu'on les a cachés pour afficher le filepanel
		_jour->infoWin->PostMessage(DRAW_INFO);
		_jour->edit_grpWin->PostMessage(SET_GRP_EDIT);			
	}
	else
	{
		//**************************************************************
		// LOAD
		//**************************************************************
		BAlert *alert;
		entry_ref ref;
		message->FindRef("refs", &ref); //cherche s'il y a nom file dans msg et le met dans ref
		BEntry entry(&ref); 
		char txt[255];
		entry.GetName(txt);

		BMessage msg; //message ou stocker l'objet sauvé avant Unflatten et Cast dans sa forme originelle

		BFile fich;
  		fich.SetTo(&entry,B_READ_ONLY);
  		off_t size; //type données pour taille (offset, pas ssize_t)
  		fich.GetSize(&size); 
  		char *flat_buffer= (char*) malloc(size); //on alloue de la ram pour stocker l'objet à sauver

		//on le charge
  		if (fich.Read(flat_buffer, size) < 0)
  		{
  		   	alert = new BAlert("","Erreur de chargement","oops..."); 
  		   	alert->Go();
  		} 
 
 		//on récupère l'objet dans le msg et on le réassigne au type bitmap (class BBitmap)
  		msg.Unflatten(flat_buffer);
  		BArchivable *archived_data = instantiate_object(&msg); 
/*
//ATTENTION CA MERDE SI C'est pas le bon type!
			//la ça restaure un bmp faut faire avec country, group etc.
   			if ( archived_data ) //si pas null
   			{  
 			   	Lock();
 			   	_country[USA] = cast_as(archived_data, Country);
       			Unlock();
		    }
		    
		    */
		    
		    //désactivé ça compile plus depuis la 4.6 et c'est pas utile pour instant
		    
		    
		delete flat_buffer; //un peu d'économie	
		delete archived_data;
   		
   		char str[1023];
   		char str2[255];

   		sprintf(str,"File name: ");
   		sprintf(str2,txt);
  		strcat(str,str2);
		sprintf(str2,"\nName: ");
		strcat(str,str2);
		sprintf(str2,_country[USA]->Name());   
		strcat(str,str2);
    
		alert = new BAlert("",str, "Daube"); 
		alert->Go();  		
	}
	_jour->is_flag_load=OFF;
}

/**** repertoire application ****/
BString W6Application::app_dir()
{
	BString		app_path;

	//tout ça pour trouver le dir de l'application, UN PEU LOURD!!! enfin...
	app_info info;
	BPath path;
	be_app->GetAppInfo(&info);  //infos sur l'app dont le directory
	BEntry tmp_entry(&info.ref);
	BEntry file_entry;
	tmp_entry.GetParent(&file_entry); //on revient en arrier car il y a le nom de l'exec!
	file_entry.GetPath(&path); 
	app_path = path.Path();
	app_path << "/w6s/";

	return	app_path;
}  	

/**** charger les images ****/
BBitmap *W6Application::LoadBitmap(const char *filename)
{
  	BBitmap *result = NULL; 
	BFile file(filename, B_READ_ONLY);
	
	result = BTranslationUtils::GetBitmapFile(filename);
 
	// info
	cout << "chargement image : " << filename << " resultat : " << (int32)result << endl;
	
  	return result;
}
