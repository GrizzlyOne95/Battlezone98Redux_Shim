
void __thiscall FUN_0062bab0(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  
  if (param_3 != 0) {
    iVar1 = FUN_0062be60(param_2,param_1);
    if (*(int *)(&DAT_008ec7d0 + iVar1 * 0x34) != 0) {
      (**(code **)(&DAT_008ec7d0 + iVar1 * 0x34))(param_3);
    }
  }
  return;
}

