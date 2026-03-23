
/* Library Function - Single Match
    public: class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
   & __thiscall std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >::replace(class std::_String_const_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >,class std::_String_const_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >,class std::_String_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >,class std::_String_iterator<class std::_String_val<struct
   std::_Simple_types<char> > >)
   
   Library: Visual Studio 2012 Release */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::replace
          (undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  uint uVar6;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  undefined4 local_c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_8;
  
  cVar1 = FID_conflict_operator__(&stack0x00000010);
  if (cVar1 == '\0') {
    puVar2 = (undefined4 *)FID_conflict_begin(local_18);
    local_10 = *puVar2;
    uVar3 = _String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::operator-
                      ((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                        *)&stack0x00000010,
                       (_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                        *)&stack0x0000000c);
    pcVar5 = (char *)FUN_00421ec0();
    uVar4 = _Pdif(param_3,param_2);
    uVar6 = _Pdif(param_2,local_10);
    replace(local_8,uVar6,uVar4,pcVar5,uVar3);
  }
  else {
    puVar2 = (undefined4 *)FID_conflict_begin(local_14);
    local_c = *puVar2;
    uVar3 = _Pdif(param_3,param_2);
    uVar4 = _Pdif(param_2,local_c);
    erase(local_8,uVar4,uVar3);
  }
  return local_8;
}

