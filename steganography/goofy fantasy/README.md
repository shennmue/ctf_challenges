---
Auteur: aliali 
Catégorie: misc 
Difficulté: Moyen 
Fichiers: goofy_fantasy.gif
Flag: JDHACK{!T_wA5_Re5erveD_fOR_Y0u}
Format du flag: JDHACK{this_is_a_flag}
Nom: goofy_fantasy
Points: 500  
Statut: Tester 
---

## Description

Vous êtes en vacances dans un pays lointain, mais vous avez oublié le mot de passe de votre chambre d'hôtel... 
Vous vous baladé alors en ville en espérant que cela finisse par vous revenir.

Le flag est dissimulé au sein des données du fichier ```goofy_fantasy.gif```. Vous étudierez alors la structure des fichiers GIF afin de le retrouver.

----------------------------------------

You are on vacation in a distant country, but you’ve forgotten your hotel room password... You wander through the city, hoping it will eventually come back to you.

The flag is hidden within the data of the goofy_fantasy.gif file. You must study the GIF file structure to find it.

## Write-Up

Les fichiers GIF sont ordonnés de cette manière :

![norme table](/misc/goofy%20fantasy/images/gif_struct.png "Titre de l'image")

Suite à la ```Global Color Table```, on retrouve les données associées à toutes les images incluses dans le fichier GIF. Chaque image correspond donc à une boucle qui comprend l'ensemble des composants situés entre la ```Global Color Table``` et le ```trailer```.

Le trailer étant l'octet qui marque la fin du fichier GIF : 0x3B.

Parmi ces blocs, étudions la composition du ```Graphic Control Extension```, ainsi que des ```Image Descriptor``` :

```Graphic Control Extension``` : 

![norme table](/misc/goofy%20fantasy/images/GCE.png "Titre de l'image")


Ce bloc optionnel contient un octet de ```Packed Fields```. Les bits 5, 6 et 7 y sont marqués comme "Reserved" (réservés pour un usage futur) et sont normalement à zéro.

```Image Descriptor``` : 

![norme table](/misc/goofy%20fantasy/images/ID.png "Titre de l'image")


Ce bloc contient également un octet de ```Packed Fields``` (situé à l'offset 9 du bloc). Ici, ce sont les bits 3 et 4 qui sont définis comme "Reserved".

Ces deux composants possèdent des bits "inutilisés" où de la donnée peut être introduite discrètement sans altérer le rendu du fichier. Cependant, la documentation indique que le bloc Graphic Control Extension est optionnel. Un fichier GIF peut théoriquement n'en contenir aucun.

Pour vérifier les valeurs de ces différents bits, il faut écrire un parser. Vous retrouverez à cette adresse un résumé schématisé de la norme GIF89a : https://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html. Une fois parsé (voir ```solve.py```), on remarque que ces bits réservés ne fluctuent qu'à partir d'une image x et uniquement dans les Image Descriptors.

Ainsi, en récupérant l'ensemble des bits réservés de chaque Image Descriptor et en les mettant bout à bout, on récupère le flag au format ASCII.

--------------------------------------------------

GIF files are organized in the following way:

![norme table](/misc/goofy%20fantasy/images/gif_struct.png "Titre de l'image")

Following the ```Global Color Table``` , we find the data associated with all the images included in the GIF file. Each image therefore corresponds to a loop that includes all the components located between the ```Global Color Table``` and the ```trailer```.

The trailer is the byte that marks the end of the GIF file: 0x3B.

Among these blocks, let’s study the composition of the ```Graphic Control Extension```, as well as the ```Image Descriptors``` :

```Graphic Control Extension``` : 

![norme table](/misc/goofy%20fantasy/images/GCE.png "Titre de l'image")

This optional block contains a ```Packed Fields``` byte. Bits 5, 6, and 7 are marked as "Reserved" (reserved for future use) and are normally set to zero.

```Image Descriptor``` : 

![norme table](/misc/goofy%20fantasy/images/ID.png "Titre de l'image")

This block also contains a ```Packed Fields``` byte (located at offset 9 of the block). Here, bits 3 and 4 are defined as "Reserved".

Both components possess "unused" bits where data can be discreetly introduced without altering the file's rendering. However, the documentation indicates that the Graphic Control Extension block is optional. A GIF file can theoretically contain none at all.

To check the values of these different bits, a parser must be written. You will find a schematized summary of the GIF89a standard at this address : https://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html. Once parsed (see ```solve.py```), we notice that these reserved bits only fluctuate starting from a specific image x and only within the Image Descriptors.

Thus, by collecting all the reserved bits from each Image Descriptor and concatenating them, the flag is retrieved in ASCII format.


