
void FUN_00689fa0(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  iVar1 = param_5;
  iVar2 = param_4;
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  if (param_5 < param_3) {
    param_5 = param_3;
    param_3 = iVar1;
  }
  local_18 = param_2;
  local_14 = param_3;
  local_10 = param_4;
  local_c = param_5;
  local_28 = 0;
  local_24 = 0;
  local_20 = *param_1 + -1;
  local_1c = param_1[1] + -1;
  iVar2 = FUN_0068f360(&local_18,&local_28);
  if (-1 < iVar2) {
    param_1[2] = local_18;
    param_1[3] = local_14;
    param_1[4] = local_10;
    param_1[5] = local_c;
  }
  FUN_0083e885();
  return;
}

