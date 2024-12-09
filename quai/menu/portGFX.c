#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"
#include <time.h>

// Dimensions par défaut de la fenêtre
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600

// États du programme
#define MENU 0
#define SIMULATION 1

// Variables globales
int etatProgramme = MENU; // Commence par le menu
int boutonSurvole = 0;     // Pour détecter le survol du bouton dans le menu

// Variables pour la simulation
float bateauX, bateauY;
int enDeplacement = 0;
int bateauSelectionne = 0;
int quaiCible = 0;
int placeCible = 0;
int mouvementActif = 0;
int SENS = 0; // 1 = arrivé, 2 = départ

// Prototypes des fonctions
void gestionEvenement(EvenementGfx evenement);
void dessineMenu();
void dessineTitreResponsive(float largeur, float hauteur);
void dessineBoutonResponsive(float largeur, float hauteur, int survole);
void dessineSimulation();

void cercle(float centreX, float centreY, float rayon);
void gestionEvenement(EvenementGfx evenement);
void dessineEau(int largeur, int hauteur, int portLargeur);
void dessinePort(int largeur, int hauteur);
void dessineQuai(float x, float y, float largeur, float hauteur);
void dessineDigueEtPhare(int largeur, int hauteur);

void dessineBateauPassagers(float x, float y, float largeur, float hauteur);
void dessineBateauMarchandises(float x, float y, float largeur, float hauteur);
void dessinePetrolier(float x, float y, float largeur, float hauteur);
void dessineYacht(float x, float y, float largeur, float hauteur);

void mouvementVersQuai(int largeurFenetre, int hauteurFenetre, float *bateauX, float *bateauY, float cibleX, float cibleY, int quaiCible, int *mouvementActif);
void mouvementVersSortie(int largeurFenetre, int hauteurFenetre, float *bateauX, float *bateauY, int quaiCible, int *mouvementActif);


int main(int argc, char **argv) {
    initialiseGfx(argc, argv);
    prepareFenetreGraphique("Menu et Simulation", LARGEUR_FENETRE, HAUTEUR_FENETRE);
    lanceBoucleEvenements();
    return 0;
}

/**
 * @brief Gère les événements principaux.
 */
