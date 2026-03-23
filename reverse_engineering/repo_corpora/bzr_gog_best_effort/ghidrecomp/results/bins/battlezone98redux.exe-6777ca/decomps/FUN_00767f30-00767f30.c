
void FUN_00767f30(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined4 local_8;
  
  puVar1 = (undefined4 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                     (param_1);
  local_8 = *puVar1;
  puVar4 = local_14;
  uVar2 = make_move_iterator<>(local_18,isspace_exref,puVar4);
  puVar1 = (undefined4 *)FUN_00770900(local_1c,uVar2);
  uVar2 = *puVar1;
  puVar1 = (undefined4 *)FUN_0076eec0(local_20);
  uVar3 = *puVar1;
  puVar1 = (undefined4 *)FUN_0076ee90(local_24);
  FUN_00770960(local_28,*puVar1,uVar3,uVar2);
  puVar1 = (undefined4 *)base(puVar4);
  local_c = *puVar1;
  FUN_0071b880(local_2c,local_c,local_8);
  return;
}

