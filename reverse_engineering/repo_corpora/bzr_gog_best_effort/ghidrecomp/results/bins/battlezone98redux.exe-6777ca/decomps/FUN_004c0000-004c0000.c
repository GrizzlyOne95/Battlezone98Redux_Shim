
void FUN_004c0000(int param_1,float param_2,int *param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = *param_3;
  local_14 = param_3[1];
  local_10 = param_3[2];
  local_c = param_3[3];
  iVar1 = FUN_0068f360(&local_18,param_1 + 8);
  if (-1 < iVar1) {
    iVar1 = FUN_00453d10((int)((float)((param_3[2] - *param_3) + 1) * param_2) + *param_3,*param_3,
                         param_3[2]);
    if (local_18 < iVar1) {
      FUN_0068af70(param_1,local_18,local_14,iVar1 + -1,local_c,param_4,0);
    }
    if (iVar1 <= local_10) {
      FUN_0068af70(param_1,iVar1,local_14,local_10,local_c,param_5,0);
    }
  }
  FUN_0083e885();
  return;
}

