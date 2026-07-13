
void FUN_00842d80(int param_1,undefined4 param_2,int *param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_5c [8];
  undefined1 auStack_54 [68];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  int *local_4;
  
  local_4 = (int *)0xffffffff;
  puStack_8 = &LAB_00865bf8;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)local_5c;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xffffff98;
  ExceptionList = &local_c;
  if (param_1 == 0) {
    if (param_3 == (int *)0x0) goto LAB_00842e13;
    *param_3 = 0;
    iVar2 = FUN_0083e820(uVar1);
  }
  else {
    if (param_3 == (int *)0x0) {
      basic_string<>(param_4);
      local_4 = param_3;
      uVar3 = FUN_0083e820(uVar1);
      FUN_00841dd0(local_5c,param_2,param_1,uVar3);
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(auStack_54,(ThrowInfo *)&DAT_008d8618);
    }
    iVar2 = FUN_0083e820(uVar1);
    *param_3 = param_1;
  }
  param_3[1] = iVar2;
LAB_00842e13:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

