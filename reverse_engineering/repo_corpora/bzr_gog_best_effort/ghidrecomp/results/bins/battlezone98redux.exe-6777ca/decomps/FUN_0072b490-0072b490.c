
void FUN_0072b490(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  undefined1 local_10 [4];
  undefined4 local_c;
  
  puVar1 = (undefined4 *)FID_conflict_begin(local_10);
  local_c = *puVar1;
  uVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
                    (param_2,param_1,param_3);
  uVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
                    (param_1,local_c,uVar2);
  FUN_006c88e0(uVar3,uVar2,param_3);
  return;
}

