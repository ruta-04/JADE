#include "donut.h"

Donut::Donut(std::string name, double price, double cost, Frosting frosting, bool sprinkles, Filling filling):Product{name, price, cost},_frosting{frosting},_filling{filling},_sprinkles{sprinkles} {}

std::string Donut::to_string()
{
  std::string full_line=" ";
  std::string fill=" ";
  std::string frost=" ";
  if(_filling==0)
    {
      fill="none";
    }
  else if(_filling==1)
    {
      fill="Creme";
    }
  else if(_filling==2)
    {
      fill="Bavarian";
    }
  else if(_filling==3)
    {
      fill="Strawberry";
    }
  else
    {
      fill="none";
    }

  if(_frosting==0)
    {
      frost="none";
    }
  else if(_frosting==1)
    {
      frost="Chocolate_pop";
    }
  else if(_frosting==2)
    {
      frost="Vanilla_pop";
    }
  else if(_frosting==3)
    {
      frost="Pink_top";
    }
  else
    {
      frost="none";
    }
    
    
//    if(_frosting!=0 && _frosting<5)
//    {
//        if(_sprinkles==true && _filling!=0)
//        {
//            full_line=Product::to_string()+"  "+"{Frosted with "+frost+" and sprinkles"+" ,filled with "+fill+" }"+"   \n";
//        }
//        else if(_sprinkles==true && _filling==0)
//        {
//            full_line=Product::to_string()+"  "+"{Frosted with "+frost+" and sprinkles"+" } \n";
//        }
//        else {
//            full_line=Product::to_string()+"  "+"{Frosted with "+frost+"  } \n";
//        }
//    }
//    else{
//        full_line=Product::to_string()+"  "+"{filled with "+fill+" }"+"   \n";
//    }
//
    //std::string full_line;
    std::string result=Product::to_string();
    full_line+=result;
    if(frost!="none")
    {
        full_line+=" (Frosted with "+frost;
        if(_sprinkles) full_line+=" and sprinkles";
        full_line+=" )";
    }
    if(frost!="none")
    {
        full_line+=" (filled with "+fill+ " )";
    }
    full_line+="\n";
  return full_line;
}
