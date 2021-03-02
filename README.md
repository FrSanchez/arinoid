# Arinoid

## Compiling

For iOS device
```bash
cd cocos2d-
mkdir ios-build && cd ios-build
cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
open Cocos2d-x.xcodeproj
```

For iOS simulator
```bash
cd cocos2d-
mkdir ios-sim && cd ios-sim
cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator
open Cocos2d-x.xcodeproj
```
## TODO:
* [ ] Add all power-ups
* [ ] Define the random ranges for each power-up
* [ ] Define animation for power-ups
* [ ] Cleanup splash screen
* [ ] Create a level chooser screen
* [ ] Create more levels
