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

    // Vérification si le stock existe déjà
    Stock *stockExistant = TrouverStoc(refStock);
    if (stockExistant != nullptr)
    {
        cout << "Un stock avec cette référence existe déjà. Veuillez en choisir une autre." << endl;
        return;
    }

    // Création du stock
    // Supposons qu'on initialise depot à nullptr

    // Demande de saisie de la référence du produit et de l'ID du dépôt
    string refProduit;
    int idDepot;
    cout << "Entrez la référence du produit : ";
    cin >> refProduit;
    cout << "Entrez l'ID du dépôt : ";
    cin >> idDepot;

    // Recherche du produit et du dépôt
    Produit *produit = TrouverProd(refProduit);
    Depot *depot = TrouverDepo(idDepot);

    // Vérification si le produit et le dépôt existent
    if (produit && depot)
    {
        // Demander le nombre de produits à ajouter
        int nombreProduits;
        cout << "Combien de produits souhaitez-vous ajouter au stock ? ";
        cin >> nombreProduits;

        // Ajouter le produit au stock autant de fois que nécessaire
        for (int i = 0; i < nombreProduits; ++i)
        {
            Stock nouveauStock(refStock, descStock, depot);
            nouveauStock.ajouterProduit(produit);
            depot->ajouterStock(&nouveauStock);
            produit->setStock(&nouveauStock);
            stocks.push_back(nouveauStock);
        }

        cout << "Stock ajouté avec succès !" << endl;
    }
    else
    {
        // Afficher les détails de l'élément non trouvé
        if (!produit)
        {
            cout << "Produit avec la référence " << refProduit << " non trouvé." << endl;
        }
        if (!depot)
        {
            cout << "Dépôt avec l'ID " << idDepot << " non trouvé." << endl;
        }
        cout << "Impossible d'ajouter le stock." << endl;
    }
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

    int choix;
    string input;
    do
    {
        cout << "\n------------------------------------------" << endl;
        cout << "\n********Menu de Gestion des Stocks********" << endl;
        cout << "1. Ajouter un stock" << endl;
        cout << "2. Afficher le nombre de produits de chaque stock" << endl;
        cout << "3. Modifier un stock" << endl;
        cout << "4. Supprimer un stock" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout << "Choix : ";
        getline(cin, input);
        if (cin.eof())
        {
             cout << "\nAu revoir !" << endl;
            break;
        }
        // Si l'entrée est vide, continuer la boucle
        if (input.empty())
        {
            cout << "Veuillez saisir une valeur." << endl;
            continue;
        }
        if (cin.fail() || input < "1" || input > "5")
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
            // Réinitialiser le flux d'entrée
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choix = 0; // Réinitialiser la variable choix pour éviter une boucle infinie
            continue;
        }

        // Convertir l'entrée en entier
        choix = stoi(input);
        switch (choix)
        {
        case 1:
        {
            // Ajouter un stock
            AjouterStock();
            AfficherStocks(stocks);
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
            AfficherStocks(stocks);
            break;
        }
        case 4:
        {
            // Supprimer un stock
            SupprimerStock();
            AfficherStocks(stocks);
            break;
        }
        case 5:
        {
            cout << "Retour au menu principal." << endl;
            break;
        }
        }
    } while (choix != 5);
}