
/* WARNING: Removing unreachable block (ram,0x0067731f) */

void __thiscall FUN_00677270(_Container_base0 *param_1,_Container_base0 *param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_32;
  undefined1 local_31;
  _Container_base0 *local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  local_14 = uVar2;
  if (param_1 != param_2) {
    uVar3 = Getal(&local_32);
    uVar4 = Getal(&local_31);
    cVar1 = operator==<>(uVar4,uVar3,uVar2);
    if (cVar1 == '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
      basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           *)local_30);
      local_8 = 0;
      FID_conflict_operator_(param_2);
      FID_conflict_operator_(local_2c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      std::_Container_base0::_Swap_all(local_30,param_2);
      FUN_006773d0(param_2);
      swap<>(local_30 + 0x10,param_2 + 0x10);
      swap<>(local_30 + 0x14,param_2 + 0x14);
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

