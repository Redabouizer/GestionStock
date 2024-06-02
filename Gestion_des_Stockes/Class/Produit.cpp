#include "../Header.hpp"

Produit::Produit(const  string &ref, const  string &des, int q, float prix, Stock *s, Fournisseur *f) : reference(ref), designation(des), quantite(q), prixHT(prix), stock(s), fournisseur(f) {}

string Produit::getReference() const { return reference; }
string Produit::getDesignation() const { return designation; }
int Produit::getQuantite() const { return quantite; }
float Produit::getPrixHT() const { return prixHT; }
Fournisseur *Produit::getFournisseur() const { return fournisseur; }
Stock *Produit::getStock() const { return stock; }

void Produit::setReference(const string &newReference) { reference = newReference; }
void Produit::setDesignation(const string &newDesignation) { designation = newDesignation; }
void Produit::setQuantite(int newQuantite) { quantite = newQuantite; }
void Produit::setPrixHT(float newPrixHT) { prixHT = newPrixHT; }
void Produit::setFournisseur(Fournisseur *newFournisseur) { fournisseur = newFournisseur; }
void Produit::setStock(Stock *newStock) { stock = newStock; }

Produit::~Produit() {}