void gestionEvenement(EvenementGfx evenement) {
    switch (evenement) {
        case Initialisation:
            demandeTemporisation(20); // Rafraîchissement toutes les 20ms
            bateauX = LARGEUR_FENETRE - 50;
            bateauY = HAUTEUR_FENETRE - 50;
            break;



        case Affichage:
            if (etatProgramme == MENU) {
                effaceFenetre(0, 128, 255); // Bleu de fond pour le menu
                dessineMenu();
            } else if (etatProgramme == SIMULATION) {
                effaceFenetre(135, 206, 250); // Bleu clair pour la simulation
                dessineSimulation();
            }
            break;

        case Souris: {
            int x = abscisseSouris();
            int y = ordonneeSouris();
            if (etatProgramme == MENU) {
                int largeur = largeurFenetre();
                int hauteur = hauteurFenetre();

                // Détection du survol du bouton "Lancer la simulation"
                boutonSurvole = (x > largeur * 0.35f && x < largeur * 0.65f &&
                                 y > hauteur * 0.4f && y < hauteur * 0.5f);

                if (etatBoutonSouris() == GaucheAppuye && boutonSurvole) {
                    etatProgramme = SIMULATION; // Passer à la simulation
                }
            }
            break;
        }

        case Clavier:
            if (caractereClavier() == 'q') {
                termineBoucleEvenements(); // Quitter avec 'q'
            }
            if (etatProgramme == SIMULATION && caractereClavier() == 'm') {
                etatProgramme = MENU; // Retourner au menu avec 'm'
            }
             char touche = caractereClavier();
            if (touche == '6') {
                bateauSelectionne = 1; // Sélectionner le yacht
                bateauX = largeurFenetre() * 0.9f;
                bateauY = hauteurFenetre() * 0.8f;
            } else if (touche == '7') {
                bateauSelectionne = 2; // Sélectionner le pétrolier
                bateauX = largeurFenetre() * 0.9f;
                bateauY = hauteurFenetre() * 0.8f;
            } else if (touche == '8') {
                bateauSelectionne = 3; // Sélectionner le bateau de passagers
                bateauX = largeurFenetre() * 0.9f;
                bateauY = hauteurFenetre() * 0.8f;
            } else if (touche == '9') {
                bateauSelectionne = 4; // Sélectionner le bateau de marchandises
                bateauX = largeurFenetre() * 0.9f;
                bateauY = hauteurFenetre() * 0.8f;
            } else if (touche == '1' && bateauSelectionne > 0) {
                quaiCible = 1;         // Déplacer vers le quai 3
                placeCible = 1;
                SENS = 1;
                mouvementActif = 1;    // Activer le mouvement
            } else if (touche == '2' && bateauSelectionne > 0) {
                quaiCible = 2;         // Déplacer vers le quai 2
                placeCible = 2;
                SENS = 1;
                mouvementActif = 1;    // Activer le mouvement
            } else if (touche == '3' && bateauSelectionne > 0) {
                quaiCible = 3;         // Déplacer vers le quai 1
                placeCible = 1;
                SENS = 1;
                mouvementActif = 1;    // Activer le mouvement
            } else if (touche == '4' && bateauSelectionne > 0) {
                quaiCible = 2;         // Déplacer vers le quai 4
                placeCible = 3;
                SENS = 1;
                mouvementActif = 1;    // Activer le mouvement
            } else if (touche == '5' && bateauSelectionne > 0) {
                SENS = 2;
                mouvementActif = 1;    // Activer le mouvement
            }
            break;
            break;

        case Temporisation:
            if (etatProgramme == SIMULATION) {
                            int largeur = largeurFenetre();
            int hauteur = hauteurFenetre();
            int portLargeur = largeur * 0.7; // Le port occupe maintenant 70% de la largeur (côté gauche étendu)
            int quaiLargeur = portLargeur * 0.85; // Chaque quai prend 85% de la largeur du port
            int quaiHauteur = hauteur * 0.2; // Hauteur des quais (20% de la hauteur totale)
            int quaiX = (portLargeur - quaiLargeur) / 2; // Centré horizontalement
            int espaceEntreQuais = (hauteur - 3 * quaiHauteur) / 4; // Distance égale entre les quais (4 espaces)
            float xOffset = quaiX + quaiLargeur * 0.02f; // Décalage horizontal pour le premier bateau
    if (mouvementActif && quaiCible > 0) {
        // Coordonées cibles pour chaque quai
        float cibleX, cibleY;
        switch(bateauSelectionne){
            //Yacht
            case 1:
                switch (quaiCible) {
                    case 1:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.15f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * (quaiLargeur * 0.15f));
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 4:
                            cibleX = xOffset + (3 * (quaiLargeur * 0.15f));
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 2:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.15f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * quaiLargeur * 0.15f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 4:
                            cibleX = xOffset + (3 * quaiLargeur * 0.15f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 3:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.15f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * quaiLargeur * 0.15f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 4:
                            cibleX = xOffset + (3 * quaiLargeur * 0.15f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                    break;
                }
            break;

            //Pétrolier
            case 2:
                switch (quaiCible) {
                    case 1:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 2:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 3:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                    break;
                }
            break;

            //Plaisancie
            case 3:
                switch (quaiCible) {
                    case 1:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX =xOffset + (quaiLargeur * 0.2f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * (quaiLargeur * 0.2f));
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 2:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX =xOffset + (quaiLargeur * 0.2f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * (quaiLargeur * 0.2f)); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 3:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + (quaiLargeur * 0.2f); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 3:
                            cibleX = xOffset + (2 * (quaiLargeur * 0.2f)); // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                    break;
                }
            break;

            //Cargo
            case 4:
                switch (quaiCible) {
                    case 1:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 0) + quaiHauteur * 0) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 2:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 1) + quaiHauteur * 1) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                        break;
                    case 3:
                        switch (placeCible){
                            case 1:
                            cibleX = xOffset; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                            case 2:
                            cibleX = xOffset + quaiLargeur * 0.3f; // Position du quai 1
                            cibleY = (espaceEntreQuais * (1 + 2) + quaiHauteur * 2) + quaiHauteur / (quaiHauteur - 5);
                            break;
                        }
                    break;
                }
            break;
        }    


        switch (SENS) {
    case 1: // Move to a quay
        mouvementVersQuai(largeurFenetre(), hauteurFenetre(), &bateauX, &bateauY, cibleX, cibleY, quaiCible, &mouvementActif);
        break;
    case 2: // Exit from the quay
        mouvementVersSortie(largeurFenetre(), hauteurFenetre(), &bateauX, &bateauY, quaiCible, &mouvementActif);
        break;
}



    }
            }
            rafraichisFenetre();
            break;

        default:
            break;
    }
}

