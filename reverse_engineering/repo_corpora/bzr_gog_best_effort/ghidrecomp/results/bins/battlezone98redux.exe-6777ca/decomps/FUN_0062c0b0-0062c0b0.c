
undefined4 __thiscall
FUN_0062c0b0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0062be60(*(undefined4 *)(param_2 + 0x84),param_1);
  if (*(int *)(&DAT_008ec7c8 + iVar1 * 0x34) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (**(code **)(&DAT_008ec7c8 + iVar1 * 0x34))(param_2,param_3,param_4);
  }
  return uVar2;
}

