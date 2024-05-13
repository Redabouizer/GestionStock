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

    int choix;
    string input;
    do
    {
        cout << "\n------------------------------------------" << endl;
        cout << "\n******** Menu de Gestion des Fournisseurs ********" << endl;
        cout << "1. Ajouter un fournisseur" << endl;
        cout << "2. Supprimer un fournisseur" << endl;
        cout << "3. Afficher les produits dont le prix est supérieur à 150dh" << endl;
        cout << "4. Retour au menu principal" << endl;
        cout << "Choix : ";
        getline(cin, input);
        if (cin.eof())
        {
            cout << "\nAu revoir !" << endl;
            break;
        }
        // Si l'entrée est vide, continuer la boucle
        if (input.empty())
        {
            cout << "Veuillez saisir une valeur." << endl;
            continue;
        }
        if (cin.fail() || input < "1" || input > "4")
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
            // Réinitialiser le flux d'entrée
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choix = 0; // Réinitialiser la variable choix pour éviter une boucle infinie
            continue;
        }

        // Convertir l'entrée en entier
        choix = stoi(input);

        switch (choix)
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
        }
    } while (choix != 4);
}