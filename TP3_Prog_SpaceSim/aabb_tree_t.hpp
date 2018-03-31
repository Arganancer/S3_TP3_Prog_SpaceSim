#ifndef AABB_TREE_T_HPP
#define AABB_TREE_T_HPP

/* REFERENCES:
 * https://www.azurefromthetrenches.com/introductory-guide-to-aabb-tree-collision-detection/
 * http://allenchou.net/2014/02/game-physics-broadphase-dynamic-aabb-tree/
 * 
 * STEPS TO ADDING A NEW GAME OBJECT TO THE TREE:
 * 1) Create a leaf node for the object and assign it an AABB based on it’s associated object.
 * 2) Find the best existing node (leaf or branch) in the tree to make the new leaf a sibling of.
 * 3) Create a new branch node for the located node and the new leaf and assign it an AABB that contains both nodes (essentially combine the AABBs of the two located node and the new leaf).
 * 4) Attach the new leaf to the new branch node.
 * 5) Remove the existing node from the tree and attach it to the new branch node.
 * 6) Attach the new branch node as a child of the existing nodes previous parent node.
 * 7) Walk back up the tree adjusting the AABB of all of our ancestors to ensure they still contain the AABBs of all of their descendants.
 * 
 * STEPS TO QUERYING THE TREE:
 * 1) Check to see if the current node intersects with the test objects AABB.
 * 2) If it does and if its a leaf node then this is a collision and so add it to the list of collisions.
 * 3) If it does and it’s a branch node then descend to the left and right and recursively repeat this process.
 */
class aabb_tree_t
{
public:

};

#endif