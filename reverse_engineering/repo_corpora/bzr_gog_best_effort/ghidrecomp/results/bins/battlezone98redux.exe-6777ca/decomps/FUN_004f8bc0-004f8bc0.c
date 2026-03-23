
void FUN_004f8bc0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  char local_34 [4];
  int local_30;
  undefined4 *local_28;
  char local_24 [16];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a850;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00611aa0(param_1,param_2,param_3);
  local_8 = 0;
  *local_28 = LauncherClass::vftable;
  FUN_00589430(local_28 + 8);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (local_28[0xc] == 0) {
    local_28[0xd] = *(undefined4 *)(param_1 + 0x34);
    local_28[0x20] = *(undefined4 *)(param_1 + 0x80);
  }
  else {
    local_28[0xd] = *(undefined4 *)(local_28[0xc] + 0x4c);
    local_28[0x20] = *(float *)(local_28[0xc] + 0x54) * *(float *)(local_28[0xc] + 0x50);
  }
  FUN_00589800(0xfa72719b,0x742c80cf,local_28 + 0x20,local_28[0x20]);
  FUN_00589800(0xfa72719b,0xd9356908,local_28 + 0x21,*(undefined4 *)(param_1 + 0x84));
  FUN_00589800(0xfa72719b,0xf7e186b5,local_28 + 0x22,*(undefined4 *)(param_1 + 0x88));
  FUN_00589800(0xfa72719b,0xa3f03b49,local_28 + 0x23,*(undefined4 *)(param_1 + 0x8c));
  FUN_0047b6c0(0xfa72719b,0x3ab425d,local_28 + 0x25,param_1 + 0x94);
  FUN_0047b6c0(0xfa72719b,0x4e2778a,local_24,0);
  if (local_24[0] == '\0') {
    local_28[0x24] = local_28[0x1a];
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    local_28[0x24] = uVar1;
  }
  FUN_0047b6c0(0xfa72719b,&DAT_027b5cb2,local_28 + 0x2a,param_1 + 0xa8);
  FUN_0047b6c0(0xfa72719b,0x748a8151,local_24,0);
  if (local_24[0] == '\0') {
    local_28[0x24] = local_28[0x1a];
  }
  else {
    uVar1 = FUN_0068bed0(local_24);
    local_28[0x29] = uVar1;
  }
  FUN_00589760(0xfa72719b,0xc188a147,local_28 + 0x2e,0);
  uVar1 = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)local_28[0x2e] * 4 >> 0x20) != 0) |
                       (uint)((ulonglong)(uint)local_28[0x2e] * 4));
  local_28[0x2f] = uVar1;
  for (local_30 = 0; local_30 < (int)local_28[0x2e]; local_30 = local_30 + 1) {
    sprintf(local_34,"%02d",local_30 + 1);
    uVar3 = 0;
    pcVar2 = local_24;
    uVar1 = FUN_00446460(local_34,0xa3a90a78,pcVar2,0);
    FUN_0047b6c0(0xfa72719b,uVar1,pcVar2,uVar3);
    uVar1 = FUN_0068bed0(local_24);
    *(undefined4 *)(local_28[0x2f] + local_30 * 4) = uVar1;
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00589530();
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

