
 
//****  creation de pays *****

/*
ATTENTION GRAND CON, oui ça changé entre l'europe et les autres groupes.
des fois on a créée bêtement des pointeurs en trop alors qu'on a pas besoin
ils sont déja dans Ct_pointer... sauf que comme on utilise ces pointeur dans
DATA.CPP FAUT PAS MODIFIER, sinon faut modifier aussi data.cpp et c'est long
de toute façon ces données finiront dans
un fichier .w6s tôt ou tard. Donc elles auront la même gueule dans l'éditeur
Pigé?
Blaireau va! ;-)
*/
 
 //europ
 Ct_pointer[PORTUGAL]   = new Country ("Portugal",PORTUGAL,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SPAIN]      = new Country ("Spain",SPAIN,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[FRANCE]     = new Country ("France",FRANCE,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[UK]         = new Country ("United Kingdom",UK,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ITALY]      = new Country ("Italy",ITALY,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BELGIUM]    = new Country ("Belgium",BELGIUM,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SLOVAKIA]   = new Country ("Slovakia",SLOVAKIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GERMANY]    = new Country ("Germany",GERMANY,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NETHERLANDS]= new Country ("Netherlands",NETHERLANDS,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[DENMARK]    = new Country ("Denmark",DENMARK,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NORWAY]     = new Country ("Norway",NORWAY,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[AUSTRIA]    = new Country ("Austria",AUSTRIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CZECHIA]    = new Country ("Czech Republic",CZECHIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GREECE]     = new Country ("Greece",GREECE,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SERBIA]     = new Country ("Serbia",SERBIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LITHUANIA]  = new Country ("Lithuania",LITHUANIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SWEDEN]     = new Country ("Sweden",SWEDEN,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[POLAND]     = new Country ("Poland",POLAND,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SWITZERLAND]= new Country ("Switzerland",SWITZERLAND,GRP_J,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer); //eh, oui
 Ct_pointer[FINLAND]    = new Country ("Finland",FINLAND,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ESTONIA]    = new Country ("Estonia",ESTONIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LETTONIA]   = new Country ("Lettonia",LETTONIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[IRELAND]    = new Country ("Ireland",IRELAND,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BOSNIA]     = new Country ("Bosnia Herzegovina",BOSNIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CROATIA]    = new Country ("Croatia",CROATIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SLOVENIA]   = new Country ("Slovenia",SLOVENIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GUYANA_FR]  = new Country ("Guyana (french)",GUYANA_FR,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SURINAM]    = new Country ("Surinam",SURINAM,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ICELAND]    = new Country ("Iceland",ICELAND,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GROENLAND]  = new Country ("Greenland",GROENLAND,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[HUNGARY]    = new Country ("Hungary",HUNGARY,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ROMANIA]    = new Country ("Romania",ROMANIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BULGARIA]   = new Country ("Bulgaria",BULGARIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ALBANIA]    = new Country ("Albania",ALBANIA,GRP_G,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);


//bon là à partir d'ici c'est un peu la version longue du grand bleu mais on s'en fout ça marche

 //soviet
 Country *russia;
 russia = new Country          ("Russia",RUSSIA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[RUSSIA]         = russia              ;


Country *mongolia;
 mongolia= new Country          ("Mongolia",MONGOLIA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MONGOLIA]         = mongolia            ;

Country *china;
 china = new Country              ("China",CHINA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CHINA]         = china               ;

Country *belarus;
 belarus= new Country        ("Belarus",BELARUS,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BELARUS]         = belarus         ;

Country *ukraine;
 ukraine= new Country             ("Ukraine", UKRAINE,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[UKRAINE]         = ukraine            ;

Country *moldavia;
 moldavia= new Country            ("Moldavia",MOLDAVIA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MOLDAVIA]         = moldavia            ;

Country *georgia;
 georgia= new Country              ("Georgia",GEORGIA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GEORGIA]         = georgia             ;

Country *armenia;
 armenia = new Country              ("Armenia",ARMENIA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ARMENIA]         = armenia             ;

Country *kazakhstan;
 kazakhstan = new Country           ("Kazakhstan",KAZAKHSTAN ,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[KAZAKHSTAN ]         = kazakhstan          ;

Country *uzbekistan;
 uzbekistan= new Country           ("Uzbekistan",UZBEKISTAN,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[UZBEKISTAN]         = uzbekistan          ;

Country *tadzikistan;
 tadzikistan= new Country         ("Tadzikistan",TADZIKISTAN,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TADZIKISTAN]         = tadzikistan         ;

Country *kirgikistan;
 kirgikistan = new Country          ("Kirgikistan",KIRGIKISTAN,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[KIRGIKISTAN]         = kirgikistan         ;

Country *north_korea ;
 north_korea = new Country         ("Northern Korea",NORTH_KOREA,GRP_D,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NORTH_KOREA]         = north_korea         ;
//et le zizikistan alors?

 //islam
Country *turkey;
 turkey = new Country               ("Turkey",TURKEY,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TURKEY]         = turkey              ;

Country *afghanistan;
 afghanistan = new Country          ("Afghanistan",AFGHANISTAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[AFGHANISTAN]         = afghanistan         ;

Country *iran;
 iran = new Country                ("Iran",IRAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[IRAN]         = iran                ;

Country *irak;
 irak = new Country                ("Irak",IRAK,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[IRAK]         = irak                ;

Country *saudi_arabia ;
 saudi_arabia = new Country        ("Saudi Arabia",SAUDI_ARABIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SAUDI_ARABIA]         = saudi_arabia        ;

Country *koweit;
koweit = new Country              ("Koweit",KOWEIT,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[KOWEIT]         = koweit              ;

Country *egypt;
egypt = new Country               ("Egypt",EGYPT,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[EGYPT]         = egypt               ;

Country *jordania;
 jordania= new Country            ("Jordania",JORDANIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[JORDANIA]         = jordania            ;

Country *syria;
syria = new Country               ("Syria",SYRIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SYRIA]         = syria               ;

Country *sudan;
 sudan = new Country               ("Sudan",SUDAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SUDAN]         = sudan               ;

Country *lybia;
lybia = new Country               ("Lybia",LYBIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LYBIA]         = lybia               ;

Country *tunisia;
tunisia = new Country             ("Tunisia",TUNISIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TUNISIA]         = tunisia             ;

Country *algeria;
 algeria = new Country             ("Algeria",ALGERIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ALGERIA]         = algeria             ;

Country *morocco;
morocco = new Country             ("Morocco",MOROCCO,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MOROCCO]         = morocco             ;

Country *djibouti;
 djibouti= new Country            ("Djibouti",DJIBOUTI,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[DJIBOUTI]         = djibouti            ;

Country *somalia;
 somalia= new Country             ("Somalia",SOMALIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SOMALIA]         = somalia             ;

Country *qatar;
 qatar= new Country               ("Qatar",QATAR,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[QATAR]         = qatar               ;

Country *azerbaidjan;
 azerbaidjan= new Country          ("Azerbaidjan",AZERBAIDJAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[AZERBAIDJAN]         = azerbaidjan         ;

Country *turkmenistan ;
 turkmenistan  = new Country       ("Turkmenistan",TURKMENISTAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TURKMENISTAN]         = turkmenistan        ;

Country *pakistan;
 pakistan= new Country             ("Pakistan",PAKISTAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PAKISTAN]         = pakistan            ;

Country *uae;
 uae= new Country                 ("United Arabic Emirates",UAE,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[UAE]         = uae                 ;

Country *yemen;
 yemen = new Country               ("Yemen",YEMEN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[YEMEN]         = yemen               ;

Country  *south_yemen;
 south_yemen = new Country         ("South Yemen",SOUTH_YEMEN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SOUTH_YEMEN]         = south_yemen         ;

Country *oman;
oman = new Country                 ("Oman",OMAN,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[OMAN]         = oman                ;

Country *malaysia;
 malaysia = new Country            ("Malaysia",MALAYSIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MALAYSIA]         = malaysia            ;

Country *indonesia;
 indonesia= new Country            ("Indonesia",INDONESIA,GRP_E,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[INDONESIA]         = indonesia           ;

 //neutral

Country *israel;
 israel= new Country         ("Israel",ISRAEL,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ISRAEL]         = israel              ;

Country *india;
 india = new Country             ("India",INDIA,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[INDIA]         = india               ;

Country *nepal;
 nepal = new Country            ("Nepal",NEPAL,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NEPAL]         = nepal               ;

Country *buthan;
 buthan= new Country            ("Buthan",BUTHAN,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BUTHAN]         = buthan              ;

Country *bangla_desh;
bangla_desh = new Country          ("Bangla Desh",BANGLA_DESH,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BANGLA_DESH]         = bangla_desh         ;

Country *sri_lanka;
 sri_lanka= new Country           ("Sri Lanka",SRI_LANKA,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SRI_LANKA]         = sri_lanka           ;

Country *australia;
 australia= new Country            ("Australia",AUSTRALIA,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[AUSTRALIA]         = australia           ;

Country *new_zealand;
 new_zealand= new Country        ("New Zealand",NEW_ZEALAND,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NEW_ZEALAND]         = new_zealand         ;

Country *new_guinea  ;
 new_guinea  = new Country         ("New Guinea",NEW_GUINEA,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NEW_GUINEA]         = new_guinea          ;

Country *lebanon;
 lebanon= new Country              ("Lebanon",LEBANON,GRP_A,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LEBANON]         = lebanon             ;



 //west african union

Country *guinea_bissau;
 guinea_bissau= new Country        ("Guinea Bissau",GUINEA_BISSAU,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GUINEA_BISSAU]         = guinea_bissau       ;

Country *mauritania;
 mauritania= new Country          ("Mauritania",MAURITANIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MAURITANIA]         = mauritania          ;

Country *mali;
mali = new Country                ("Mali",MALI,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MALI]         = mali          ;

Country *senegal;
senegal = new Country            ("Senegal",SENEGAL,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SENEGAL]         = senegal             ;

Country *guinea;
 guinea = new Country              ("Guinea",GUINEA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GUINEA]         = guinea              ;

Country *sierra_leone ;
 sierra_leone = new Country        ("Sierra Leone",SIERRA_LEONE,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SIERRA_LEONE]         = sierra_leone        ;

Country *liberia;
 liberia = new Country              ("Liberia",LIBERIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LIBERIA]         = liberia             ;

Country *ivory_coast;
 ivory_coast= new Country        ("Ivory Coast",IVORY_COAST,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[IVORY_COAST]         = ivory_coast         ;

Country *ghana;
 ghana = new Country               ("Ghana",GHANA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GHANA]         = ghana               ;

Country *burkina_faso;
 burkina_faso= new Country         ("Burkina Faso",BURKINA_FASO,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BURKINA_FASO]         = burkina_faso        ;

Country *togo;
 togo= new Country                ("Togo",TOGO,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TOGO]         = togo                ;

Country *benin;
 benin= new Country               ("Benin",BENIN,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BENIN]         = benin               ;

Country *niger;
 niger= new Country                ("Niger",NIGER,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NIGER]         = niger               ;

Country *nigeria;
 nigeria= new Country             ("Nigeria",NIGERIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NIGERIA]         = nigeria             ;

Country *cameroon;
 cameroon= new Country           ("Cameroun",CAMEROON,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CAMEROON]         = cameroon            ;

Country *tchad;
 tchad= new Country              ("Tchad",TCHAD,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TCHAD]         = tchad               ;

Country *centrafrica;
 centrafrica= new Country          ("Central Africa Republic",CENTRAFRICA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CENTRAFRICA]         = centrafrica         ;

Country *equatorial_guinea;
 equatorial_guinea= new Country    ("Equatorial Guineas",EQUATORIAL_GUINEA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[EQUATORIAL_GUINEA]         = equatorial_guinea   ;

Country *gabon  ;
gabon   = new Country              ("Gabon",GABON,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GABON]         = gabon               ;

Country *rep_congo;
rep_congo = new Country            ("Democratic Republic of Congo",REP_CONGO,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[REP_CONGO]         = rep_congo           ;

Country *congo;
congo = new Country               ("Congo (ex-Zaire)",CONGO,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CONGO]         = congo               ;

Country *uganda  ;
 uganda  = new Country             ("Uganda",UGANDA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[UGANDA]         = uganda              ;

Country *ethiopia  ;
 ethiopia  = new Country           ("Ethiopia",ETHIOPIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ETHIOPIA]         = ethiopia            ;

Country *kenya;
 kenya = new Country                ("Kenya",KENYA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[KENYA]         = kenya               ;

Country *rwanda;
 rwanda= new Country               ("Rwanda",RWANDA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[RWANDA]         = rwanda              ;

Country *burundi;
 burundi= new Country              ("Burundi",BURUNDI,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BURUNDI]         = burundi             ;

Country *tanzania;
tanzania = new Country             ("Tanzania",TANZANIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TANZANIA]         = tanzania            ;

Country *mozambique;
 mozambique= new Country           ("Mozambique",MOZAMBIQUE,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MOZAMBIQUE]         = mozambique          ;

Country *malawi;
malawi = new Country              ("Malawi",MALAWI,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MALAWI]         = malawi              ;

Country *madagascar;
 madagascar= new Country           ("Madagascar",MADAGASCAR,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MADAGASCAR]         = madagascar          ;

Country *zambia;
 zambia= new Country               ("Zambia",ZAMBIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ZAMBIA]         = zambia              ;

Country *zimbabwe;
 zimbabwe= new Country            ("Zimbabwe",ZIMBABWE,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ZIMBABWE]         = zimbabwe            ;

Country *botswana;
 botswana= new Country             ("Botswana",BOTSWANA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BOTSWANA]         = botswana            ;

Country *namibia;
 namibia = new Country              ("Namibia",NAMIBIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NAMIBIA]         = namibia             ;

Country *angola;
 angola = new Country               ("Angola",ANGOLA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ANGOLA]         = angola              ;

Country *gambia;
 gambia = new Country               ("Gambia",GAMBIA,GRP_C,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GAMBIA]         = gambia              ;

 //white national

Country *canada;
 canada= new Country              ("Canada",CANADA,GRP_B,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CANADA]         = canada             ;

Country *usa;
 usa= new Country                 ("United States",USA,GRP_B,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[USA]         = usa                ;

Country *south_africa;
 south_africa = new Country        ("South Africa",SOUTH_AFRICA,GRP_B,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SOUTH_AFRICA]         = south_africa       ;

Country *lesotho;
  lesotho= new Country            ("Lesotho",LESOTHO,GRP_B,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LESOTHO]         = lesotho            ;

Country  *swaziland;
 swaziland= new Country          ("Swaziland",SWAZILAND,GRP_B,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SWAZILAND]         = swaziland          ;

 //christian nation (sudac)
Country *brazil;
 brazil= new Country              ("Brazil",BRAZIL,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BRAZIL]         = brazil             ;

Country *venezuela;
 venezuela = new Country           ("Venezuela",VENEZUELA,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[VENEZUELA]         = venezuela          ;

Country *colombia;
 colombia = new Country           ("Colombia",COLOMBIA,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[COLOMBIA]         = colombia           ;

Country *ecuador;
 ecuador= new Country             ("Ecuador",ECUADOR,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ECUADOR]         = ecuador            ;

Country *uruguay;
 uruguay = new Country             ("Uruguay",URUGUAY,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[URUGUAY]         = uruguay            ;

Country *paraguay;
 paraguay= new Country            ("Paraguay",PARAGUAY,GRP_H,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PARAGUAY]         = paraguay           ;


 //socialist group (sudac)

Country *mexico;
 mexico = new Country              ("Mexico",MEXICO,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[MEXICO]         = mexico             ;

Country *belize;
 belize= new Country              ("Belize",BELIZE,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BELIZE]         = belize             ;

Country *guatemala;
 guatemala= new Country           ("Guatemala",GUATEMALA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GUATEMALA]         = guatemala          ;

Country *honduras;
 honduras= new Country            ("Honduras",HONDURAS,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[HONDURAS]         = honduras           ;

Country *salvador;
salvador = new Country           ("El Salvador",SALVADOR,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SALVADOR]         = salvador           ;

Country *nicaragua;
 nicaragua= new Country           ("Nicaragua",NICARAGUA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[NICARAGUA]         = nicaragua          ;

Country *costa_rica;
 costa_rica = new Country          ("Costa Rica",COSTA_RICA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[COSTA_RICA]         = costa_rica         ;

Country *panama;
 panama = new Country              ("Panama",PANAMA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PANAMA]         = panama             ;

Country *cuba;
 cuba = new Country                ("Cuba",CUBA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CUBA]         = cuba               ;

Country *jamaica;
 jamaica = new Country             ("Jamaica",JAMAICA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[JAMAICA]         = jamaica            ;

Country *haiti;
haiti = new Country               ("Haiti",HAITI,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[HAITI]         = haiti              ;

Country *dominican;
dominican = new Country           ("Dominican Republic",DOMINICAN,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[DOMINICAN]         = dominican          ;

Country *puerto_rico;
 puerto_rico= new Country         ("Puerto Rico",PUERTO_RICO,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PUERTO_RICO]         = puerto_rico        ;

Country *guyana;
 guyana= new Country              ("Guyana",GUYANA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[GUYANA]         = guyana             ;

Country *peru;
 peru= new Country                ("Peru",PERU,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PERU]         = peru               ;

Country *bolivia;
 bolivia= new Country             ("Bolivia",BOLIVIA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BOLIVIA]         = bolivia            ;

Country *chili;
 chili= new Country               ("Chili",CHILI,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CHILI]         = chili              ;

Country *argentina;
 argentina= new Country           ("Argentina",ARGENTINA,GRP_I,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[ARGENTINA]         = argentina          ;

 //Sun Empire
Country *japan;
 japan = new Country               ("Japan",JAPAN,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[JAPAN]         = japan              ;

Country *birmania;
 birmania = new Country            ("Birmania",BIRMANIA,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[BIRMANIA]         = birmania           ;

Country *thailand;
 thailand= new Country           ("Thailand",THAILAND,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[THAILAND]         = thailand           ;

Country *laos;
 laos= new Country                ("Laos",LAOS,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[LAOS]         = laos               ;

Country *cambodge;
 cambodge = new Country            ("Cambodge",CAMBODGE,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[CAMBODGE]         = cambodge           ;

Country *vietnam;
 vietnam = new Country             ("Vietnam",VIETNAM,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[VIETNAM]         = vietnam            ;

Country *south_korea;
 south_korea= new Country         ("Southern Korea",SOUTH_KOREA,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[SOUTH_KOREA]         = south_korea        ;

Country *philippines;
philippines = new Country         ("Philippines",PHILIPPINES,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[PHILIPPINES]         = philippines        ;

Country *taiwan;
 taiwan= new Country              ("Taiwan",TAIWAN,GRP_F,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[TAIWAN]         = taiwan             ;
 

///////////////////////////////////////////////////////////////////////////////////
//pour éviter des plantages ceci est nécessaie deux pays fake pour la couleur eau + frontière

 Ct_pointer[COL_SEA]         = new Country              ("",COL_SEA,GRP_X,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
 Ct_pointer[COL_BORDER]      = new Country              ("",COL_BORDER,GRP_X,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);
//pour editeur (pays vides)

//CETTE LIGNE FAIT TOUT MERDER POURQUOI???
// Ct_pointer[COL_EMPTY]       = new Country              ("empty",COL_BORDER,GRP_X,jour,Grp_pointer,Ct_pointer, Pol_pointer, Wpn_pointer);

//le grp_X est aussi un group fake avec politique fake (ennemi de personne, ami de tous, personne attaque ces pays!)
