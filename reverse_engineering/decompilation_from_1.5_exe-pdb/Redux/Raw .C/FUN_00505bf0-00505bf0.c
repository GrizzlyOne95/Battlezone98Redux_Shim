
void FUN_00505bf0(int *param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_90 [11];
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  char *pcStack_54;
  undefined1 local_48 [16];
  undefined4 *local_38;
  int local_34;
  undefined4 *local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined2 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined2 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pcStack_54 = (char *)param_4;
  uStack_58 = param_3;
  uStack_5c = 0x505c0f;
  iVar1 = FUN_0082c882();
  if (iVar1 != 0) {
    pcStack_54 = "__type";
    uStack_58 = 0xffffffff;
    uStack_5c = param_3;
    uStack_60 = 0x505c2a;
    FUN_0082c82c();
    pcStack_54 = (char *)0x811c9dc5;
    uStack_58 = 0;
    uStack_5c = 0xffffffff;
    uStack_60 = param_3;
    uStack_64 = 0x505c3f;
    uStack_58 = FUN_0082ba59();
    uStack_5c = 0x505c48;
    local_34 = FUN_00446460();
    pcStack_54 = (char *)0xfffffffd;
    uStack_58 = param_3;
    uStack_5c = 0x505c59;
    FUN_0082d226();
    local_2c = local_34;
    if (local_34 == 0xe3f3088) {
      if (*param_1 + 0xcU < param_2) {
        *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x01';
        pcStack_54 = (char *)param_4;
        uStack_58 = param_3;
        uStack_5c = 0x505cae;
        local_38 = (undefined4 *)FUN_004ff7a0();
        puVar2 = (undefined4 *)*param_1;
        *puVar2 = *local_38;
        puVar2[1] = local_38[1];
        puVar2[2] = local_38[2];
        *param_1 = *param_1 + 0xc;
      }
    }
    else if ((local_34 == 0x247e1851) && (*param_1 + 0xfU < param_2)) {
      *(char *)(*param_1 + -1) = *(char *)(*param_1 + -1) + '\x02';
      pcStack_54 = (char *)param_4;
      uStack_58 = param_3;
      uStack_5c = 0x505d13;
      local_30 = (undefined4 *)FUN_004ff820();
      puVar2 = local_30;
      puVar3 = auStack_90;
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      puVar2 = (undefined4 *)FUN_006255b0(local_48);
      local_28 = *puVar2;
      local_24 = puVar2[1];
      local_20 = puVar2[2];
      local_1c = *(undefined2 *)(puVar2 + 3);
      puVar2 = (undefined4 *)*param_1;
      *puVar2 = local_28;
      puVar2[1] = local_24;
      puVar2[2] = local_20;
      *(undefined2 *)(puVar2 + 3) = local_1c;
      *param_1 = *param_1 + 0xe;
      local_18 = local_28;
      local_14 = local_24;
      local_10 = local_20;
      local_c = local_1c;
    }
  }
  FUN_0083e885();
  return;
}

