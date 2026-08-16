#!/bin/bash

# --- LA LIGNE MAGIQUE ---
# Redirige TOUT le flux d'erreur (fd 2) vers le néant pour tout le script.
# Plus aucun log (stty, nsjail, bash errors) ne pourra atteindre le joueur.
exec 2>/dev/null
# ------------------------

export TERM=xterm
export TERMINFO=/usr/share/terminfo

# On force la taille
stty rows 50 cols 150

# Plus besoin de mettre 2>/dev/null à la fin ici, c'est géré globalement
exec nsjail \
    --quiet \
    --user nobody \
    --group nogroup \
    --hostname magic_maze \
    --chroot /app \
    --disable_clone_newcgroup \
    --keep_env \
    -R /dev/urandom \
    -R /dev/tty \
    -R /dev/null \
    -R /dev/zero \
    -R /lib -R /lib64 -R /usr/lib \
    -R /usr/share/terminfo \
    -R /bin -R /usr/bin \
    -R /app/flag.txt \
    -R /app/magic_maze \
    -- /app/magic_maze
