///ATTENTION TOUTES CES DONNEES DE POPULATION DATENT DE 1969-70!!!!
//faut avancer dans le temps avant de commencer ailleurs qu'en 1970

/**********************************************************************/
/**********************************************************************/
//GROUP_G
//DEFINITIONS POUR LE GROUPE EUROPE
/**********************************************************************/
/**********************************************************************/

/*
ATTENTION GRAND CON, oui ça changé entre l'europe et les autres groupes.
des fois on a créée bêtement des pointeurs en trop alors qu'on a pas besoin
ils sont déja dans Ct_pointer... sauf que comme on utilise ces pointeur dans
DATA.CPP FAUT PAS MODIFIER, de toute façon ces données finiront dans
un fichier .w6s tôt ou tard. Pigé?

*/


//par défaut access_sea=ON, access_nuke=OFF
//Portugal----------------------------------------------
   Ct_pointer[PORTUGAL]->set_population  (32807000);
   Ct_pointer[PORTUGAL]->set_birth_rate  (1.6);
   Ct_pointer[PORTUGAL]->set_tech_level  (65);
   Ct_pointer[PORTUGAL]->set_pnb         (1000);

//Spain----------------------------------------------
   Ct_pointer[SPAIN]->set_population  (33290000);
   Ct_pointer[SPAIN]->set_birth_rate  (1.3);
   Ct_pointer[SPAIN]->set_tech_level  (70);
   Ct_pointer[SPAIN]->set_pnb         (1200);
//France----------------------------------------------
   Ct_pointer[FRANCE]->set_population  (50770000);
   Ct_pointer[FRANCE]->set_birth_rate  (1.3);
   Ct_pointer[FRANCE]->set_tech_level  (85);
   Ct_pointer[FRANCE]->set_pnb         (2400);
   Ct_pointer[FRANCE]->access_nuke     = ON  ;
//United Kingdom----------------------------------------------
   Ct_pointer[UK]->set_population  (55711000);
   Ct_pointer[UK]->set_birth_rate  (1.3);
   Ct_pointer[UK]->set_tech_level  (85);
   Ct_pointer[UK]->set_pnb         (1950);
   Ct_pointer[UK]->access_nuke     = ON  ;  //officiel
//Austria----------------------------------------------
   Ct_pointer[AUSTRIA]->set_population  (13000000);
   Ct_pointer[AUSTRIA]->set_birth_rate  (1.3);
   Ct_pointer[AUSTRIA]->set_tech_level  (80);
   Ct_pointer[AUSTRIA]->set_pnb         (1950);
   Ct_pointer[AUSTRIA]->access_nuke     = OFF  ;
//Ct_pointer[ITALY]----------------------------------------------
   Ct_pointer[ITALY]->set_population  (53170000);
   Ct_pointer[ITALY]->set_birth_rate  (1.3);
   Ct_pointer[ITALY]->set_tech_level  (80);
   Ct_pointer[ITALY]->set_pnb         (1800);
//Ct_pointer[BELGIUM]----------------------------------------------
   Ct_pointer[BELGIUM]->set_population  (9646000);
   Ct_pointer[BELGIUM]->set_birth_rate  (1.3);
   Ct_pointer[BELGIUM]->set_tech_level  (80);
   Ct_pointer[BELGIUM]->set_pnb         (2080);
//Slovaquie----------------------------------------------
   Ct_pointer[SLOVAKIA]->set_population  (6120000); //environ 40% tchecoslovaquie!
   Ct_pointer[SLOVAKIA]->set_birth_rate  (1.6);
   Ct_pointer[SLOVAKIA]->set_tech_level  (70);
   Ct_pointer[SLOVAKIA]->set_pnb         (1000);
   Ct_pointer[SLOVAKIA]->access_sea      = OFF  ;
//Ct_pointer[GERMANY]----------------------------------------------
   Ct_pointer[GERMANY]->set_population  (75554000);
   Ct_pointer[GERMANY]->set_birth_rate  (1.3);
   Ct_pointer[GERMANY]->set_tech_level  (80);
   Ct_pointer[GERMANY]->set_pnb         (2180);
//Ct_pointer[NETHERLANDS]----------------------------------------------
   Ct_pointer[NETHERLANDS]->set_population  (13019000);
   Ct_pointer[NETHERLANDS]->set_birth_rate  (1.4);
   Ct_pointer[NETHERLANDS]->set_tech_level  (80);
   Ct_pointer[NETHERLANDS]->set_pnb         (1970);
//Ct_pointer[DENMARK]----------------------------------------------
   Ct_pointer[DENMARK]->set_population  (4891000);
   Ct_pointer[DENMARK]->set_birth_rate  (1.4);
   Ct_pointer[DENMARK]->set_tech_level  (80);
   Ct_pointer[DENMARK]->set_pnb         (2420);
//Ct_pointer[NORWAY]----------------------------------------------
   Ct_pointer[NORWAY]->set_population  (3879000);
   Ct_pointer[NORWAY]->set_birth_rate  (1.3);
   Ct_pointer[NORWAY]->set_tech_level  (75);
   Ct_pointer[NORWAY]->set_pnb         (2280);
