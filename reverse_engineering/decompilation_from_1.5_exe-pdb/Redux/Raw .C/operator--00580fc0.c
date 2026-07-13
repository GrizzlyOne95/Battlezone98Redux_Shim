
/* Library Function - Single Match
    public: int __thiscall std::_String_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >::operator-(class std::_String_const_iterator<class
   std::_String_val<struct std::_Simple_types<char> > > const &)const 
   
   Library: Visual Studio 2015 Release */

int __thiscall
std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::operator-
          (_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *this,
          _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *param_1
          )

{
  int iVar1;
  
  iVar1 = _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator-((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                     *)this,param_1);
  return iVar1;
}

