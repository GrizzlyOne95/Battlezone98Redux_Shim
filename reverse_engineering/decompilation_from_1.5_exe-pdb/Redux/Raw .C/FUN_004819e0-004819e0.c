
void FUN_004819e0(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *local_c;
  
  if (param_1 == (undefined4 *)0x0) {
    local_c = &DAT_0091739c;
  }
  else {
    local_c = param_1;
  }
  iVar1 = FUN_004817a0(local_c,param_2);
  if (((iVar1 != 0) && (*(short *)(iVar1 + 0x14) != 0)) &&
     (*(short *)(iVar1 + 0x14) = *(short *)(iVar1 + 0x14) + -1, *(short *)(iVar1 + 0x14) == 0)) {
    FUN_004814e0(local_c,iVar1);
  }
  return;
}

