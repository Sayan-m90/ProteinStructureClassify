# 🍩 RandomHomology 🍩
> Random Filtration of a GIC. Outputs a sequence of collapses which can be used to 
calculate homology (via SimPers).

This software creates a 'random' filtration of Graph Induced Complex. To create the 
filtration a preordering is designated to the N-Dimensional input point set via Morton 
Codes. This ordering allows us to subsample the point set and still respect the underlying density of the 
data. These successive subsamples can then be used to create collapses which is then fed into SimPers to 
compute topological persistence of the data set. The output is a set of barcodes.

![Alt text](http://web.cse.ohio-state.edu/~varchow/out2.gif "Data Viewing Window")

# Installation
Right now this project is being built via Xcode, but hope to create a CMake file soon.

```
echo "coming soon...";
```

# Dependencies
- ANN
- Boost
- GLUT
- OpenGL
- GLFW
- GLM

# References
 - [Graph Induced Complex](http://web.cse.ohio-state.edu/~tamaldey/GIC/gic.html) Tamal K. Dey, Fengtao Fan, Yusu Wang.
 - [Topological Persistence for Simplicial Maps](http://web.cse.ohio-state.edu/~tamaldey/paper/simplicial-map/simplicial-map.pdf) Tamal K. Dey, Fengtao Fan, Yusu Wang.
 - [Morton Codes](http://www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/) Jeroen Baert
 - [Z-Order Curve](https://en.wikipedia.org/wiki/Z-order_curve) - Wikipedia
 - [SimPers](http://web.cse.ohio-state.edu/~tamaldey/SimpPers/SimpPers-software/)

# License
[![CC 
BY-NC-ND](https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png)](https://creativecommons.org/licenses/)
# MortonHomology
# ProtienStructureClassify
