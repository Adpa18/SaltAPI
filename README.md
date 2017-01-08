# SaltAPI

Une **bonne** API pour le projet HTTPd / Zia {EPITECH} promo 2019

## Notre merveilleux site web

[SaltAPI](https://saltapi.github.io/)

## Nous suivre

* [Twitter *soon*](https://twitter.com)
* [Github](https://github.com/Adpa18/SaltAPI)
* [Yammer](https://www.yammer.com/epitech.eu/#/threads/inGroup?type=in_group&feedId=10244128)

## Caractéristiques

Notre API possède plusieurs propriétés intéressantes.

### Un design modulaire poussé, près pour le futur.

Le concept de modularité poussé dans ses derniers retranchements grâce au découpage malin des différentes actions du serveur web en modules.
Le core même du serveur est proposé en tant que module. La partie réseau est elle aussi proposée en tant que module.
Il n'aura jamais été aussi simple d'implémenter un serveur web dans un autre protocole que TCP par exemple!

### Philosophie UNIX *compliant*

> Write programs that do one thing and do it well.

Le design de notre API permet de découper le fonctionnement entier d'un serveur web sous forme de modules.
Chacun des modules que nous vous proposons est dédié à une et une seule tâche.

> Write programs to work together.

Car bien documentée, faire fonctionner des modules de pair n'aura jamais été aussi simple.
En effet, nous vous permettons de les assembler afin de traiter au mieux vos requêtes HTTP.

Le traitement du message HTTP du client (a.k.a requête HTTP) est effectué de manière consistante grâce à l'utilisation des modules dédiés.
La requête du client ainsi que la réponse du serveur sont des objets structurellement similaire que vous pouvez manipuler de manière rapide et précise.

### Abstraction entre la partie *serveur* et le traitement de la requête HTTP

Structurellement, la partie dite *serveur* et le traitement des messages HTTP sont séparés.
Vous ne serez donc pas perturbé par le fonctionnement du serveur pendant votre traitement de la requête HTTP.

### Configuration en XML, JSON, ou YAML?

Plus besoin de se plier aux exigences d'un format que vous n'appréciez pas!
La configuration du serveur web est faite grâce à un module. Dès lors, vous pouvez implémenter n'importe quel parser sans avoir à recompiler votre serveur.

### Les modules sont facilement interchangeables

Le module de logging ne vous plaît pas? Implémentez le votre pour écrire vos logs à plusieurs endroits:
	* dans un fichier
	* sur la sortie standard
	* dans syslog
	* dans systemd
	* un envoi par mail ??

### Une requête HTTP mérite beaucoup de soin

Parce qu'elle le vaut bien, une requête HTTP demande un suivi à la fois approprié et personnalisé.
Pour son traitement délicat, nous avons déjà anticipé ces besoins et lui mettons à disposition des modules:
	* de décompression
	* d'exécution de script via CGI
	* de lecture de fichier
Elle peut profiter de ces services en les ajoutant à sa convenance sur sa *processing list*.

### A l'assaut des requêtes simultanées

Avec cette API, la création d'une threadpool gérant le traitement des différentes requêtes HTTP est simplifiée.
Le serveur doit pouvoir gérer les requêtes des différents clients, c'est pour cela que nous avons prévu dans notre design un traitement multithreadé ce celles-ci.
