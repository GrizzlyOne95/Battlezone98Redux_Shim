
undefined4 FUN_00816d40(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_c [8];
  
  uVar1 = FUN_00417780(param_3);
  puVar2 = (undefined4 *)make_move_iterator<>(local_c,uVar1);
  uVar1 = *puVar2;
  uVar4 = 1;
  uVar3 = max_size(param_2,1,uVar1);
  FUN_00816f40(param_1,uVar3,uVar4,uVar1);
  return param_1;
}

