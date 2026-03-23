
void FUN_00611840(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float local_a0;
  uint local_9c;
  undefined4 local_94 [16];
  undefined4 local_54 [10];
  undefined8 local_2c;
  double local_24;
  undefined8 local_1c;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_0081fe60();
  puVar3 = local_94;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_94;
  puVar3 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_00785730(local_2c,local_1c,&local_a0,local_14);
  local_9c = (uint)((double)(local_a0 + 0.1) < local_24);
  FUN_0083e885();
  return;
}

