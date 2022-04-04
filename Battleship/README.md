Implemented a Battleship game which has an AI agent who places their own boats against the user. The game is fully functional and can be played by any user.

The BattleBoats system consisted of two main modules, Agent and Message, both of which are connected. Agent holds a state machine that moves around between the possible states that the game can be in, whether our agent is attacking, defending or waiting, it knows exactly what to do and when to do it. Message goes through a message received or creates a message with a payload, message ID, data fields and checksum that can be used to send information to the opponent or decode information sent to it and take the appropriate action. Agent utilizes the submodules, Field and Negotiation to correctly create the state machine. Field creates the battlefield and can modify and check both our own field and the opponent's field. We also use field to register enemy attacks, place our boats in the beginning, and make our guesses for when we are attacking. Negotiation is used to detect cheating, create a hash, and dictate which agent goes first based on a type of coin flip. My AI is completely random excpet for the direction that the boats are placed. For example, the huge boat is always South and the large boat is always east.

The rules of BattleBoats are nearly identical to the classic game Battleship: 
  1. A coin flip determines which player goes first 
  2. Both players place all of their boats on their own field. 
    a. Traditionally, there are four boats of various sizes.  Each boat takes up more 
      than one square, and no two boats can overlap. 
  3. Starting with the winner of the coin flip, players take turns.  Each turn: 
    a. The attacking player makes a guess, stating a row and a column to fire a shot. 
    b. The defending player describes the result of that shot.  The shot can: 
      i. MISS, i.e. land in open water. 
      ii. HIT a ship, but not sink it.  The portion of the ship that lies in that square 
        is damaged. 
      iii. SINK a ship, if it has hit the last undamaged square of a ship. 
    c. Both players record the results of the shot, and then the roles are reversed. 
  4. The game is over when one player is out of ships. 

Battleboats diverges from these rules in three small ways.  First, it uses different grid dimensions 
than the Hasbro game, as well as different ship sizes.  Second, it uses a more complicated 
method for determining the first player.  And finally, communication between players is handled 
using a very specific protocol. 
