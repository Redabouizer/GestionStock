#include "Header.hpp"

set<Fournisseur> fournisseurs;
list<Stock> stocks;
deque<Paiement> paiements;
map<string, Produit *> produits;
vector<Depot> depots;

void AfficherFournisseurs(const set<Fournisseur> &fournisseurs)
{
    cout << "Liste des fournisseurs :" << endl;
    cout << left << setw(15) << "ID" << setw(20) << "Nom" << setw(20) << "Contact" << setw(20) << "Produits" << setw(20) << "Paiements" << endl;

    for (const auto &fournisseur : fournisseurs)
    {
        cout << left << setw(15) << fournisseur.getIdFournisseur() << setw(20) << fournisseur.getNom() << setw(20) << fournisseur.getContact();

        // Display associated products
        cout << setw(20);
        for (const auto &produit : fournisseur.getProduits())
        {
            cout << produit.getDesignation() << ", ";
        }

        // Display associated payments
        cout << setw(20);
        for (const auto &paiement : fournisseur.getPaiements())
        {
            cout << paiement->getIdPaiement() << ", ";
        }

        cout << endl;
    }
}

void AfficherStocks(const list<Stock> &stocks)
{
    cout << "Liste des stocks :" << endl;

    // Affichage de l'en-tête du tableau
    cout << left << setw(20) << "Référence" << setw(20) << "Description" << setw(20) << "Depot" << setw(20) << "Produits" << endl;

    for (const auto &stock : stocks)
    {
        cout << left << setw(20) << stock.getReferenceStock() << setw(20) << stock.getDescriptionStock();

        // Afficher le depot associé
        if (stock.getDepot() != nullptr)
        {
            cout << setw(20) << stock.getDepot()->getAdresse();
        }
        else
        {
            cout << setw(20) << "Aucun depot";
        }

        // Retrieve the associated products of the stock
        vector<Produit *> produits = stock.getProduits();
        if (!produits.empty())
        {
            // Print the products
            for (const auto &produit : produits)
            {
                cout << produit->getDesignation() << ", ";
            }
        }
        else
        {
            cout << "Aucun produit";
        }

        cout << endl;
    }
}

void AfficherPaiements(const deque<Paiement> &paiements)
{
    cout << "Liste des paiements :" << endl;

    // Affichage de l'en-tête du tableau
    cout << left << setw(20) << "ID_P" << setw(20) << "Montant" << setw(20) << "Date" << setw(20) << "ID_Four" << setw(20) << "Produits" << endl;

    for (const auto &paiement : paiements)
    {
        cout << left << setw(20) << paiement.getIdPaiement() << setw(20) << paiement.getMontant() << paiement.getDatePaiement().jour << "/" << paiement.getDatePaiement().mois << "/" << setw(20) << paiement.getDatePaiement().annee << setw(20) << paiement.getFournisseur()->getIdFournisseur();

        // Affichage des produits associés au paiement
        string produitsStr;
        for (const auto &produit : paiement.getProduits())
        {
            produitsStr += produit->getReference() + ", ";
        }
        if (!produitsStr.empty())
        {
            // Supprimer la virgule et l'espace en trop à la fin
            produitsStr = produitsStr.substr(0, produitsStr.size() - 2);
        }
        cout << setw(20) << produitsStr << endl;
    }
}

void AfficherProduits(const map<string, Produit *> &produits)
{
    cout << "Liste des produits :" << endl;

    // Affichage de l'en-tête du tableau
    cout << left << setw(20) << "Référence" << setw(20) << "Désignation" << setw(20) << "Quantité" << setw(20) << "Prix_HT" << setw(20) << "Réf_Stock" << setw(20) << "ID_Fournisseur" << endl;

    for (const auto &pair : produits)
    {
        const Produit *produit = pair.second;
        cout << left << setw(20) << produit->getReference() << setw(20) << produit->getDesignation() << setw(20) << produit->getQuantite() << setw(20) << produit->getPrixHT();

        // Vérifier si le produit est associé à un stock
        if (produit->getStock() != nullptr)
        {
            cout << setw(20) << produit->getStock()->getReferenceStock();
        }
        else
        {
            cout << setw(20) << "-";
        }

        // Vérifier si le produit est associé à un fournisseur
        if (produit->getFournisseur() != nullptr)
        {
            cout << setw(20) << produit->getFournisseur()->getIdFournisseur();
        }
        else
        {
            cout << setw(20) << "-";
        }

        cout << endl;
    }
}

void AfficherDepots(const vector<Depot> &depots)
{
    cout << "Liste des dépôts :" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Adresse" << setw(10) << "Capacité" << setw(20) << "Stocks" << endl;

    for (const auto &depot : depots)
    {
        cout << left << setw(10) << depot.getIdDepot() << setw(20) << depot.getAdresse() << setw(10) << depot.getCapacite();

        // Afficher les stocks associés
        vector<Stock *> stocks = depot.getStocks();
        if (!stocks.empty())
        {
            cout << setw(20);
            for (const auto &stock : stocks)
            {
                cout << stock->getReferenceStock() << ", ";
            }
        }
        else
        {
            cout << "Aucun stock";
        }

        cout << endl;
    }
}

Fournisseur *TrouverFourni(int idFournisseur)
{
    for (const auto &fournisseur : fournisseurs)
    {
        if (fournisseur.getIdFournisseur() == idFournisseur)
        {
            return const_cast<Fournisseur *>(&fournisseur);
        }
    }
    return nullptr;
}

Produit *TrouverProd(string refProduit)
{
    for (const auto &paire : produits)
    {
        if (paire.second->getReference() == refProduit)
        {
            return paire.second;
        }
    }
    return nullptr;
}

Stock *TrouverStoc(string referenceStock)
{
    for (auto it = stocks.begin(); it != stocks.end(); ++it)
    {
        if (it->getReferenceStock() == referenceStock)
        {
            return &(*it);
        }
    }
    return nullptr; // Stock non trouvé
}

Depot* TrouverDepo(int idDepot)
{
    for (auto& depot : depots)
    {
        if (depot.getIdDepot() == idDepot)
        {
            return &depot;
        }
    }
    return nullptr;
}

Paiement* TrouverPaiem(int idPaiement)
{
    for (auto& paiement : paiements)
    {
        if (paiement.getIdPaiement() == idPaiement)
        {
            return &paiement;
        }
    }
    return nullptr;
}