/**
 * @brief Dessine le menu principal.
 */
void dessineMenu() {
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    dessineTitreResponsive(largeur, hauteur);
    dessineBoutonResponsive(largeur, hauteur, boutonSurvole);
}

/**
 * @brief Dessine le titre "SGM" de manière responsive.
 */
void dessineTitreResponsive(float largeur, float hauteur) {
    float xTitre = largeur / 2 - largeur * 0.1f;
    float yTitre = hauteur * 0.7f;

    couleurCourante(0, 0, 0); // Ombre noire
    afficheChaine("SGM", hauteur * 0.12f, xTitre + 2, yTitre - 2);

    couleurCourante(255, 255, 255); // Blanc
    afficheChaine("SGM", hauteur * 0.12f, xTitre, yTitre);
}

/**
 * @brief Dessine le bouton "Lancer la simulation".
 */
void dessineBoutonResponsive(float largeur, float hauteur, int survole) {
    float xBouton = largeur * 0.35f;
    float yBouton = hauteur * 0.4f;
    float largeurBouton = largeur * 0.3f;
    float hauteurBouton = hauteur * 0.1f;

    couleurCourante(survole ? 255 : 0, survole ? 255 : 102, survole ? 0 : 204);
    rectangle(xBouton, yBouton, xBouton + largeurBouton, yBouton + hauteurBouton);

    couleurCourante(255, 255, 255);
    afficheChaine("Lancer la simulation", hauteur * 0.03f, xBouton + largeurBouton * 0.1f, yBouton + hauteurBouton * 0.3f);
}

/**
 * @brief Dessine la simulation du port maritime.
 */
void dessineSimulation() {
    int largeur = largeurFenetre();
    int hauteur = hauteurFenetre();

    // Effacer l'écran avec une couleur de fond (bleu clair pour l'eau)
    effaceFenetre(0, 128, 255);

    // Dessiner le port et l'eau
    dessinePort(largeur, hauteur);                // Dessiner le port
    dessineEau(largeur, hauteur, largeur * 0.42); // Eau à partir de la fin du port

    // Dessiner le bateau à sa position actuelle, responsive
    if (bateauSelectionne > 0) {
        int portLargeur = largeur * 0.7; // Le port occupe maintenant 70% de la largeur (côté gauche étendu)
        int quaiLargeur = portLargeur * 0.85; // Chaque quai prend 85% de la largeur du port
        int quaiHauteur = hauteur * 0.2; // Hauteur des quais (20% de la hauteur totale)

        // Dessiner le bateau sélectionné, responsive
        switch (bateauSelectionne) {
            case 1: // Yacht
                dessineYacht(bateauX, bateauY, quaiLargeur * 0.50f, quaiHauteur * 0.6f);
                break;

            case 2: // Pétrolier
                dessinePetrolier(bateauX, bateauY, quaiLargeur * 0.27f, quaiHauteur * 0.6f);
                break;

            case 3: // Passagers
                dessineBateauPassagers(bateauX, bateauY, quaiLargeur * 0.55f, quaiHauteur * 0.6f);
                break;

            case 4: // Marchandises
                dessineBateauMarchandises(bateauX, bateauY, quaiLargeur * 0.27f, quaiHauteur * 0.8f);
                break;
        }
    }

    // Dessiner la digue et le phare
    dessineDigueEtPhare(largeur, hauteur);

}



/**
 * @brief Dessiner l'eau.
 */
