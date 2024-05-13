#include "../Header.hpp"

void afficherMenuGestionPaiement()
{
    cout << "\n-----------------------------------------------" << endl;
    cout << "\n******** Menu de Gestion des Paiements ********" << endl;
    cout << "1. Remplir la liste des paiements" << endl;
    cout << "2. Ajouter 20% de TVA sur les produits de chaque paiement" << endl;
    cout << "3. Modifier le fournisseur d'un paiement donné" << endl;
    cout << "4. Ajouter/modifier/supprimer un produit d'un paiement donné" << endl;
    cout << "5. Afficher la fiche de paiement pour chaque paiement" << endl;
    cout << "6. Retour au menu principal" << endl;
    cout << "Choix : ";
}

void remplirListePaiements()
{
    int nombrePaiements;
    cout << "Entrez le nombre de paiements à ajouter : ";
    cin >> nombrePaiements;

    for (int i = 0; i < nombrePaiements; ++i)
    {
        int idPaiement, idFournisseur;
        float montant;
        int jour, mois, annee;

        cout << "ID du paiement : ";
        cin >> idPaiement;
        cout << "Montant : ";
        cin >> montant;
        cout << "Date (jour mois annee) : ";
        cin >> jour >> mois >> annee;
        Date datePaiement = {jour, mois, annee};

        cout << "ID du fournisseur : ";
        cin >> idFournisseur;

        // Recherche du fournisseur correspondant dans une liste de fournisseurs existante
        Fournisseur *fournisseur = TrouverFourni(idFournisseur);

        if (fournisseur != nullptr)
        {
            // Créer un nouveau paiement avec le fournisseur
            Paiement paiement(idPaiement, montant, datePaiement, fournisseur);

            // Saisir les détails du produit associé
            int nombreProduits;
            cout << "Entrez le nombre de produits associés au paiement : ";
            cin >> nombreProduits;

            for (int j = 0; j < nombreProduits; ++j)
            {
                string refProduit;
                cout << "Reference du produit associé #" << j + 1 << " : ";
                cin >> refProduit;

                // Recherche du produit correspondant
                Produit *produit = TrouverProd(refProduit);
                if (produit != nullptr)
                {
                    // Ajouter le produit à la liste de produits du paiement
                    paiement.ajouterProduit(produit);
                    fournisseur->ajouterProduit(*produit);
                }
                else
                {
                    cout << "Le produit avec la reference spécifiée n'a pas été trouvé." << endl;
                }
            }

            // Ajouter le paiement à la liste des paiements
            paiements.emplace_back(paiement);
            fournisseur->ajouterPaiement(&paiements.back());
        }
        else
        {
            cout << "Le fournisseur avec l'ID spécifié n'a pas été trouvé." << endl;
        }
    }
    cout << "Liste des paiements ajoutée avec succès." << endl;
}

void ajouterTVA()
{
    const float tauxTVA = 0.20; // Taux de TVA à 20%

    for (auto &paiement : paiements)
    {
        for (auto &produit : paiement.getProduits())
        {
            float prixHT = produit->getPrixHT();
            float prixTTC = prixHT * (1 + tauxTVA); // Calcul du prix TTC avec TVA
            produit->setPrixHT(prixTTC);
        }
    }

    cout << "TVA ajoutée avec succès sur les produits de chaque paiement." << endl;
}

void ModifierFournisseurPaiement()
{
    // Modifier le fournisseur d'un paiement donné
    int idPaiementModif;
    cout << "Entrez l'identifiant du paiement à modifier : ";
    cin >> idPaiementModif;

    // Recherche du paiement dans la liste
    auto it = find_if(paiements.begin(), paiements.end(), [&](const Paiement &paiement)
                      { return paiement.getIdPaiement() == idPaiementModif; });

    if (it != paiements.end())
    {
        // Le paiement est trouvé
        cout << "Paiement trouvé. Entrez les nouveaux détails : " << endl;

        // Demander à l'utilisateur de saisir les détails du nouveau fournisseur
        int idFournisseur;
        cout << "Nouvel identifiant du fournisseur : ";
        cin >> idFournisseur;

        // Recherche du fournisseur dans la liste des fournisseurs
        auto itFournisseur = find_if(fournisseurs.begin(), fournisseurs.end(), [&](const Fournisseur &fournisseur)
                                     { return fournisseur.getIdFournisseur() == idFournisseur; });

        if (itFournisseur != fournisseurs.end())
        {
            // Le fournisseur est trouvé
            it->setFournisseur(&(*itFournisseur));
            cout << "Le fournisseur du paiement a été modifié avec succès !" << endl;
        }
        else
        {
            cout << "Aucun fournisseur trouvé avec cet identifiant." << endl;
        }
    }
    else
    {
        // Le paiement n'a pas été trouvé
        cout << "Aucun paiement trouvé avec cet identifiant." << endl;
    }

    cout << "TVA ajoutée avec succès sur les produits de chaque paiement." << endl;
}

