#include "../Header.hpp"

Fournisseur::Fournisseur(int id, string n, string c) : idFournisseur(id), nom(n), contact(c) {}

int Fournisseur::getIdFournisseur() const { return idFournisseur; }
string Fournisseur::getNom() const { return nom; }
string Fournisseur::getContact() const { return contact; }


void Fournisseur::ajouterProduit(const Produit &produit)
{
    produits.push_back(produit);
}

void Fournisseur::SupprimerProduit(const string &refProduit)
{
    auto it = find_if(produits.begin(), produits.end(),
                      [&](const Produit &prod) { return prod.getReference() == refProduit; });

    if (it != produits.end())
    {
        produits.erase(it);
        cout << "Produit supprimé avec succès du fournisseur !" << endl;
    }
    else
    {
        cout << "Aucun produit trouvé avec cette référence dans la liste du fournisseur." << endl;
    }
}

void Fournisseur::ajouterPaiement(Paiement* paiement)
{
    paiements.push_back(paiement);
}

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