void dessineEau(int largeur, int hauteur, int portLargeur) {
    static float offset = 0; // Décalage pour l'animation des vagues
    offset += 0.3f;          // Incrémenter plus rapidement pour créer une animation plus rapide

    for (int x = portLargeur; x < largeur; x += 10) {
        float intensiteBleu = 255 * (1 - (float)(x - portLargeur) / (largeur - portLargeur));
        couleurCourante(0, intensiteBleu, 255);
        rectangle(x, 0, x + 10, hauteur);

        // Dessiner des vagues animées
        couleurCourante(255, 255, 255); // Blanc pour les crêtes
        for (int y = 0; y < hauteur; y += 40) {
            float yVague = y + 10 * sin(2 * M_PI * (x + offset) / 50); // Fréquence plus rapide
            ligne(x, yVague, x + 10, yVague + 5);
        }
    }
}




/**
 * @brief Dessiner le port.
 */
void dessinePort(int largeur, int hauteur) {
    int portLargeur = largeur * 0.7; // Le port occupe maintenant 70% de la largeur (côté gauche étendu)
    int quaiLargeur = portLargeur * 0.85; // Chaque quai prend 85% de la largeur du port
    int quaiHauteur = hauteur * 0.2; // Hauteur des quais (20% de la hauteur totale)
    int espaceEntreQuais = (hauteur - 3 * quaiHauteur) / 4; // Distance égale entre les quais (4 espaces)

    // Dessiner la zone grise représentant le port (l'eau devient maintenant le fond gris)
    couleurCourante(169, 169, 169); // Gris pour le fond du port
    rectangle(0, 0, portLargeur, hauteur); // Zone grise représentant le port

    // Dessiner les quais bleus (turquoise) à l'intérieur du port
    couleurCourante(0, 255, 255); // Bleu turquoise pour les quais
    for (int i = 0; i < 3; i++) {
        int quaiX = (portLargeur - quaiLargeur) / 2; // Centré horizontalement
        int quaiY = espaceEntreQuais * (i + 1) + quaiHauteur * i; // Espacement uniforme
        rectangle(quaiX, quaiY, quaiX + quaiLargeur, quaiY + quaiHauteur); // Dessiner le quai
    }

    // Dessiner les bateaux dans la zone bleue (l'eau) sous les quais
    /*for (int i = 0; i < 3; i++) {
        int quaiX = (portLargeur - quaiLargeur) / 2; // Centré horizontalement
        int quaiY = espaceEntreQuais * (i + 1) + quaiHauteur * i; // Espacement uniforme

        // Placer les bateaux dans la zone bleue sous le quai (l'eau) en les alignant horizontalement
        float xOffset = quaiX + quaiLargeur * 0.02f; // Décalage horizontal pour le premier bateau

        if (i == 0) { // Pétrolier dans le premier quai
            dessinePetrolier(xOffset, quaiY + quaiHauteur / (quaiHauteur - 5), quaiLargeur * 0.55f, quaiHauteur * 0.6f);
        }
        else if (i == 1) { // Bateau de marchandises dans le deuxième quai
            dessineBateauMarchandises(xOffset, quaiY + quaiHauteur / (quaiHauteur - 80), quaiLargeur * 0.55f, quaiHauteur * 0.8f);
        }
        else if (i == 2) { // Yacht dans le troisième quai
            dessineYacht(xOffset, quaiY + quaiHauteur / (quaiHauteur - 5), quaiLargeur * 0.50f, quaiHauteur * 0.6f);
            dessineYacht(xOffset + quaiLargeur * 0.15f, quaiY + quaiHauteur / (quaiHauteur - 5), quaiLargeur * 0.50f, quaiHauteur * 0.6f);
            dessineYacht(xOffset + (2 * (quaiLargeur * 0.15f)), quaiY + quaiHauteur / (quaiHauteur - 5), quaiLargeur * 0.50f, quaiHauteur * 0.6f);
            dessineYacht(xOffset + (3 * (quaiLargeur * 0.15f)), quaiY + quaiHauteur / (quaiHauteur - 5), quaiLargeur * 0.50f, quaiHauteur * 0.6f);
            dessineBateauPassagers(xOffset, quaiY  / (quaiHauteur - 5), quaiLargeur * 0.6f, quaiHauteur * 0.6f);
            dessineBateauPassagers(xOffset + (quaiLargeur * 0.2f), quaiY  / (quaiHauteur - 5), quaiLargeur * 0.6f, quaiHauteur * 0.6f);
            dessineBateauPassagers(xOffset + (2 * (quaiLargeur * 0.2f)), quaiY  / (quaiHauteur - 5), quaiLargeur * 0.6f, quaiHauteur * 0.6f);
        }
    }*/
}






