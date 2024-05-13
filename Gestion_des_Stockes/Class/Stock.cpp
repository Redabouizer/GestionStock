#include "../Header.hpp"

Stock::Stock(string ref, string des, Depot *d) : referenceStock(ref), descriptionStock(des), depot(d) {}

// Méthodes pour accéder aux attributs
string Stock::getReferenceStock() const { return referenceStock; }
string Stock::getDescriptionStock() const { return descriptionStock; }
vector<Produit *> Stock::getProduits() const { return produits; }
Depot* Stock::getDepot() const { return depot; }

void Stock::setDescriptionStock(const string &newDescription)
{
    descriptionStock = newDescription;
}

// Méthode pour ajouter un produit au stock
void Stock::ajouterProduit(Produit *produit)
{
    produits.push_back(produit);
}
