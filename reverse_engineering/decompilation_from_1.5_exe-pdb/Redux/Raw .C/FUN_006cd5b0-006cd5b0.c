
undefined4 FUN_006cd5b0(undefined4 param_1,undefined4 param_2,char param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined4 local_10;
  uint local_c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_8;
  
  puVar1 = (undefined4 *)FID_conflict_begin(local_14);
  local_10 = *puVar1;
  local_c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
                      (param_2,local_10);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::insert
            (local_8,local_c,1,param_3);
  uVar2 = param_1;
  uVar3 = local_c;
  FID_conflict_begin(local_18);
  FID_conflict_operator_(uVar2,uVar3);
  return param_1;
}