/**
 * @brief Dessiner une digue et un phare.
 */
void dessineDigueEtPhare(int largeur, int hauteur) {
    float digueLargeur = largeur * 0.05f; // Digue étroite
    float digueHauteur = hauteur * 0.6f; // Hauteur ajustée
    float xDigue = largeur - digueLargeur - largeur * 0.2f; // Position de la digue à gauche de l'espace pour un bateau

    // Dessiner la digue
    couleurCourante(105, 105, 105); // Gris clair pour la base
    rectangle(xDigue, 0, xDigue + digueLargeur, digueHauteur);

    // Dessiner un phare au sommet de la digue, légèrement abaissé
    float phareBaseX = xDigue + digueLargeur / 2;
    float phareBaseY = digueHauteur - 30; // Base abaissée
    float phareHauteur = hauteur * 0.3f; // Taille réduite du phare

    // Base rouge
    couleurCourante(139, 0, 0); // Rouge sombre
    rectangle(phareBaseX - 15, phareBaseY, phareBaseX + 15, phareBaseY + phareHauteur * 0.3f);

    // Tour blanche avec bandes rouges
    couleurCourante(255, 255, 255); // Blanc
    rectangle(phareBaseX - 10, phareBaseY + phareHauteur * 0.3f, phareBaseX + 10, phareBaseY + phareHauteur);
    couleurCourante(139, 0, 0); // Bandes rouges
    rectangle(phareBaseX - 10, phareBaseY + phareHauteur * 0.4f, phareBaseX + 10, phareBaseY + phareHauteur * 0.45f);
    rectangle(phareBaseX - 10, phareBaseY + phareHauteur * 0.6f, phareBaseX + 10, phareBaseY + phareHauteur * 0.65f);

    // Coupole jaune
    couleurCourante(255, 223, 0); // Jaune doré
    cercle(phareBaseX, phareBaseY + phareHauteur, 10);

    // Lumière du phare
    couleurCourante(255, 255, 0); // Jaune pour la lumière
    cercle(phareBaseX, phareBaseY + phareHauteur + 5, 7);
}


/**
 * @brief Dessiner un cercle.
 */
void cercle(float centreX, float centreY, float rayon) {
    const int SEGMENTS = 100;
    const float ANGLE = 2.0f * M_PI / SEGMENTS;

    float angleCourant = 0.0f;

    for (int i = 0; i < SEGMENTS; ++i) {
        float x1 = centreX + rayon * cos(angleCourant);
        float y1 = centreY + rayon * sin(angleCourant);

        angleCourant += ANGLE;

        float x2 = centreX + rayon * cos(angleCourant);
        float y2 = centreY + rayon * sin(angleCourant);

        ligne(x1, y1, x2, y2);
    }
}


/**
 * @brief Dessiner un bateau de passagers.
 */
void dessineBateauPassagers(float x, float y, float quaiLargeur, float quaiHauteur) {
    float largeur = quaiLargeur / 3;  // Largeur = 1/3 de la largeur du quai
    float hauteur = quaiHauteur / 2; // Hauteur = moitié de la hauteur du quai

    // Coque
    couleurCourante(139, 69, 19); // Marron foncé
    rectangle(x, y, x + largeur, y + hauteur * 0.3f);

    // Cabine principale
    couleurCourante(255, 255, 255); // Blanc
    rectangle(x + largeur * 0.1f, y + hauteur * 0.3f, x + largeur * 0.9f, y + hauteur * 0.7f);

    // Étages supérieurs
    rectangle(x + largeur * 0.2f, y + hauteur * 0.7f, x + largeur * 0.8f, y + hauteur * 0.9f);

    // Fenêtres
    couleurCourante(0, 191, 255); // Bleu clair
    for (float i = 0.15f; i < 0.85f; i += 0.1f) {
        cercle(x + largeur * i, y + hauteur * 0.5f, largeur * 0.03f);
        cercle(x + largeur * i, y + hauteur * 0.8f, largeur * 0.02f);
    }

    // Cheminées
    couleurCourante(255, 0, 0); // Rouge
    rectangle(x + largeur * 0.4f, y + hauteur * 0.9f, x + largeur * 0.45f, y + hauteur * 1.0f);
    rectangle(x + largeur * 0.6f, y + hauteur * 0.9f, x + largeur * 0.65f, y + hauteur * 1.0f);
}