void AjouterProduit(deque<Paiement>::iterator it)
{
    // Demander à l'utilisateur de saisir la référence du produit à ajouter
    string refProduit;
    cout << "Référence du produit à ajouter : ";
    cin >> refProduit;

    // Recherche du produit dans la map
    auto produitIt = produits.find(refProduit);

    if (produitIt != produits.end()) // Le produit existe dans la map
    {
        // Ajouter le produit au paiement
        it->ajouterProduit(produitIt->second);
        cout << "Produit ajouté avec succès au paiement !" << endl;
    }
    else // Le produit n'existe pas
    {
        cout << "Produit avec la référence " << refProduit << " non trouvé." << endl;
    }
}

// Modifier un produit dans un paiement donné
void ModifierProduit(deque<Paiement>::iterator it)
{
    // Vérifiez s'il y a des produits dans le paiement
    if (it->getProduits().empty())
    {
        cout << "Aucun produit dans ce paiement." << endl;
        return;
    }

    // Affichez les produits dans le paiement
    cout << "Produits dans ce paiement :" << endl;
    int i = 1;
    for (const auto &produit : it->getProduits())
    {
        cout << i << ". " << produit->getReference() << " - " << produit->getDesignation() << endl;
        i++;
    }

    // Demandez à l'utilisateur de choisir le produit à modifier
    size_t choixProduit;
    cout << "Choisissez le produit à modifier (entrez son numéro) : ";
    cin >> choixProduit;

    // Vérifiez si le numéro de produit est valide
    if (static_cast<size_t>(choixProduit) < 1 || static_cast<size_t>(choixProduit) > it->getProduits().size())
    {
        cout << "Numéro de produit invalide." << endl;
        return;
    }

    // Obtenez un pointeur vers le produit sélectionné
    Produit *produitAModifier = it->getProduits()[choixProduit - 1];

    // Affichez les détails du produit sélectionné
    cout << "Détails du produit sélectionné :" << endl;
    cout << "Référence : " << produitAModifier->getReference() << endl;
    cout << "Désignation : " << produitAModifier->getDesignation() << endl;
    cout << "Quantité : " << produitAModifier->getQuantite() << endl;
    cout << "Prix : " << produitAModifier->getPrixHT() << endl;

    // Demandez à l'utilisateur de saisir la nouvelle référence du produit
    string nouvelleRef;
    cout << "Entrez la nouvelle référence du produit : ";
    cin >> nouvelleRef;

    // Recherchez le produit dans la map
    auto produitIt = produits.find(nouvelleRef);

    if (produitIt != produits.end()) // Le produit existe dans la map
    {
        // Mettez à jour le produit dans le paiement avec le produit trouvé dans la map
        produitAModifier = produitIt->second;
        cout << "Produit mis à jour avec succès !" << endl;
    }
    else // Le produit n'existe pas
    {
        cout << "Produit avec la référence " << nouvelleRef << " non trouvé." << endl;
    }
}

