#include "../Header.hpp"

void AjouterFournisseur()
{
    cout << "Ajouter un nouveau fournisseur :" << endl;

    string idFournisseurStr;
    int idFournisseur;
    string nomFournisseur;
    string contactFournisseur;

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
            cout <<"\033[31m"<< "L'ID du fournisseur doit être un nombre entier. Veuillez réessayer." << "\033[0m" << endl;
        }
    }

    cout << "Nom du fournisseur : ";
    cin >> nomFournisseur;

    cout << "Contact du fournisseur : ";
    cin >> contactFournisseur;

    Fournisseur nouveauFournisseur(idFournisseur, nomFournisseur, contactFournisseur);

    fournisseurs.insert(nouveauFournisseur);
    cout << "\033[32m" << "Fournisseur ajouté avec succès !"<< "\033[0m" << endl;
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
            cout <<"\033[31m"<< "L'identifiant du fournisseur doit être un nombre entier. Veuillez réessayer : "<< "\033[0m";
        }
    }

    auto itFournisseur = fournisseurs.begin();
    while (itFournisseur != fournisseurs.end())
    {
        if (itFournisseur->getIdFournisseur() == idFournisseurSuppr)
        {
            fournisseurs.erase(itFournisseur);
            cout << "\033[32m" <<"Fournisseur supprimé avec succès !" << "\033[0m"<< endl;

            for (auto &pair : produits)
            {
                if (pair.second->getFournisseur()->getIdFournisseur() == idFournisseurSuppr)
                {
                    delete pair.second;
                    pair.second = nullptr;
                }
            }

            cout << "\033[32m" << "Produits associés au fournisseur supprimés avec succès !" << "\033[0m"<< endl;

            return;
        }
        ++itFournisseur;
    }

    cout <<"\033[31m"<< "Aucun fournisseur trouvé avec cet identifiant." << "\033[0m"<< endl;
}

void AfficherProduitsS()
{
    cout << "\033[32m" << "Produits dont le prix est supérieur à 150dh :" << "\033[0m"<< endl;

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
        cout << "\033[1;31m"<< "\n------------------------------------------" << endl;
        cout <<"\033[36m"<< "\n******** Menu de Gestion des Fournisseurs ********" << endl;
        cout << "1. Ajouter un fournisseur" << endl;
        cout << "2. Supprimer un fournisseur" << endl;
        cout << "3. Afficher les produits dont le prix est supérieur à 150dh" << endl;
        cout << "4. Retour au menu principal" << endl;
        cout <<"\033[33m"<< "Choix : "<< "\033[0m";

        cin >> input;

        if (cin.eof())
        {
            cout << "\033[32m" <<"\nAu revoir !" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "4")
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro entre 1 et 4." << "\033[0m"<< endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro valide." << "\033[0m"<< endl;
            continue;
        }

        switch (choix)
        {
        case 1:
        {
            cout << "\n------------------------------------------" << endl;
            AjouterFournisseur();
            // AfficherFournisseurs(fournisseurs);
            break;
        }
        case 2:
            cout << "\n------------------------------------------" << endl;
            SupprimerFournisseur();
            // AfficherFournisseurs(fournisseurs);
            break;
        case 3:
            cout << "\n------------------------------------------" << endl;
            AfficherProduitsS();
            break;
        case 4:
            cout << "\033[32m" << "Retour au menu principal." << "\033[0m"<< endl;
            break;
        }
    } while (choix != 4);
}
