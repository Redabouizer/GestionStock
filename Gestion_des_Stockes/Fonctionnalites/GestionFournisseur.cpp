#include "../Header.hpp"

void AjouterFournisseur()
{
    cout << "Ajouter un nouveau fournisseur :" << endl;

    int idFournisseur;
    string nomFournisseur;
    string contactFournisseur;

    cout << "ID du fournisseur : ";
    cin >> idFournisseur;
    cout << "Nom du fournisseur : ";
    cin >> nomFournisseur;
    cout << "Contact du fournisseur : ";
    cin >> contactFournisseur;

    // Création du fournisseur
    Fournisseur nouveauFournisseur(idFournisseur, nomFournisseur, contactFournisseur);

    // Ajout du fournisseur au set
    fournisseurs.insert(nouveauFournisseur);
    cout << "Fournisseur ajouté avec succès !" << endl;
}

void SupprimerFournisseur()
{
    cout << "Entrez l'identifiant du fournisseur à supprimer : ";
    int idFournisseurSuppr;
    cin >> idFournisseurSuppr;

    // Recherche du fournisseur dans le set
    auto it = fournisseurs.begin();
    while (it != fournisseurs.end())
    {
        if (it->getIdFournisseur() == idFournisseurSuppr)
        {
            fournisseurs.erase(it);
            cout << "Fournisseur supprimé avec succès !" << endl;
            break;
        }
        ++it;
    }

    if (it == fournisseurs.end())
    {
        cout << "Aucun fournisseur trouvé avec cet identifiant." << endl;
    }
}

void AfficherProduitsS()
{
    cout << "Produits dont le prix est supérieur à 150dh :" << endl;

    for (const auto &fournisseur : fournisseurs)
    {
        cout << "Fournisseur : " << fournisseur.getNom() << endl;

        // Parcourir les produits du fournisseur
        for (const auto &produit : fournisseur.getProduits())
        {
            if (produit.getPrixHT() > 150)
            {
                cout << "  Produit : " << produit.getDesignation() << " - Prix : " << produit.getPrixHT() << " dh" << endl;
            }
        }
    }
}

void GestionFournisseur()
{

    string choix;
    do
    {
        if (cin.eof())
        {
            cout << "\n";
            break;
        }
        // Affichage du menu de gestion des fournisseurs
        cout << "\n******** Menu de Gestion des Fournisseurs ********" << endl;
        cout << "1. Ajouter un fournisseur" << endl;
        cout << "2. Supprimer un fournisseur" << endl;
        cout << "3. Afficher les produits dont le prix est supérieur à 150dh" << endl;
        cout << "4. Retour au menu principal" << endl;
        cout << "Choix : ";
        getline(cin, choix);                                       // Utiliser getline() pour lire l'entrée de l'utilisateur
        if (choix.find_first_not_of("0123456789") == string::npos && !choix.empty()) // Vérifier si la saisie est un entier
        {
            int choixInt = stoi(choix);
            switch (choixInt)
            {
            case 1:
            {
                // Ajouter un fournisseur
                AjouterFournisseur();
                AfficherFournisseurs(fournisseurs);
                break;
            }
            case 2:
            {
                // Supprimer un fournisseur
                SupprimerFournisseur();
                AfficherFournisseurs(fournisseurs);
                break;
            }
            case 3:
            {
                // Afficher les produits dont le prix est supérieur à 150dh pour chaque fournisseur
                AfficherProduitsS();
                break;
            }
            case 4:
            {
                cout << "Retour au menu principal." << endl;
                break;
            }
            default:
            {
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
                break;
            }
            }
        }
        else
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
        }
    } while (choix != "4");
}