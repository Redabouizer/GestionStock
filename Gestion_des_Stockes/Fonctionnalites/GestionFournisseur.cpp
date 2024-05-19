#include "../Header.hpp"

void AjouterFournisseur()
{
    cout << "Ajouter un nouveau fournisseur :" << endl;

    string idFournisseurStr;
    int idFournisseur;
    string nomFournisseur;
    string contactFournisseur;

    // Prompt and validate the ID of the supplier
    while (true)
    {
        cout << "ID du fournisseur : ";
        cin >> idFournisseurStr;
        if (estNombre(idFournisseurStr))
        {
            idFournisseur = stoi(idFournisseurStr);
            break;
        }
        else
        {
            cout << "L'ID du fournisseur doit être un nombre entier. Veuillez réessayer." << endl;
        }
    }

    cout << "Nom du fournisseur : ";
    cin >> nomFournisseur;

    cout << "Contact du fournisseur : ";
    cin >> contactFournisseur;

    Fournisseur nouveauFournisseur(idFournisseur, nomFournisseur, contactFournisseur);

    fournisseurs.insert(nouveauFournisseur);
    cout << "Fournisseur ajouté avec succès !" << endl;
}

void SupprimerFournisseur()
{
    cout << "Entrez l'identifiant du fournisseur à supprimer : ";
    string idFournisseurSupprStr;
    int idFournisseurSuppr;

    while (true)
    {
        cin >> idFournisseurSupprStr;
        if (estNombre(idFournisseurSupprStr))
        {
            idFournisseurSuppr = stoi(idFournisseurSupprStr);
            break;
        }
        else
        {
            cout << "L'identifiant du fournisseur doit être un nombre entier. Veuillez réessayer : ";
        }
    }

    auto itFournisseur = fournisseurs.begin();
    while (itFournisseur != fournisseurs.end())
    {
        if (itFournisseur->getIdFournisseur() == idFournisseurSuppr)
        {
            // Supprimez le fournisseur de la liste
            fournisseurs.erase(itFournisseur);
            cout << "Fournisseur supprimé avec succès !" << endl;

            for (auto &pair : produits)
            {
                if (pair.second->getFournisseur()->getIdFournisseur() == idFournisseurSuppr)
                {
                    delete pair.second;
                    pair.second = nullptr;
                }
            }

            cout << "Produits associés au fournisseur supprimés avec succès !" << endl;

            return;
        }
        ++itFournisseur;
    }

    cout << "Aucun fournisseur trouvé avec cet identifiant." << endl;
}

void AfficherProduitsS()
{
    cout << "Produits dont le prix est supérieur à 150dh :" << endl;

    for (const auto &fournisseur : fournisseurs)
    {
        cout << "Fournisseur : " << fournisseur.getNom() << endl;

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

        cin >> input;

        if (cin.eof())
        {
            cout << "\nAu revoir !" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "4")
        {
            cout << "Choix invalide. Veuillez saisir un numéro entre 1 et 4." << endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
            continue;
        }

        switch (choix)
        {
        case 1:
        {
            cout << "\n------------------------------------------" << endl;
            AjouterFournisseur();
            AfficherFournisseurs(fournisseurs);
            break;
        }
        case 2:
            cout << "\n------------------------------------------" << endl;
            SupprimerFournisseur();
            AfficherFournisseurs(fournisseurs);
            break;
        case 3:
            cout << "\n------------------------------------------" << endl;
            AfficherProduitsS();
            break;
        case 4:
            cout << "Retour au menu principal." << endl;
            break;
        }
    } while (choix != 4);
}