/**
 * @brief Dessiner un bateau de marchandises.
 */
void dessineBateauMarchandises(float x, float y, float quaiLargeur, float quaiHauteur) {
    float largeur = quaiLargeur; // Largeur = largeur du quai
    float hauteur = quaiHauteur / 2; // Hauteur = moitié de la hauteur du quai

    // Coque
    couleurCourante(105, 105, 105); // Gris foncé
    rectangle(x, y, x + largeur, y + hauteur * 0.4f); // Coque

    // Ombre sous la coque
    couleurCourante(50, 50, 50); // Gris sombre
    rectangle(x, y - hauteur * 0.05f, x + largeur, y); // Ombre

    // Conteneurs avec ombres
    for (float i = 0.05f; i < 0.9f; i += 0.2f) {
        // Conteneur principal
        couleurCourante(0, 255, 0); // Vert
        rectangle(x + largeur * i, y + hauteur * 0.4f, x + largeur * (i + 0.15f), y + hauteur * 0.6f); // Conteneur principal

        // Ombre des conteneurs
        couleurCourante(0, 200, 0); // Vert foncé
        rectangle(x + largeur * i, y + hauteur * 0.4f, x + largeur * (i + 0.15f), y + hauteur * 0.45f); // Ombre
    }

    // Base de la grue
    couleurCourante(169, 169, 169); // Gris clair pour la grue
    rectangle(x + largeur * 0.4f, y + hauteur * 0.6f, x + largeur * 0.45f, y + hauteur * 0.8f); // Base de la grue

    // Bras de la grue
    ligne(x + largeur * 0.425f, y + hauteur * 0.8f, x + largeur * 0.6f, y + hauteur * 0.9f); // Inclinaison du bras
    ligne(x + largeur * 0.6f, y + hauteur * 0.9f, x + largeur * 0.65f, y + hauteur * 0.9f); // Bras horizontal

    // Crochet de la grue
    cercle(x + largeur * 0.65f, y + hauteur * 0.85f, largeur * 0.02f); // Poulie
    ligne(x + largeur * 0.65f, y + hauteur * 0.85f, x + largeur * 0.65f, y + hauteur * 0.7f); // Câble
    rectangle(x + largeur * 0.63f, y + hauteur * 0.7f, x + largeur * 0.67f, y + hauteur * 0.68f); // Crochet
}


/**
 * @brief Dessiner un pétrolier.
 */
void dessinePetrolier(float x, float y, float largeur, float hauteur) {
    // Coque
    couleurCourante(139, 0, 0); // Rouge sombre pour la coque
    rectangle(x, y, x + largeur, y + hauteur * 0.3f);

    // Réservoirs
    couleurCourante(169, 169, 169); // Gris clair pour les réservoirs
    for (float i = 0.1f; i < 0.9f; i += 0.3f) {
        rectangle(x + largeur * i, y + hauteur * 0.3f, x + largeur * (i + 0.2f), y + hauteur * 0.6f);
    }

    // Pipelines
    couleurCourante(0, 0, 0); // Noir pour les pipelines
    ligne(x + largeur * 0.15f, y + hauteur * 0.6f, x + largeur * 0.85f, y + hauteur * 0.6f);
    ligne(x + largeur * 0.2f, y + hauteur * 0.5f, x + largeur * 0.8f, y + hauteur * 0.5f);
}

/**
 * @brief Dessiner un yacht.
 */
