
void __thiscall
FUN_00757190(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  int iVar1;
  
  if ((param_4 - param_2) / 0x50 < 0x29) {
    FUN_00757690(param_2,param_3,param_4,param_5,param_1);
  }
  else {
    iVar1 = (param_4 - param_2) / 0x50 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_00757690(param_2,iVar1 * 0x50 + param_2,iVar1 * 0xa0 + param_2,param_5);
    FUN_00757690(param_3 + iVar1 * -0x50,param_3,iVar1 * 0x50 + param_3,param_5);
    FUN_00757690(param_4 + iVar1 * -0xa0,param_4 + iVar1 * -0x50,param_4,param_5);
    FUN_00757690(iVar1 * 0x50 + param_2,param_3,param_4 + iVar1 * -0x50,param_5);
  }
  return;
}

