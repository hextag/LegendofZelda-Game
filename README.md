

Current Folder
      |
      ---CMakeLists.txt
      ---README.md
      ---src
           |
          ---- code files
      --external

#How to run the game?

1) Go to the the directory  and run the following commands
mkdir build
cd build
cmake ..
sudo make
./graphics_asgn1

#Game controls:

The player is controlled by the arrow keys:
"left key" => Rotate left,
 "right key" => Rotate right
 "up key" => Move Forward
 "space key" => jump
 "1 key" => Default view
 "2 key" => Follow Camera view
 "3 key" => Camera in Boat
 "4 key" => Top view 1
 "5 key" => Top view 2
 "6 key" => Tower view
 "7 key" => Helicopter view
 "w key" => Bring the Helicopter closer
 "s key" => Take the Helicopter far away from the boat
 "a key" => Take the Helicopter leftwards
 "d key" => Take the Helicopter rightwards
 "b key" => Boost the boat
 "c key" => Fire a fireballs through the cannon


Score, Level and Lives left are displayed on the title.

#Lives
The player is given 3 lives at the beginning. He will loose a life if he collides with a monster.

#Health
There are certain gifts on the sea which when collected will increase the health of the boat.

#Collision
On collision with rocks and enemy boats, the health of the boat is decreased.

#Gifts
There are barrels floating on the sea with gifts on them which when jumped over would increase the score of the boat.

#Boosters
There are some boosters floating on the sea which when collected would give boost to the boat for a couple of seconds.

#Fireball
Fireballs an be used to kill the monsters. They are realeased through cannons which is in front of the boat.

#Killing monsters
On Killing the monsters through Cannons, the score of the boat is increased and also the monsters leaves a booster when it dies which can be collected to boost the speed of the boat.

#Boss Monster
On Killing 4 Monsters, a Boss Monster would appear in the sea. To kill the boss monster, the boat should fire atleast 3 fireballs to kill the Boss Monster. When it dies, it leaves a booster and the score of the boat is increased.

##
Initially, you are given with health of 300. If you collide with an enemy boat or rocks, you loose health. When the health reaches 0, the GAME IS OVER.


##
Initially, you are given with 3 lifes. If you collide with a monster, you loose 1 life. When all the three lives are used, the GAME ENDS.
