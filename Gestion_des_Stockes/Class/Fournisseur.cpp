#include "../Header.hpp"

Fournisseur::Fournisseur(int id, string n, string c) : idFournisseur(id), nom(n), contact(c) {}

// Méthodes pour accéder aux attributs
int Fournisseur::getIdFournisseur() const { return idFournisseur; }
string Fournisseur::getNom() const { return nom; }
string Fournisseur::getContact() const { return contact; }

// Méthode pour ajouter un produit
void Fournisseur::ajouterProduit(const Produit &produit)
{
    produits.push_back(produit);
}

// Méthode pour accéder aux produits du fournisseur
const vector<Produit> &Fournisseur::getProduits() const
{
    return produits;
}

const vector<Paiement *> Fournisseur::getPaiements() const
{
    return paiements;
}

bool Fournisseur::operator<(const Fournisseur& other) const {
    return this->getIdFournisseur() < other.getIdFournisseur();
}
