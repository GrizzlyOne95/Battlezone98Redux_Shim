
void FUN_0062bf70(undefined4 *param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_9c [72];
  int local_54;
  undefined4 local_50 [18];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_54 = FUN_0062be60(*(undefined4 *)(param_2 + 0x84));
  if (*(int *)(&DAT_008ec7c0 + local_54 * 0x34) == 0) {
    FUN_00444970(local_50);
  }
  else {
    puVar1 = (undefined4 *)(**(code **)(&DAT_008ec7c0 + local_54 * 0x34))(local_9c,param_2);
    puVar3 = local_50;
    for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  puVar1 = local_50;
  for (iVar2 = 0x12; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

