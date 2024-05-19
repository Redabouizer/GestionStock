#include "../Header.hpp"

void remplirListePaiements()
{
    int nombrePaiements;

    // Loop until a valid integer is entered for the number of payments
    while (true)
    {
        cout << "Entrez le nombre de paiements à ajouter : ";
        string nombrePaiementsStr;
        cin >> nombrePaiementsStr;

        // Validate if input is a valid integer
        if (estNombre(nombrePaiementsStr))
        {
            nombrePaiements = stoi(nombrePaiementsStr);
            break;
        }
        else
        {
            cout << "Le nombre de paiements doit être un nombre entier. Veuillez réessayer." << endl;
        }
    }

    for (int i = 0; i < nombrePaiements; ++i)
    {
        int idPaiement, idFournisseur;
        float montant;
        int jour, mois, annee;

        // Input validation loop for payment ID
        while (true)
        {
            cout << "ID du paiement : ";
            string idPaiementStr;
            cin >> idPaiementStr;

            // Validate if input is a valid integer
            if (estNombre(idPaiementStr))
            {
                idPaiement = stoi(idPaiementStr);

                // Check if the payment ID already exists
                bool idExists = false;
                for (const auto &p : paiements)
                {
                    if (p.getIdPaiement() == idPaiement)
                    {
                        idExists = true;
                        break;
                    }
                }

                if (idExists)
                {
                    cout << "Ce ID de paiement existe déjà. Veuillez réessayer." << endl;
                    continue; // Ask user to re-enter ID
                }

                break;
            }
            else
            {
                cout << "L'ID du paiement doit être un nombre entier. Veuillez réessayer." << endl;
            }
        }

        while (true)
        {
            cout << "Montant : ";
            string montantStr;
            cin >> montantStr;

            // Validate if input is a valid floating-point number
            if (estNombreFlottant(montantStr))
            {
                montant = stof(montantStr);
                break;
            }
            else
            {
                cout << "Le montant doit être un nombre valide. Veuillez réessayer." << endl;
            }
        }

        // Input validation loop for date components
        while (true)
        {
            cout << "Date (jour mois annee) : ";
            string jourStr, moisStr, anneeStr;
            cin >> jourStr >> moisStr >> anneeStr;

            // Validate if input is a valid integer
            if (estNombreFlottant(jourStr) && estNombreFlottant(moisStr) && estNombreFlottant(anneeStr))
            {
                jour = stoi(jourStr);
                mois = stoi(moisStr);
                annee = stoi(anneeStr);

                // Validate if the date components form a valid date
                if (jour >= 1 && jour <= 31 && mois >= 1 && mois <= 12 && annee >= 1900 && annee <= 2024)
                {
                    break;
                }
                else
                {
                    cout << "La date doit être valide. Veuillez réessayer." << endl;
                }
            }
            else
            {
                cout << "Les composants de la date doivent être des nombres entiers. Veuillez réessayer." << endl;
            }
        }

        Date datePaiement = {jour, mois, annee};

        while (true)
        {
            cout << "ID du fournisseur : ";
            string idFournisseurStr;
            cin >> idFournisseurStr;

            if (estNombre(idFournisseurStr))
            {
                idFournisseur = stoi(idFournisseurStr);
                break;
            }
            else
            {
                cout << "L'ID du fournisseur doit être un nombre entier. Veuillez réessayer." << endl;
            }
        }
        Fournisseur *fournisseur = TrouverFourni(idFournisseur);

        if (fournisseur != nullptr)
        {
            Paiement paiement(idPaiement, montant, datePaiement, fournisseur);

            int nombreProduits;

            while (true)
            {
                cout << "Entrez le nombre de produits associés au paiement : ";
                string nombreProduitsStr;
                cin >> nombreProduitsStr;

                if (estNombre(nombreProduitsStr))
                {
                    nombreProduits = stoi(nombreProduitsStr);
                    break;
                }
                else
                {
                    cout << "Le nombre de produits associés doit être un nombre entier. Veuillez réessayer." << endl;
                }
            }

            for (int j = 0; j < nombreProduits; ++j)
            {
                string refProduit;
                cout << "Reference du produit associé #" << j + 1 << " : ";
                cin >> refProduit;

                // Check if the product reference is already associated with the payment
                bool produitDejaAssocie = false;
                for (const auto &p : paiement.getProduits())
                {
                    if (p->getReference() == refProduit)
                    {
                        produitDejaAssocie = true;
                        break;
                    }
                }

                if (produitDejaAssocie)
                {
                    cout << "Ce produit est déjà associé à ce paiement. Veuillez réessayer." << endl;
                    --j;
                    continue;
                }

                Produit *produit = TrouverProd(refProduit);
                if (produit != nullptr)
                {

                    paiement.ajouterProduit(produit);
                    fournisseur->ajouterProduit(*produit);
                }
                else
                {
                    cout << "Le produit avec la reference spécifiée n'a pas été trouvé." << endl;
                    --j;
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
    string idPaiementModifStr;
    int idPaiementModif;

    // Loop until a valid integer is entered for the payment identifier
    while (true)
    {
        cout << "Entrez l'identifiant du paiement à modifier : ";
        cin >> idPaiementModifStr;

        // Validate if input is a valid integer
        if (estNombre(idPaiementModifStr))
        {
            idPaiementModif = stoi(idPaiementModifStr);
            break;
        }
        else
        {
            cout << "L'identifiant du paiement doit être un nombre entier. Veuillez réessayer." << endl;
        }
    }

    // Recherche du paiement dans la liste
    auto it = find_if(paiements.begin(), paiements.end(), [&](const Paiement &paiement)
                      { return paiement.getIdPaiement() == idPaiementModif; });

    if (it != paiements.end())
    {
        // Le paiement est trouvé
        cout << "Paiement trouvé. Entrez les nouveaux détails : " << endl;

        // Demander à l'utilisateur de saisir les détails du nouveau fournisseur
        string idFournisseurStr;
        int idFournisseur;

        // Loop until a valid integer is entered for the supplier identifier
        while (true)
        {
            cout << "Nouvel identifiant du fournisseur : ";
            cin >> idFournisseurStr;

            // Validate if input is a valid integer
            if (estNombre(idFournisseurStr))
            {
                idFournisseur = stoi(idFournisseurStr);
                break;
            }
            else
            {
                cout << "L'identifiant du fournisseur doit être un nombre entier. Veuillez réessayer." << endl;
            }
        }

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

void ModifierProduit(deque<Paiement>::iterator it)
{
    // Check if there are products in the payment
    if (it->getProduits().empty())
    {
        cout << "Aucun produit dans ce paiement." << endl;
        return;
    }

    // Display products in the payment
    cout << "Produits dans ce paiement :" << endl;
    int i = 1;
    for (const auto &produit : it->getProduits())
    {
        cout << i << ". " << produit->getReference() << " - " << produit->getDesignation() << endl;
        i++;
    }

    // Ask the user to choose the product to modify
    string choixProduitStr;
    size_t choixProduit;

    while (true)
    {
        cout << "Choisissez le produit à modifier (entrez son numéro) : ";
        cin >> choixProduitStr;
        if (estNombre(choixProduitStr))
        {
            choixProduit = stoi(choixProduitStr);
            if (choixProduit >= 1 && choixProduit <= it->getProduits().size())
            {
                break;
            }
            else
            {
                cout << "Numéro de produit invalide. Veuillez entrer un numéro entre 1 et " << it->getProduits().size() << "." << endl;
            }
        }
        else
        {
            cout << "Veuillez entrer un nombre entier valide." << endl;
        }
    }

    // Get a pointer to the selected product
    Produit *produitAModifier = it->getProduits()[choixProduit - 1];

    // Display the details of the selected product
    cout << "Détails du produit sélectionné :" << endl;
    cout << "Référence : " << produitAModifier->getReference() << endl;
    cout << "Désignation : " << produitAModifier->getDesignation() << endl;
    cout << "Quantité : " << produitAModifier->getQuantite() << endl;
    cout << "Prix : " << produitAModifier->getPrixHT() << endl;

    // Ask the user to enter the new reference of the product
    string nouvelleRef;
    cout << "Entrez la nouvelle référence du produit : ";
    cin >> nouvelleRef;

    // Search for the product in the map
    auto produitIt = produits.find(nouvelleRef);

    if (produitIt != produits.end())
    { // The product exists in the map
        // Update the product in the payment with the product found in the map
        produitAModifier->setReference(nouvelleRef);
        cout << "Produit mis à jour avec succès !" << endl;
    }
    else
    { // The product does not exist
        cout << "Produit avec la référence " << nouvelleRef << " non trouvé." << endl;
    }
}

void SupprimerProduit(deque<Paiement>::iterator it)
{
    if (it->getProduits().empty())
    {
        cout << "Aucun produit dans ce paiement." << endl;
        return;
    }

    cout << "Produits dans ce paiement :" << endl;
    int i = 1;
    for (const auto &produit : it->getProduits())
    {
        cout << i << ". " << produit->getReference() << " - " << produit->getDesignation() << endl;
        i++;
    }

    string choixProduitStr;
    int choixProduit;

    while (true)
    {
        cout << "Choisissez le produit à supprimer (entrez son numéro) : ";
        cin >> choixProduitStr;
        if (estNombre(choixProduitStr))
        {
            choixProduit = stoi(choixProduitStr);
            if (choixProduit >= 1 && choixProduit <= static_cast<int>(it->getProduits().size()))
            {
                break;
            }
            else
            {
                cout << "Numéro de produit invalide. Veuillez entrer un numéro entre 1 et " << it->getProduits().size() << "." << endl;
            }
        }
        else
        {
            cout << "Veuillez entrer un nombre entier valide." << endl;
        }
    }

    // Utilisez la méthode de suppression de produit de la classe Paiement
    it->supprimerProduit(choixProduit - 1);
}

void ActionProduitPaiement()
{

    cout << "Entrez l'identifiant du paiement auquel vous souhaitez apporter des modifications : ";
    string idPaiementModifStr;
    int idPaiementModif;

    // Validate input to ensure it's an integer
    while (true)
    {
        cin >> idPaiementModifStr;
        if (estNombre(idPaiementModifStr))
        {
            idPaiementModif = stoi(idPaiementModifStr);
            break;
        }
        else
        {
            cout << "L'identifiant du paiement doit être un nombre entier. Veuillez réessayer : ";
        }
    }

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
            cout << "\n------------------------------------------" << endl;
            cout << "Choisissez une action : " << endl;
            cout << "1. Ajouter un produit" << endl;
            cout << "2. Modifier un produit" << endl;
            cout << "3. Supprimer un produit" << endl;
            cout << "4. Retour au menu" << ::endl;
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
                cout << "\n------------------------------------------" << endl;
                AjouterProduit(it);
                break;
            case 2:
                cout << "\n------------------------------------------" << endl;
                ModifierProduit(it);
                break;
            case 3:
                cout << "\n------------------------------------------" << endl;
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
        cout << "\n-----------------------------------------------" << endl;
        cout << "\n******** Menu de Gestion des Paiements ********" << endl;
        cout << "1. Remplir la liste des paiements" << endl;
        cout << "2. Ajouter 20% de TVA sur les produits de chaque paiement" << endl;
        cout << "3. Modifier le fournisseur d'un paiement donné" << endl;
        cout << "4. Ajouter/modifier/supprimer un produit d'un paiement donné" << endl;
        cout << "5. Afficher la fiche de paiement pour chaque paiement" << endl;
        cout << "6. Retour au menu principal" << endl;
        cout << "Choix : ";

        cin >> input;

        if (cin.eof())
        {
            cout << "\nAu revoir !" << endl;
            break;
        }

        if (cin.fail() || input < "1" || input > "6")
        {
            cout << "Choix invalide. Veuillez saisir un numéro entre 1 et 6." << endl;
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
            remplirListePaiements();
            AfficherPaiements(paiements);
            break;
        }
        case 2:
        {
            cout << "\n------------------------------------------" << endl;
            ajouterTVA();
            AfficherPaiements(paiements);
            break;
        }
        case 3:
        {
            cout << "\n------------------------------------------" << endl;
            ModifierFournisseurPaiement();
            AfficherPaiements(paiements);
            break;
        }
        case 4:
        {
            cout << "\n------------------------------------------" << endl;
            ActionProduitPaiement();
            AfficherPaiements(paiements);
            break;
        }
        case 5:
        {
            cout << "\n------------------------------------------" << endl;
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
