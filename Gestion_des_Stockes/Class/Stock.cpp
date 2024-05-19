#include "../Header.hpp"

Stock::Stock(string ref, string des, Depot *d) : referenceStock(ref), descriptionStock(des), depot(d) {}

string Stock::getReferenceStock() const { return referenceStock; }
string Stock::getDescriptionStock() const { return descriptionStock; }
vector<Produit *> Stock::getProduits() const { return produits; }
Depot* Stock::getDepot() const { return depot; }

void Stock::setDescriptionStock(const string &newDescription)
{
    descriptionStock = newDescription;
}

void Stock::ajouterProduit(Produit *produit)
{
    produits.push_back(produit);
}

void Stock::supprimerProduit(Produit* produit) {
        auto it = find(produits.begin(), produits.end(), produit);
        if (it != produits.end()) {
            produits.erase(it);
        }
    }