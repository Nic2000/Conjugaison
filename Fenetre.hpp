#ifndef DEF_FENETRE
#define DEF_FENETRE
//déclaration des widgets à utiliser
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/stock.h>
#include <string.h>
#include <gtkmm/table.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
using namespace std;
class Fenetre : public Gtk::Window{
    public:
        Fenetre();
    private:
        Gtk::Button bouton_conjuguer,bouton_reinitialiser,bouton_affichefonction,bouton_reinitialiser_phrase;
        Gtk::Entry zonedetexte_verbe,zonedetexte_phrase;
        Gtk::Label lbl_verbe,lbl_temps,lbl_conjugaison,lbl_affichage,lbl_phrase,lbl_sujet,lbl_affichageSujet,lbl_verbephrase,lbl_affichageVerbe,lbl_tempsphrase,lbl_affichageTemps;
        Gtk::RadioButton radiobouton_present,radiobouton_futur;
        Gtk::Table table_montableau;
        void Reinitialiser();
        void Reinitialiser_phrase();
        void Conjugaison();
        void Devinette();
        string sujet[9] = {"je","tu","il","elle","on","nous","vous","ils","elles"};
        string liste_terminaison[3] = {"er","ir","re"};
    /*terminaison pour les verbes du 1er groupe*/
        string prem_term_present[9] = {"e","es","e","e","e","ons","ez","ent","ent"};
        string prem_term_futur[9] = {"ai","as","a","a","a","ons","ez","ont","ont"};
        string aller_present[9] = {"vais","vas","va","va","va","allons","allez","vont","vont"};
        string etre_present[9] = {"suis","es","est","est","est","sommes","etes","sont","sont"};
    /*terminaison pour les verbes du 2e groupe*/
        string deux_term_present[9] = {"is","is","it","it","it","issons","issez","issent","issent"};
    /*termminaison pour les verbes du 3e groupe*/
        string trois_term_present[9] = {"s","s","","","","ons","ez","ent","ent"};
    //** terminaison tir ** /
        string tir_term_present[9] = {"s","s","t","t","t","tons","tez","tent","tent"};
    //** terminaison ire ** /
        string ire_term_present[9] = {"s","s","t","t","t","sons","sez","sent","sent"};

};
#endif // DEF_FENETRE
