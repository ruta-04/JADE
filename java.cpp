#include "java.h"
#include <iostream>

Java::Java(std::string name, double price, double cost,Darkness darkness):_darkness{darkness},Product{name,price,cost}  {}


void Java::add_shot(Shot shot)
{
	_shots.push_back(shot);
}


std::string Java::to_string() 
{
//  std:: string full_line=" ";
//  std::string shot=" ";
//  for(auto e:_shots)
//    {
//      if(e==0)
//    {
//
//    }
//      else if(e==1)
//    {
//      shot="Chocolate";
//    }
//      else if(e==2)
//    {
//      shot="Vanilla";
//    }
//      else if(e==3)
//    {
//      shot="Peppermint";
//    }
//      else if(e==4)
//    {
//      shot="Hazlenut";
//    }
//      else
//    {
//
//    }
//      shot=shot+" ";
//    }
//
//    std::string dark="Blond";
//
//    if(_darkness==0)
//    {
//        dark="Blond";
//    }
//    else if(_darkness==1)
//    {
//        dark="Light";
//    }
//    else if(_darkness==2)
//    {
//        dark=="Medium";
//    }
//    else if(_darkness==3)
//    {
//        dark="Dark";
//    }
//    else
//    {
//        dark="Extra Dark";
//    }
//    full_line=Product::to_string()+"( "+dark+" )"+"{ with "+shot+" }"+"\n";
    
    std::vector<std::string> darkness_to_string =
    {"Blonde", "Light", "Medium", "Dark", "Extra Dark"};
    
    std::vector<std::string> shot_to_string =
    {" ", "Chocolate", "Vanillaa", "Peppermint", "Hazlenut"};
    std::string result =  Product::to_string() + " (" + darkness_to_string[_darkness]+")";
    if(_darkness==1 || _darkness==2 || _darkness==3 || _darkness==4)
    {
        result+=" with ";
    }
    std::string separator = " ";
    for (auto s : _shots) {result += separator + shot_to_string[s]; separator = ", ";}
  return result+"\n";
}
