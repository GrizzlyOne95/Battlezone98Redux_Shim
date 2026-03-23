
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::iterator __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::iterator::operator+(int)const 
   
   Library: Visual Studio 2003 Debug */

int __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
operator+(iterator *this,int param_1)

{
  iterator *piVar1;
  int in_stack_00000008;
  undefined4 local_c;
  iterator *local_8;
  
  local_c = *(undefined4 *)this;
  local_8 = this;
  piVar1 = operator+=((iterator *)&local_c,in_stack_00000008);
  *(undefined4 *)param_1 = *(undefined4 *)piVar1;
  return param_1;
}