//Ct_pointer[CZECHIA]----------------------------------------------
   Ct_pointer[CZECHIA]->set_population  (8443000);  //env. 65% tchecoslovaquie
   Ct_pointer[CZECHIA]->set_birth_rate  (1.5);
   Ct_pointer[CZECHIA]->set_tech_level  (70);
   Ct_pointer[CZECHIA]->set_pnb         (1200);
   Ct_pointer[CZECHIA]->access_sea      = OFF  ;
//Ct_pointer[GREECE]----------------------------------------------
   Ct_pointer[GREECE]->set_population  (8880000);
   Ct_pointer[GREECE]->set_birth_rate  (1.5);
   Ct_pointer[GREECE]->set_tech_level  (70);
   Ct_pointer[GREECE]->set_pnb         (900);
//Ct_pointer[SERBIA]----------------------------------------------
   Ct_pointer[SERBIA]->set_population  (6040000); //deduit d'apres yougo.
   Ct_pointer[SERBIA]->set_birth_rate  (1.5);
   Ct_pointer[SERBIA]->set_tech_level  (65);
   Ct_pointer[SERBIA]->set_pnb         (510);
//Ct_pointer[LITHUANIA]----------------------------------------------
   Ct_pointer[LITHUANIA]->set_population  (1300000); //au bol!
   Ct_pointer[LITHUANIA]->set_birth_rate  (1.5);
   Ct_pointer[LITHUANIA]->set_tech_level  (65);
   Ct_pointer[LITHUANIA]->set_pnb         (850);
//Ct_pointer[SWEDEN]----------------------------------------------
   Ct_pointer[SWEDEN]->set_population  (8093000);
   Ct_pointer[SWEDEN]->set_birth_rate  (1.3);
   Ct_pointer[SWEDEN]->set_tech_level  (75);
   Ct_pointer[SWEDEN]->set_pnb         (2920);
//Ct_pointer[POLAND]----------------------------------------------
   Ct_pointer[POLAND]->set_population  (32807000);
   Ct_pointer[POLAND]->set_birth_rate  (1.6);
   Ct_pointer[POLAND]->set_tech_level  (65);
   Ct_pointer[POLAND]->set_pnb         (940);
//Ct_pointer[SWITZERLAND]----------------------------------------------
   Ct_pointer[SWITZERLAND]->set_population  (6270000);
   Ct_pointer[SWITZERLAND]->set_birth_rate  (1.5);
   Ct_pointer[SWITZERLAND]->set_tech_level  (75);
   Ct_pointer[SWITZERLAND]->set_pnb         (2710);
   Ct_pointer[SWITZERLAND]->access_sea      = OFF  ;
//Ct_pointer[FINLAND]----------------------------------------------
   Ct_pointer[FINLAND]->set_population  (4710000);
   Ct_pointer[FINLAND]->set_birth_rate  (1.3);
   Ct_pointer[FINLAND]->set_tech_level  (70);
   Ct_pointer[FINLAND]->set_pnb         (1740);
//Ct_pointer[ESTONIA]----------------------------------------------
   Ct_pointer[ESTONIA]->set_population  (900000);   //AU BOL!!!
   Ct_pointer[ESTONIA]->set_birth_rate  (1.6);
   Ct_pointer[ESTONIA]->set_tech_level  (65);
   Ct_pointer[ESTONIA]->set_pnb         (850);
//Ct_pointer[LETTONIA]----------------------------------------------
   Ct_pointer[LETTONIA]->set_population  (852000);  //AU BOL!!!
   Ct_pointer[LETTONIA]->set_birth_rate  (1.6);
   Ct_pointer[LETTONIA]->set_tech_level  (65);
   Ct_pointer[LETTONIA]->set_pnb         (850);
//Ct_pointer[IRELAND]----------------------------------------------
   Ct_pointer[IRELAND]->set_population  (2944000);
   Ct_pointer[IRELAND]->set_birth_rate  (1.3);
   Ct_pointer[IRELAND]->set_tech_level  (70);
   Ct_pointer[IRELAND]->set_pnb         (1000);
//Ct_pointer[BOSNIA]----------------------------------------------
   Ct_pointer[BOSNIA]->set_population  (3950000); //deduction d'apres yougo
   Ct_pointer[BOSNIA]->set_birth_rate  (1.6);
   Ct_pointer[BOSNIA]->set_tech_level  (65);
   Ct_pointer[BOSNIA]->set_pnb         (510);
//Ct_pointer[CROATIA]----------------------------------------------
   Ct_pointer[CROATIA]->set_population  (5980000);      //deduction d'apres yougo
   Ct_pointer[CROATIA]->set_birth_rate  (1.6);
   Ct_pointer[CROATIA]->set_tech_level  (65);
   Ct_pointer[CROATIA]->set_pnb         (510);
//Ct_pointer[SLOVENIA]----------------------------------------------
   Ct_pointer[SLOVENIA]->set_population  (3450000);    //deduction d'apres yougo
   Ct_pointer[SLOVENIA]->set_birth_rate  (1.4);
   Ct_pointer[SLOVENIA]->set_tech_level  (65);
   Ct_pointer[SLOVENIA]->set_pnb         (600);
