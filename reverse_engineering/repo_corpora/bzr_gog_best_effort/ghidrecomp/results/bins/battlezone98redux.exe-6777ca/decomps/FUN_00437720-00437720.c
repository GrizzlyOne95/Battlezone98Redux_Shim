
void FUN_00437720(int param_1,int param_2,undefined1 *param_3)

{
  int *piVar1;
  undefined1 local_34 [44];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (((param_2 != 0) ||
      ((piVar1 = (int *)FUN_0062c840(), piVar1 != (int *)0x0 && (param_2 = *piVar1, param_2 != 0))))
     && (param_1 != 0)) {
    if (param_3 == (undefined1 *)0x0) {
      param_3 = local_34;
      FUN_0043a990(param_3);
    }
    *(uint *)(param_3 + 0x10) = *(uint *)(param_3 + 0x10) | 0x400;
    FUN_0043aa30(param_1,param_2,param_3,0);
  }
  FUN_0083e885();
  return;
}

