
/* Library Function - Single Match
    public: int __thiscall std::_String_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >::operator-(class std::_String_const_iterator<class
   std::_String_val<struct std::_Simple_types<char> > > const &)const 
   
   Library: Visual Studio 2012 Release */

int __thiscall
std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::operator-
          (_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *this,
          _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *param_1
          )

{
  int iVar1;
  undefined4 local_c;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *local_8;
  
  local_c = *(undefined4 *)this;
  local_8 = this;
  iVar1 = _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator-((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                     *)&local_c,param_1);
  return iVar1;
}

