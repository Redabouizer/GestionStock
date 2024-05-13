#include "../Header.hpp"
void AjouterStock()
{
    cout << "Ajouter un nouveau stock :" << endl;

    string refStock;
    string descStock;
    cout << "Référence du stock : ";
    cin >> refStock;
    cout << "Description du stock : ";
    cin >> descStock;

    // Création du stock
    Stock nouveauStock(refStock, descStock, nullptr); // Supposons qu'on initialise depot à nullptr

    // Ajout du stock à la liste
    stocks.push_back(nouveauStock);
    cout << "Stock ajouté avec succès !" << endl;
}

void AfficherNbProduits()
{
    for (const auto &stock : stocks)
    {
        cout << "Stock " << stock.getReferenceStock() << " : " << stock.getProduits().size() << " produits" << endl;
    }
}

void ModifierStock()
{
    string refStockModif;
    cout << "Entrez la référence du stock à modifier : ";
    cin >> refStockModif;

    // Recherche du stock dans la liste
    auto it = find_if(stocks.begin(), stocks.end(), [&](const Stock &stock)
                      { return stock.getReferenceStock() == refStockModif; });

    if (it != stocks.end())
    {
        // Le stock est trouvé
        cout << "Stock trouvé. Entrez les nouveaux détails : " << endl;
        string nouvelleDesc;
        cout << "Nouvelle description : ";
        cin >> nouvelleDesc;

        // Modifier les détails du stock
        it->setDescriptionStock(nouvelleDesc);
        cout << "Le stock a été modifié avec succès !" << endl;
    }
    else
    {
        // Le stock n'a pas été trouvé
        cout << "Aucun stock trouvé avec cette référence." << endl;
    }
}

void SupprimerStock()
{
    string refStockSuppr;
    cout << "Entrez la référence du stock à supprimer : ";
    cin >> refStockSuppr;

    // Recherche du stock dans la liste
    auto it = find_if(stocks.begin(), stocks.end(), [&](const Stock &stock)
                      { return stock.getReferenceStock() == refStockSuppr; });

    if (it != stocks.end())
    {
        // Le stock est trouvé, le supprimer de la liste
        stocks.erase(it);
        cout << "Stock supprimé avec succès !" << endl;
    }
    else
    {
        // Le stock n'a pas été trouvé
        cout << "Aucun stock trouvé avec cette référence." << endl;
    }
}

void GestionStock()
{

    string choix;
    do
    {
        // Affichage du menu de gestion des stocks
        cout << "\n********Menu de Gestion des Stocks********" << endl;
        cout << "1. Ajouter un stock" << endl;
        cout << "2. Afficher le nombre de produits de chaque stock" << endl;
        cout << "3. Modifier un stock" << endl;
        cout << "4. Supprimer un stock" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Choix : ";
        getline(cin, choix);
        if (choix.find_first_not_of("0123456789") == string::npos && choix != "") // Vérifier si la saisie est un entier
        {
            int choixInt = stoi(choix);
            switch (choixInt)
            {
            case 1:
            {
                // Ajouter un stock
                AjouterStock();
                break;
            }
            case 2:
            {
                // Afficher le nombre de produits de chaque stock
                AfficherNbProduits();
                break;
            }
            case 3:
            {
                // Modifier un stock
                ModifierStock();
                break;
            }
            case 4:
            {
                // Supprimer un stock
                SupprimerStock();
                break;
            }
            case 5:
            {
                cout << "Retour au menu principal." << endl;
                break;
            }
            default:
            {
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
                break;
            }
            }
        }
        else
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
        }
    } while (choix != "5");
}