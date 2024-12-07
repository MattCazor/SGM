#include "GfxLib.h" // Inclure les bibliothèques nécessaires
#include "BmpLib.h"
#include "ESLib.h"
#include <math.h> // Pour les calculs trigonométriques

#define LARGEUR_MENU 800
#define HAUTEUR_MENU 600

void dessineMenu();       // Dessiner le menu principal
void dessineBouton(float x, float y, float largeur, float hauteur, const char *texte);
void dessineVagues(float largeur, float hauteur);

void gestionEvenementMenu(EvenementGfx evenement) {
    switch (evenement) {
        case Initialisation:
            demandeTemporisation(20); // Rafraîchissement toutes les 20 ms
            break;

        case Affichage:
            effaceFenetre(0, 128, 255); // Fond bleu clair
            dessineMenu(); // Appeler la fonction pour dessiner le menu
            break;

        case Clavier:
            if (caractereClavier() == 'q') {
                termineBoucleEvenements(); // Quitter le programme avec 'q'
            }
            break;

        case Souris:
            if (etatBoutonSouris() == GaucheAppuye) {
                int x = abscisseSouris();
                int y = ordonneeSouris();
                // Actions pour chaque bouton
                if (x > 300 && x < 500 && y > 400 && y < 450) {
                    // Jouer
                    ecrisChaine("Commencer le jeu !", 18, 10, 10);
                } else if (x > 300 && x < 500 && y > 300 && y < 350) {
                    // Options
                    ecrisChaine("Options du jeu", 18, 10, 10);
                } else if (x > 300 && x < 500 && y > 200 && y < 250) {
                    // Quitter
                    termineBoucleEvenements();
                }
            }
            break;

        default:
            break;
    }
}

/**
 * @brief Dessiner le menu principal.
 */
void dessineMenu() {
    // Arrière-plan : Dégradé bleu pour représenter la mer
    for (int i = 0; i < HAUTEUR_MENU; i += 5) {
        float intensiteBleu = 255 * (1 - (float)i / HAUTEUR_MENU); // Dégradé
        couleurCourante(0, intensiteBleu, 255);
        rectangle(0, i, LARGEUR_MENU, i + 5);
    }

    // Vagues en bas de l'écran
    dessineVagues(LARGEUR_MENU, HAUTEUR_MENU * 0.2);

    // Titre
    couleurCourante(255, 255, 255); // Blanc
    afficheChaine("Port Simulator", 30, 250, 500); // Centré en haut

    // Boutons du menu
    dessineBouton(300, 400, 200, 50, "Jouer");
    dessineBouton(300, 300, 200, 50, "Options");
    dessineBouton(300, 200, 200, 50, "Quitter");
}

/**
 * @brief Dessiner un bouton rectangulaire avec texte.
 */
void dessineBouton(float x, float y, float largeur, float hauteur, const char *texte) {
    couleurCourante(0, 102, 204); // Bleu foncé pour le bouton
    rectangle(x, y, x + largeur, y + hauteur);

    couleurCourante(255, 255, 255); // Blanc pour le texte
    afficheChaine(texte, 18, x + largeur * 0.25f, y + hauteur * 0.3f);
}

/**
 * @brief Dessiner des vagues animées en bas de l'écran.
 */
void dessineVagues(float largeur, float hauteur) {
    couleurCourante(255, 255, 255); // Blanc pour les vagues
    for (float x = 0; x < largeur; x += 40) {
        for (float y = 0; y < hauteur; y += 40) {
            float amplitude = 5; // Amplitude des vagues
            float yVague = y + amplitude * sin(2 * M_PI * x / 80 + y / 40);
            cercle(x, yVague, 10); // Petits cercles pour représenter les vagues
        }
    }
}