//Ct_pointer[GUYANA_FR]----------------------------------------------
   Ct_pointer[GUYANA_FR]->set_population  (48000);
   Ct_pointer[GUYANA_FR]->set_birth_rate  (1.6);
   Ct_pointer[GUYANA_FR]->set_tech_level  (80);
   Ct_pointer[GUYANA_FR]->set_pnb         (2000);
//Ct_pointer[SURINAM]----------------------------------------------
   Ct_pointer[SURINAM]->set_population  (403000);
   Ct_pointer[SURINAM]->set_birth_rate  (1.7);
   Ct_pointer[SURINAM]->set_tech_level  (75);
   Ct_pointer[SURINAM]->set_pnb         (600);
//Ct_pointer[ICELAND]----------------------------------------------
   Ct_pointer[ICELAND]->set_population  (205000);
   Ct_pointer[ICELAND]->set_birth_rate  (1.3);
   Ct_pointer[ICELAND]->set_tech_level  (70);
   Ct_pointer[ICELAND]->set_pnb         (1740);
//Ct_pointer[groenland]----------------------------------------------
   Ct_pointer[GROENLAND]->set_population  (47000);
   Ct_pointer[GROENLAND]->set_birth_rate  (1.3);
   Ct_pointer[GROENLAND]->set_tech_level  (65);
   Ct_pointer[GROENLAND]->set_pnb         (2000);

//----------------------------------------------
   Ct_pointer[HUNGARY]->set_population  (10331000);
   Ct_pointer[HUNGARY]->set_birth_rate  (1.6);
   Ct_pointer[HUNGARY]->set_tech_level  (65);
   Ct_pointer[HUNGARY]->set_pnb         (1100);
   Ct_pointer[HUNGARY]->access_sea      = OFF ;
//----------------------------------------------
   Ct_pointer[ROMANIA]->set_population  (20253000);
   Ct_pointer[ROMANIA]->set_birth_rate  (1.6);
   Ct_pointer[ROMANIA]->set_tech_level  (70);
   Ct_pointer[ROMANIA]->set_pnb         (860);
//----------------------------------------------
   Ct_pointer[BULGARIA]->set_population  (8500000);
   Ct_pointer[BULGARIA]->set_birth_rate  (1.6);
   Ct_pointer[BULGARIA]->set_tech_level  (70);
   Ct_pointer[BULGARIA]->set_pnb         (620);
//----------------------------------------------
   Ct_pointer[ALBANIA]->set_population  (2075000);
   Ct_pointer[ALBANIA]->set_birth_rate  (1.7);
   Ct_pointer[ALBANIA]->set_tech_level  (65);
   Ct_pointer[ALBANIA]->set_pnb         (440);

/**********************************************************************/
/**********************************************************************/
//GROUP_D
//DEFINITIONS POUR LE GROUPE COMMUNISME
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
   russia->set_population  (180000000);  //deduit d'URSS (250 mio)
   russia->set_birth_rate  (1.6);
   russia->set_tech_level  (84);  //seuil avant division infantry
   russia->set_pnb         (2100); //plus haut que le reste URSS
   russia->access_nuke     = ON ;
//----------------------------------------------
   mongolia->set_population  (1240000);
   mongolia->set_birth_rate  (1.6);
   mongolia->set_tech_level  (65);
   mongolia->set_pnb         (250);
//----------------------------------------------
   china->set_population  (830000000);
   china->set_birth_rate  (1.7);
   china->set_tech_level  (60);
   china->set_pnb         (200);
   china->access_nuke     = ON ;
//----------------------------------------------
   belarus->set_population  (17500000); //deduit d'URSS (250 mio)
   belarus->set_birth_rate  (1.6);
   belarus->set_tech_level  (75);
   belarus->set_pnb         (1000);
   belarus->access_sea      = OFF  ;
//----------------------------------------------
   ukraine->set_population  (20200000); //deduit d'URSS (250 mio)
   ukraine->set_birth_rate  (1.5);
   ukraine->set_tech_level  (83);
   ukraine->set_pnb         (1200);
   ukraine->access_nuke     = ON ;
//----------------------------------------------
   moldavia->set_population  (3000000);  //deduit d'URSS (250 mio)
   moldavia->set_birth_rate  (1.6);
   moldavia->set_tech_level  (75);
   moldavia->set_pnb         (900);
   moldavia->access_sea      = OFF  ;
//----------------------------------------------
   georgia->set_population  (4000000);   //deduit d'URSS (250 mio)
   georgia->set_birth_rate  (1.6);
   georgia->set_tech_level  (75);
   georgia->set_pnb         (900);
//----------------------------------------------
   armenia->set_population  (2600000);    //deduit d'URSS (250 mio)
   armenia->set_birth_rate  (1.6);
   armenia->set_tech_level  (65);
   armenia->set_pnb         (700);
   armenia->access_sea      = OFF  ;
//----------------------------------------------
   kazakhstan->set_population  (6200000);      //deduit d'URSS (250 mio)
   kazakhstan->set_birth_rate  (1.6);
   kazakhstan->set_tech_level  (70);
   kazakhstan->set_pnb         (500);
   kazakhstan->access_sea      = OFF  ;
