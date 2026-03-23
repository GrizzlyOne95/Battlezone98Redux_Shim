
void __thiscall FUN_004db650(int *param_1,int param_2)

{
  int iVar1;
  
  FUN_004d9ae0(param_1[0x3d],param_2);
  param_1[0x5d] = param_2;
  iVar1 = FUN_005e0bc0(param_2);
  param_1[0x5f] = iVar1;
  if ((param_1 == DAT_00917afc) || ((char)param_1[0x1e] != '\0')) {
    param_1[0x5e] = 0;
  }
  else if ((*(int *)(param_1[0x3e] + 0x13c) < 0) || (*(int *)(param_1[0x3e] + 0x140) < 0)) {
    param_1[0x5e] = -1;
  }
  else {
    iVar1 = FUN_005e0f90(*(undefined4 *)(param_1[0x3e] + 0x13c),
                         *(undefined4 *)(param_1[0x3e] + 0x140));
    param_1[0x5e] = iVar1;
  }
  if ((param_1[0x5f] != 0) && (param_1[0x5e] != -1)) {
    FUN_005e0f50(param_1[0x5e],param_1);
  }
  FUN_004db800();
  (**(code **)(*param_1 + 0x5c))();
  FUN_004723b0(0);
  return;
}

