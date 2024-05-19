#include "../Header.hpp"

ProduitElectronique::ProduitElectronique(string ref, string des, int q, float prix, Stock *s, Fournisseur *f, string versionMat, string versionLog)
    : Produit(ref, des, q, prix, s, f), versionMateriel(versionMat), versionLogiciel(versionLog) {}
string ProduitElectronique ::getVersionMateriel() const { return versionMateriel; }
string ProduitElectronique ::getVersionLogiciel() const { return versionLogiciel; }

void ProduitElectronique::setVersionMateriel(const string &versionMat) { versionMateriel = versionMat; }
void ProduitElectronique::setVersionLogiciel(const string &versionLog) { versionLogiciel = versionLog; }
ProduitElectronique::~ProduitElectronique() {}