//----------------------------------------------
   uzbekistan->set_population  (4000000);
   uzbekistan->set_birth_rate  (1.6);
   uzbekistan->set_tech_level  (70);
   uzbekistan->set_pnb         (600);
   uzbekistan->access_sea      = OFF ;
//----------------------------------------------
   tadzikistan->set_population  (2000000);
   tadzikistan->set_birth_rate  (1.6);
   tadzikistan->set_tech_level  (70);
   tadzikistan->set_pnb         (500);
   tadzikistan->access_sea      = OFF  ;
//----------------------------------------------
   kirgikistan->set_population  (2500000);
   kirgikistan->set_birth_rate  (1.6);
   kirgikistan->set_tech_level  (70);
   kirgikistan->set_pnb         (400);
   kirgikistan->access_sea      = OFF  ;
//----------------------------------------------
   north_korea->set_population  (13600000);
   north_korea->set_birth_rate  (1.6);
   north_korea->set_tech_level  (70);
   north_korea->set_pnb         (250);

/**********************************************************************/
/**********************************************************************/
//GROUP_E
//DEFINITIONS POUR LE GROUPE ISLAM
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
   turkey->set_population  (34500000);
   turkey->set_birth_rate  (1.8);
   turkey->set_tech_level  (65);
   turkey->set_pnb         (400);
//----------------------------------------------
   afghanistan->set_population  (17125000);
   afghanistan->set_birth_rate  (2.0);
   afghanistan->set_tech_level  (55);
   afghanistan->set_pnb         (70);
   afghanistan->access_sea      = OFF  ;
//----------------------------------------------
   iran->set_population  (28662000);
   iran->set_birth_rate  (2.0);
   iran->set_tech_level  (55);
   iran->set_pnb         (300);
//----------------------------------------------
   irak->set_population  (9350000);
   irak->set_birth_rate  (1.9);
   irak->set_tech_level  (70);
   irak->set_pnb         (350);
   irak->access_sea      = OFF ;  //ou alors a peine?
//----------------------------------------------
   saudi_arabia->set_population  (6870000);
   saudi_arabia->set_birth_rate  (2.3);
   saudi_arabia->set_tech_level  (65);
   saudi_arabia->set_pnb         (500);
//----------------------------------------------
   koweit->set_population  (600000);
   koweit->set_birth_rate  (2.0);
   koweit->set_tech_level  (70);
   koweit->set_pnb         (4830); //wow!
//----------------------------------------------
   egypt->set_population  (33329000);
   egypt->set_birth_rate  (2.0);
   egypt->set_tech_level  (65);
   egypt->set_pnb         (170);
//----------------------------------------------
   jordania->set_population  (2217000);
   jordania->set_birth_rate  (1.9);
   jordania->set_tech_level  (68);
   jordania->set_pnb         (220);
   jordania->access_sea      = OFF  ;
//----------------------------------------------
   syria->set_population  (6098000);
   syria->set_birth_rate  (2.0);
   syria->set_tech_level  (65);
   syria->set_pnb         (260);
//----------------------------------------------
   sudan->set_population  (15695000);
   sudan->set_birth_rate  (2.4);
   sudan->set_tech_level  (45);
   sudan->set_pnb         (110);
//----------------------------------------------
   lybia->set_population  (6869000);
   lybia->set_birth_rate  (2.0);
   lybia->set_tech_level  (60);
   lybia->set_pnb         (1700);
//----------------------------------------------
   tunisia->set_population  (5137000);
   tunisia->set_birth_rate  (2.0);
   tunisia->set_tech_level  (65);
   tunisia->set_pnb         (300);
//----------------------------------------------
   algeria->set_population  (13349000);
   algeria->set_birth_rate  (2.8);
   algeria->set_tech_level  (65);
   algeria->set_pnb         (280);
//----------------------------------------------
   morocco->set_population  (15525000);
   morocco->set_birth_rate  (2.0);
   morocco->set_tech_level  (65);
   morocco->set_pnb         (190);
//----------------------------------------------
   djibouti->set_population  (500000); //AU BOL!!
   djibouti->set_birth_rate  (2.0);
   djibouti->set_tech_level  (65);
   djibouti->set_pnb         (200);  //AU BOL!!!
//----------------------------------------------
   somalia->set_population  (2730000);
   somalia->set_birth_rate  (2.9);
   somalia->set_tech_level  (50);
   somalia->set_pnb         (70);
//----------------------------------------------
   qatar->set_population  (100000);
   qatar->set_birth_rate  (2.0);
   qatar->set_tech_level  (70);
   qatar->set_pnb         (800);
//----------------------------------------------
   azerbaidjan->set_population  (3540000);  //d'apres URSS Au bol quoi...
   azerbaidjan->set_birth_rate  (2.0);
   azerbaidjan->set_tech_level  (70);
   azerbaidjan->set_pnb         (500);
   azerbaidjan->access_sea      = OFF ;
