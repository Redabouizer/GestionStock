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
            cout <<"\033[31m" << "Un stock avec cette référence existe déjà. Veuillez en choisir une autre."<< "\033[0m" << endl;
        }
    } while (stockExistant != nullptr);

    cout << "Description du stock : ";
    cin >> descStock;

    int idDepot;
    string idDepotstr;
    Depot *depot = nullptr;
    vector<Depot> depots; 

    do
    {
        cout << "Entrez l'ID du dépôt : ";
        cin >> idDepotstr;

        if (!estNombre(idDepotstr))
        {
            cout <<"\033[31m" << "L'ID du dépôt doit être un nombre entier. Veuillez réessayer."<< "\033[0m" << endl;
            continue;
        }

        idDepot = stoi(idDepotstr);

        depot = TrouverDepo(idDepot);

        if (!depot)
        {
            cout <<"\033[31m"<< "Dépôt avec l'ID " << idDepot << " non trouvé. Voulez-vous le créer ? (O/N) : "<< "\033[0m";
            char choix;
            cin >> choix;
            if (choix == 'O' || choix == 'o')
            {
                cout << "Création du nouveau dépôt avec l'ID " << idDepot << "." << endl;
                string address;
                int capacity;
                cout << "Entrez l'adresse du nouveau dépôt : ";
                cin >> address;
                cout << "Entrez la capacité du nouveau dépôt : ";
                cin >> capacity;
                depots.emplace_back(idDepot, address, capacity);
                depot = &depots.back();
            }
        }
    } while (!depot);

    // Création du nouveau stock
    Stock nouveauStock(refStock, descStock, depot);

     set<string> referencesAjoutees;

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
                cout <<"\033[31m"<< "Le produit avec la référence " << refProduit << " a déjà été ajouté. Veuillez essayer une autre référence." << "\033[0m"<< endl;
                continue;
            }

            produit = TrouverProd(refProduit);
            if (!produit)
            {
                cout <<"\033[31m"<< "Produit avec la référence " << refProduit << " non trouvé. Veuillez essayer à nouveau." << "\033[0m"<< endl;
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

    cout << "\033[32m" "Stock ajouté avec succès !"<< "\033[0m" << endl;
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

    auto it = find_if(stocks.begin(), stocks.end(), [&](const Stock &stock)
                      { return stock.getReferenceStock() == refStockModif; });

    if (it != stocks.end())
    {
        int choix;
        string input;
        do
        {
           cout << "\033[1;31m"<< "\n------------------------------------------" << endl;
        cout <<"\033[36m"<<"\nQue souhaitez-vous faire ?" << endl;
            cout << "1. Modifier la description du stock." << endl;
            cout << "2. Ajouter un produit au stock." << endl;
            cout << "3. Supprimer un produit du stock." << endl;
            cout << "4. Retour au menu principal" << endl;
            cout <<"\033[33m"<< "Choix : "<< "\033[0m";

            cin >> input;

            if (cin.eof())
            {
                cout << "\033[32m" "\nAu revoir !" << endl;
                break;
            }

            if (cin.fail() || input < "1" || input > "4")
            {
                cout <<"\033[31m" << "Choix invalide. Veuillez saisir un numéro entre 1 et 4." << "\033[0m"<< endl;
                continue;
            }

            try
            {
                choix = stoi(input);
            }
            catch (...)
            {
                cout <<"\033[31m" << "Choix invalide. Veuillez saisir un numéro valide." << "\033[0m"<< endl;
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
                cout <<"\033[32m"<< "La description du stock a été modifiée avec succès !" << "\033[0m"<< endl;
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
                        cout <<"\033[31m" << "Ce produit existe déjà dans le stock. Veuillez réessayer." << "\033[0m"<< endl;
                    }
                    else
                    {
                        Produit *existingProduct = TrouverProd(refProduit);
                        if (!existingProduct)
                        {
                            cout <<"\033[31m" << "Produit non trouvé. Veuillez réessayer." << "\033[0m"<< endl;
                            continue;
                        }

                        it->ajouterProduit(existingProduct);
                        existingProduct->setStock(&(*it));

                        cout << "\033[32m" "Le produit a été ajouté au stock avec succès !"<< "\033[0m"<< endl;
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
                    cout <<"\033[31m"<< "Ce produit n'existe pas dans le stock."<< "\033[0m" << endl;
                }
                else
                {
                    it->supprimerProduit(produitASupprimer);
                    produitASupprimer->setStock(nullptr);
                    cout << "\033[32m" "Le produit a été supprimé du stock avec succès !" << "\033[0m"<< endl;
                }
                break;
            }
            case 4:
            {
                cout << "\033[32m" "Retour au menu principal." << "\033[0m"<< endl;
                return;
            }
            }
        } while (choix != 5);
    }
    else
    {
       cout <<"\033[31m"<< "Aucun stock trouvé avec cette référence." << "\033[0m"<< endl;
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
        cout << "\033[32m" "Stock supprimé avec succès !" << "\033[0m"<< endl;
    }
    else
    {
        // Le stock n'a pas été trouvé
        cout <<"\033[31m"<< "Aucun stock trouvé avec cette référence."<< "\033[0m" << endl;
    }
}

void GestionStock()
{

    int choix;
    string input;
    do
    {
        cout << "\033[1;31m"<< "\n------------------------------------------" << endl;
        cout <<"\033[36m"<<"\n********Menu de Gestion des Stocks********" << endl;
        cout << "1. Ajouter un stock" << endl;
        cout << "2. Afficher le nombre de produits de chaque stock" << endl;
        cout << "3. Modifier un stock" << endl;
        cout << "4. Supprimer un stock" << endl;
        cout << "5. Retour au menu principal" << endl;
        cout <<"\033[33m"<< "Choix : "<< "\033[0m";
        cin >> input;

        // Vérification si l'utilisateur souhaite quitter
        if (cin.eof())
        {
            cout << "\033[32m"<< "\nAu revoir !" << "\033[0m" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "5")
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro entre 1 et 5."<< "\033[0m" << endl;
            continue;
        }

        try
        {
            choix = stoi(input);
        }
        catch (...)
        {
            cout <<"\033[31m"<< "Choix invalide. Veuillez saisir un numéro valide." << "\033[0m"<< endl;
            continue;
        }

        switch (choix)
        {
        case 1:
        {
            cout << "\n------------------------------------------" << endl;
            AjouterStock();
            // AfficherStocks(stocks);
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
            // AfficherStocks(stocks);
            break;
        }
        case 4:
        {
            cout << "\n------------------------------------------" << endl;
            SupprimerStock();
            // AfficherStocks(stocks);
            break;
        }
        case 5:
        {
            cout << "\033[32m" << "Retour au menu principal." << "\033[0m"<< endl;
            break;
        }
        }
    } while (choix != 5);
}