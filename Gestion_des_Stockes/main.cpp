#include "Header.hpp"


int main()
{
    Fournisseur fournisseur1(1, "Fournisseur 1", "Contact 1");
    Fournisseur fournisseur2(2, "Fournisseur 2", "Contact 2");

    fournisseurs.insert(fournisseur1);
    fournisseurs.insert(fournisseur2);

    Stock stock1("Stock1", "Description Stock 1", nullptr);
    Stock stock2("Stock2", "Description Stock 2", nullptr);
    Produit produit1("Ref1", "Produit 1", 10, 100.0f, &stock1, &fournisseur1);
    Produit produit2("Ref2", "Produit 2", 20, 200.0f, &stock2, &fournisseur2);

    produits["Ref1"] = &produit1;
    produits["Ref2"] = &produit2;

    Paiement paiement1(1, 500.0f, Date(), &fournisseur1);
    Paiement paiement2(2, 700.0f, Date(), &fournisseur2);

    paiements.push_back(paiement1);
    paiements.push_back(paiement2);

    Depot depot1(1, "Adresse 1", 100);
    Depot depot2(2, "Adresse 2", 200);

    depots.push_back(depot1);
    depots.push_back(depot2);

    cout << "\033[38;2;255;166;47m" << "    __  ___          _____ __             __  " << endl;
    cout << "   /  |/  /____     / ___// /_____  _____/ /__" << endl;  //
    cout << "  / /|_/ / ___/     \\__ \\/ __/ __ \\/ ___/ //_/" << endl; 
    cout << " / /  / / /  _     ___/ / /_/ /_/ / /__/ ,<   " << endl;  
    cout << "/_/  /_/_/  (_)   /____/\\__/\\____/\\___/_/|_|  " << "\033[0m" << endl;

    

    int choix;
    string input;
    do
    {
        cout << "\033[1;31m"<< "\n------------------------------------------" << endl;
        cout <<"\033[36m"<<"\n******** Menu Principal ********" << endl;
        cout << "1. Gestion des produits" << endl;
        cout << "2. Gestion des stocks" << endl;
        cout << "3. Gestion des fournisseurs" << endl;
        cout << "4. Gestion des paiements" << endl;
        cout << "5. Quitter" << endl;
        cout <<"\033[33m"<< "Choix : "<< "\033[0m";

        cin >> input;

        if (cin.eof())
        {
            cout << "\033[32m" <<"\nAu revoir !"<< "\033[0m" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "5")
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro entre 1 et 5." << "\033[0m"<< endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro valide."<< "\033[0m" << endl;
            continue;
        }

        switch (choix)
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
            cout <<"\033[32m"<< "Au revoir !" << "\033[0m"<<  endl;
            break;
        }

    } while (choix != 5);

    return 0;
}