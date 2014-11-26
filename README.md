TiledMapEngine
==============

Features :

- Support all types of Tiled Map (orthogonnal, isometric & staggered)
- Resource System to easily share Image/Texture
- Loading/Saving .tmx & .tsx files



Working on :
--> Rect Optimizations System
 You give to the Manager/Map a special part of the world to render
 At the 26/11/14, the Rect Optimizations System work for Layer,
 it means that :
 - Only maps viewed are rendered
 - Only layers viewed of viewed maps are rendered
 - Only tiles viewed of viewed layers of viewed maps are rendered
 And tomorrow I hope that I could add ImageLayer and/or Object&ObjectGroup
