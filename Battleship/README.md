CruzID: taksandh@ucsc.edu

SOLO

I WROTE:
-AGENT.C
-AGENTTEST.C
-FIELD.C
-FIELDTEST.C

The BattleBoats system consisted of two main modules, Agent and Message, both of which are connected. Agent holds a state machine that moves around between the possible states that the game can be in, whether our agent is attacking, defending or waiting, it knows exactly what to do and when to do it. Message goes through a message received or creates a message with a payload, message ID, data fields and checksum that can be used to send information to the opponent or decode information sent to it and take the appropriate action. Agent utilizes the submodules, Field and Negotiation to correctly create the state machine. Field creates the battlefield and can modify and check both our own field and the opponent's field. We also use field to register enemy attacks, place our boats in the beginning, and make our guesses for when we are attacking. Negotiation is used to detect cheating, create a hash, and dictate which agent goes first based on a type of coin flip. My AI is completely random excpet for the direction that the boats are placed. For example, the huge boat is always South and the large boat is always east.

Starting this lab, like all other labs, was the most difficult part. Once I got field started, it was easy to understand and implement my logic for the rest of field, but Agent was a different story. I joined two labs and an office hour section before I fully understood how to code the agent state machine. A testing strategy I found very effective was putting random print statements into places or functions that were ont working or breaking my code. This helped me see just how far my code ran before the error occurred. It also helped me find the exact line where the error was in most cases. 

In this lab, I learned how to implement state machines in a bigger way to create a game that can be played by people or agents. I also learned how to use new functions in C like rand() and srand(). There were a lot of enumerated valued to use in our code, so I also learned and gained an appreciation for enumeration and how creating a struct can help keep ur code organized instead of just having a bunch of magic numbers. My MPLab was not working for most of this lab and I had to restart my computer every time if I wanted to run the code. It was a struggle but I got through it, and I really hope that it compiled and works correctly for the grader. 

This lab was satisfying to finish buvt every little bit of it was excruciating. Here I am at 11:46 typing this on the night it is due, having a panic attack, eve though  I have been working on this basically 24 hours a day for 4 days. This lab is so hard and the manual does not do a good job at explaining anything. The only reason I knew how to do anything was because of Oly, so thank you! Other than that, this lab is a hard no from me.`
