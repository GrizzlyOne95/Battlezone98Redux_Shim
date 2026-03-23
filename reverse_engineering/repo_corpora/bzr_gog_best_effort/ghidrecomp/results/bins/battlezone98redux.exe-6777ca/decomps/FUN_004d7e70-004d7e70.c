
void __thiscall
FUN_004d7e70(undefined4 param_1,int param_2,int param_3,int param_4,undefined1 param_5)

{
  int iVar1;
  
  if (param_4 - param_2 >> 2 < 0x29) {
    FUN_004d8b60(param_2,param_3,param_4,param_5,param_1);
  }
  else {
    iVar1 = (param_4 - param_2 >> 2) + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_004d8b60(param_2,param_2 + iVar1 * 4,param_2 + iVar1 * 8,param_5);
    FUN_004d8b60(param_3 + iVar1 * -4,param_3,param_3 + iVar1 * 4,param_5);
    FUN_004d8b60(param_4 + iVar1 * -8,param_4 + iVar1 * -4,param_4,param_5);
    FUN_004d8b60(param_2 + iVar1 * 4,param_3,param_4 + iVar1 * -4,param_5);
  }
  return;
}

