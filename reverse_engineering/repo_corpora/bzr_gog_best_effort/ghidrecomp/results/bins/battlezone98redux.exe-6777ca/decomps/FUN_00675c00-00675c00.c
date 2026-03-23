
void __thiscall
FUN_00675c00(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  int iVar1;
  
  if ((param_4 - param_2) / 0x1c < 0x29) {
    FUN_006767c0(param_2,param_3,param_4,param_5,param_1);
  }
  else {
    iVar1 = (param_4 - param_2) / 0x1c + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_006767c0(param_2,iVar1 * 0x1c + param_2,iVar1 * 0x38 + param_2,param_5);
    FUN_006767c0(param_3 + iVar1 * -0x1c,param_3,iVar1 * 0x1c + param_3,param_5);
    FUN_006767c0(param_4 + iVar1 * -0x38,param_4 + iVar1 * -0x1c,param_4,param_5);
    FUN_006767c0(iVar1 * 0x1c + param_2,param_3,param_4 + iVar1 * -0x1c,param_5);
  }
  return;
}

