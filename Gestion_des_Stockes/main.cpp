#include "Header.hpp"

int main()
{

    // Creating Fournisseurs
    Fournisseur fournisseur1(1, "Fournisseur 1", "Contact 1");
    Fournisseur fournisseur2(2, "Fournisseur 2", "Contact 2");

    Depot depot1(1, "Adresse 1", 100);
    Depot depot2(2, "Adresse 2", 200);
    depots.push_back(depot1);
    depots.push_back(depot2);

    Stock stock1("REF001", "Description du stock 1", &depot1);
    Stock stock2("REF002", "Description du stock 2", &depot2); 

    // Creating Produits
    Produit produit1("REF001", "Produit 1", 10, 100.0, &stock1, &fournisseur1);
    Produit produit2("REF002", "Produit 2", 5, 50.0, &stock2, &fournisseur2);

    // Creating Dates
    Date date1 = {12, 5, 2024};
    Date date2 = {20, 6, 2024};

    // Creating Paiements
    Paiement paiement1(1, 150.0, date1, &fournisseur1);
    paiement1.ajouterProduit(&produit1);

    Paiement paiement2(2, 200.0, date2, &fournisseur2);
    paiement2.ajouterProduit(&produit2);

    depot1.ajouterStock(&stock1);
    depot2.ajouterStock(&stock2);

    fournisseurs.insert(fournisseur1);
    fournisseurs.insert(fournisseur2);

    stocks.push_back(stock1);
    stocks.push_back(stock2);

    paiements.push_back(paiement1);
    paiements.push_back(paiement2);

    produits.emplace(produit1.getReference(), &produit1);
    produits.emplace(produit2.getReference(), &produit2);

    // Affichage du menu principal
    string choix;
    do
    {

        if (cin.eof())
        {
            cout << "\n";
            break;
        }                                                      // Utiliser getline() pour lire l'entrée de l'utilisateur
        cout << "\n******** Menu Principal ********" << endl;
        cout << "1. Gestion des produits" << endl;
        cout << "2. Gestion des stocks" << endl;
        cout << "3. Gestion des fournisseurs" << endl;
        cout << "4. Gestion des paiements" << endl;
        cout << "5. Quitter" << endl;
        cout << "Choix : ";
        getline(cin, choix);
        if (choix.find_first_not_of("0123456789") == string::npos && !choix.empty() ) // Vérifier si la saisie est un entier
        {
            int choixInt = stoi(choix); // onvertir la chaîne en entier
            switch (choixInt)
            {
            case 1:
                gestionProduits();
                break;
            case 2:
                GestionStock();
                break;
            case 3:
                GestionFournisseur();
                break;
            case 4:
                GestionPaiement();
                break;
            case 5:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
                break;
            }
        }
        else
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
        }
    } while (choix != "5");

    return 0;
}