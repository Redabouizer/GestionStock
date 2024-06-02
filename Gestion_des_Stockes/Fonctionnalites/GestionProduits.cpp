#include "../Header.hpp"

void AjouterProduit()
{
    cout << "Ajouter un nouveau produit :" << endl;

    string refProduit;
    string designationProduit;
    int quantiteProduit;
    float prixProduit;
    string typeProduit;

    cout << "Type du produit (Standard/Electronique) : ";
    cin >> typeProduit;

    while (true)
    {
        cout << "Référence du produit : ";
        cin >> refProduit;

        bool referenceExists = false;

        if (produits.find(refProduit) != produits.end())
        {
            cout <<"\033[31m"<< "Un produit avec cette référence existe déjà. Veuillez utiliser une autre référence." << "\033[0m" << endl;
            referenceExists = true;
        }

        if (!referenceExists)
        {
            break;
        }
    }

    cout << "Désignation du produit : ";
    cin >> designationProduit;

    string quantiteStr;
    while (true)
    {
        cout << "Quantité du produit : ";
        cin >> quantiteStr;
        if (estNombre(quantiteStr))
        {
            quantiteProduit = stoi(quantiteStr);
            break;
        }
        else
        {
            cout <<"\033[31m"<< "La quantité doit être un nombre entier. Veuillez réessayer." << "\033[0m" <<endl;
        }
    }

    string prixStr;
    while (true)
    {
        cout << "Prix du produit : ";
        cin >> prixStr;
        if (estNombreFlottant(prixStr))
        {
            prixProduit = stof(prixStr);
            break;
        }
        else
        {
            cout <<"\033[31m"<< "Le prix doit être un nombre valide. Veuillez réessayer." << "\033[0m" << endl;
        }
    }

    Stock *stock = nullptr;
    string refStock;
    while (stock == nullptr)
    {
        cout << "Référence du stock : ";
        cin >> refStock;
        stock = TrouverStoc(refStock);
        if (stock == nullptr)
        {
            cout <<"\033[31m"<< "Stock non trouvé. Veuillez saisir une référence valide." << "\033[0m" << endl;
        }
    }

    int idFournisseur;
    Fournisseur *fournisseur = nullptr;
    string idFournisseurStr;
    while (true)
    {
        cout << "ID du fournisseur : ";
        cin >> idFournisseurStr;

        if (!estNombre(idFournisseurStr))
        {
            cout <<"\033[31m"<<"L'ID du fournisseur doit être un nombre entier. Veuillez réessayer." << "\033[0m" << endl;
            continue;
        }

        idFournisseur = stoi(idFournisseurStr);
        fournisseur = TrouverFourni(idFournisseur);
        if (fournisseur == nullptr)
        {
            cout <<"\033[31m"<<"Fournisseur non trouvé. Veuillez saisir une ID valide." << "\033[0m" << endl;
        }
        else
        {
            break;
        }
    }

    Produit *nouveauProduit = nullptr;

    if (typeProduit == "Electronique" || typeProduit == "electronique")
    {
        string versionMateriel;
        string versionLogiciel;

        cout << "Version matériel : ";
        cin >> versionMateriel;
        cout << "Version logiciel : ";
        cin >> versionLogiciel;

        ProduitElectronique *nouveauProduitEle = new ProduitElectronique(refProduit, designationProduit, quantiteProduit, prixProduit, stock, fournisseur, versionMateriel, versionLogiciel);
        produits[refProduit] = nouveauProduitEle;
        fournisseur->ajouterProduit(*nouveauProduitEle);
        stock->ajouterProduit(nouveauProduitEle);
    }
    else
    {
        nouveauProduit = new Produit(refProduit, designationProduit, quantiteProduit, prixProduit, stock, fournisseur);
        produits[refProduit] = nouveauProduit;
        fournisseur->ajouterProduit(*nouveauProduit);
        stock->ajouterProduit(nouveauProduit);
    }

    cout << "\033[32m" <<  "Produit ajouté avec succès !" << "\033[0m" << endl;
}

void ModifierProduit()
{
    cout << "Modifier un produit :" << endl;

    string refProduit;
    cout << "Entrez la référence du produit à modifier : ";
    cin >> refProduit;

    auto it = produits.find(refProduit);
    if (it != produits.end())
    {
        cout << "Détails actuels du produit : " << endl;
        cout << "Référence du produit : " << it->second->getReference() << endl;
        cout << "Désignation du produit : " << it->second->getDesignation() << endl;
        cout << "Quantité du produit : " << it->second->getQuantite() << endl;
        cout << "Prix du produit : " << it->second->getPrixHT() << endl;

        string nouvelleDesignation;
        int nouvelleQuantite;
        float nouveauPrix;

        cout << "Nouvelle désignation du produit : ";
        cin >> nouvelleDesignation;

        string nouvelleQuantiteStr;
        while (true)
        {
            cout << "Nouvelle quantité du produit : ";
            cin >> nouvelleQuantiteStr;
            if (estNombre(nouvelleQuantiteStr))
            {
                nouvelleQuantite = stoi(nouvelleQuantiteStr);
                break;
            }
            else
            {
                cout <<"\033[31m"<< "La quantité doit être un nombre entier. Veuillez réessayer." << "\033[0m" << endl;
            }
        }

        string nouveauPrixStr;
        while (true)
        {
            cout << "Nouveau prix du produit : ";
            cin >> nouveauPrixStr;
            if (estNombreFlottant(nouveauPrixStr))
            {
                nouveauPrix = stof(nouveauPrixStr);
                break;
            }
            else
            {
                cout <<"\033[31m"<< "Le prix doit être un nombre valide. Veuillez réessayer." << "\033[0m" << endl;
            }
        }

        it->second->setDesignation(nouvelleDesignation);
        it->second->setQuantite(nouvelleQuantite);
        it->second->setPrixHT(nouveauPrix);

        if (dynamic_cast<ProduitElectronique *>(it->second) != nullptr)
        {
            string nouvelleVersionMateriel, nouvelleVersionLogiciel;
            cout << "Nouvelle version matériel : ";
            cin >> nouvelleVersionMateriel;
            cout << "Nouvelle version logiciel : ";
            cin >> nouvelleVersionLogiciel;
            dynamic_cast<ProduitElectronique *>(it->second)->setVersionMateriel(nouvelleVersionMateriel);
            dynamic_cast<ProduitElectronique *>(it->second)->setVersionLogiciel(nouvelleVersionLogiciel);
        }

        cout << "\033[32m" <<  "Produit modifié avec succès !" << "\033[0m" << endl;
    }
    else
    {
        cout <<"\033[31m"<< "Aucun produit trouvé avec cette référence." << "\033[0m" <<endl;
    }
}

