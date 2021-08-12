Consider the set of all permutations of the Pocket Cube. This set forms a group with the operator of composition of $2$ states of the Pocket Cube, where if we treat each a permutation of a Pocket Cube as a permutation of it's stickers, the operator is just composition over the permutation of stickers.

It is interesting to note that for the case of the 2x2x2 and 3x3x3 Rubik's cube, the permutation of it's stickers can be uniquely determined by the color of stickers on a Rubik's cube as every piece consists of a unique tuple of stickers. For instance, in the 2x2x2 Rubik's cube, the tuples are $\{WBR,WBO,WOG,WGR,YBR,YRG,YGO,YOB\}$. This does not hold on bigger Rubik's cubes. Consider the center pieces of the 4x4x4 Rubik's cubes, they can be swapped without changing how the stickers look (need to find a sequence of moves that shows this).

We call the group of permutations (up to rotation) of the Pocket Cube $G_N$. We also denote the minimal number of moves to solve a Rubik's cube as $GOD_N$. In this paper, the quarter-turn metric will be used.

Lemma $1$: The minimal number of moves to travel between any $2$ states of a Rubik's cube is $GOD_N$.

Proof of Lemma $1$: Clear. $\blacksquare$

Lemma $2$: An upper bound of the Devil's algorithm is $2(\frac{ord(G_N)}{meo(G_N)}-1)+GOD_N$.

Proof of lemma $2$:

Suppose $x \in G_N$ and $ord(x)=meo(G_N)$. Put $a$ and $b$ in the same congruency class if $x \star a=b$, note that order matters as the operator is not commutative. Then, the are $\frac{ord(G_N)}{meo(G_N)}$ congruency classes, each with $meo(G_N)$ elements. Suppose that a single pass of our algorithm transforms $1_e$ to $x$. Then, if we visited element $a$ in the first pass of the Devil's algorithm, we would visit $x \star a$ in the second pass and $x^2 \star a$ in the third pass and so on. Therefore, we only need to visit each congruency class at least once in the first pass of the Devil's algorithm then transform the cube to $x$. 

Define a graph $G(V,E)$ with $V$ being the set of congruency classes and edge $(A,B)$ existing in $G$ if for congruency class $A$ and $B$, there exists elements $a \in A$ and $b \in B$ such that $dist(a,b)=1$. Then, $G$ is connected. We will prove this by showing that for any $2$ congruency classes $A$ and $B$, a path between them exists in $G$. Arbitrarily choose $a \in A$ and $b \in B$. Consider a sequence $p_1, p_2, \ldots, p_k$ such that $p_1=a$, $p_k=b$ and $dist(p_i,p_{i+1})=1$. Such a sequence obviously exists. Therefore, $b$ is reachable from $A$ on $G$. 

As such, we are able to find a spanning tree of weight $\frac{ord(G_N)}{meo(G_N)}-1$ over the congruency classes. A valid Devil's algorithm is to traverse the Euler tour of this spanning tree in $2(\frac{ord(G_N)}{meo(G_N)}-1)$ moves then move to element $x$ in at most $GOD_N$ moves using lemma $1$. $\blacksquare$

Lemma $3$: The lower bound of the Devil's algorithm on when one of the corner's is fixed is $\frac{ord(G_N)}{meo(G_N)}$.



## Optimizing Devil's Algorithm for 2x2x2

By direct search, we find that $ord(G_2)=3674160$​, $meo(G_2)=36$​ and $GOD_2=14$​. Therefore, an upper bound of the Devil's algorithm on a 2x2x2 Rubik's cube is $204132$​. A stronger bound on the case of the 2x2x2 Rubik's cube is $204123$​ as we can find that there exists a element of order $36$​ using the moves $\texttt{U'LULF'}$​​.

An obvious way to cut the number of moves used is by finding disjoint chains in the graph.

Use some heuristic for Hamiltonian path to get size $102061$​.

When finding such a sequence of moves through dfs on $G$, it should be noted that the source node has to be the congruency class of $1_e$. As if you start at arbitrary state $s$, $s \star a$ and $s \star x \star a$ is not in the same congruency class.

We will prove that the lower bound on the size of the Devil's Algorithm for the 2x2x2 is $102061$.

By lemma $3$, the lower bound is at least $102060$. It suffices to show that the lower bound is not $102060$. We will use parity argument.
