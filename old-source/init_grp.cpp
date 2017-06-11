//PAR DEFAUT TOUT LES GROUPES SONT AU COMPUTER
//creation de Groupes et Politiques plus bas

//les numeros des politiques sont définis dans def_col
//PO_ANARCHY =0 ... PO_SOCIALISM=6
 jour->politic_first = PO_ANARCHY;   //premier groupe
 jour->politic_last  = PO_SOCIALISM; //dernier groupe
 Pol_pointer[PO_ANARCHY]    = new Politic    ("Anarchy"   ,PO_ANARCHY);
 Pol_pointer[PO_DEMOCRACY]  = new Politic    ("Democracy" ,PO_DEMOCRACY);
 Pol_pointer[PO_FASCISM]    = new Politic    ("Fascism"   ,PO_FASCISM);
 Pol_pointer[PO_COMMUNISM]  = new Politic    ("Communism" ,PO_COMMUNISM);
 Pol_pointer[PO_KINGDOM]    = new Politic    ("Kingdom"   ,PO_KINGDOM);
 Pol_pointer[PO_THEOCRACY]  = new Politic    ("Theocracy" ,PO_THEOCRACY);
 Pol_pointer[PO_SOCIALISM]  = new Politic    ("Socialism" ,PO_SOCIALISM);
 
 //pour sea and border fake countries
 Pol_pointer[PO_NOTHING]    = new Politic      ("FAKE POLITIC" ,PO_NOTHING);
 //par défaut, elle est amie avec tous donc on modifie rien
 
 //repression (1 à 100);
 Pol_pointer[PO_ANARCHY]->repression=0; 
 Pol_pointer[PO_DEMOCRACY]->repression=10; 
 Pol_pointer[PO_FASCISM]->repression=95; 
 Pol_pointer[PO_COMMUNISM]->repression=75; 
 Pol_pointer[PO_KINGDOM]->repression=50; 
 Pol_pointer[PO_THEOCRACY]->repression=85; 
 Pol_pointer[PO_SOCIALISM]->repression=15; 
 Pol_pointer[PO_NOTHING]->repression=0; 
 
 //propaganda (1 à 100);
 Pol_pointer[PO_ANARCHY]->propaganda=0; 
 Pol_pointer[PO_DEMOCRACY]->propaganda=10; 
 Pol_pointer[PO_FASCISM]->propaganda=30; 
 Pol_pointer[PO_COMMUNISM]->propaganda=35; 
 Pol_pointer[PO_KINGDOM]->propaganda=15; 
 Pol_pointer[PO_THEOCRACY]->propaganda=20; 
 Pol_pointer[PO_SOCIALISM]->propaganda=20; 
 Pol_pointer[PO_NOTHING]->propaganda=0; 
 