//----------------------------------------------
   turkmenistan->set_population  (3200000); //d'apres URSS Au bol quoi...
   turkmenistan->set_birth_rate  (2.0);
   turkmenistan->set_tech_level  (70);
   turkmenistan->set_pnb         (500);
   turkmenistan->access_sea      = OFF ;
//----------------------------------------------
   pakistan->set_population  (57000000);
   pakistan->set_birth_rate  (2.9);
   pakistan->set_tech_level  (65);
   pakistan->set_pnb         (105);
   pakistan->access_nuke     = ON ; //non officiel
//----------------------------------------------
   uae->set_population  (945000);  
   uae->set_birth_rate  (2.1);
   uae->set_tech_level  (65);
   uae->set_pnb         (800);
//----------------------------------------------
   yemen->set_population  (1200000);
   yemen->set_birth_rate  (2.0);
   yemen->set_tech_level  (65);
   yemen->set_pnb         (100);
//----------------------------------------------
   south_yemen->set_population  (5100000);
   south_yemen->set_birth_rate  (2.0);
   south_yemen->set_tech_level  (65);
   south_yemen->set_pnb         (110);
//----------------------------------------------
   oman->set_population  (750000);
   oman->set_birth_rate  (2.0);
   oman->set_tech_level  (65);
   oman->set_pnb         (800);
//----------------------------------------------
   malaysia->set_population  (10650000);
   malaysia->set_birth_rate  (2.6);
   malaysia->set_tech_level  (65);
   malaysia->set_pnb         (340);
//----------------------------------------------
   indonesia->set_population  (116918000);
   indonesia->set_birth_rate  (2.8);
   indonesia->set_tech_level  (65);
   indonesia->set_pnb         (90);

/**********************************************************************/
/**********************************************************************/
//GROUP_A
//DEFINITIONS POUR LE GROUPE NEUTRE ET IDEALISTE
/**********************************************************************/
/**********************************************************************/


//----------------------------------------------
  israel->set_population  (2998000);
  israel->set_birth_rate  (2.2);   //beaucoup immigr.
  israel->set_tech_level  (80);
  israel->set_pnb         (1480);
  israel->access_nuke     = ON ;  ///non officiel
//----------------------------------------------
  india->set_population  (546950000);
  india->set_birth_rate  (3.4);
  india->set_tech_level  (70);
  india->set_pnb         (80);
  india->access_nuke     = ON ; //non officiel
//----------------------------------------------
  nepal->set_population  (10465000);
  nepal->set_birth_rate  (1.9);
  nepal->set_tech_level  (65);
  nepal->set_pnb         (70);
  nepal->access_sea      = OFF  ;
//----------------------------------------------
  buthan->set_population  (800000);
  buthan->set_birth_rate  (1.8);
  buthan->set_tech_level  (65);
  buthan->set_pnb         (100);
  buthan->access_sea      = OFF ;
//----------------------------------------------
  bangla_desh->set_population  (70000000);
  bangla_desh->set_birth_rate  (3.2);
  bangla_desh->set_tech_level  (45);
  bangla_desh->set_pnb         (95);
//----------------------------------------------
  sri_lanka->set_population  (12514000);
  sri_lanka->set_birth_rate  (2.0);
  sri_lanka->set_tech_level  (65);
  sri_lanka->set_pnb         (150);
//----------------------------------------------
  australia->set_population  (12552000);
  australia->set_birth_rate  (1.8);
  australia->set_tech_level  (75);
  australia->set_pnb         (2260);
//----------------------------------------------
  new_zealand->set_population  (2816000);
  new_zealand->set_birth_rate  (1.7);
  new_zealand->set_tech_level  (65);
  new_zealand->set_pnb         (1810);
//----------------------------------------------
  new_guinea->set_population  (1701000);
  new_guinea->set_birth_rate  (1.9);
  new_guinea->set_tech_level  (60);
  new_guinea->set_pnb         (1800);
//----------------------------------------------
  lebanon->set_population  (2645000);
  lebanon->set_birth_rate  (1.6);
  lebanon->set_tech_level  (65);
  lebanon->set_pnb         (480);

/**********************************************************************/
/**********************************************************************/
//GROUP_C
//DEFINITIONS POUR LE GROUPE WEST AFRICAN
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  guinea_bissau->set_population  (530000);
  guinea_bissau->set_birth_rate  (2.8);
  guinea_bissau->set_tech_level  (45);
  guinea_bissau->set_pnb         (75);
//----------------------------------------------
  mauritania->set_population  (1150000);
  mauritania->set_birth_rate  (2.3);
  mauritania->set_tech_level  (54);
  mauritania->set_pnb         (140);
//----------------------------------------------
  senegal->set_population  (3870000);
  senegal->set_birth_rate  (2.8);
  senegal->set_tech_level  (45);
  senegal->set_pnb         (200);
//----------------------------------------------
  guinea->set_population  (3890000);
  guinea->set_birth_rate  (2.8);
  guinea->set_tech_level  (46);
  guinea->set_pnb         (100);
//----------------------------------------------
  sierra_leone->set_population  (2512000);
  sierra_leone->set_birth_rate  (2.8);
  sierra_leone->set_tech_level  (45);
  sierra_leone->set_pnb         (170);
