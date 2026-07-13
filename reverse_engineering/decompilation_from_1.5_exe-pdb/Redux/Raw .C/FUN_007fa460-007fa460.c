
undefined4 FUN_007fa460(undefined4 param_1,undefined4 param_2,undefined4 param_3,byte *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 in_stack_ffffffd4;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_20 [16];
  undefined4 local_10;
  undefined1 local_b [3];
  undefined1 local_8;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar1 = FUN_007e7720(param_2);
  uVar3 = 0x7fa47b;
  local_10 = max_size(uVar1);
  local_5 = 0;
  uVar2 = (uint)*param_4;
  FUN_007dd520(local_10);
  FUN_007fa6c0(&local_6,in_stack_ffffffd4,uVar3,uVar2);
  puVar4 = &local_6;
  uVar1 = FUN_007fa700(param_2,param_3,puVar4);
  uVar1 = FUN_007fa720(&local_8,uVar1,param_3,puVar4);
  uVar1 = FUN_007e7390(local_b,uVar1);
  FUN_007fa750(local_20,local_10,uVar1);
  local_7 = 0;
  FUN_007fa770(param_1,local_20,param_4);
  return param_1;
}