void dessineYacht(float x, float y, float quaiLargeur, float quaiHauteur) {
    float largeur = quaiLargeur / 4;  // Largeur = 1/4 de la largeur du quai
    float hauteur = quaiHauteur / 2; // Hauteur = moitié de la hauteur du quai

    // Coque
    couleurCourante(0, 0, 139); // Bleu marine
    rectangle(x, y, x + largeur, y + hauteur * 0.3f); // Coque du yacht

    // Lignes lisses pour la coque
    couleurCourante(255, 255, 255); // Blanc
    ligne(x, y + hauteur * 0.05f, x + largeur, y + hauteur * 0.05f); // Lignes supérieures
    ligne(x, y + hauteur * 0.15f, x + largeur, y + hauteur * 0.15f); // Lignes inférieures

    // Cabine inclinée
    couleurCourante(255, 255, 255); // Blanc pour la cabine
    rectangle(x + largeur * 0.3f, y + hauteur * 0.3f, x + largeur * 0.7f, y + hauteur * 0.6f); // Cabine principale
    triangle(x + largeur * 0.3f, y + hauteur * 0.6f, x + largeur * 0.7f, y + hauteur * 0.6f, x + largeur * 0.5f, y + hauteur * 0.8f); // Toit de la cabine

    // Fenêtres hublots
    couleurCourante(0, 191, 255); // Bleu clair pour les hublots
    for (float i = 0.35f; i < 0.65f; i += 0.1f) {
        cercle(x + largeur * i, y + hauteur * 0.45f, largeur * 0.02f); // Fenêtres de la cabine
    }

    // Pont supérieur
    couleurCourante(255, 255, 0); // Jaune
    rectangle(x + largeur * 0.4f, y + hauteur * 0.8f, x + largeur * 0.6f, y + hauteur * 0.85f); // Pont supérieur

    // Parasol simplifié sur le pont
    couleurCourante(255, 0, 0); // Rouge
    cercle(x + largeur * 0.5f, y + hauteur * 0.87f, largeur * 0.03f); // Parasol

    couleurCourante(0, 0, 0); // Noir pour le pied du parasol
    ligne(x + largeur * 0.5f, y + hauteur * 0.85f, x + largeur * 0.5f, y + hauteur * 0.8f); // Pied du parasol
}


void mouvementVersQuai(int largeurFenetre, int hauteurFenetre, float *bateauX, float *bateauY, float cibleX, float cibleY, int quaiCible, int *mouvementActif) {
    switch (quaiCible) {
        case 1: // Quay 1 specific path
                    if (*bateauY > hauteurFenetre * 0.8f && *bateauX > largeurFenetre * 0.9f) {
                *bateauY -= 2; // Descendre verticalement
            } else if (*bateauY <= hauteurFenetre * 0.8f && *bateauX > largeurFenetre * 0.55f) {
                *bateauX -= 2; // Avancer horizontalement vers le phare
            } else if (*bateauY > hauteurFenetre * 0.5f && *bateauX <= largeurFenetre * 0.6f) {
                *bateauY -= 2; // Descendre près du phare
            } else if (*bateauY >= cibleY * 2.2f) {
                *bateauY -= 2; // Descendre jusqu'au quai
            } else if (*bateauX > cibleX) {
                *bateauX -= 2; // Aller horizontalement vers le quai
            } else if (*bateauY != cibleY || *bateauX != cibleX) {
                // Ajustement final pour s'amarrer
                if (*bateauY < cibleY) *bateauY += 2;
                else if (*bateauY > cibleY) *bateauY -= 2;

                if (*bateauX < cibleX) *bateauX += 2;
                else if (*bateauX > cibleX) *bateauX -= 2;
            } else {
                *mouvementActif = 0; // Arrêt du mouvement à destination
            }

            // Vérification de la distance pour stopper
            if (fabs(*bateauX - cibleX) < 3 && fabs(*bateauY - cibleY) < 3) {
                *mouvementActif = 0; // Stop si proche de la cible
            }
            break;

        case 2: // Quay 2 specific path
            if (*bateauY > hauteurFenetre * 0.8f && *bateauX > largeurFenetre * 0.9f) {
                *bateauY -= 2; // Descendre verticalement
            } else if (*bateauY <= hauteurFenetre * 0.8f && *bateauX > largeurFenetre * 0.55f) {
                *bateauX -= 2; // Avancer horizontalement vers le phare
            } else if (*bateauY > hauteurFenetre * 0.5f && *bateauX <= largeurFenetre * 0.6f) {
                *bateauY -= 2; // Descendre près du phare
            } else if (*bateauY >= cibleY * 2.1f) {
                *bateauY -= 2; // Descendre jusqu'au quai
            } else if (*bateauX > cibleX) {
                *bateauX -= 2; // Aller horizontalement vers le quai
            } else if (*bateauY != cibleY || *bateauX != cibleX) {
                // Ajustement final pour s'amarrer
                if (*bateauY < cibleY) *bateauY += 2;
                else if (*bateauY > cibleY) *bateauY -= 2;

                if (*bateauX < cibleX) *bateauX += 2;
                else if (*bateauX > cibleX) *bateauX -= 2;
            } else {
                *mouvementActif = 0; // Arrêt du mouvement à destination
            }

            // Vérification de la distance pour stopper
            if (fabs(*bateauX - cibleX) < 3 && fabs(*bateauY - cibleY) < 3) {
                *mouvementActif = 0; // Stop si proche de la cible
            }
            break;

        case 3: // Quay 3 specific path
            if (*bateauY >= cibleY * 2.2f) {
                *bateauY -= 2; // Descendre jusqu'au quai
            } else if (*bateauX > cibleX) {
                *bateauX -= 2; // Aller horizontalement vers le quai
            } else if (*bateauY != cibleY || *bateauX != cibleX) {
                // Ajustement final pour s'amarrer
                if (*bateauY < cibleY) *bateauY += 2;
                else if (*bateauY > cibleY) *bateauY -= 2;

                if (*bateauX < cibleX) *bateauX += 2;
                else if (*bateauX > cibleX) *bateauX -= 2;
            } else {
                *mouvementActif = 0; // Arrêt du mouvement à destination
            }

            // Vérification de la distance pour stopper
            if (fabs(*bateauX - cibleX) < 3 && fabs(*bateauY - cibleY) < 3) {
                *mouvementActif = 0; // Stop si proche de la cible
            }
            break;

        default:
            *mouvementActif = 0; // Default to no movement
            break;
    }

    if (fabs(*bateauX - cibleX) < 3 && fabs(*bateauY - cibleY) < 3) {
        *mouvementActif = 0; // Stop if close enough to the target
    }
}




