# macro_generator
While trying to find the way to generate repeated code for macroses in Visual Studio for C++ i made this small function which generate all combinations without permutations from any number of sets of names to make unique not repetitive macroses. [Discussion where i started here.](https://stackoverflow.com/questions/67560932/how-to-generate-repeated-code-in-visual-studio-for-c-using-macros-like-define)

## Usage in Visual Studio 19 Windows 10.

1. Build .exe from source.
2. Add Enviroment Varible to .exe file in Windows settings, for ex MACRO_GENERATOR.
3. In `Visual Studio -> project Properties->Build Events-> Pre-Build Event` add `call %MACRO_GENERATOR% $(ProjectDir)` and then all files in Project directory will be executed.
4. Add word `#GENERATE` at first string and use `//#define[]` and `//#for` like this:
```
#GENERATE
#define ADD_FUNC(NAME,PROPERTY) void f_##NAME##_##PROPERTY(){};
#define ADD_FUNC2(NAME,PROPERTY,WEIGHT) void f_##NAME##_##PROPERTY##_##WEIGHT();
#define ADD_FUNC3(NAME,PROPERTY,WEIGHT,KLMN) void f_##NAME##_##PROPERTY##_##WEIGHT##_##KLMN();

//#define[] NAME one,two
//#define[] COLOR red,green,blue
//#define[] WEIGHT low,big,very_nice
//#define[] KLMN K,L,M,N

//#for ADD_FUNC(NAME, COLOR)
//#for ADD_FUNC2(NAME,COLOR,WEIGHT)
//#for ADD_FUNC3(NAME,COLOR,WEIGHT,KLMN)

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
```
5. After pre-build files in the project dir will be replaced with new with generated macroses.
```
#define ADD_FUNC(NAME,PROPERTY) void f_##NAME##_##PROPERTY(){};
#define ADD_FUNC2(NAME,PROPERTY,WEIGHT) void f_##NAME##_##PROPERTY##_##WEIGHT();
#define ADD_FUNC3(NAME,PROPERTY,WEIGHT,KLMN) void f_##NAME##_##PROPERTY##_##WEIGHT##_##KLMN();

//NAME one,two
//COLOR red,green,blue
//WEIGHT low,big,very_nice
//KLMN K,L,M,N

// ADD_FUNC(NAME, COLOR) START GENERATION
 ADD_FUNC(one,red)
 ADD_FUNC(one,green)
 ADD_FUNC(one,blue)
 ADD_FUNC(two,red)
 ADD_FUNC(two,green)
 ADD_FUNC(two,blue)
// ADD_FUNC(NAME, COLOR) END GENERATION

// ADD_FUNC2(NAME,COLOR,WEIGHT) START GENERATION
 ADD_FUNC2(one,red,low)
 ADD_FUNC2(one,red,big)
 ADD_FUNC2(one,red,very_nice)
 ADD_FUNC2(one,green,low)
 ADD_FUNC2(one,green,big)
 ADD_FUNC2(one,green,very_nice)
 ADD_FUNC2(one,blue,low)
 ADD_FUNC2(one,blue,big)
 ADD_FUNC2(one,blue,very_nice)
 ADD_FUNC2(two,red,low)
 ADD_FUNC2(two,red,big)
 ADD_FUNC2(two,red,very_nice)
 ADD_FUNC2(two,green,low)
 ADD_FUNC2(two,green,big)
 ADD_FUNC2(two,green,very_nice)
 ADD_FUNC2(two,blue,low)
 ADD_FUNC2(two,blue,big)
 ADD_FUNC2(two,blue,very_nice)
// ADD_FUNC2(NAME,COLOR,WEIGHT) END GENERATION

// ADD_FUNC3(NAME,COLOR,WEIGHT,KLMN) START GENERATION
 ADD_FUNC3(one,red,low,K)
 ADD_FUNC3(one,red,low,L)
 ADD_FUNC3(one,red,low,M)
 ADD_FUNC3(one,red,low,N)
 ADD_FUNC3(one,red,big,K)
 ADD_FUNC3(one,red,big,L)
 ADD_FUNC3(one,red,big,M)
 ADD_FUNC3(one,red,big,N)
 ADD_FUNC3(one,red,very_nice,K)
 ADD_FUNC3(one,red,very_nice,L)
 ADD_FUNC3(one,red,very_nice,M)
 ADD_FUNC3(one,red,very_nice,N)
 ADD_FUNC3(one,green,low,K)
 ADD_FUNC3(one,green,low,L)
 ADD_FUNC3(one,green,low,M)
 ADD_FUNC3(one,green,low,N)
 ADD_FUNC3(one,green,big,K)
 ADD_FUNC3(one,green,big,L)
 ADD_FUNC3(one,green,big,M)
 ADD_FUNC3(one,green,big,N)
 ADD_FUNC3(one,green,very_nice,K)
 ADD_FUNC3(one,green,very_nice,L)
 ADD_FUNC3(one,green,very_nice,M)
 ADD_FUNC3(one,green,very_nice,N)
 ADD_FUNC3(one,blue,low,K)
 ADD_FUNC3(one,blue,low,L)
 ADD_FUNC3(one,blue,low,M)
 ADD_FUNC3(one,blue,low,N)
 ADD_FUNC3(one,blue,big,K)
 ADD_FUNC3(one,blue,big,L)
 ADD_FUNC3(one,blue,big,M)
 ADD_FUNC3(one,blue,big,N)
 ADD_FUNC3(one,blue,very_nice,K)
 ADD_FUNC3(one,blue,very_nice,L)
 ADD_FUNC3(one,blue,very_nice,M)
 ADD_FUNC3(one,blue,very_nice,N)
 ADD_FUNC3(two,red,low,K)
 ADD_FUNC3(two,red,low,L)
 ADD_FUNC3(two,red,low,M)
 ADD_FUNC3(two,red,low,N)
 ADD_FUNC3(two,red,big,K)
 ADD_FUNC3(two,red,big,L)
 ADD_FUNC3(two,red,big,M)
 ADD_FUNC3(two,red,big,N)
 ADD_FUNC3(two,red,very_nice,K)
 ADD_FUNC3(two,red,very_nice,L)
 ADD_FUNC3(two,red,very_nice,M)
 ADD_FUNC3(two,red,very_nice,N)
 ADD_FUNC3(two,green,low,K)
 ADD_FUNC3(two,green,low,L)
 ADD_FUNC3(two,green,low,M)
 ADD_FUNC3(two,green,low,N)
 ADD_FUNC3(two,green,big,K)
 ADD_FUNC3(two,green,big,L)
 ADD_FUNC3(two,green,big,M)
 ADD_FUNC3(two,green,big,N)
 ADD_FUNC3(two,green,very_nice,K)
 ADD_FUNC3(two,green,very_nice,L)
 ADD_FUNC3(two,green,very_nice,M)
 ADD_FUNC3(two,green,very_nice,N)
 ADD_FUNC3(two,blue,low,K)
 ADD_FUNC3(two,blue,low,L)
 ADD_FUNC3(two,blue,low,M)
 ADD_FUNC3(two,blue,low,N)
 ADD_FUNC3(two,blue,big,K)
 ADD_FUNC3(two,blue,big,L)
 ADD_FUNC3(two,blue,big,M)
 ADD_FUNC3(two,blue,big,N)
 ADD_FUNC3(two,blue,very_nice,K)
 ADD_FUNC3(two,blue,very_nice,L)
 ADD_FUNC3(two,blue,very_nice,M)
 ADD_FUNC3(two,blue,very_nice,N)
// ADD_FUNC3(NAME,COLOR,WEIGHT,KLMN) END GENERATION

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}
```
6. Be carefull to use it in important part of code! :) Only few checks added. The text of generation commands must be really closer to example.
