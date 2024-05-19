#include "../Header.hpp"
void AjouterStock()
{
    cout << "Ajouter un nouveau stock :" << endl;

    string refStock;
    string descStock;

    // Demande et vérification de la référence du stock
    Stock *stockExistant = nullptr;
    do
    {
        cout << "Référence du stock : ";
        cin >> refStock;

        stockExistant = TrouverStoc(refStock);
        if (stockExistant != nullptr)
        {
            cout << "Un stock avec cette référence existe déjà. Veuillez en choisir une autre." << endl;
        }
    } while (stockExistant != nullptr);

    cout << "Description du stock : ";
    cin >> descStock;

    int idDepot;
    string idDepotstr;
    Depot *depot = nullptr;

    // Demande de l'ID du dépôt avec vérification
    do
    {
        cout << "Entrez l'ID du dépôt : ";
        cin >> idDepotstr;

        // Check if the input is a valid integer
        if (!estNombre(idDepotstr)) // Assuming estNombre() is a function that checks if the string represents a valid integer
        {
            cout << "L'ID du dépôt doit être un nombre entier. Veuillez réessayer." << endl;
            continue;
        }

        idDepot = stoi(idDepotstr); // Convert string to integer

        depot = TrouverDepo(idDepot);
        if (!depot)
        {
            cout << "Dépôt avec l'ID " << idDepot << " non trouvé. Veuillez essayer à nouveau." << endl;
        }
    } while (!depot);

    // Création du nouveau stock
    Stock nouveauStock(refStock, descStock, depot);

    std::set<string> referencesAjoutees;

    int nombreProduits;
    cout << "Combien de produits souhaitez-vous ajouter au stock ? ";
    cin >> nombreProduits;

    // Ajout des produits au stock
    for (int i = 0; i < nombreProduits; ++i)
    {
        string refProduit;
        Produit *produit = nullptr;

        // Demande de la référence du produit avec vérification
        bool produitAjoute = false;
        do
        {
            cout << "Entrez la référence du produit : ";
            cin >> refProduit;

            if (referencesAjoutees.find(refProduit) != referencesAjoutees.end())
            {
                cout << "Le produit avec la référence " << refProduit << " a déjà été ajouté. Veuillez essayer une autre référence." << endl;
                continue;
            }

            produit = TrouverProd(refProduit);
            if (!produit)
            {
                cout << "Produit avec la référence " << refProduit << " non trouvé. Veuillez essayer à nouveau." << endl;
            }
            else
            {
                nouveauStock.ajouterProduit(produit);
                referencesAjoutees.insert(refProduit);
                produitAjoute = true;
            }
        } while (!produitAjoute);
    }

    // Ajout du stock au dépôt et à la liste des stocks
    depot->ajouterStock(&nouveauStock);
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
        int choix;
        string input;
        do
        {
            cout << "\n------------------------------------------" << endl;
            cout << "\nQue souhaitez-vous faire ?" << endl;
            cout << "1. Modifier la description du stock." << endl;
            cout << "2. Ajouter un produit au stock." << endl;
            cout << "3. Supprimer un produit du stock." << endl;
            cout << "4. Retour au menu principal" << endl;
            cout << "Choix : ";

            cin >> input;

            if (cin.eof())
            {
                cout << "\nAu revoir !" << endl;
                break;
            }

            if (cin.fail() || input < "1" || input > "4")
            {
                cout << "Choix invalide. Veuillez saisir un numéro entre 1 et 4." << endl;
                continue;
            }

            try
            {
                choix = stoi(input);
            }
            catch (...)
            {
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
                continue;
            }

            switch (choix)
            {
            case 1:
            {
                cout << "Nouvelle description : ";
                string nouvelleDesc;
                cin >> nouvelleDesc;
                it->setDescriptionStock(nouvelleDesc);
                cout << "La description du stock a été modifiée avec succès !" << endl;
                break;
            }
            case 2:
            {
                string refProduit;
                bool produitExiste;

                do
                {
                    cout << "Entrez la référence du produit à ajouter : ";
                    cin >> refProduit;

                    produitExiste = false;
                    for (Produit *produit : it->getProduits())
                    {
                        if (produit->getReference() == refProduit)
                        {
                            produitExiste = true;
                            break;
                        }
                    }

                    if (produitExiste)
                    {
                        cout << "Ce produit existe déjà dans le stock. Veuillez réessayer." << endl;
                    }
                    else
                    {
                        Produit *existingProduct = TrouverProd(refProduit);
                        if (!existingProduct)
                        {
                            cout << "Produit non trouvé. Veuillez réessayer." << endl;
                            continue;
                        }

                        it->ajouterProduit(existingProduct);
                        existingProduct->setStock(&(*it));

                        cout << "Le produit a été ajouté au stock avec succès !" << endl;
                        break;
                    }
                } while (true);

                break;
            }
            case 3:
            {
                string refProduit;
                cout << "Entrez la référence du produit à supprimer : ";
                cin >> refProduit;

                Produit *produitASupprimer = nullptr;
                for (Produit *produit : it->getProduits())
                {
                    if (produit->getReference() == refProduit)
                    {
                        produitASupprimer = produit;
                        break;
                    }
                }

                if (!produitASupprimer)
                {
                    cout << "Ce produit n'existe pas dans le stock." << endl;
                }
                else
                {
                    it->supprimerProduit(produitASupprimer);
                    produitASupprimer->setStock(nullptr);
                    cout << "Le produit a été supprimé du stock avec succès !" << endl;
                }
                break;
            }
            case 4:
            {
                cout << "Retour au menu principal." << endl;
                return;
            }
            }
        } while (choix != 5);
    }
    else
    {
        cout << "Aucun stock trouvé avec cette référence." << endl;
    }
}

void SupprimerStock()
{
    string refStockSuppr;
    cout << "Entrez la référence du stock à supprimer : ";
    cin >> refStockSuppr;

    auto it = find_if(stocks.begin(), stocks.end(), [&](const Stock &stock)
                      { return stock.getReferenceStock() == refStockSuppr; });

    if (it != stocks.end())
    {
        for (Produit *produit : it->getProduits())
        {
            produit->getFournisseur()->SupprimerProduit(produit->getReference());
            produit->setStock(nullptr);
        }

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
        cin >> input;

        // Vérification si l'utilisateur souhaite quitter
        if (cin.eof())
        {
            cout << "\nAu revoir !" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "5")
        {
            cout << "Choix invalide. Veuillez saisir un numéro entre 1 et 5." << endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
            continue;
        }

        switch (choix)
        {
        case 1:
        {
            cout << "\n------------------------------------------" << endl;
            AjouterStock();
            AfficherStocks(stocks);
            break;
        }
        case 2:
        {
            cout << "\n------------------------------------------" << endl;
            AfficherNbProduits();
            break;
        }
        case 3:
        {
            cout << "\n------------------------------------------" << endl;
            ModifierStock();
            AfficherStocks(stocks);
            break;
        }
        case 4:
        {
            cout << "\n------------------------------------------" << endl;
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