//----------------------------------------------
  liberia->set_population  (1150000);
  liberia->set_birth_rate  (2.8);
  liberia->set_tech_level  (44);
  liberia->set_pnb         (290);
//----------------------------------------------
  ivory_coast->set_population  (4195000);
  ivory_coast->set_birth_rate  (2.8);
  ivory_coast->set_tech_level  (50);
  ivory_coast->set_pnb         (230);
//----------------------------------------------
  ghana->set_population  (8600000);
  ghana->set_birth_rate  (2.8);
  ghana->set_tech_level  (45);
  ghana->set_pnb         (220);
//----------------------------------------------
  burkina_faso->set_population  (5384000);
  burkina_faso->set_birth_rate  (2.8);
  burkina_faso->set_tech_level  (41);
  burkina_faso->set_pnb         (50);
  burkina_faso->access_sea      = OFF  ;
//----------------------------------------------
  togo->set_population  (1857000);
  togo->set_birth_rate  (2.8);
  togo->set_tech_level  (45);
  togo->set_pnb         (100);
//----------------------------------------------
  benin->set_population  (2640000);
  benin->set_birth_rate  (2.8);
  benin->set_tech_level  (45);
  benin->set_pnb         (80);
//----------------------------------------------
  mali->set_population  (10000000); //aU BOL!!
  mali->set_birth_rate  (2.8);
  mali->set_tech_level  (45);
  mali->set_pnb         (80);
//----------------------------------------------
  niger->set_population  (4016000);
  niger->set_birth_rate  (2.8);
  niger->set_tech_level  (45);
  niger->set_pnb         (80);
//----------------------------------------------
  nigeria->set_population  (66174000);
  nigeria->set_birth_rate  (2.8);
  nigeria->set_tech_level  (45);
  nigeria->set_pnb         (80);
//----------------------------------------------
  cameroon->set_population  (5836000);
  cameroon->set_birth_rate  (2.8);
  cameroon->set_tech_level  (45);
  cameroon->set_pnb         (150);
//----------------------------------------------
  tchad->set_population  (3510000);
  tchad->set_birth_rate  (2.8);
  tchad->set_tech_level  (45);
  tchad->set_pnb         (70);
  tchad->access_sea      = OFF ;
//----------------------------------------------
  centrafrica->set_population  (1518000);
  centrafrica->set_birth_rate  (2.8);
  centrafrica->set_tech_level  (45);
  centrafrica->set_pnb         (130);
  centrafrica->access_sea      = OFF  ;
//----------------------------------------------
  equatorial_guinea->set_population  (286000);
  equatorial_guinea->set_birth_rate  (2.8);
  equatorial_guinea->set_tech_level  (45);
  equatorial_guinea->set_pnb        (150);
//----------------------------------------------
  gabon->set_population  (500000);
  gabon->set_birth_rate  (2.8);
  gabon->set_tech_level  (48);
  gabon->set_pnb         (410);
//----------------------------------------------
  rep_congo->set_population  (915000);
  rep_congo->set_birth_rate  (2.8);
  rep_congo->set_tech_level  (55);
  rep_congo->set_pnb         (160);
//----------------------------------------------
  congo->set_population  (17100000);
  congo->set_birth_rate  (2.8);
  congo->set_tech_level  (50);
  congo->set_pnb         (70);
//----------------------------------------------
  uganda->set_population  (9764000);
  uganda->set_birth_rate  (2.8);
  uganda->set_tech_level  (45);
  uganda->set_pnb         (110);
  uganda->access_sea      = OFF  ;
//----------------------------------------------
  ethiopia->set_population  (24769000);
  ethiopia->set_birth_rate  (2.9);
  ethiopia->set_tech_level  (43);
  ethiopia->set_pnb         (60);
//----------------------------------------------
  kenya->set_population  (11152000);
  kenya->set_birth_rate  (2.7);
  kenya->set_tech_level  (50);
  kenya->set_pnb         (130);
//----------------------------------------------
  rwanda->set_population  (3500000);
  rwanda->set_birth_rate  (2.8);
  rwanda->set_tech_level  (45);
  rwanda->set_pnb         (80);
  rwanda->access_sea      = OFF ;
//----------------------------------------------
  burundi->set_population  (3475000);
  burundi->set_birth_rate  (2.8);
  burundi->set_tech_level  (45);
  burundi->set_pnb         (90);
  burundi->access_sea      = OFF  ;
//----------------------------------------------
  tanzania->set_population  (13273000);
  tanzania->set_birth_rate  (3.1);
  tanzania->set_tech_level  (45);
  tanzania->set_pnb         (100);
//----------------------------------------------
  mozambique->set_population  (7376000);
  mozambique->set_birth_rate  (2.8);
  mozambique->set_tech_level  (45);
  mozambique->set_pnb         (70);
//----------------------------------------------
  malawi->set_population  (4530000);
  malawi->set_birth_rate  (2.8);
  malawi->set_tech_level  (45);
  malawi->set_pnb         (60);
  malawi->access_sea      = OFF  ;
