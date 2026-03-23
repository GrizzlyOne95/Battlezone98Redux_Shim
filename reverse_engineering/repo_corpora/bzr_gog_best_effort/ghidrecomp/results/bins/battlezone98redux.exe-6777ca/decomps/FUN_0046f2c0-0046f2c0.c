
void __thiscall FUN_0046f2c0(undefined4 param_1,int *param_2)

{
  longlong lVar1;
  int iVar2;
  
  if (*param_2 == 0) {
    lVar1 = ((longlong)DAT_0260d6d4 * (longlong)DAT_0260d638 & 0xffffffffU) * 4;
    iVar2 = FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1,param_1);
    *param_2 = iVar2;
  }
  memset((void *)*param_2,0,DAT_0260d6d4 * 4 * DAT_0260d638);
  return;
}

