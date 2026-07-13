
/* Library Function - Single Match
    public: virtual class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> > __thiscall std::_Iostream_error_category::message(int)const 
   
   Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017 */

int __thiscall std::_Iostream_error_category::message(_Iostream_error_category *this,int param_1)

{
  int in_stack_00000008;
  
  if (in_stack_00000008 == 1) {
    basic_string<>("iostream stream error");
  }
  else {
    FUN_00416590(param_1,in_stack_00000008);
  }
  return param_1;
}