//----------------------------------------------
  madagascar->set_population  (6750000);
  madagascar->set_birth_rate  (2.8);
  madagascar->set_tech_level  (43);
  madagascar->set_pnb         (110);
//----------------------------------------------
  zambia->set_population  (4208000);
  zambia->set_birth_rate  (2.8);
  zambia->set_tech_level  (45);
  zambia->set_pnb         (280);
  zambia->access_sea      = OFF  ;
//----------------------------------------------
  zimbabwe->set_population  (5270000);
  zimbabwe->set_birth_rate  (2.8);
  zimbabwe->set_tech_level  (45);
  zimbabwe->set_pnb         (240);
  zimbabwe->access_sea      = OFF  ;
//----------------------------------------------
  botswana->set_population  (648000);
  botswana->set_birth_rate  (2.8);
  botswana->set_tech_level  (45);
  botswana->set_pnb         (180);
  botswana->access_sea      = OFF  ;
//----------------------------------------------
  namibia->set_population  (615000);
  namibia->set_birth_rate  (2.8);
  namibia->set_tech_level  (52);
  namibia->set_pnb         (250); //AU BOL!!!
//----------------------------------------------
  angola->set_population  (5430000);
  angola->set_birth_rate  (2.8);
  angola->set_tech_level  (45);
  angola->set_pnb         (210);
//----------------------------------------------
  gambia->set_population  (357000);
  gambia->set_birth_rate  (2.8);
  gambia->set_tech_level  (45);
  gambia->set_pnb         (80); //AU BOL!!!

/**********************************************************************/
/**********************************************************************/
//GROUP_B
//DEFINITIONS POUR LE GROUPE WHITE NATIONAL
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  canada->set_population  (21700000);
  canada->set_birth_rate  (1.7);
  canada->set_tech_level  (82);
  canada->set_pnb         (2620);
//----------------------------------------------
  usa->set_population  (207200000);
  usa->set_birth_rate  (1.6);
  usa->set_tech_level  (90);
  usa->set_pnb         (4240);
  usa->access_nuke     = ON ;
//----------------------------------------------
  south_africa->set_population  (21282000);
  south_africa->set_birth_rate  (1.9);
  south_africa->set_tech_level  (75);
  south_africa->set_pnb         (710);
//----------------------------------------------
  lesotho->set_population  (920000);
  lesotho->set_birth_rate  (2.0);
  lesotho->set_tech_level  (70);
  lesotho->set_pnb         (400);
  lesotho->access_sea      = OFF  ;
//----------------------------------------------
  swaziland->set_population  (408000);
  swaziland->set_birth_rate  (2.1);
  swaziland->set_tech_level  (65);
  swaziland->set_pnb         (500);
  swaziland->access_sea      = OFF ;
//----------------------------------------------

/**********************************************************************/
/**********************************************************************/
//GROUP_H
//DEFINITIONS POUR LE GROUPE CHRISTIAN NATION
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  brazil->set_population  (95305000);
  brazil->set_birth_rate  (2.0);
  brazil->set_tech_level  (66);
  brazil->set_pnb         (280);
//----------------------------------------------
  venezuela->set_population  (10399000);
  venezuela->set_birth_rate  (1.9);
  venezuela->set_tech_level  (65);
  venezuela->set_pnb         (1000);
//----------------------------------------------
  colombia->set_population  (20463000);
  colombia->set_birth_rate  (1.9);
  colombia->set_tech_level  (65);
  colombia->set_pnb         (340);
//----------------------------------------------
  ecuador->set_population  (6093000);
  ecuador->set_birth_rate  (1.9);
  ecuador->set_tech_level  (60);
  ecuador->set_pnb         (230);
//----------------------------------------------
  uruguay->set_population  (2886000);
  uruguay->set_birth_rate  (1.9);
  uruguay->set_tech_level  (65);
  uruguay->set_pnb         (580);
//----------------------------------------------
  paraguay->set_population  (2379000);
  paraguay->set_birth_rate  (1.8);
  paraguay->set_tech_level  (65);
  paraguay->set_pnb         (220);
  paraguay->access_sea      = OFF  ;

/**********************************************************************/
/**********************************************************************/
//GROUP_I
//DEFINITIONS POUR LE GROUPE SOCIALIST GROUP
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  mexico->set_population  (50670000);
  mexico->set_birth_rate  (2.0);
  mexico->set_tech_level  (60);
  mexico->set_pnb         (580);
//----------------------------------------------
  belize->set_population  (120000);  //=honduras britanique???
  belize->set_birth_rate  (2.0);
  belize->set_tech_level  (58);
  belize->set_pnb         (240);
//----------------------------------------------
  guatemala->set_population  (5014000);
  guatemala->set_birth_rate  (2.0);
  guatemala->set_tech_level  (62);
  guatemala->set_pnb         (300);
//----------------------------------------------
  honduras->set_population  (2570000);
  honduras->set_birth_rate  (2.0);
  honduras->set_tech_level  (62);
  honduras->set_pnb         (240);
//----------------------------------------------
  salvador->set_population  (3390000);
  salvador->set_birth_rate  (2.2);
  salvador->set_tech_level  (58);
  salvador->set_pnb         (260);
