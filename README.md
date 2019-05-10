# Carrom
===============================================================
NOTE : THIS IS A SINGLE PLAYER GAME WITH MULTIPLE MODES OF PLAY
===============================================================

Instructions to Use(When the game screen appears)
===============================================================
    * USING THE KEYBOARD
        # Press 'a' key to move the striker left
        # Press 's' key to move the stiker right
        # Press up and down arrow keys to adjust the power of the strike
        # Press left and right arrow keys to adjust the angle of strike
        # Press space bar to hit the Striker

    * USING THE MOUSE
        # Hold the right mouse button to select the striker and release to drop
          it to the appropriate position
        # Press the left mouse button, drag it to up or down to increase or decrease
          power, dragging left or right changes the angle, release the button to hit
          the striker
================================================================

MODES OF PLAY
================================================================

    * There are three modes of play
        # Normal Mode
            // Player can pocket all coins wihthout losing any points except for that
               with each second the player loses some points.
        # Black Mode
            // Player will get points for only pocketing the black coins, pocketing
               or hitting the white coins will cause the player to lose points
        # White Mode
            // Player will get points for only pocketing the white coins, pocketing
               or hitting the black coins will cause the player to lose points
    
    * In all the modes the player can pocket the queen without losing any points.

   |=================|====================|===================|==================|
   |  COIN TYPE      | NORMAL MODE        |     BLACK MODE    |     WHITE MODE   |
   |=================|====================|===================|==================|
   |  BLACK          |       10           |       20          |       -5 / -10   |
   |=================|====================|===================|==================|
   |  WHITE          |       20           |       -5 / 10     |        20        |
   |=================|====================|===================|==================|
   |  QUEEN (RED)    |       50           |        50         |        50        |
   |=================|====================|===================|==================|

=================================================================

Instructions to start the game
=================================================================
     * In the command line, argument needs to be supplied in order to change the mode
       of play, argument 1 for black mode, argument 2 for white mode, mo argument
       for normal mode
     * make
     * ./carrom (to start with normal mode)
     * ./carrom 1 (to start with black mode)
     * ./carrom 2 (to start with white mode)
================================================
