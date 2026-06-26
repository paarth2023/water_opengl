# What is this repo about? 

This repo is to document as well as implement concepts that will be needed to simulate water filling a bucket (fluid mechanics) in opengl.

## Steps till the last commit

1. Some of the very first steps i took was building a simple rendereing layer that abstracts away a lot of setup that is done using various shader, vertex buffers and vertex array functions.
2. On doing so, I did what most opengl noobies do, created a triangle which I cannot show since I got the idea of documenting this late. 
3. After knocking that out of the park, I did what any noobie would do, create a circle. 
4. On using some AI to read on what is needed, I got the gist that all comes down to gravity hence after some more help from AI, I implemented free fall of a ball under gravity.

[FreeFall](https://github.com/user-attachments/assets/1e106f9a-ecd3-4b82-bf55-542f875e208e)

5. I added an abstraction to circle rendering and now I can draw a ton of circles, hooray!!

<img width="1278" height="746" alt="image" src="https://github.com/user-attachments/assets/1b8b762c-3ac6-4641-93fe-450ffd555e27" />

## Next steps

1. Adding a color to the circles in the grid. 
2. Reading more on what **Smooth Particle Hydrodynamics** is and how I can implement a part of it.
3. Abstracting away a lot of the matrices that I am using if needed.
