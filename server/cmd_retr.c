/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:52:44 by galy              #+#    #+#             */
/*   Updated: 2018/06/21 16:58:06 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

// 125 Canal de données déjà ouvert; début de transfert.
// 150 Statut de fichier vérifié; ouverture de canal de données en cours.
// 226 Fermeture du canal de données. Service terminé (par exemple, transfert defichier ou avortement)
// 250 Service fichier terminé.
// 421 Service non disponible, canal de contrôle fermé. Répondu à toute commande lorsque la fermeture imminente du service est prévue.
// 425 Erreur d'ouverture du canal de données.
// 426 Connexion fermée, transfert interrompu.
// 450 Service fichier non traité. Fichier non disponible (ex., fichier verrouillé par un autre utilisateur).
// 451 Service interrompu. Erreur locale de traitement.
// 452 Service interrompu. Espace insuffisant.
// 500 Erreur de syntaxe, commande non reconnue. Inclut le cas d'une ligne de commande trop longue.
// 501 Erreur de syntaxe dans le paramètres ou arguments.
// 530 Session non ouverte.
// 551 Service interrompu. Type de page inconnu.
// 552 Service fichier interrompu. Quota dépassé (pour le répertoire ou compte courant).

void	retr_cmd_response(t_vault *vault)
{

}

int		cmd_retr(t_vault *vault)
{	
	retr_cmd_response(vault);
	return (0);
}