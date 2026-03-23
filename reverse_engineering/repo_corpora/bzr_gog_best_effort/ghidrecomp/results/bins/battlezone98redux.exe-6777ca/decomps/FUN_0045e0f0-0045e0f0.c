
/* WARNING: Removing unreachable block (ram,0x0045e115) */

basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_0045e0f0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_14 [8];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_c;
  undefined1 local_7;
  undefined1 local_6 [2];
  
  local_c = param_1;
  if (param_1 != param_2) {
    FID_conflict__Tidy(1,0);
    uVar2 = Getal(local_6);
    uVar3 = Getal(&local_7);
    cVar1 = operator!=<>(uVar3,uVar2);
    if (cVar1 == '\0') {
      uVar2 = FUN_00417780(param_2);
      FID_conflict__Assign_rv(uVar2);
    }
    else {
      puVar4 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               end(param_2);
      uVar2 = *puVar4;
      puVar4 = (undefined4 *)FID_conflict_begin(local_14);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
                (local_c,*puVar4,uVar2);
    }
  }
  return local_c;
}

