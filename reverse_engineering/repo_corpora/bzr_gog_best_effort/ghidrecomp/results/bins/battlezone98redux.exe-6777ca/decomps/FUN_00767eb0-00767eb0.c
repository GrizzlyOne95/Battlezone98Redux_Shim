
void FUN_00767eb0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  uVar1 = make_move_iterator<>(local_10,isspace_exref);
  puVar2 = (undefined4 *)FUN_00770900(local_14,uVar1);
  uVar1 = *puVar2;
  puVar2 = (undefined4 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                     (param_1);
  uVar3 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_1c);
  puVar2 = (undefined4 *)FUN_00770920(local_20,*puVar2,uVar3,uVar1);
  local_8 = *puVar2;
  puVar2 = (undefined4 *)FID_conflict_begin(local_24);
  local_c = *puVar2;
  FUN_0071b880(local_28,local_c,local_8);
  return;
}

