---
Auteur: aliali 
Catégorie: misc 
Difficulté: Difficile 
Fichiers: gameplay.mp4
Flag: JDHACK{g0Od_oFF$eT_Go0D_CHUnK5}
Format du flag: JDHACK{this_is_a_flag}
Nom: blind_distribution 
Points: 500  
Statut: Tester 
---

## Description

Votre neveu était très content d'avoir réalisé sa première vidéo sur son jeu vidéo préféré. 
Malheureusement, il a renversé du café sur son ordinateur et sa vidéo ne s'affiche plus correctement... Aidez-le à retrouver la vidéo originale !

Vous obtiendrez le flag en visionnant la vidéo ```gameplay.mp4``` une fois qu'elle sera redevenue à son état d'origine.

-- English

Your nephew was thrilled to have recorded his very first video of his favorite game. Unfortunately, 
he spilled coffee all over his laptop, and now his video isn't loading correctly anymore... Help him recover the original footage!

You will find the flag by watching the video ```gameplay.mp4``` once it has been restored to its original state.

## Write-Up

-- Français 

Les fichiers MP4 sont organisés en ```box```. Chaque box contient d'autres boxes et celles-ci forment l'écosystème du fichier. Chacune d'entre elles possède une utilité différente, une taille et un type bien précis.

Un exemple de box importante est ```mdat``` : celle-ci contient l'ensemble des données brutes relatives à l'audio et aux images du fichier MP4.

Le header d'une box fait toujours 8 octets minimum :
Les 4 premiers octets définissent la Taille totale de la box.
Les 4 octets suivants définissent le Type (son nom en 4 caractères ASCII).

Ainsi pour se deplacer dans l'arboressence, il suffit de lire la taillen le nom de la box, si elle nous interesse "entrer dedans" en lisant les 8 octet suivants, sinon se déplacer de la taille de toute la box.

Voici l'imbrication de ces boxes selon la norme ISO/IEC 14496-12 :

![norme table](/misc/blind_distribution/images/norme.png "Titre de l'image")


Mais quel est le rapport entre ces boxs et l'affichage noir de la vidéo ? 

Plusieurs raisons peuvent amener le lecteur d'un fichier MP4 à ne faire paraître aucune image (tout en gardant la bande son). Ici il fallait s'intéressé à la box stco (Chunk Offset Box). Celle-ci est l'une des plus importantes puisqu'elle contient, pour chaque morceau de la vidéo, l'offset correspondant dans la box mdat.

Ainsi lorsqu'on analyse cette box avec un script on observe ceci :

![shuffle table](/misc/blind_distribution/images/shuffle_stco.png "Titre de l'image")

Ce qui n'est pas normal c'est que presque systématiquement, les offsets dans stco doivent être dans l'ordre croissant. En triant simplement cette liste pour remettre les adresses dans le bon ordre, on retrouvait la vidéo d'origine.

Voir ```solve.c``` pour plus de détails 

-- English

MP4 File Structure

MP4 files are organized into "boxes". Each box can contain other boxes, forming the file's ecosystem. Each of these has a specific purpose, as well as a defined size and type.

A prime example of an important box is ```mdat```. This box contains all the raw data for the audio and video frames of the MP4 file.

Every box header is at least 8 bytes long:

The first 4 bytes define the total Size of the box (in bytes).
The next 4 bytes define the Type (its name in 4 ASCII characters).

To navigate through the file hierarchy, you simply read the size and the name of the box. If the box is relevant to your search, you "enter" it by reading the next 8 bytes. If not, you skip ahead by moving your file pointer by the total size of the box.

Here is the nesting hierarchy of these boxes according to the ISO/IEC 14496-12 standard:
![norme table](/misc/blind_distribution/images/norme.png "Titre de l'image")


But what is the link between the black screen and the box's ?

There are several reasons why an MP4 player might display a black screen while still playing the audio track. In this challenge, the focus was on the stco (Chunk Offset Box). This is one of the most critical boxes because it contains the offset for every chunk of video data located in the mdat box.

When analyzing this box with a script, we observe the following:

![shuffle table](/misc/blind_distribution/images/shuffle_stco.png "Titre de l'image")

What is not normal here is that, almost systematically, the offsets in the stco table must be in ascending order. Since the video data is written sequentially in the file, the addresses should naturally increase. By simply sorting this list to put the offsets back in the correct order, the original video is restored.

See ```solve.c``` for more details 
