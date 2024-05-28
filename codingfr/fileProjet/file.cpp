//
// application de partage de fichier et synchronisation de dossier entre deux machines
//

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem> 

using namespace std;

namespace fs = std::filesystem;

//*******************************************************************
//Créer par Ayman Boulikamte

class GestionnaireFichiers {
public:
    static string lireFichier(const string& nomFichier) {
        ifstream fichier(nomFichier);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier : " << nomFichier << endl;
            return "";
        }
        string contenu((istreambuf_iterator<char>(fichier)), istreambuf_iterator<char>());
        return contenu;
    }

    static bool ecrireFichier(const string& nomFichier, const string& contenu) {
        ofstream fichier(nomFichier);
        if (!fichier.is_open()) {
            cerr << "Erreur lors de l'ouverture du fichier en écriture : " << nomFichier << endl;
            return false;
        }
        fichier << contenu;
        return true;
    }
};
//
//********************************************************************
//Créer par Soufiane Khalil

class SynchronisationDossiers {
public:
    static void synchroniserDossiers(const string& dossierSource, const string& dossierDest) {
        for (const auto& entree : fs::directory_iterator(dossierSource)) {
            if (fs::is_regular_file(entree)) {
                string nomFichier = entree.path().filename();
                string fichierSource = dossierSource + "/" + nomFichier;
                string fichierDest = dossierDest + "/" + nomFichier;
                string contenu = GestionnaireFichiers::lireFichier(fichierSource);
                if (!GestionnaireFichiers::ecrireFichier(fichierDest, contenu)) {
                    cerr << "Erreur lors de l'écriture du fichier : " << fichierDest << endl;
                }
            }
        }
    }
};
//
//*******************************************************************
//Créer par Anass Louriqua 

class Reseau {
public:
    static void envoyerDonnees(const string& donnees, const string& adresseIP) {
        cout << "Envoi de données à " << adresseIP << " : " << donnees << endl;
            }

    static string recevoirDonnees(const string& adresseIP) {
        cout << "Réception de données depuis " << adresseIP << endl;
        return "Données reçues";
    }
};
//
//********************************************************************
//
int main() {
    string contenuFichier = GestionnaireFichiers::lireFichier("exemple.txt");
    cout << "Contenu du fichier : " << contenuFichier << endl;

    GestionnaireFichiers::ecrireFichier("exemple_copie.txt", contenuFichier);
    cout << "Fichier copié avec succès" << endl;

    SynchronisationDossiers::synchroniserDossiers("dossier_source", "dossier_destination");
    cout << "Dossiers synchronisés avec succès" << endl;

    Reseau::envoyerDonnees("Bonjour, monde !", "192.168.1.100");

    string donneesRecues = Reseau::recevoirDonnees("192.168.1.100");
    cout << "Données reçues : " << donneesRecues << endl;

    return 0;
}