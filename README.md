# BSTree — Binary Search Tree with Duplicate Counting

A C++ binary search tree that stores string keys, tracking a count for
duplicate insertions instead of storing repeated nodes — with full
insert/remove/search, min/max, subtree height, and tree traversals.

## Project Description

This project implements a binary search tree (BST) of strings, where
inserting a key that already exists simply increments a counter on the
existing node rather than creating a duplicate node. It supports the full
set of standard BST operations, including a non-trivial remove that
correctly re-balances the tree structure using in-order predecessor/
successor replacement, and includes both a menu-driven console program and
an automated test harness.

## Features

- **Duplicate-aware insertion** — inserting an existing key increments
  that node's count instead of creating a duplicate node
- **Search** — recursive BST search by key
- **Min / max** — `smallest()` / `largest()` walk to the leftmost/
  rightmost node
- **Subtree height** — `height(key)` computes the height of the subtree
  rooted at a given key
- **Full removal logic**
  - Decrements the count if a key has duplicates
  - Removes leaf nodes directly
  - For nodes with one or two children, replaces the key with an in-order
    predecessor (left subtree's rightmost node) or successor (right
    subtree's leftmost node) and recursively removes that replacement node
- **Tree traversals** — `preOrder()`, `inOrder()`, and `postOrder()` print
  each key with its duplicate count, e.g. `Charlie(2)`
- **Menu-driven console interface** — insert, remove, print (all three
  traversals), search, smallest, largest, height, and quit
- **Automated test suite** — an included test harness (`test14.cpp`)
  redirects stdout/stderr to verify tree behavior and traversal output
  against expected results, plus 13 additional input-based test cases

## Technologies Used

- **Language:** C++14
- **Data structure:** custom binary search tree (`Node`-based, recursive
  operations)

## Files

| File | Description |
|------|-------------|
| `BSTree.h` / `BSTree.cpp` | `BSTree` class: insert, remove, search, traversals, height |
| `Node.h` / `Node.cpp` | Tree node: key, duplicate count, left/right children |
| `main.cpp` | Menu-driven console driver (provided starter code) |
| `test14.cpp` | Automated test harness verifying core behavior and traversal output |
| `test1.in` – `test13.in` | Sample input files for manual/automated testing |
| `README` | Original build/test instructions for this assignment |

## How It Works

1. `insert()` walks down the tree comparing keys; if the key is found, its
   count is incremented, otherwise a new `Node` is attached as a leaf.
2. `remove()` recursively locates the target key. If it has duplicates, the
   count is decremented; otherwise the node is removed and, if it has
   children, replaced by its in-order predecessor or successor to preserve
   BST ordering.
3. `height(key)` locates the node for the given key, then recursively
   computes `1 + max(leftHeight, rightHeight)` for that subtree.
4. The three traversal functions recurse over the tree in pre-, in-, and
   post-order, printing each node's key and count.

## Build & Run

```bash
g++ -std=c++14 -o bst main.cpp BSTree.cpp Node.cpp
./bst < test1.in
```

Or run the automated test harness:

```bash
g++ -std=c++14 -o test14 test14.cpp BSTree.cpp Node.cpp
./test14
```

To validate against expected output for a given test case:

```bash
./bst < test1.in > output.1
diff output.1 expected.1
```
