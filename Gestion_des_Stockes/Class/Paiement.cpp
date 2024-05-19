#include "../Header.hpp"

Paiement::Paiement(int id, float m, Date d, Fournisseur *f) : idPaiement(id), montant(m), datePaiement(d), fournisseur(f) {}

int Paiement::getIdPaiement() const { return idPaiement; }
double Paiement::getMontant() const { return montant; }
Date Paiement::getDatePaiement() const { return datePaiement; }
const Fournisseur *Paiement::getFournisseur() const { return fournisseur; }
vector<Produit *> Paiement::getProduits() const { return produits; }

void Paiement::setMontant(double newMontant) { montant = newMontant; }
void Paiement::setDatePaiement(const Date &newDatePaiement) { datePaiement = newDatePaiement; }
void Paiement::setFournisseur(const Fournisseur *newFournisseur) { fournisseur = newFournisseur; }

void Paiement::ajouterProduit(Produit *produit)
{
    produits.push_back(produit);
}

void Paiement::supprimerProduit(size_t index) {
    if (index < produits.size()) {
        // Supprimez le produit à l'index spécifié
        produits.erase(produits.begin() + index);
        cout << "Produit supprimé avec succès !" << endl;
    } else {
        cout << "Index de produit invalide." << endl;
    }
}


void Paiement::fichePaiement() const
{
    cout << "- Identifiant paiement : " << idPaiement << endl;
    cout << "- Date paiement: " << datePaiement.jour << "/" << datePaiement.mois << "/" << datePaiement.annee << endl;
    cout << "- Identifiant fournisseur : " << fournisseur->getIdFournisseur() << endl;
    cout << "- Liste des produits : " << endl;
    cout << "\nRéférence produit \t Désignation \t Quantité \t Prix" << endl;
    for (const auto &produit : produits)
    {
        cout << produit->getReference() << "\t" << produit->getDesignation() << "\t" << produit->getQuantite() << "\t" << produit->getPrixHT() << endl;
    }
    float total = 0.0;
    for (const auto &produit : produits)
    {
        total += produit->getQuantite() * produit->getPrixHT();
    }
    cout << "\tTotal à payer  : " << total << endl;
}
