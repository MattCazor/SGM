#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "GfxLib.h"
#include "BmpLib.h"
#include "ESLib.h"

// Prototypes
void gestionEvenement(EvenementGfx evenement);
void dessineMenu();
void dessineTitre(float largeur, float hauteur);
void dessineBoutonLancer(float largeur, float hauteur, int survole);
void dessineVaguesResponsive(float largeur, float hauteur);
void cercle(float centreX, float centreY, float rayon);

// Variables globales
int boutonSurvole = 0; // Indique si le bouton "Lancer" est survolé
float offsetVagues = 0; // Décalage pour animer les vagues

int main(int argc, char **argv) {
    initialiseGfx(argc, argv); // Initialisation
    prepareFenetreGraphique("Menu Simulation", 800, 600); // Taille initiale
    lanceBoucleEvenements(); // Boucle principale
    return 0;
}

/**
 * @brief Gérer les événements principaux
 */
void gestionEvenement(EvenementGfx evenement) {
    switch (evenement) {
        case Initialisation:
            demandeTemporisation(20); // Animation à 20 ms
            break;

        case Affichage:
            effaceFenetre(0, 128, 255); // Fond bleu clair
            dessineMenu();
            break;

        case Souris: {
            int x = abscisseSouris();
            int y = ordonneeSouris();
            int largeur = largeurFenetre();
            int hauteur = hauteurFenetre();

            // Détecter si la souris survole le bouton "Lancer"
            boutonSurvole = (x > largeur * 0.35f && x < largeur * 0.65f &&
                             y > hauteur * 0.55f && y < hauteur * 0.65f);

            if (etatBoutonSouris() == GaucheAppuye && boutonSurvole) {
                afficheChaine("Simulation en cours...", 18, 10, 10); // Placeholder
            }
            break;
        }

        case Clavier:
            if (caractereClavier() == 'q') {
                termineBoucleEvenements(); // Quitter avec 'q'
            }
            break;

        case Temporisation:
            offsetVagues += 0.02f; // Animation lente des vagues
            if (offsetVagues > 2 * M_PI) {
                offsetVagues -= 2 * M_PI;
            }
            rafraichisFenetre(); // Redessiner
            break;

        default:
            break;
    }
}

/**
 * @brief Dessiner le menu principal
 */
void dessineMenu() {
    float largeur = largeurFenetre();
    float hauteur = hauteurFenetre();

    // Fond dégradé bleu
    for (int y = 0; y < hauteur; y += 5) {
        float intensiteBleu = 128 + 127 * (1 - (float)y / hauteur);
        couleurCourante(0, intensiteBleu, 255);
        rectangle(0, y, largeur, y + 5);
    }

    // Dessiner les vagues
    dessineVaguesResponsive(largeur, hauteur * 0.2);

    // Dessiner le titre
    dessineTitre(largeur, hauteur);

    // Bouton Lancer
    dessineBoutonLancer(largeur, hauteur, boutonSurvole);
}

/**
 * @brief Dessiner le titre "SGM" en style graffiti
 */
void dessineTitre(float largeur, float hauteur) {
    float xTitre = largeur / 2 - 150; // Centrer le titre horizontalement
    float yTitre = hauteur * 0.2;

    // Ombre
    couleurCourante(0, 0, 0); // Noir pour l'ombre
    afficheChaine("SGM", 80, xTitre + 2, yTitre + 2);

    // Texte principal
    couleurCourante(255, 255, 255); // Blanc
    afficheChaine("SGM", 80, xTitre, yTitre); // Titre principal
}

/**
 * @brief Dessiner le bouton "Lancer"
 */
void dessineBoutonLancer(float largeur, float hauteur, int survole) {
    float xBouton = largeur * 0.35f;
    float yBouton = hauteur * 0.55f;
    float largeurBouton = largeur * 0.3f;
    float hauteurBouton = hauteur * 0.1f;

    // Couleur du bouton
    if (survole) {
        couleurCourante(255, 255, 0); // Jaune vif au survol
    } else {
        couleurCourante(0, 102, 204); // Bleu foncé
    }
    rectangle(xBouton, yBouton, xBouton + largeurBouton, yBouton + hauteurBouton);

    // Bordure blanche
    couleurCourante(255, 255, 255);
    ligne(xBouton, yBouton, xBouton + largeurBouton, yBouton); // Bord supérieur
    ligne(xBouton, yBouton, xBouton, yBouton + hauteurBouton); // Bord gauche
    ligne(xBouton + largeurBouton, yBouton, xBouton + largeurBouton, yBouton + hauteurBouton); // Bord droit
    ligne(xBouton, yBouton + hauteurBouton, xBouton + largeurBouton, yBouton + hauteurBouton); // Bord inférieur

    // Texte du bouton
    couleurCourante(255, 255, 255); // Blanc pour le texte
    afficheChaine("Lancer la simulation", 24, xBouton + largeurBouton * 0.05f, yBouton + hauteurBouton * 0.3f);
}

/**
 * @brief Dessiner les vagues animées
 */
void dessineVaguesResponsive(float largeur, float hauteur) {
    couleurCourante(255, 255, 255); // Blanc pour les vagues
    for (float x = 0; x < largeur; x += 40) {
        for (float y = 0; y < hauteur; y += 40) {
            float amplitude = 10; // Amplitude des vagues
            float yVague = y + amplitude * sin(2 * M_PI * (x + offsetVagues) / 200);
            cercle(x, yVague, 8); // Petits cercles pour représenter les vagues
        }
    }
}

/**
 * @brief Dessiner un cercle approximé
 */
void cercle(float centreX, float centreY, float rayon) {
    const int SEGMENTS = 100;
    for (int i = 0; i < SEGMENTS; i++) {
        float angle1 = 2 * M_PI * i / SEGMENTS;
        float angle2 = 2 * M_PI * (i + 1) / SEGMENTS;
        float x1 = centreX + rayon * cos(angle1);
        float y1 = centreY + rayon * sin(angle1);
        float x2 = centreX + rayon * cos(angle2);
        float y2 = centreY + rayon * sin(angle2);
        ligne(x1, y1, x2, y2);
    }
}
