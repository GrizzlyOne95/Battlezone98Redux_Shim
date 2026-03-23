
undefined4 __thiscall
FUN_0070dbd0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> local_c [4];
  undefined4 local_8;
  
  local_14 = param_3;
  local_8 = param_1;
  do {
    cVar1 = FID_conflict_operator__(&param_4);
    if (cVar1 == '\0') {
      FUN_006ff2c0(param_4,param_4);
      return param_2;
    }
    cVar1 = FUN_00718620(local_8);
    if (cVar1 != '\0') {
      FUN_006ff2c0(param_4,param_4);
      return param_2;
    }
    local_10 = local_14;
    base(local_c);
    while (cVar1 = FID_conflict_operator__(&param_4), cVar1 != '\0') {
      uVar2 = FUN_00710360(local_18);
      cVar1 = FID_conflict_operator__(uVar2);
      if (cVar1 == '\0') break;
      uVar2 = get();
      uVar3 = FUN_00421ec0(uVar2);
      cVar1 = FUN_00708c90(uVar3,uVar2);
      if (cVar1 == '\0') break;
      FUN_004f5330();
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++(local_c);
    }
    uVar2 = FUN_00710360(local_1c);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 != '\0') {
      FUN_006ff2c0(local_14,local_10);
      return param_2;
    }
    FUN_004f5330();
  } while( true );
}