//----------------------------------------------
  nicaragua->set_population  (1984000);
  nicaragua->set_birth_rate  (2.0);
  nicaragua->set_tech_level  (60);
  nicaragua->set_pnb         (360);
//----------------------------------------------
  costa_rica->set_population  (1700000);
  costa_rica->set_birth_rate  (2.0);
  costa_rica->set_tech_level  (62);
  costa_rica->set_pnb         (450);
//----------------------------------------------
  panama->set_population  (1464000);
  panama->set_birth_rate  (2.0);
  panama->set_tech_level  (62);
  panama->set_pnb         (580);
//----------------------------------------------
  cuba->set_population  (8250000);
  cuba->set_birth_rate  (2.0);
  cuba->set_tech_level  (64);
  cuba->set_pnb         (280);
//----------------------------------------------
  jamaica->set_population  (1955000);
  jamaica->set_birth_rate  (2.4);
  jamaica->set_tech_level  (58);
  jamaica->set_pnb         (490);
//----------------------------------------------
  haiti->set_population  (4867000);
  haiti->set_birth_rate  (2.9);
  haiti->set_tech_level  (40);
  haiti->set_pnb         (90);
//----------------------------------------------
  dominican->set_population  (4325000);
  dominican->set_birth_rate  (2.2);
  dominican->set_tech_level  (56);
  dominican->set_pnb         (260);
//----------------------------------------------
  puerto_rico->set_population  (2775000);
  puerto_rico->set_birth_rate  (2.5);
  puerto_rico->set_tech_level  (58);
  puerto_rico->set_pnb         (1000);  //USA
//----------------------------------------------
  guyana->set_population  (763000);
  guyana->set_birth_rate  (2.0);
  guyana->set_tech_level  (66);
  guyana->set_pnb         (280);
//----------------------------------------------
  peru->set_population  (13586000);
  peru->set_birth_rate  (2.0);
  peru->set_tech_level  (63);
  peru->set_pnb         (270);
//----------------------------------------------
  bolivia->set_population  (4931000);
  bolivia->set_birth_rate  (2.0);
  bolivia->set_tech_level  (62);
  bolivia->set_pnb         (180);
  bolivia->access_sea      = OFF  ;
//----------------------------------------------
  chili->set_population  (9780000);
  chili->set_birth_rate  (2.0);
  chili->set_tech_level  (62);
  chili->set_pnb         (560);
//----------------------------------------------
  argentina->set_population  (24352000);
  argentina->set_birth_rate  (1.9);
  argentina->set_tech_level  (66);
  argentina->set_pnb         (740);


/**********************************************************************/
/**********************************************************************/
//GROUP_F
//DEFINITIONS POUR LE GROUPE SUN EMPIRE
/**********************************************************************/
/**********************************************************************/

//----------------------------------------------
  japan->set_population  (104513000);
  japan->set_birth_rate  (1.3);
  japan->set_tech_level  (84);
  japan->set_pnb         (2800);
//----------------------------------------------
  birmania->set_population  (27584000);
  birmania->set_birth_rate  (2.5);
  birmania->set_tech_level  (58);
  birmania->set_pnb         (70);
//----------------------------------------------
  thailand->set_population  (35814000);
  thailand->set_birth_rate  (2.5);
  thailand->set_tech_level  (62);
  thailand->set_pnb         (160);
//----------------------------------------------
  laos->set_population  (18322000);
  laos->set_birth_rate  (2.4);
  laos->set_tech_level  (62);
  laos->set_pnb         (70);
  laos->access_sea      = OFF  ;
//----------------------------------------------
  cambodge->set_population  (6701000);
  cambodge->set_birth_rate  (2.5);
  cambodge->set_tech_level  (60);
  cambodge->set_pnb         (80);
//----------------------------------------------
  vietnam->set_population  (21999000);
  vietnam->set_birth_rate  (2.4);
  vietnam->set_tech_level  (62);
  vietnam->set_pnb         (140);
//----------------------------------------------
  south_korea->set_population  (1360000);
  south_korea->set_birth_rate  (2.0);
  south_korea->set_tech_level  (66);
  south_korea->set_pnb         (530);
//----------------------------------------------
  philippines->set_population  (38493000);
  philippines->set_birth_rate  (2.4);
  philippines->set_tech_level  (62);
  philippines->set_pnb         (320);
//----------------------------------------------
  taiwan->set_population  (14910000);
  taiwan->set_birth_rate  (1.9);
  taiwan->set_tech_level  (74);
  taiwan->set_pnb         (350);

//set_army pour tous les pays
unsigned char the_ctry = jour->country_first; //pour pointer dans list pays
while (the_ctry != jour->country_last+1) 
{Ct_pointer[the_ctry]->set_army(); //génére valeurs par défaut pour le pays
Ct_pointer[the_ctry]->default_army(); //met une fois ces valeurs dans le pays
//met une fois ces valeurs dans le pays

the_ctry++;
}


//pays speciaux
russia->add_infantry(800000); //sinon ca fait pas assez
                             //en regard des 4 mio d'origine de l'URSS!!!