// Supprimer un produit dans un paiement donné
void SupprimerProduit(deque<Paiement>::iterator it)
{
    // Vérifiez s'il y a des produits dans le paiement
    if (it->getProduits().empty())
    {
        cout << "Aucun produit dans ce paiement." << endl;
        return;
    }

    // Affichez les produits dans le paiement
    cout << "Produits dans ce paiement :" << endl;
    int i = 1;
    for (const auto &produit : it->getProduits())
    {
        cout << i << ". " << produit->getReference() << " - " << produit->getDesignation() << endl;
        i++;
    }

    // Demandez à l'utilisateur de choisir le produit à supprimer
    int choixProduit;
    cout << "Choisissez le produit à supprimer (entrez son numéro) : ";
    cin >> choixProduit;

    // Vérifiez si le numéro de produit est valide
    if (static_cast<size_t>(choixProduit) < 1 || static_cast<size_t>(choixProduit) > it->getProduits().size())
    {
        cout << "Numéro de produit invalide." << endl;
        return;
    }

    // Obtenez un pointeur vers le produit sélectionné
    Produit *produitASupprimer = it->getProduits()[choixProduit - 1];

    // Recherchez le produit dans la map
    auto produitIt = find_if(produits.begin(), produits.end(),
                             [&](const pair<string, Produit *> &p)
                             { return p.second == produitASupprimer; });

    if (produitIt != produits.end()) // Le produit existe dans la map
    {
        // Supprimez le produit du paiement
        it->getProduits().erase(it->getProduits().begin() + choixProduit - 1);
        cout << "Produit supprimé avec succès !" << endl;
    }
    else // Le produit n'existe pas
    {
        cout << "Le produit sélectionné n'est pas trouvé dans la liste des produits." << endl;
    }
}

void ActionProduitPaiement()
{

    // Fonctionnalité d: Ajouter/modifier/supprimer un produit d'un paiement donné
    cout << "Entrez l'identifiant du paiement auquel vous souhaitez apporter des modifications : ";
    int idPaiementModif;
    cin >> idPaiementModif;

    // Recherche du paiement dans la liste
    auto it = find_if(paiements.begin(), paiements.end(), [&](const Paiement &paiement)
                      { return paiement.getIdPaiement() == idPaiementModif; });

    if (it != paiements.end())
    {
        // Le paiement est trouvé
        cout << "Paiement trouvé. Voici les produits associés : " << endl;
        const vector<Produit *> &produits = it->getProduits();
        for (size_t i = 0; i < produits.size(); ++i)
        {
            cout << i + 1 << ". " << produits[i]->getReference() << " - " << produits[i]->getDesignation() << endl;
        }
        int choix;
        string input;
        do
        {

            // Proposer à l'utilisateur de choisir l'action à effectuer
            cout << "\n------------------------------------------" << endl;
            cout << "Choisissez une action : " << endl;
            cout << "1. Ajouter un produit" << endl;
            cout << "2. Modifier un produit" << endl;
            cout << "3. Supprimer un produit" << endl;
            cout << "4. Retour au menu" << ::endl;
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
            if (cin.fail() || input < "1" || input > "4")
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
                // Ajouter un produit
                AjouterProduit(it);
                break;
            case 2:
                // Modifier un Produit
                ModifierProduit(it);
                break;
            case 3:
                // Supprimer un produit
                SupprimerProduit(it);
                break;
            case 4:
            {
                cout << "Retour au menu principal." << ::endl;
                break;
            }
            }

        } while (choix != 4);
    }
}

void AfficherFiche()
{

    cout << "\nAffichage des fiches de paiement pour chaque paiement :" << endl;
    for (const auto &paiement : paiements)
    {
        paiement.fichePaiement();
        cout << endl;
    }
}

void GestionPaiement()
{
    int choix;
    string input;
    do
    {
        afficherMenuGestionPaiement();
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
        if (cin.fail() || input < "1" || input > "6")
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
            // Fonctionnalité a: Remplir la liste des paiements
            remplirListePaiements();
            AfficherPaiements(paiements);
            break;
        }
        case 2:
        {
            // Fonctionnalité b: Ajouter 20% de TVA sur les produits de chaque paiement
            ajouterTVA();
            AfficherPaiements(paiements);
            break;
        }
        case 3:
        {
            // Fonctionnalité c: Modifier le fournisseur d'un paiement donné
            ModifierFournisseurPaiement();
            AfficherPaiements(paiements);
            break;
        }
        case 4:
        {
            // Fonctionnalité d: Ajouter/modifier/supprimer un produit d'un paiement donné
            ActionProduitPaiement();
            AfficherPaiements(paiements);
            break;
        }
        case 5:
        {
            // Fonctionnalité e: Afficher la fiche de paiement pour chaque paiement
            AfficherFiche();
            break;
        }
        case 6:
        {
            cout << "Retour au menu principal." << endl;
            break;
        }
        }

    } while (choix != 6);
}
