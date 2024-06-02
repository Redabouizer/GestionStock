#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <deque>
#include <iomanip>
#include <map>
#include <ctime>  // Pour utiliser time()
#include <chrono> // Pour travailler avec le temps
#include <csignal> // for signal handling
#include <cstdlib>  // for exit()

using namespace std;

class Produit;
class ProduitElectronique;
class Fournisseur;
class Paiement;
class Stock;
class Depot;

extern set<Fournisseur> fournisseurs;
extern list<Stock> stocks;
extern deque<Paiement> paiements;
extern map<string, Produit *> produits;
extern vector<Depot> depots;

struct Date
{
    int jour;
    int mois;
    int annee;
};

class Produit
{
private:
    string reference;
    string designation;
    int quantite;
    float prixHT;
    Stock *stock;
    Fournisseur *fournisseur;

public:
    
    Produit(const  string &ref, const  string &des, int q, float prix, Stock *s, Fournisseur *f);
    virtual ~Produit();

    string getReference() const;
    string getDesignation() const;
    int getQuantite() const;
    float getPrixHT() const;
    Fournisseur *getFournisseur() const;
    Stock *getStock() const;

    void setReference(const string &newReference);
    void setDesignation(const string &newDesignation);
    void setQuantite(int newQuantite);
    void setPrixHT(float newPrixHT);
    void setFournisseur(Fournisseur *newFournisseur);
    void setStock(Stock *newStock);

};

class ProduitElectronique : public Produit
{
private:
    string versionMateriel;
    string versionLogiciel;

public:
    ProduitElectronique(string ref, string des, int q, float prix, Stock *s, Fournisseur *f, string versionMat, string versionLog);
    ~ProduitElectronique();
    
    string getVersionMateriel() const;
    string getVersionLogiciel() const;
    void setVersionMateriel(const string &versionMat);
    void setVersionLogiciel(const string &versionLog);
    
};

class Fournisseur
{
private:
    int idFournisseur;
    string nom;
    string contact;
    vector<Produit> produits;//*
    vector<Paiement *> paiements;

public:
    Fournisseur(int id, string n, string c);
    int getIdFournisseur() const;
    string getNom() const;
    string getContact() const;
    const vector<Produit> &getProduits() const;
    const vector<Paiement *> getPaiements() const;
    void ajouterProduit(const Produit &produit);
    void SupprimerProduit(const string &refProduit);
    void ajouterPaiement(Paiement *paiement);
    bool operator<(const Fournisseur &other) const;
};

class Paiement
{
private:
    int idPaiement;
    float montant;
    Date datePaiement;
    const Fournisseur *fournisseur;
    vector<Produit *> produits;

public:
    Paiement(int id, float m, Date d, Fournisseur *f);
    int getIdPaiement() const;
    double getMontant() const;
    Date getDatePaiement() const;
    const Fournisseur *getFournisseur() const;
    vector<Produit *> getProduits() const;

    void setMontant(double newMontant);
    void setDatePaiement(const Date &newDatePaiement);
    void setFournisseur(const Fournisseur *newFournisseur);
    void ajouterProduit(Produit *produit);
    void supprimerProduit(size_t index);
    void fichePaiement() const;
};

class Stock
{
private:
    string referenceStock;
    string descriptionStock;
    vector<Produit *> produits;
    Depot *depot;

public:
    Stock(string ref, string des, Depot *d);
    string getReferenceStock() const;
    string getDescriptionStock() const;
    vector<Produit *> getProduits() const;
    Depot *getDepot() const;
    void setDescriptionStock(const string &newDescription);
    void ajouterProduit(Produit *produit);
    void supprimerProduit(Produit* produit);
};

class Depot
{
private:
    int idDepot;
    string adresse;
    int capacite;
    vector<Stock *> stocks;//son*

public:
    Depot(int id, string ad, int cap);
    int getIdDepot() const;
    string getAdresse() const;
    int getCapacite() const;
    vector<Stock *> getStocks() const;
    void ajouterStock(Stock *stock);
};

void GestionFournisseur();
void GestionPaiement();
void gestionProduits();
void GestionStock();

void AfficherFournisseurs(const set<Fournisseur> &fournisseurs);
void AfficherStocks(const list<Stock> &stocks);
void AfficherPaiements(const deque<Paiement> &paiements);
void AfficherProduits(const map<string, Produit *> &produits);
void AfficherProduitsElectroniques(const map<string, ProduitElectronique *> &produits);
void AfficherDepots(const vector<Depot> &depots);

Fournisseur *TrouverFourni(int idFournisseur);
Produit *TrouverProd(const string &refProduit);
ProduitElectronique *TrouverProdEle(const string &refProduit);
Stock *TrouverStoc(string referenceStock);
Paiement *TrouverPaiem(int idPaiement);
Depot *TrouverDepo(int idDepot);

bool estNombre(const string &str);
bool estNombreFlottant(const string &str);



#endif