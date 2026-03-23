
undefined4 FUN_006dcd90(undefined4 param_1,undefined4 param_2)

{
  undefined4 extraout_ECX;
  undefined4 uVar1;
  undefined4 *puStack_1c;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c [2];
  
  puStack_1c = (undefined4 *)0x6dcda2;
  local_10 = FUN_006d4b50();
  puStack_1c = (undefined4 *)0x6dcdad;
  local_c[0] = FUN_006d4b30();
  uVar1 = extraout_ECX;
  FUN_006d1160(&stack0x0000000c);
  FUN_006ee3f0(&puStack_1c,uVar1);
  local_14 = FUN_006ee420(local_c,param_2);
  puStack_1c = &local_10;
  FUN_006d4b70(&local_14);
  return param_1;
}

