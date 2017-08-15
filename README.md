# Shooter
Third Person Shooter game developed using Unreal Engine 4.

## Few key project's features:

- Experimental "Environment Query System" (EQS). NPC randomly choses next point to check being in Patrol Mode.
Points are chosen based on distance and visibility to NPC. Alongside with Perception system this gives nice AI Behavior.
![AI_System](https://github.com/vgomeniuk-games/Shooter/blob/master/AI_System.gif)
- Random map Generator with simple API to add any custom Blueprint object to be spawned.
Generator also checks intersection of the spawned object to avoid visible Mesh collisions.
![Generator_RandomArena](https://github.com/vgomeniuk-games/Shooter/blob/master/Generator_RandomArena.gif)
- NPC can be used both on maps randomly generated as well as manually designed. The only requirement is properly placed NaviMeshVolume.
![Gameplay_RandomArena](https://github.com/vgomeniuk-games/Shooter/blob/master/Gameplay_RandomArena.gif)
![Gameplay_InfinityBlade](https://github.com/vgomeniuk-games/Shooter/blob/master/Gameplay_InfinityBlade.gif)

Game was developed using free UE Marketplace assets and assets found on the web.

<b>Copyright information:</b>

All resources (sounds, music, font, spritesheets etc.) used in game were found online and are free for non-commercial use.
In case of any commercial usage, please, contact original authors for permission.
