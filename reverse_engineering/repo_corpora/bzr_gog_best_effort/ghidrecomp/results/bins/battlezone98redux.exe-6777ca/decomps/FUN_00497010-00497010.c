
void __thiscall
FUN_00497010(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  int iVar1;
  
  if (param_4 - param_2 >> 3 < 0x29) {
    FUN_00497310(param_2,param_3,param_4,param_5,param_1);
  }
  else {
    iVar1 = (param_4 - param_2 >> 3) + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_00497310(param_2,param_2 + iVar1 * 8,param_2 + iVar1 * 0x10,param_5);
    FUN_00497310(param_3 + iVar1 * -8,param_3,param_3 + iVar1 * 8,param_5);
    FUN_00497310(param_4 + iVar1 * -0x10,param_4 + iVar1 * -8,param_4,param_5);
    FUN_00497310(param_2 + iVar1 * 8,param_3,param_4 + iVar1 * -8,param_5);
  }
  return;
}

