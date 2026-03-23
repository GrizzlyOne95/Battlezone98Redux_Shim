
void FUN_0060f720(undefined4 *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  undefined1 local_50 [12];
  undefined1 local_44 [12];
  uint local_38;
  uint local_34;
  float local_30;
  uint local_2c;
  undefined4 *local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_28 = param_1;
  puVar2 = (undefined4 *)FUN_00625950(local_44,*param_1,*(undefined2 *)(param_1 + 1));
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(iVar1 + 0x1c) = local_20;
  *(undefined4 *)(iVar1 + 0x20) = local_1c;
  *(undefined4 *)(iVar1 + 0x24) = local_18;
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(local_24 + 0x114) = *(undefined4 *)(iVar1 + 0x1c);
  *(undefined4 *)(local_24 + 0x118) = *(undefined4 *)(iVar1 + 0x20);
  *(undefined4 *)(local_24 + 0x11c) = *(undefined4 *)(iVar1 + 0x24);
  puVar2 = (undefined4 *)
           FUN_00625950(local_50,*(undefined4 *)((int)local_28 + 6),
                        *(undefined2 *)((int)local_28 + 10));
  local_14 = *puVar2;
  local_10 = puVar2[1];
  local_c = puVar2[2];
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(iVar1 + 0x28) = local_14;
  *(undefined4 *)(iVar1 + 0x2c) = local_10;
  *(undefined4 *)(iVar1 + 0x30) = local_c;
  iVar1 = *(int *)(local_24 + 0x218);
  *(undefined4 *)(local_24 + 0x120) = *(undefined4 *)(iVar1 + 0x28);
  *(undefined4 *)(local_24 + 0x124) = *(undefined4 *)(iVar1 + 0x2c);
  *(undefined4 *)(local_24 + 0x128) = *(undefined4 *)(iVar1 + 0x30);
  fVar3 = (float10)FUN_0045c420(*(undefined4 *)(local_24 + 0x114),*(undefined4 *)(local_24 + 0x118),
                                *(undefined4 *)(local_24 + 0x11c));
  *(float *)(*(int *)(local_24 + 0x218) + 0xc) = (float)fVar3;
  if (*(float *)(*(int *)(local_24 + 0x218) + 0xc) <= 0.0) {
    local_30 = 1e+30;
  }
  else {
    local_30 = 1.0 / *(float *)(*(int *)(local_24 + 0x218) + 0xc);
  }
  *(float *)(*(int *)(local_24 + 0x218) + 0x10) = local_30;
  *(undefined4 *)(local_24 + 0x104) = *(undefined4 *)(*(int *)(local_24 + 0x218) + 0xc);
  *(undefined4 *)(local_24 + 0x108) = *(undefined4 *)(*(int *)(local_24 + 0x218) + 0x10);
  local_38 = (uint)((*(byte *)(local_28 + 4) & 1) != 0);
  *(uint *)(*(int *)(local_24 + 0x218) + 0xd8) = local_38;
  local_2c = (uint)((*(byte *)(local_28 + 4) & 2) != 0);
  *(uint *)(*(int *)(local_24 + 0x218) + 0xd4) = local_2c;
  local_34 = (uint)((*(byte *)(local_28 + 4) & 4) != 0);
  *(uint *)(*(int *)(local_24 + 0x218) + 0xdc) = local_34;
  if ((*(byte *)(local_28 + 4) & 0x40) == 0) {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) & 0xffffefff;
  }
  else {
    *(uint *)(*(int *)(local_24 + 0x218) + 0x114) =
         *(uint *)(*(int *)(local_24 + 0x218) + 0x114) | 0x1000;
  }
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)(local_28 + 3));
  *(float *)(*(int *)(local_24 + 0x218) + 0xc4) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)((int)local_28 + 0xd));
  *(float *)(*(int *)(local_24 + 0x218) + 200) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)((int)local_28 + 0xe));
  *(float *)(*(int *)(local_24 + 0x218) + 0xcc) = (float)fVar3;
  fVar3 = (float10)FUN_006258b0(*(undefined1 *)((int)local_28 + 0xf));
  *(float *)(*(int *)(local_24 + 0x218) + 0xd0) = (float)fVar3;
  *param_2 = *param_2 + -0x12;
  FUN_004ae3b0((int)local_28 + 0x12,param_2);
  FUN_0083e885();
  return;
}

