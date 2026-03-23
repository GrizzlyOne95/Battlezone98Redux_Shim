
void FUN_005f1900(undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_34 [12];
  uint local_28;
  uint local_24;
  uint local_20;
  undefined4 *local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  puVar2 = (undefined4 *)FUN_00625950(local_34,*param_1,*(undefined2 *)(param_1 + 1));
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  iVar1 = *(int *)(local_18 + 0x218);
  *(undefined4 *)(iVar1 + 0x28) = local_14;
  *(undefined4 *)(iVar1 + 0x2c) = local_10;
  *(undefined4 *)(iVar1 + 0x30) = local_c;
  iVar1 = *(int *)(local_18 + 0x218);
  *(undefined4 *)(local_18 + 0x120) = *(undefined4 *)(iVar1 + 0x28);
  *(undefined4 *)(local_18 + 0x124) = *(undefined4 *)(iVar1 + 0x2c);
  *(undefined4 *)(local_18 + 0x128) = *(undefined4 *)(iVar1 + 0x30);
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)((int)local_1c + 6));
  *(float *)(*(int *)(local_18 + 0x218) + 0xc4) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)((int)local_1c + 7));
  *(float *)(*(int *)(local_18 + 0x218) + 200) = (float)fVar3;
  local_24 = (uint)((*(byte *)(local_1c + 2) & 1) != 0);
  *(uint *)(*(int *)(local_18 + 0x218) + 0xd8) = local_24;
  local_20 = (uint)((*(byte *)(local_1c + 2) & 2) != 0);
  *(uint *)(*(int *)(local_18 + 0x218) + 0xd4) = local_20;
  local_28 = (uint)((*(byte *)(local_1c + 2) & 4) != 0);
  *(uint *)(*(int *)(local_18 + 0x218) + 0xdc) = local_28;
  if ((*(byte *)(local_1c + 2) & 8) == 0) {
    *(uint *)(*(int *)(local_18 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_18 + 0x218) + 0x114) & 0xffffffdf;
  }
  else {
    *(uint *)(*(int *)(local_18 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_18 + 0x218) + 0x114) | 0x20;
  }
  if ((*(byte *)(local_1c + 2) & 0x40) == 0) {
    *(uint *)(*(int *)(local_18 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_18 + 0x218) + 0x114) & 0xffffefff;
  }
  else {
    *(uint *)(*(int *)(local_18 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_18 + 0x218) + 0x114) | 0x1000;
  }
  *param_2 = *param_2 + -10;
  FUN_004ae3b0((int)local_1c + 10,param_2);
  FUN_0083e885();
  return;
}

