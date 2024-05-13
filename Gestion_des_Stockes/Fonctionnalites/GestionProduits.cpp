#include "../Header.hpp"

void AjouterProduit()
{
    cout << "Ajouter un nouveau produit :" << endl;

    string refProduit;
    string designationProduit;
    int quantiteProduit;
    float prixProduit;

    cout << "Référence du produit : ";
    cin >> refProduit;
    cout << "Désignation du produit : ";
    cin >> designationProduit;
    cout << "Quantité du produit : ";
    cin >> quantiteProduit;
    cout << "Prix du produit : ";
    cin >> prixProduit;

    // Création du produit
    Produit *nouveauProduit = new Produit(refProduit, designationProduit, quantiteProduit, prixProduit, nullptr, nullptr);

    // Demander à l'utilisateur de remplir les informations sur le fournisseur
    int idFournisseur;
    cout << "ID du fournisseur : ";
    cin >> idFournisseur;
    Fournisseur *fournisseur = TrouverFourni(idFournisseur);
    if (fournisseur == nullptr)
    {
        cout << "Fournisseur non trouvé. Veuillez créer le fournisseur avant d'ajouter le produit." << endl;
        return;
    }


    nouveauProduit->setFournisseur(fournisseur);

    // Ajout du produit au fournisseur
    fournisseur->ajouterProduit(*nouveauProduit);

    // Ajout du produit au map
    produits[refProduit] = nouveauProduit;
    cout << "Produit ajouté avec succès !" << endl;
}

void ModifierProduit()
{
    // Modifier un produit
    cout << "Modifier un produit :" << endl;

    string refProduit;
    cout << "Entrez la référence du produit à modifier : ";
    cin >> refProduit;

    auto it = produits.find(refProduit);
    if (it != produits.end())
    {
        // Le produit est trouvé, affichez les détails actuels et demandez les nouveaux détails
        cout << "Détails actuels du produit : " << endl;
        cout << "Référence du produit : " << it->second->getReference() << endl;
        cout << "Désignation du produit : " << it->second->getDesignation() << endl;
        cout << "Quantité du produit : " << it->second->getQuantite() << endl;
        cout << "Prix du produit : " << it->second->getPrixHT() << endl;

        // Demandez les nouveaux détails du produit
        string nouvelleDesignation;
        int nouvelleQuantite;
        float nouveauPrix;
        cout << "Nouvelle désignation du produit : ";
        cin >> nouvelleDesignation;
        cout << "Nouvelle quantité du produit : ";
        cin >> nouvelleQuantite;
        cout << "Nouveau prix du produit : ";
        cin >> nouveauPrix;

        // Mettre à jour les détails du produit
        it->second->setDesignation(nouvelleDesignation);
        it->second->setQuantite(nouvelleQuantite);
        it->second->setPrixHT(nouveauPrix);

        cout << "Produit modifié avec succès !" << endl;
    }
    else
    {
        // Le produit n'est pas trouvé
        cout << "Aucun produit trouvé avec cette référence." << endl;
    }
}

void SupprimerProduit()
{
    cout << "Supprimer un produit :" << endl;

    string refProduit;
    cout << "Entrez la référence du produit à supprimer : ";
    cin >> refProduit;

    auto it = produits.find(refProduit);
    if (it != produits.end())
    {
        // Le produit est trouvé, le supprimer du map
        delete it->second; // Assurez-vous de libérer la mémoire pour éviter les fuites
        produits.erase(it);
        cout << "Produit supprimé avec succès !" << endl;
    }
    else
    {
        // Le produit n'est pas trouvé
        cout << "Aucun produit trouvé avec cette référence." << endl;
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

    // Afficher le nombre total de produits dont la date de paiement a dépassé les 6 mois
    cout << "Nombre total de produits dont la date de paiement a depasse les 6 mois : " << totalProduitsDepasses << endl;
}

void AugmenterPrix()
{
    for (auto &pair : produits)
    {
        Produit *produit = pair.second;
        if (produit->getQuantite() < 100)
        {
            // Augmenter le prix de 20%
            float nouveauPrix = produit->getPrixHT() * 1.2; // Augmentation de 20%
            produit->setPrixHT(nouveauPrix);
            cout << "Le prix du produit " << produit->getReference() << " a été augmenté de 20%." << endl;
        }
    }
}

void gestionProduits()
{
    string choix;
    do
    {
        if (cin.eof())
        {
            cout << "\n";
            break;
        }
        // Affichage du menu de gestion des produits
        cout << "\n******** Menu de Gestion des Produits ********" << endl;
        cout << "1. Ajouter un produit" << endl;
        cout << "2. Modifier un produit" << endl;
        cout << "3. Supprimer un produit" << endl;
        cout << "4. Afficher le nombre de produits dont la date de paiement a dépassé les 6 mois" << endl;
        cout << "5. Augmenter le prix des produits de 20% si la quantité est inférieure à 100 pièces" << endl;
        cout << "6. Retour au menu principal" << endl;
        cout << "Choix : ";
        getline(cin, choix);
        if (choix.find_first_not_of("0123456789") == string::npos && !choix.empty()) // Vérifier si la saisie est un entier
        {
            int choixInt = stoi(choix);
            switch (choixInt)
            {
            case 1:
                // Ajouter un produit
                AjouterProduit();
                AfficherProduits(produits);
                break;
            case 2:
                // Modifier un produit
                ModifierProduit();
                AfficherProduits(produits);
                break;
            case 3:
                // Supprimer un produit
                SupprimerProduit();
                AfficherProduits(produits);
                break;
            case 4:
                // Afficher le nombre de produits dont la date de paiement a dépassé les 6 mois
                ProduitsDate();
                break;
            case 5:
                // Augmenter le prix des produits de 20% si la quantité est inférieure à 100 pièces
                AugmenterPrix();
                AfficherProduits(produits);
                break;
            case 6:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
                break;
            }
        }
        else
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
        }
    } while (choix != "6");
}