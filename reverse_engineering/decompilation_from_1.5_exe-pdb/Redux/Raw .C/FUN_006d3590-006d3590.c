
void FUN_006d3590(undefined4 *param_1,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_30 [40];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar5 = param_4;
  uVar2 = FUN_006b3f90(param_4);
  uVar3 = FUN_006b3f80(uVar2);
  uVar4 = get(uVar3);
  FUN_006b17f0(local_30,param_2,uVar4,uVar3,uVar2,puVar5);
  cVar1 = FUN_004c85a0();
  if (cVar1 != '\0') {
    *(undefined4 *)(param_2 + 0x1c) = *param_3;
    *(undefined1 *)(param_2 + 0x20) = 0;
    uVar2 = FUN_006cb470();
    FUN_006cb4c0(uVar2);
  }
  uVar2 = param_4[1];
  *param_1 = *param_4;
  param_1[1] = uVar2;
  FUN_0083e885();
  return;
}

