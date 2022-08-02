## Features

- Finde Class from name
- Get StaticFields from Class
- Get Method by name

## Usage/Examples

```c++
// by default findclass function use "Assembly-CSharp" 
auto NetworkManager = il2cpp::FindClass("NetworkManager"/*your class name*/);
//if your class in  other module you need do like this
auto Camera = il2cpp::FindClass("Camera","UnityEngine.CoreModule");

auto get_main = Camera->FindMethod("get_main",0/*how many arguments in your method*/); //get address function "get_main" from camera class

auto NetworkManagerStaticFields = NetworkManager->StaticFields() // get class static fields

```


## Screenshots

![image](https://user-images.githubusercontent.com/47825265/182267870-fd76772d-68d5-4ec5-9f63-57b7fda7b2be.png)


