# Draconophobia

A Pwn (Binary Exploitation) challenge focused on heap corruption.

## The Pitch

> You and your friend have been sent on a mission to defeat the mountain dragon. 
> This quest will reward you with experience points and fame. 
> Do you accept it?

## Objective

The goal of this challenge is to analyze and exploit the provided binary to successfully trigger the `lvl_up` function and read the contents of the `flag.txt` file.

## Local Deployment

The complete environment is provided via Docker to ensure the challenge is reproducible (isolated using `nsjail`). To start the server locally:

```bash
# Build the image and start the container in the background
docker-compose up -d --build
```
Once the server is running : 

```bash
nc 127.0.0.1 9004
```
## Write up

Are you stuck ? I invite you to read this article I wrote that explain the chall step by step.
[Read the full article and detailed Write-Up here] (Replace with your blog/article link)
