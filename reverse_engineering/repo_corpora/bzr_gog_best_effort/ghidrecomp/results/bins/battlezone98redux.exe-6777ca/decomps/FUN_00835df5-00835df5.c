
int FUN_00835df5(int param_1,void *param_2,int param_3)

{
  uint _Size;
  int iVar1;
  
  param_3 = param_3 + -0x31;
  if (((param_3 < 0) || (*(int *)(param_1 + 0xc) <= param_3)) ||
     (*(int *)(param_1 + 0x14 + param_3 * 8) == -1)) {
    param_3 = FUN_0082bc39(*(undefined4 *)(param_1 + 8),"invalid capture index");
  }
  _Size = *(uint *)(param_1 + 0x14 + param_3 * 8);
  if ((_Size <= (uint)(*(int *)(param_1 + 4) - (int)param_2)) &&
     (iVar1 = memcmp(*(void **)(param_1 + 0x10 + param_3 * 8),param_2,_Size), iVar1 == 0)) {
    return _Size + (int)param_2;
  }
  return 0;
}

