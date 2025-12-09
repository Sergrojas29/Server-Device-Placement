# Server-Device-Placement
Backend C++ for TS UI

File Structure:

```
<project_root>/
│
├─ CMakeLists.txt            
├─ /src                      
│   ├─ main.cpp
│       └── routes/
│
├─ /libs                      
│   └─/kdtree
│       └─/src
│       │    └─ sorted_kdtree.cpp
│       ├─/include
│       │    ├─ sorted_kdtree.hpp
│       │    ├─ pointInfo.hpp
│       │    ├─ node.hpp
│       │    ├─ distance.hpp
│       │    └─ nearestResult.hpp            
│       └─ CMakeLists.txt


```




1. Delete the old configuration

rmdir /s /q build

Generate:

cmake -S . -B build


Build:

cmake --build build

shadow milk cookie
