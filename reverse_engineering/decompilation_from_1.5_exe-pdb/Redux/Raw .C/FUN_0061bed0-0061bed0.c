
void FUN_0061bed0(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_90 [64];
  float local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = FUN_00439e60();
  puVar1 = (undefined4 *)FUN_004c8250(local_90);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  fVar4 = (float10)FUN_004c8240();
  local_50 = (float)fVar4;
  FUN_00689090(local_4c,local_48);
  if (*(float *)(local_4c + 0x30) != local_50) {
    FUN_006885c0(local_4c,local_50);
  }
  FUN_0083e885();
  return;
}

