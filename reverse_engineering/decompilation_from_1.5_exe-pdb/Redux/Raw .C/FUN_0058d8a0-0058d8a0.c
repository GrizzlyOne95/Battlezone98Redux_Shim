
/* WARNING: Removing unreachable block (ram,0x0058d8e9) */
/* WARNING: Removing unreachable block (ram,0x0058d90f) */
/* WARNING: Removing unreachable block (ram,0x0058d8ef) */

int FUN_0058d8a0(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int local_8;
  
  local_8 = param_4;
  FUN_0041fe40(&local_8);
  *(undefined4 *)(local_8 + 0x24) = param_1;
  *(undefined4 *)(local_8 + 0x28) = param_2;
  if (param_3 != 0) {
    *(undefined1 *)(local_8 + 0x1f) = *(undefined1 *)(param_3 + 0x1f);
  }
  return local_8;
}

