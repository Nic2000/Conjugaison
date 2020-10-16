/*--Exemple des verbes utilisés comme test pour le programme:
1er groupe: accepter,chanter,danser,ecouter,parler,cacher,acheter,appeler,ajouter,poser,prier,quitter,raconter,regarder,
rentrer,gagner,assurer,exister,exprimer,arriver

2eme groupe:finir,accomplir,approfondir,grossir,reussir,trahir,grandir,surgir,vieillir,obeir,remplir,pourrir,fleurir,
desobeir,guerrir,franchir,choisir,maigrir,mincir,saisir

3eme groupe:apprendre,aller,avoir,croire,dormir,mentir,mettre,ouvrir,partir,prendre,sortir,rendre,vendre,voir,lire,dire,comprendre,
tendre,defendre,correspondre

*/
#include "Fenetre.hpp"
#include <iostream>
using namespace std;
Fenetre::Fenetre():
    table_montableau(9,3),lbl_verbe("Verbe à conjuguer:"),lbl_temps("Temps: "),
    zonedetexte_verbe(),radiobouton_present("Present"),radiobouton_futur("Futur"),
    bouton_conjuguer("Conjuguer"),bouton_reinitialiser("Réinitialiser"),lbl_conjugaison("Conjugaison: "),lbl_phrase("Votre phrase: "),
    zonedetexte_phrase(),bouton_affichefonction("Afficher les fonctions"),bouton_reinitialiser_phrase("Reinitialiser"),
    lbl_sujet("Sujet: "),lbl_verbephrase("Verbe: "), lbl_tempsphrase("Temps: ")
    {
        set_title("Conjugaison");//titre de la fenêtre
        set_default_size(200,25);//taille de la fenêtre
        add(table_montableau);//ajout du tableau dans la fenêtre

        zonedetexte_verbe.set_width_chars(30);//taille de la zone de texte

        //Mettre les radiobuttons dans le même groupe
        radiobouton_present.join_group(radiobouton_futur);

        //ajout des widgets dans le tableau
        table_montableau.attach(lbl_verbe,0,1,0,1);
        table_montableau.attach(zonedetexte_verbe,1,2,0,1);
        table_montableau.attach(lbl_temps,0,1,1,2);
        table_montableau.attach(radiobouton_present,1,2,1,2);
        table_montableau.attach(radiobouton_futur,2,3,1,2);
        table_montableau.attach(bouton_conjuguer,0,1,2,3);
        table_montableau.attach(bouton_reinitialiser,2,3,2,3);
        table_montableau.attach(lbl_conjugaison,0,1,3,4);
        table_montableau.attach(lbl_affichage,1,2,3,4);
        table_montableau.attach(lbl_phrase,0,1,4,5);
        table_montableau.attach(zonedetexte_phrase,1,2,4,5);
        table_montableau.attach(bouton_affichefonction,0,1,5,6);
        table_montableau.attach(bouton_reinitialiser_phrase,2,3,5,6);
        table_montableau.attach(lbl_sujet,0,1,6,7);
        table_montableau.attach(lbl_affichageSujet,1,2,6,7);
        table_montableau.attach(lbl_verbephrase,0,1,7,8);
        table_montableau.attach(lbl_affichageVerbe,1,2,7,8);
        table_montableau.attach(lbl_tempsphrase,0,1,8,9);
        table_montableau.attach(lbl_affichageTemps,1,2,8,9);
        //évènements lors du clique des boutons
        bouton_conjuguer.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::Conjugaison));
        bouton_reinitialiser.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::Reinitialiser));
        bouton_affichefonction.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::Devinette));
        bouton_reinitialiser_phrase.signal_clicked().connect(sigc::mem_fun(*this,&Fenetre::Reinitialiser_phrase));
        //rendre les widgets visibles
        show_all();

}
//mets la zone de texte et label vides
void Fenetre::Reinitialiser(){
    zonedetexte_verbe.set_text("");
    lbl_affichage.set_text("");
}
void Fenetre:: Conjugaison(){
    lbl_affichage.set_text("");

    string temps, recup_debut,terminaison,verbe_conjuguer = "",verbe_conjuguer_3e = "",verbe_tir = "", verbe_ire = "";
    int compteur = 0,longueur = zonedetexte_verbe.get_text_length(),i;
    terminaison = zonedetexte_verbe.get_chars(longueur-2,longueur);//récupère la terminaison du verbe à conjuguer

    //on vérifie si la terminaison du verbe entré par l'utilisateur est er ou ir ou re
    for (i = 0; i < 3; i++){
        if (terminaison == liste_terminaison[i]){
            compteur += 1;
        }
    }
    //si la terminaison ne correspond à aucun des données dans le tableau terminaison
    if(compteur == 0){
        lbl_affichage.set_text("Votre verbe n'est pas reconnu par le programme");
    }

    verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2);
    verbe_conjuguer_3e = zonedetexte_verbe.get_chars(0,longueur-1);
    verbe_tir = zonedetexte_verbe.get_chars(0,longueur-3);
    verbe_ire = zonedetexte_verbe.get_chars(0,longueur-2);

    //on teste si le début du verbe est a ou i pour que le premier sujet soit j' mais non je
    recup_debut = zonedetexte_verbe.get_chars(longueur-longueur,1);
    if (recup_debut == "a" or recup_debut == "i" or recup_debut == "e" or recup_debut == "o"){
        sujet[0] = "j'";
    }
    else{
        sujet[0] = "je";
    }
    //on vérifie le temps choisi en fonction des radiobouttons cochés
    if (radiobouton_present.get_active()){
        temps = "present";
    }
    if(radiobouton_futur.get_active()){
        temps = "futur";
    }

    //conjugaison au temps présent
    if(temps == "present"){
    //si la terminaison est "er"
        if (terminaison == liste_terminaison[0]){
            if (zonedetexte_verbe.get_text() == "aller"){
                sujet[0] = "je";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + aller_present[i]+ "\n");
                }
            }
            else if (zonedetexte_verbe.get_text() == "appeler"){
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_conjuguer + "l" + prem_term_present[i]+ "\n");
                }
            }
            else{
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+prem_term_present[i] + "\n");
                }
            }
        }
    //si la terminaison est "ir"
        if (terminaison == liste_terminaison[1]){
            if (zonedetexte_verbe.get_text() == "avoir"){
                sujet[0] = "j'";
                prem_term_futur[5] = "avons";
                prem_term_futur[6] = "avez";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+prem_term_futur[i] + "\n");
                }
            }
            else if (zonedetexte_verbe.get_text() == "ouvrir"){
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+prem_term_present[i] + "\n");
                }
            }
            else if (zonedetexte_verbe.get_text() == "voir"){
                verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-1);
                for (i = 0; i < 9 ; i++){
                    if (i == 5 or i == 6)
                        verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2) + "y";
                    if ( i == 7 or i == 8) verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-1);
                    if (i > 1 and i < 5)  verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-1) + "t";

                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+trois_term_present[i] + "\n");
                }


            }
            else if (zonedetexte_verbe.get_chars(longueur-3,longueur-2) == "t"){
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_tir + tir_term_present[i] + "\n");
                }
            }

            else if (zonedetexte_verbe.get_chars(longueur-3,longueur-2) == "m"){
                for (i = 0; i < 9 ; i++){
                    if (i == 2 or i == 3 or i == 4) verbe_tir = zonedetexte_verbe.get_chars(0,longueur-3) + "t";
                    if (i > 4) verbe_tir = zonedetexte_verbe.get_chars(0,longueur-2);

                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_tir + trois_term_present[i] + "\n");
                }
            }
            else{
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+deux_term_present[i] + "\n");
                }
            }
        }
        //si la terminaison est "re"
        if (terminaison == liste_terminaison[2]){
            if (zonedetexte_verbe.get_text() == "etre"){
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+etre_present[i] + "\n");
                }
            }
            else{
            //si le verbe est comprendre ou apprendre
                if(zonedetexte_verbe.get_text() == "comprendre" or zonedetexte_verbe.get_text() == "apprendre" or zonedetexte_verbe.get_text() == "prendre" or zonedetexte_verbe.get_text() == "tendre"){
                    for (i = 0; i < 9 ; i++){
                    // regler l'affichage pour nous et vous:
                        if (i == 5 or i == 6) verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-3);
                        // regler l'affichage pour ils et elles
                        if (i==7 or i == 8 ) verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-3) + "n";
                        lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+trois_term_present[i] + "\n");
                    }
                }
                else  if (zonedetexte_verbe.get_text() == "croire" or zonedetexte_verbe.get_text() == "voir"){
                   for (i = 0; i < 9 ; i++){

                            if (i == 5 or i == 6)
                                verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-3) + "y";
                            if ( i == 7 or i == 8) verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2);
                            if (i > 1 and i < 5)  verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2) + "t";
                            lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+trois_term_present[i] + "\n");
                    }
                }



                else{
                    if(zonedetexte_verbe.get_chars(longueur-3,longueur-2) == "d"){
                        for (i = 0; i < 9 ; i++){
                            lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+trois_term_present[i] + "\n");
                        }
                    }
                    else{
                        for (i = 0; i < 9 ; i++){
                            if (i > 1 and i < 5)  verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2) + "t";
                            if (i > 4 ) verbe_conjuguer = zonedetexte_verbe.get_chars(0,longueur-2) + "s";
                            lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i]+" "+verbe_conjuguer+trois_term_present[i] + "\n");
                        }
                    }
                }
            }
        }
    }
    //conjugaison au temps futur
    if(temps == "futur"){
        if (terminaison == liste_terminaison[0]){
            if (zonedetexte_verbe.get_text() == "aller"){
                sujet[0] = "j'";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + "ir" + prem_term_futur[i] + "\n");
                }
            }
            else if (zonedetexte_verbe.get_text() == "appeler"){
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_conjuguer + "ler" + prem_term_futur[i]+ "\n");
                }
            }
            else{
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + zonedetexte_verbe.get_text() + prem_term_futur[i] + "\n");
                }
            }
        }
        if (terminaison == liste_terminaison[1]){
            if (zonedetexte_verbe.get_text() == "avoir"){
                sujet[0] = "j'";
                terminaison = "aur";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + terminaison + prem_term_futur[i] + "\n");
                }
            }
            else if( zonedetexte_verbe.get_text() == "voir"){
                verbe_conjuguer = "verr";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_conjuguer + prem_term_futur[i] + "\n");
                }
            }
            else{
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + zonedetexte_verbe.get_text() + prem_term_futur[i] + "\n");
                }
            }
        }
        if (terminaison == liste_terminaison[2]){
            if (zonedetexte_verbe.get_text() == "etre"){
                terminaison = "ser";
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + terminaison + prem_term_futur[i] + "\n");
                }
            }
            else{
                for (i = 0; i < 9 ; i++){
                    lbl_affichage.set_text(lbl_affichage.get_text() + sujet[i] + " " + verbe_conjuguer_3e + prem_term_futur[i] + "\n");
                }
            }
        }
    }
}
void Fenetre::Devinette(){
    int i, j ,k,longueur_verbe, place_sujet, compteur = 0, lg = zonedetexte_phrase.get_text_length();
    string sujet_phrase,verbe_phrase,test = "",test_futur="";
/*on compte d'abord les espaces,on récupère les caractères qui se placent devant l'espace : le sujet et les caractères qui se placent
    après: verbe
*/
    for(i = 0; i < lg-1; i++){
        if (zonedetexte_phrase.get_chars(i,i+1) == " "){
            compteur += 1;
            sujet_phrase = zonedetexte_phrase.get_chars(0,i);
            k=i+1;
            //recuperer le sujet et la place du sujet
            for(j = 0; j < 9; j++){
                if (sujet_phrase == sujet[j]){
                    lbl_affichageSujet.set_text(sujet_phrase);
                    place_sujet = j;
                    break;
                }
            }

            for(i = k; i<lg; i++){
                if (zonedetexte_phrase.get_chars(i,i+1) == " " and compteur == 1 ) {
                    verbe_phrase = zonedetexte_phrase.get_chars(k,i);
                    lbl_affichageVerbe.set_text(verbe_phrase);
                    break;
                }
            }

        }


    }

   //recuperer la terminaison du verbe pour savoir le temps
    longueur_verbe = verbe_phrase.size();
    //pour les verbes etre, aller
    for(i = 0; i < 9; i++){
        if (verbe_phrase == etre_present[i]){
            lbl_affichageTemps.set_text("present");
        }
        if (verbe_phrase == aller_present[i]){
            lbl_affichageTemps.set_text("present");
        }
    }
    for(i = verbe_phrase.size()-1;i >= verbe_phrase.size() - prem_term_futur[place_sujet].size();i-- ){
        test_futur = verbe_phrase[i] + test_futur;
        if (test_futur == prem_term_futur[place_sujet]){
            lbl_affichageTemps.set_text("futur");
        }
    }

    for( i = verbe_phrase.size()-1;i >= verbe_phrase.size() - prem_term_present[place_sujet].size();i-- ){
        test = verbe_phrase[i] + test;
        if (test == prem_term_present[place_sujet]){
            lbl_affichageTemps.set_text("present");
        }
    }
}
//mets la zone de texte et label vides
void Fenetre::Reinitialiser_phrase(){
        zonedetexte_phrase.set_text("");
        lbl_affichageSujet.set_text("");
        lbl_affichageVerbe.set_text("");
        lbl_affichageTemps.set_text("");
    }
