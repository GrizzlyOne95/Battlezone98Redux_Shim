
undefined4 FUN_0062c000(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_c;
  
  local_c = 0;
  iVar1 = FUN_0062be60(*(undefined4 *)(param_1 + 0x84));
  if (*(int *)(&DAT_008ec7c4 + iVar1 * 0x34) != 0) {
    iVar1 = (**(code **)(&DAT_008ec7c4 + iVar1 * 0x34))(param_1,param_2,param_3,param_4);
    if (iVar1 != 0) {
      local_c = 1;
    }
  }
  iVar1 = FUN_0062be60(*(undefined4 *)(param_2 + 0x84));
  if (*(int *)(&DAT_008ec7c4 + iVar1 * 0x34) != 0) {
    iVar1 = (**(code **)(&DAT_008ec7c4 + iVar1 * 0x34))(param_2,param_1,param_4,param_3);
    if (iVar1 != 0) {
      local_c = 1;
    }
  }
  return local_c;
}

