

## Description

> You are on vacation in a distant country, but you’ve forgotten your hotel room password... You wander through the city, hoping it will eventually come back to you.
>
> The flag is hidden within the data of the goofy_fantasy.gif file. You must study the GIF file structure to find it.

## Write-Up

GIF files are organized in the following way:

![norme table](images/gif_struct.png "Titre de l'image")

Following the ```Global Color Table``` , we find the data associated with all the images included in the GIF file. Each image therefore corresponds to a loop that includes all the components located between the ```Global Color Table``` and the ```trailer```.

The trailer is the byte that marks the end of the GIF file: 0x3B.

Among these blocks, let’s study the composition of the ```Graphic Control Extension```, as well as the ```Image Descriptors``` :

```Graphic Control Extension``` : 

![norme table](images/GCE.png "Titre de l'image")

This optional block contains a ```Packed Fields``` byte. Bits 5, 6, and 7 are marked as "Reserved" (reserved for future use) and are normally set to zero.

```Image Descriptor``` : 

![norme table](images/ID.png "Titre de l'image")

This block also contains a ```Packed Fields``` byte (located at offset 9 of the block). Here, bits 3 and 4 are defined as "Reserved".

Both components possess "unused" bits where data can be discreetly introduced without altering the file's rendering. However, the documentation indicates that the Graphic Control Extension block is optional. A GIF file can theoretically contain none at all.

## Parsing Gif file

To verify the values of these different bits, a parser must be written. You can find a diagrammed summary of the GIF89a standard at this address: https://giflib.sourceforge.net/whatsinagif/bits_and_bytes.html.

There are a few subtleties to take into account. Most blocks have a fixed size, so you simply need to skip over the block once its signature is identified.

Others have variable sizes and require a small calculation. For example:

![norme table](images/GCT.png "Titre de l'image")

The **Global Color Table** is an optional block that allows colors to be defined for all images, without them being redefined every time. In other words, it is a constant color macro.

To skip this block, you need to know the value of **N**. This is located in the previous block.

![norme table](images/LSD.png "Titre de l'image")

# Exploitation

Once parsed, it is noticeable that these reserved bits only fluctuate starting from image and only within the Image Descriptors.

Thus, by retrieving all the reserved bits from each Image Descriptor and concatenating them, the flag is recovered in ASCII format.

Look at ```solve.py```



