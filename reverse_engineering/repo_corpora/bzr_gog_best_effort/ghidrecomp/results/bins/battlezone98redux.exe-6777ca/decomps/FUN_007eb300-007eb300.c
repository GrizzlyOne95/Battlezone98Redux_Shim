
undefined4 FUN_007eb300(undefined4 param_1,undefined4 param_2,undefined4 param_3,byte *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined1 local_b [3];
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar1 = FUN_007e3040(param_2);
  local_10 = max_size(uVar1);
  local_5 = 0;
  uVar2 = (uint)*param_4;
  uVar1 = 0;
  FUN_007dd8d0(local_10);
  FUN_007ebd30(&local_6,uVar1,uVar2);
  puVar3 = &local_6;
  uVar1 = FUN_007e31c0(param_2,param_3,puVar3);
  uVar1 = FUN_007e78f0(&local_8,uVar1,param_3,puVar3);
  uVar1 = FUN_007e7390(local_b,uVar1);
  FUN_007ebd70(local_1c,local_10,uVar1);
  local_7 = 0;
  FUN_007ebd90(param_1,local_1c,param_4);
  return param_1;
}

