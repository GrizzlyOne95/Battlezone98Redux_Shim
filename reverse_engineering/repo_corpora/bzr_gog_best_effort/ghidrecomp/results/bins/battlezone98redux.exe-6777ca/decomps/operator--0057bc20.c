
/* Library Function - Single Match
    public: class std::_String_iterator<class std::_String_val<struct std::_Simple_types<wchar_t> >
   > __thiscall std::_String_iterator<class std::_String_val<struct std::_Simple_types<wchar_t> >
   >::operator-(int)const 
   
   Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release */

int __thiscall
std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::operator-
          (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *this,
          int param_1)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000008;
  
  puVar1 = (undefined4 *)FID_conflict_operator__(in_stack_00000008);
  *(undefined4 *)param_1 = *puVar1;
  return param_1;
}

