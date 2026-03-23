
void __thiscall
FUN_00676450(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  int iVar1;
  
  if ((param_4 - param_2) / 0x18 < 0x29) {
    FUN_00676e00(param_2,param_3,param_4,param_5,param_1);
  }
  else {
    iVar1 = (param_4 - param_2) / 0x18 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_00676e00(param_2,iVar1 * 0x18 + param_2,iVar1 * 0x30 + param_2,param_5);
    FUN_00676e00(param_3 + iVar1 * -0x18,param_3,iVar1 * 0x18 + param_3,param_5);
    FUN_00676e00(param_4 + iVar1 * -0x30,param_4 + iVar1 * -0x18,param_4,param_5);
    FUN_00676e00(iVar1 * 0x18 + param_2,param_3,param_4 + iVar1 * -0x18,param_5);
  }
  return;
}

