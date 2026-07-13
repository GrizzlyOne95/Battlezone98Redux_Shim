
void FUN_006d3080(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_var;
  undefined4 local_28;
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006cb4c0(param_2 + 9);
  local_28 = FUN_006d5810(extraout_var);
  uVar1 = FUN_006d0d10(&local_28,*(undefined1 *)(param_2 + 8),param_3);
  iVar2 = FUN_006af6f0(*param_2,uVar1);
  if (iVar2 == 0) {
    FUN_006d57f0(local_28);
    FUN_006cb4c0(local_24);
  }
  else {
    FUN_006cb470();
  }
  FUN_0083e885();
  return;
}

