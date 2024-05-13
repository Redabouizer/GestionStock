#include "../Header.hpp"

void afficherMenuGestionPaiement()
{
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
                    // Gérer le cas où le produit n'est pas trouvé
                    // Peut-être demander à l'utilisateur de saisir à nouveau la référence du produit ou gérer d'une autre manière
                }
            }

            // Ajouter le paiement à la liste des paiements
            paiements.emplace_back(paiement);
            fournisseur->ajouterPaiement(&paiements.back());
        }
        else
        {
            cout << "Le fournisseur avec l'ID spécifié n'a pas été trouvé." << endl;
            // Gérer le cas où le fournisseur n'est pas trouvé
            // Peut-être demander à l'utilisateur de saisir à nouveau l'ID du fournisseur ou gérer d'une autre manière
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
    // Ajouter un produit
    // Demander à l'utilisateur de saisir les détails du nouveau produit
    string refProduit, desProduit;
    int quantiteProduit;
    float prixProduit;

    cout << "Nouveau produit :" << endl;
    cout << "Référence du produit : ";
    cin >> refProduit;
    cout << "Désignation du produit : ";
    cin >> desProduit;
    cout << "Quantité du produit : ";
    cin >> quantiteProduit;
    cout << "Prix du produit : ";
    cin >> prixProduit;

    // Création du nouveau produit
    Produit *nouveauProduit = new Produit(refProduit, desProduit, quantiteProduit, prixProduit, nullptr, nullptr);

    // Ajouter le nouveau produit au paiement
    it->ajouterProduit(nouveauProduit);

    cout << "Produit ajouté avec succès au paiement !" << endl;
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

    // Demandez à l'utilisateur de saisir les nouveaux détails du produit
    string nouvelleRef, nouvelleDes;
    int nouvelleQuantite;
    float nouveauPrix;

    cout << "Entrez les nouveaux détails du produit :" << endl;
    cout << "Nouvelle référence : ";
    cin >> nouvelleRef;
    cout << "Nouvelle désignation : ";
    cin >> nouvelleDes;
    cout << "Nouvelle quantité : ";
    cin >> nouvelleQuantite;
    cout << "Nouveau prix : ";
    cin >> nouveauPrix;

    // Mettez à jour les détails du produit dans le paiement
    produitAModifier->setReference(nouvelleRef);
    produitAModifier->setDesignation(nouvelleDes);
    produitAModifier->setQuantite(nouvelleQuantite);
    produitAModifier->setPrixHT(nouveauPrix);

    cout << "Produit mis à jour avec succès !" << endl;
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

    // Obtenez un itérateur vers le produit sélectionné
    auto produitASupprimer = it->getProduits().begin() + choixProduit - 1;

    // Supprimez le produit du paiement
    it->getProduits().erase(produitASupprimer);

    cout << "Produit supprimé avec succès !" << endl;
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
        string action;
        do
        {
            if (cin.eof())
            {
                cout << "\n";
                break;
            }
            // Proposer à l'utilisateur de choisir l'action à effectuer
            cout << "Choisissez une action : " << endl;
            cout << "1. Ajouter un produit" << endl;
            cout << "2. Modifier un produit" << endl;
            cout << "3. Supprimer un produit" << endl;
            getline(cin, action);
            if (action.find_first_not_of("0123456789") == string::npos && !action.empty()) // Vérifier si la saisie est un entier
            {
                int actionInt = stoi(action);
                switch (actionInt)
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
                default:
                {
                    cout << "Choix invalide. Veuillez saisir une option valide." << ::endl;
                    break;
                }
                }
            }
            else
            {
                cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
            }
        } while (action != "4");
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
    string choix;
    do
    {
        if (cin.eof())
        {
            cout << "\n";
            break;
        }
        afficherMenuGestionPaiement();
        getline(cin, choix);
        if (choix.find_first_not_of("0123456789") == string::npos && !choix.empty()) // Vérifier si la saisie est un entier
        {
            int choixInt = stoi(choix);
            switch (choixInt)
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
            default:
            {
                cout << "Choix invalide. Veuillez saisir une option valide." << endl;
                break;
            }
            }
        }
        else
        {
            cout << "Choix invalide. Veuillez saisir un numéro valide." << endl;
        }
    } while (choix != "6");
}