void SupprimerProduit()
{
    cout << "Supprimer un produit :" << endl;

    string refProduit;
    cout << "Entrez la référence du produit à supprimer : ";
    cin >> refProduit;

    // Obtenez le produit à partir de sa référence
    Produit *produit = TrouverProd(refProduit);

    if (produit != nullptr) // Vérifiez si le produit existe
    {
        // Obtenez le fournisseur associé au produit
        Fournisseur *fournisseur = produit->getFournisseur();

        if (fournisseur != nullptr) // Vérifiez si le fournisseur est valide
        {
            // Supprimez le produit du fournisseur
            fournisseur->SupprimerProduit(refProduit);
            cout << "\033[32m" <<  "Produit supprimé avec succès !"<< "\033[0m" << endl;
        }
        else
        {
            cout <<"\033[31m"<<"Aucun fournisseur trouvé pour ce produit." << "\033[0m" << endl;
        }
    }
    else
    {
        cout <<"\033[31m"<< "Aucun produit trouvé avec cette référence." << "\033[0m" << endl;
    }
}

bool dateDepassee6Mois(const Date &date)
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    // Convertir la date actuelle en mois et années
    int moisActuel = 1 + ltm->tm_mon;
    int anneeActuelle = 1900 + ltm->tm_year;

    // Calculer le nombre de mois écoulés depuis la date fournie
    int moisEcoules = (anneeActuelle - date.annee) * 12 + (moisActuel - date.mois);

    return moisEcoules > 6;
}

void ProduitsDate()
{
    int totalProduitsDepasses = 0;

    // Parcourez chaque paiement
    for (const Paiement &paiement : paiements)
    {
        // Vérifiez si la date de paiement a dépassé les 6 mois
        if (dateDepassee6Mois(paiement.getDatePaiement()))
        {
            // Si oui, comptez le nombre de produits associés à ce paiement
            totalProduitsDepasses += paiement.getProduits().size();
        }
    }

    cout << "\033[32m" <<  "Nombre total de produits dont la date de paiement a depasse les 6 mois : " << totalProduitsDepasses << "\033[0m" << endl;
}

void AugmenterPrix()
{
    for (auto &pair : produits)
    {
        Produit *produit = pair.second;
        if (produit->getQuantite() < 100)
        {
            float nouveauPrix = produit->getPrixHT() * 1.2;
            produit->setPrixHT(nouveauPrix);
            cout << "\033[32m" <<  "Le prix du produit " << produit->getReference() << " a été augmenté de 20%." << "\033[0m" << endl;
        }
    }
}

void gestionProduits()
{
    int choix;
    string input;
    do
    {
        cout << "\033[1;31m"<< "\n------------------------------------------" << endl;
        cout <<"\033[36m"<< "\n******** Menu de Gestion des Produits ********" << endl;
        cout << "1. Ajouter un produit" << endl;
        cout << "2. Modifier un produit" << endl;
        cout << "3. Supprimer un produit" << endl;
        cout << "4. Afficher le nombre de produits dont la date de paiement a dépassé les 6 mois" << endl;
        cout << "5. Augmenter le prix des produits de 20% si la quantité est inférieure à 100 pièces" << endl;
        cout << "6. Retour au menu principal"<< "\033[0m" << endl;
        cout <<"\033[33m"<< "Choix : "<< "\033[0m";
        cin >> input;

        if (cin.eof())
        {
            cout << "\033[32m" << "\nAu revoir !" << "\033[0m" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "6")
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro entre 1 et 6." << "\033[0m"<< endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro valide."<< "\033[0m" << endl;
            continue;
        }

        switch (choix)
        {
        case 1:
            cout << "\n------------------------------------------" << endl;
            AjouterProduit();
            // AfficherProduits(produits);
            break;
        case 2:
            cout << "\n------------------------------------------" << endl;
            ModifierProduit();
            // AfficherProduits(produits);
            break;
        case 3:
            cout << "\n------------------------------------------" << endl;
            SupprimerProduit();
            // AfficherProduits(produits);
            break;
        case 4:
            cout << "\n------------------------------------------" << endl;
            ProduitsDate();
            break;
        case 5:
            cout << "\n------------------------------------------" << endl;
            AugmenterPrix();
            // AfficherProduits(produits);
            break;
        case 6:
            cout << "\033[32m" << "Retour au menu principal."<< "\033[0m" << endl;
            break;
        }
    } while (choix != 6);
}