# CMP105 Alternative Project

## Game 

**Dino Hanyman: Spanner in the Works** 

Dino Handyman is a 2D SFML platformer where the player controls a small dinosaur navigating a tile-based world. The player must use movement abilities, environmental interactions, and tools such as a throwable spanner to defeat enemies, unlock progression, and complete levels as quickly as possible. The game features data-driven level loading, multiple systems, and extended gameplay mechanics including checkpoints, enemies, and a leaderboard.

The engineering for this game is restricted to solely using the framework with few additions. 

**Controls:** 

A / D – Move left / right
Space – Jump
Space (mid-air) – Double jump (if unlocked)
Left Ctrl – Sprint / dash
R – Throw spanner
F – Interact (levers / end goal)
Escape – Pause game

***Extension suggestions***

In addition to the proposal laid out below, there are several features which could usefully be added to this game as part of a branch project, here are a few:

**Changelist**
Implemented a data-driven tilemap loading system using external files to construct levels
Added a basic enemy system (Gremlins) with simple movement/collision behaviour and player interaction
Added a spanner projectile system with basic physics-based movement and collision detection
Implemented checkpoints allowing player respawn after death at specific locations
Added pause, game over, and win menus with basic UI interaction
Implemented a leaderboard system that saves and loads completion times from file
Added a HUD system displaying player lives and a level timer during gameplay
Extended project structure to support multiple playable levels

## Student Details

**Student Name:** Stanislav Husak

**Student Number:** 2502567

**Course:** _CGAD_.

---
---

# Proposal

## Brief Overview of game 

Dino Handyman: Spanner in the Works is a 2D platformer where the player controls a small dinosaur navigating a hazardous tile-based environment. The core gameplay focuses on movement and timing-based platforming challenges. Progression is structured around the gradual introduction of new abilities such as sprinting, double jumping, and attacking, which are required to access new areas of the level. The player is timed throughout the game to encourage replayability and improved performance. Upon completion, the player is shown their completion time alongside a saved best time using a simple leaderboard system.

## Must Have Features

* Gremlin Animations: The gremlins will have different animation cycles including walking, running, idle, and attacking, for various actions they can be performing. 

* New types of enemies with different behaviour

## Should Have Features

* Moving platforms or environmental hazards (lava, spikes, etc.)

* Bonuses (speed boost, temporary invincibility)

## Could Have Features

* Achievement system (e.g. ‘complete without dying’)

* Coyote Time: The platforming will be enhanced by coyote time, a grace period during which the player can still jump even if they are not on a platform. 


## Wish to Have Features

* Large levels more complex multi-screen environments designed to extend playtime, expand exploration and support multiple playthroughs. Rather than short, linear levels, these levels are structured as interconnected sections featuring checkpoints, verticality and optional routes.

* Difficulty levels (easy/normal/hard)
