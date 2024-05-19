#include "../Header.hpp"

Depot::Depot(int id, string ad, int cap) : idDepot(id), adresse(ad), capacite(cap) {}

int Depot::getIdDepot() const { return idDepot; }
string Depot::getAdresse() const { return adresse; }
int Depot::getCapacite() const { return capacite; }
vector<Stock *> Depot::getStocks() const {return stocks;}

void Depot::ajouterStock(Stock *stock)
{
    stocks.push_back(stock);
}