//-------------------------------------------------------------------------------------------
 
 
 //Relations entre les politiques

 //anarchy
 Pol_pointer[PO_ANARCHY]->relation[PO_ANARCHY]=FRIEND; //Anarchy "aime" tout le monde
 Pol_pointer[PO_ANARCHY]->relation[PO_DEMOCRACY]=FRIEND; //et attaque personne
 Pol_pointer[PO_ANARCHY]->relation[PO_FASCISM]=FRIEND; 
 Pol_pointer[PO_ANARCHY]->relation[PO_COMMUNISM]=FRIEND; 
 Pol_pointer[PO_ANARCHY]->relation[PO_KINGDOM]=FRIEND;
 Pol_pointer[PO_ANARCHY]->relation[PO_THEOCRACY]=FRIEND; 
 Pol_pointer[PO_ANARCHY]->relation[PO_SOCIALISM]=FRIEND; 
 Pol_pointer[PO_ANARCHY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Democracy
 Pol_pointer[PO_DEMOCRACY]->relation[PO_ANARCHY]=NEUTRAL; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_DEMOCRACY]=FRIEND; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_FASCISM]=ENNEMY; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_COMMUNISM]=NEUTRAL; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_KINGDOM]=ENNEMY; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_THEOCRACY]=ENNEMY; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_SOCIALISM]=NEUTRAL; 
 Pol_pointer[PO_DEMOCRACY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Fascism
 Pol_pointer[PO_FASCISM]->relation[PO_ANARCHY]=ENNEMY; 
 Pol_pointer[PO_FASCISM]->relation[PO_DEMOCRACY]=ENNEMY; 
 Pol_pointer[PO_FASCISM]->relation[PO_FASCISM]=NEUTRAL; 
 Pol_pointer[PO_FASCISM]->relation[PO_COMMUNISM]=ENNEMY;  
 Pol_pointer[PO_FASCISM]->relation[PO_KINGDOM]=NEUTRAL;  
 Pol_pointer[PO_FASCISM]->relation[PO_THEOCRACY]=NEUTRAL;  
 Pol_pointer[PO_FASCISM]->relation[PO_SOCIALISM]=ENNEMY;  
 Pol_pointer[PO_FASCISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Communism
 Pol_pointer[PO_COMMUNISM]->relation[PO_ANARCHY]=NEUTRAL; //Fascism deteste tous meme fascism
 Pol_pointer[PO_COMMUNISM]->relation[PO_DEMOCRACY]=NEUTRAL; 
 Pol_pointer[PO_COMMUNISM]->relation[PO_FASCISM]=ENNEMY; 
 Pol_pointer[PO_COMMUNISM]->relation[PO_COMMUNISM]=FRIEND;  
 Pol_pointer[PO_COMMUNISM]->relation[PO_KINGDOM]=ENNEMY;  
 Pol_pointer[PO_COMMUNISM]->relation[PO_THEOCRACY]=ENNEMY;  
 Pol_pointer[PO_COMMUNISM]->relation[PO_SOCIALISM]=NEUTRAL;  
 Pol_pointer[PO_COMMUNISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Kingdom
 Pol_pointer[PO_KINGDOM]->relation[PO_ANARCHY]=ENNEMY; 
 Pol_pointer[PO_KINGDOM]->relation[PO_DEMOCRACY]=ENNEMY; 
 Pol_pointer[PO_KINGDOM]->relation[PO_FASCISM]=NEUTRAL; 
 Pol_pointer[PO_KINGDOM]->relation[PO_COMMUNISM]=ENNEMY;  
 Pol_pointer[PO_KINGDOM]->relation[PO_KINGDOM]=NEUTRAL;  
 Pol_pointer[PO_KINGDOM]->relation[PO_THEOCRACY]=NEUTRAL;  
 Pol_pointer[PO_KINGDOM]->relation[PO_SOCIALISM]=ENNEMY;  
 Pol_pointer[PO_KINGDOM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Theocracy
 Pol_pointer[PO_THEOCRACY]->relation[PO_ANARCHY]=ENNEMY; 
 Pol_pointer[PO_THEOCRACY]->relation[PO_DEMOCRACY]=ENNEMY; 
 Pol_pointer[PO_THEOCRACY]->relation[PO_FASCISM]=NEUTRAL; 
 Pol_pointer[PO_THEOCRACY]->relation[PO_COMMUNISM]=ENNEMY;  
 Pol_pointer[PO_THEOCRACY]->relation[PO_KINGDOM]=NEUTRAL;  
 Pol_pointer[PO_THEOCRACY]->relation[PO_THEOCRACY]=ENNEMY;  
 Pol_pointer[PO_THEOCRACY]->relation[PO_SOCIALISM]=ENNEMY;  
 Pol_pointer[PO_THEOCRACY]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 

 //Socialism
 Pol_pointer[PO_SOCIALISM]->relation[PO_ANARCHY]=NEUTRAL; 
 Pol_pointer[PO_SOCIALISM]->relation[PO_DEMOCRACY]=NEUTRAL; 
 Pol_pointer[PO_SOCIALISM]->relation[PO_FASCISM]=ENNEMY; 
 Pol_pointer[PO_SOCIALISM]->relation[PO_COMMUNISM]=NEUTRAL;  
 Pol_pointer[PO_SOCIALISM]->relation[PO_KINGDOM]=ENNEMY;  
 Pol_pointer[PO_SOCIALISM]->relation[PO_THEOCRACY]=ENNEMY;  
 Pol_pointer[PO_SOCIALISM]->relation[PO_SOCIALISM]=FRIEND;  
 Pol_pointer[PO_SOCIALISM]->relation[PO_NOTHING]=FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 


 //NOTHING
 Pol_pointer[PO_NOTHING]->relation[PO_ANARCHY]   = FRIEND; 
 Pol_pointer[PO_NOTHING]->relation[PO_DEMOCRACY] = FRIEND; 
 Pol_pointer[PO_NOTHING]->relation[PO_FASCISM]   = FRIEND; 
 Pol_pointer[PO_NOTHING]->relation[PO_COMMUNISM] = FRIEND;  
 Pol_pointer[PO_NOTHING]->relation[PO_KINGDOM]   = FRIEND;  
 Pol_pointer[PO_NOTHING]->relation[PO_THEOCRACY] = FRIEND;  
 Pol_pointer[PO_NOTHING]->relation[PO_SOCIALISM] = FRIEND;  
 Pol_pointer[PO_NOTHING]->relation[PO_NOTHING]   = FRIEND; //POUR FAKE COUNTRIES (histoire que personne les attaque) 




//----------------------------------------------------



//----------------------------------------------------
//CREATION GROUPES
  
 rgb_color couleur;

 jour->group_first=GRP_A; //premier groupe

 couleur= (rgb_color) {230,230,230,0};
 Grp_pointer[GRP_A]      = new Group  		(COMPUTER,"Pacific Union",GRP_A,couleur,PO_ANARCHY,"pacific.png",jour);

 couleur= (rgb_color) {190,160,172,0};
 Grp_pointer[GRP_B]         =  new Group		(COMPUTER,"White Nationalists",GRP_B,couleur,PO_FASCISM,"white.png",jour);

 couleur= (rgb_color) {230,170,0,0};
 Grp_pointer[GRP_C]         = new Group        (COMPUTER,"African Union",GRP_C,couleur,PO_DEMOCRACY,"africa.png",jour);

 couleur= (rgb_color) {240,0,0,0};
 Grp_pointer[GRP_D]         = new Group    (COMPUTER,"Neo-Communist Union",GRP_D,couleur,PO_COMMUNISM,"soviet.png",jour);
 
 couleur= (rgb_color) {97,181,90,0};
 Grp_pointer[GRP_E]         =  new Group           (COMPUTER,"Islamic Revolution",GRP_E,couleur,PO_THEOCRACY,"islam.png",jour);
 
 couleur= (rgb_color) {255,255,100,0};
 Grp_pointer[GRP_F]         = new Group        (COMPUTER,"Sun Empire",GRP_F,couleur,PO_KINGDOM,"japan.png",jour);

 couleur= (rgb_color) {98,156,255,0};
 Grp_pointer[GRP_G]         = new Group          (COMPUTER,"European Union",GRP_G,couleur,PO_DEMOCRACY,"europe.png",jour);

 couleur= (rgb_color) {186,200,255,0};
 Grp_pointer[GRP_H]         = new Group          (COMPUTER,"Christian Nation",GRP_H,couleur,PO_THEOCRACY,"christ.png",jour);

 couleur= (rgb_color) {255,100,185,0};
 Grp_pointer[GRP_I]         =new Group         (COMPUTER,"Socialist Group",GRP_I,couleur,PO_SOCIALISM,"social.png",jour);

 couleur= (rgb_color) {255,210,210,0};
 Grp_pointer[GRP_J]         = new Group      (COMPUTER,"Roschti Neutral Activists",GRP_J,couleur,PO_DEMOCRACY,"roschti.png",jour);
 
 jour->group_last=GRP_J; //dernier groupe
 
 couleur= (rgb_color) {0,255,120,120}; //vert pétant
 Grp_pointer[GRP_X]         = new Group      (COMPUTER,"Fake for sea and border",GRP_X,couleur,PO_NOTHING,"",jour);
 
