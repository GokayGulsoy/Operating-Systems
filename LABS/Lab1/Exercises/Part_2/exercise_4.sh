#!/bin/bash

read -p "Are you a student? Y/N " ANSWER
case "$ANSWER" in
   [yY] | [yY][eE][sS])
     echo "You got the discount :)"
     ;;
   [nN] | [nN][oO])
     echo "No discount!"
     ;;
   *)
     echo "Please enter y/yes or n/no"
     ;;
 Esac
