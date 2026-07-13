
void FUN_00841910(short *param_1,short *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  short sVar2;
  void *pvVar3;
  short *psVar4;
  undefined4 local_11c;
  undefined4 local_118;
  void *local_114;
  undefined1 local_110 [256];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0086595b;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)&local_11c;
  ExceptionList = &local_c;
  local_11c = param_3;
  local_118 = param_4;
  if (param_2 == (short *)0x0) {
    psVar4 = param_1;
    do {
      sVar2 = *psVar4;
      psVar4 = psVar4 + 1;
    } while (sVar2 != 0);
    param_2 = param_1 + ((int)psVar4 - (int)(param_1 + 1) >> 1);
  }
  if (param_1 != param_2) {
    uVar1 = ((int)param_2 - (int)param_1 >> 1) * 4 + 4;
    if (uVar1 < 0x101) {
      FUN_00841b20(param_1,param_2,local_110,&local_10,param_3,param_4,
                   DAT_008e7000 ^ (uint)&stack0xfffffed4);
    }
    else {
      pvVar3 = (void *)FUN_0083d92c(uVar1);
      local_4 = 0;
      local_114 = pvVar3;
      FUN_00841b20(param_1,param_2,pvVar3,(int)pvVar3 + uVar1,local_11c,local_118);
      operator_delete__(pvVar3);
    }
  }
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

