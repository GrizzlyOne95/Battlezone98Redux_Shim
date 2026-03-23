
void FUN_00785fe0(undefined4 param_1,int param_2,int param_3,double param_4,double param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint local_2c;
  uint local_24;
  float local_14;
  float local_c;
  
  iVar7 = 10;
  iVar1 = FUN_0046eaf0(param_4,10);
  local_2c = (uint)(iVar1 < param_2 * 0x80 + -1);
  iVar2 = FUN_0046eaf0(param_5);
  local_24 = (uint)(iVar2 < param_3 * 0x80 + -1);
  iVar3 = FUN_00785f50(param_1,param_2,param_3,iVar1,iVar2);
  iVar4 = FUN_00785f50(param_1,param_2,param_3,iVar1 + local_2c,iVar2 + local_24);
  if ((float)(param_5 - (double)iVar2) <= (float)(param_4 - (double)iVar1)) {
    iVar5 = FUN_00785f50(param_1,param_2,param_3,iVar1 + local_2c,iVar2);
    iVar6 = iVar3 - iVar5;
    iVar5 = iVar5 - iVar4;
  }
  else {
    iVar5 = FUN_00785f50(param_1,param_2,param_3,iVar1,iVar2 + local_24);
    iVar6 = iVar5 - iVar4;
    iVar5 = iVar3 - iVar5;
  }
  local_c = (float)iVar5 * 0.010000001;
  local_14 = (float)iVar6 * 0.010000001;
  FUN_0083e885(iVar7,iVar3 - (int)((((float)(param_4 - (double)iVar1) * local_14 +
                                    (float)(param_5 - (double)iVar2) * local_c) * (float)iVar7) /
                                  0.1));
  return;
}

