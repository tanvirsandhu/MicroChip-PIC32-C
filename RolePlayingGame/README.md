In this C program, I created a role-playing game on the micro controller which displays the room name, its description, and the directions that the user can go from that room (some directions don't have an exit). In addition, the user also has an inventory in which items can be picked up from rooms and used to enter other locked rooms. Based on the player's inventory, certain rooms will display certain messages.

For example, if the player's inventory does not hold the 'Golden Key' required to open the 'Golden Room,' the description might read something like: 'Welcome to the Throne Room. The throne is currently vacant.' And the available exits might be none. But, if the player has gone to the room that holds the golden key and added it to their inventory, the description might read something like: 'Welcome to the Throne Room. The throne is currently vacant, and you can feel the Golden Key weighing down in your pocket.' And the available exits will now be north. 

Each room has a corresponding file that has all of the information in between its lines. My program reads through the file, finds the information I need to choose which description to print, which exits to display, and what to add to the inventory. Have fun!

You can press q at anytime and exit the program.


