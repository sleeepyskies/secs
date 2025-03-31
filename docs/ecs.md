## Overview

This document is mainly for my own use, so I do not have to spam comments inside my code to remember stuff.
It covers my reasoning behind writing code the way I have.

## Data Classes
### Entity

This struct represents an Entity in the sle ecs. An entity is at its core just an id, but in sle it is a little more.
An entity here holds an ID as well as a bitmask used as 32 bools, indicating whether the Entity has a component type or
not. Furthermore, an ID of 0 is used to indicate an invalid Entity. This allows us to easily check if an Entity is still
alive by using either the boolean overload, or calling e.alive().

### IComponentList and ComponentList

So the class IComponentList exists to allow polymorphism for the lists in ComponentManager. It lets us store shared
pointers to objects of IComponentList, which will then be ComponentList<T>. This lets us store different underlying T's,
since just having the one ComponentList<T> definition would allow for only one underlying type, or we would have to
specify T, U, V, W.... for each type.

ComponentList maintains a vector of the Component it holds. Functions are provided to insert, remove Components, as well
as other utility functions.

## Logic Classes
### EntityManager

This class is used for managing entity ID creation, as well as managing the entity bit masks. A queue is used to reuse
any IDs of deleted Entities.

### ComponentManager

## TODO
- make MAX_ENTITIES specifiable? maybe with an secs::init or something.
- fix imports, sometimes have to use dir prefix, sometimes not, i dont know why.
