---
Auteur: aliali 
Catégorie: misc 
Difficulté: Moyen 
Fichiers: navi's_mania.mp4
Flag: JDHACK{l0st_tRaK$_!n_Th3_wO0d}
Format du flag: JDHACK{this_is_a_flag}
Nom: navi's mania  
Points: 500 
Statut: Tester 
---

## Description

Link est piégé dans une boucle temporelle par le Fléau. Il ouvre ce coffre pour l'éternité mais celui-ci semble désespérément vide. À vous d'analyser ce songe pour en extraire le véritable contenu.

Le flag est présent dans un support ```mp4```, vous étudierez la structure des fichiers mp4 afin de le retrouver. 

Puisse la documentation vous aider : https://b.goeswhere.com/ISO_IEC_14496-12_2015.pdf

----------------------------------------

Link is trapped in a time loop by the Calamity. He has been opening this chest for eternity, yet it remains hopelessly empty. It is up to you to analyze this dream and extract its true contents

The flag is hidden within an MP4 file. You must study the structure of MP4 files to find it.

May the documentation help you : https://b.goeswhere.com/ISO_IEC_14496-12_2015.pdf

## Write-Up

Les fichiers MP4 sont organisés en ```box```. Chaque box contient d'autres boxes et celles-ci forment l'écosystème du fichier. Chacune d'entre elles possède une utilité différente, une taille et un type bien précis.

Un exemple de box importante est ```mdat``` : celle-ci contient l'ensemble des données brutes relatives à l'audio et aux images du fichier MP4.

Le header d'une box fait toujours 8 octets minimum :
Les 4 premiers octets définissent la Taille totale de la box.
Les 4 octets suivants définissent le Type (son nom en 4 caractères ASCII).

Ainsi pour se deplacer dans l'arboressence, il suffit de lire la taillen le nom de la box, si elle nous interesse "entrer dedans" en lisant les 8 octet suivants, sinon se déplacer de la taille de toute la box.

Voici l'imbrication de ces boxes selon la norme ISO/IEC 14496-12 :

![norme table](/misc/blind_distribution/images/norme.png "Titre de l'image")

De plus généralement l'ensemble des information relatif à la vidéo se trouveront dans deux atomes trak, un pour les données audio, un pour les données vidéos.
Lorsque qu'un fichier mp4 contient plusieurs trak, quasiement tout les lecteurs propose une option pour transiter entre les différentes pistes contenue au sein du même fichier mp4.

Lorsque on utilise un tool pour parser tout le fichier et avoir une vue de surface (https://www.onlinemp4parser.com/) : 

![norme table](/misc/navi's%20mania/images/t1.png "Titre de l'image")

![norme table](/misc/navi's%20mania/images/t2.png "Titre de l'image")

Dans un fichier MP4, l'atome free (ou skip) est un espace réservé ou "vide" qui ne contient aucune donnée multimédia exploitable par le lecteur. Il sert principalement de zone tampon : les logiciels d'édition l'utilisent pour ajuster la taille du fichier ou insérer des métadonnées sans avoir à réécrire l'intégralité du contenu, ce qui rend le traitement beaucoup plus rapide.

On remarque deux choses très étranges : premièrement, le second atome free fait exactement la même taille que celui qui suit le premier trak. Secondement, un atome free de cette taille est très inhabituel.

De plus, les trak sont placés les uns à côté des autres au sein de l'atome moov. Il faut aussi noter que les lecteurs multimédias, lorsqu'ils rencontrent l'atome free, le skippent directement sans chercher à savoir ce qu'il contient.

On en déduit alors que l'atome free qui suit le second trak était la piste qui contenait le flag. Seul le nom de l'atome a été renommé.

Alors, il suffit de le re-renommer en trak ? Enfaite non, on compris vite que les données présentes y ont été randomisées. Il fallait alors copier toutes les données présentes dans le dernier free qui est en fait une copie du trak originel qui représentait la vidéo à retrouver.

Il suffit ensuite de les insérer à la place du free qui suit le premier trak, et renommer l'atome en trak.

Voir ```solve.c``` pour plus de détails.

-----------------------------------------------------

```MP4``` files are organized into ```box``` structures. Each box contains other boxes, forming the file's ecosystem. Each one has a specific purpose, a precise size, and a type.

An important example is the ```mdat``` box: it contains all the raw data related to the audio and images of the MP4 file.

A box header is always at least 8 bytes long: The first 4 bytes define the total Size of the box. The next 4 bytes define the Type (its name in 4 ASCII characters).

So, to navigate the tree structure, you just need to read the size and the name of the box. If we are interested in it, we "go inside" by reading the next 8 bytes; otherwise, we skip ahead by the size of the entire box.

Here is the nesting of these boxes according to the ISO/IEC 14496-12 standard :

![norme table](/misc/blind_distribution/images/norme.png "Titre de l'image")

Furthermore, generally all information related to the video will be found in two trak atoms: one for audio data and one for video data. When an MP4 file contains multiple trak atoms, almost all players offer an option to switch between the different tracks contained within the same MP4 file.

When using a tool to parse the whole file and get a surface view (https://www.onlinemp4parser.com/):

![norme table](/misc/navi's%20mania/images/t1.png "Titre de l'image")

![norme table](/misc/navi's%20mania/images/t2.png "Titre de l'image")

In an MP4 file, the free (or skip) atom is a reserved or "empty" space that contains no multimedia data usable by the player. It mainly serves as a buffer zone: editing software uses it to adjust the file size or insert metadata without having to rewrite the entire content, which makes processing much faster.

We notice two very strange things: firstly, the second free atom is exactly the same size as the one following the first trak. Secondly, a free atom of this size is very unusual.

Moreover, trak atoms are placed next to each other within the moov atom. It should also be noted that when multimedia players encounter a free atom, they skip it directly without checking its contents.

We can then deduce that the free atom following the second trak was the track containing the flag. Only the atom's name was renamed.

So, should we just rename it back to trak? Actually no, we quickly realized that the data inside had been randomized. We then had to copy all the data present in the last free atom, which is actually a copy of the original trak representing the video we needed to recover.

Then, simply insert them in place of the free atom following the first trak, and rename the atom to trak.

See ```solve.c``` for more details.