void mouvementVersSortie(int largeurFenetre, int hauteurFenetre, float *bateauX, float *bateauY, int quaiCible, int *mouvementActif) {
    float pointDeSortieX = largeurFenetre + 20;

    switch (quaiCible) {
        case 1: // Exit from Quay 1
                     if (*bateauY < hauteurFenetre * 0.2f) {
                *bateauY += 2; // Monter verticalement
            } else if (*bateauX <= largeurFenetre * 0.5f) {
                *bateauX += 2; // Aller horizontalement à droite
            } else if (*bateauY < hauteurFenetre * 0.8f) {
                *bateauY += 2; // Monter vers la sortie
            } else if (*bateauX < pointDeSortieX) {
                *bateauX += 2; // Aller horizontalement hors de la fenêtre
                *bateauY += 1; // Montée légère pour effet
            } else {
                *bateauY += 500; // Sortir complètement
                *mouvementActif = 0; // Arrêt
            }
            break;

        case 2: // Exit from Quay 2
            if (*bateauY < hauteurFenetre * 0.5f) {
                *bateauY += 2; // Monter verticalement
            } else if (*bateauX <= largeurFenetre * 0.5f) {
                *bateauX += 2; // Aller horizontalement à droite
            } else if (*bateauY < hauteurFenetre * 0.8f) {
                *bateauY += 2; // Monter vers la sortie
            } else if (*bateauX < pointDeSortieX) {
                *bateauX += 2; // Aller horizontalement hors de la fenêtre
                *bateauY += 1; // Montée légère pour effet
            } else {
                *bateauY += 500; // Sortir complètement
                *mouvementActif = 0; // Arrêt
            }
            break;

        case 3: // Exit from Quay 3
            if (*bateauY < hauteurFenetre * 0.8f) {
                *bateauY += 2; // Monter verticalement
            } else if (*bateauX <= largeurFenetre * 0.5f) {
                *bateauX += 2; // Aller horizontalement à droite
            } else if (*bateauY < hauteurFenetre * 0.8f) {
                *bateauY += 2; // Monter vers la sortie
            } else if (*bateauX < pointDeSortieX) {
                *bateauX += 2; // Aller horizontalement hors de la fenêtre
                *bateauY += 1; // Montée légère pour effet
            } else {
                *bateauY += 500; // Sortir complètement
                *mouvementActif = 0; // Arrêt
            }
            break;

    }
}
