#include "../Header.hpp"

ProduitElectronique::ProduitElectronique(string ref, string des, int q, float prix, string versionMat, string versionLog)
    : Produit(ref, des, q, prix, nullptr, nullptr), versionMateriel(versionMat), versionLogiciel(versionLog) {}
string ProduitElectronique ::getVersionMateriel() const { return versionMateriel; }
string ProduitElectronique ::getVersionLogiciel() const { return versionLogiciel; }