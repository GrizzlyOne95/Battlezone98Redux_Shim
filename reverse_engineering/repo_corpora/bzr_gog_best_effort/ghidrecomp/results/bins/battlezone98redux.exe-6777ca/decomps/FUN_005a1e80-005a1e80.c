
void __thiscall FUN_005a1e80(int param_1,undefined1 *param_2,int *param_3)

{
  undefined1 uVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_44 [8];
  undefined1 local_3c [8];
  undefined4 local_34;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  uint local_28;
  float local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  float local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  local_8 = param_2;
  *param_3 = *param_3 + 0x14;
  if (0.0 < *(float *)(param_1 + 500)) {
    local_1c = (int)(*(float *)(param_1 + 500) * 255.0);
    param_2[1] = (undefined1)local_1c;
  }
  else {
    param_2[1] = 0;
  }
  local_c = param_1;
  if (0.0 < *(float *)(param_1 + 0x1e8)) {
    local_14 = *(float *)(param_1 + 0x1e8);
    if (1.0 < local_14) {
      local_14 = 1.0;
    }
    FUN_0043d610(local_14 * 255.0);
    local_20 = FUN_0083f040();
    *local_8 = (undefined1)local_20;
  }
  else {
    *param_2 = 0;
  }
  puVar3 = (undefined4 *)
           FUN_006259c0(local_3c,*(undefined4 *)(local_c + 0x114),*(undefined4 *)(local_c + 0x118),
                        *(undefined4 *)(local_c + 0x11c));
  local_2e = *puVar3;
  local_2a = *(undefined2 *)(puVar3 + 1);
  *(undefined4 *)(local_8 + 2) = local_2e;
  *(undefined2 *)(local_8 + 6) = local_2a;
  puVar3 = (undefined4 *)
           FUN_006259c0(local_44,*(undefined4 *)(local_c + 0x120),*(undefined4 *)(local_c + 0x124),
                        *(undefined4 *)(local_c + 0x128));
  local_34 = *puVar3;
  local_30 = *(undefined2 *)(puVar3 + 1);
  *(undefined4 *)(local_8 + 8) = local_34;
  *(undefined2 *)(local_8 + 0xc) = local_30;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 0xc4));
  local_8[0xe] = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 200));
  local_8[0xf] = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 0xcc));
  local_8[0x10] = uVar1;
  uVar1 = FUN_006258d0(*(undefined4 *)(*(int *)(local_c + 0x218) + 0xd0));
  local_8[0x11] = uVar1;
  local_8[0x12] = 0;
  if (*(int *)(*(int *)(local_c + 0x218) + 0xd8) != 0) {
    local_8[0x12] = local_8[0x12] | 1;
  }
  if (*(int *)(*(int *)(local_c + 0x218) + 0xd4) != 0) {
    local_8[0x12] = local_8[0x12] | 2;
  }
  if (*(int *)(*(int *)(local_c + 0x218) + 0xdc) != 0) {
    local_8[0x12] = local_8[0x12] | 4;
  }
  if ((*(uint *)(*(int *)(local_c + 0x218) + 0x114) & 0x80) != 0) {
    local_8[0x12] = local_8[0x12] | 8;
  }
  if ((*(uint *)(*(int *)(local_c + 0x218) + 0x114) & 4) != 0) {
    local_8[0x12] = local_8[0x12] | 0x10;
  }
  cVar2 = FUN_0046fbf0();
  if (cVar2 != '\0') {
    local_8[0x12] = local_8[0x12] | 0x20;
  }
  if ((*(uint *)(*(int *)(local_c + 0xdc) + 0x14) & 0x10) != 0) {
    iVar4 = FUN_004e96a0();
    if (iVar4 != 0) {
      local_8[0x12] = local_8[0x12] | 0x40;
    }
  }
  fVar5 = (float10)FUN_0046fbd0();
  local_24 = (float)fVar5;
  if (local_24 < 0.0) {
    local_8[0x12] = local_8[0x12] | 0x80;
  }
  local_8[0x13] = 0;
  if (*(int *)(local_c + 0x210) == 2) {
    local_8[0x13] = 0;
  }
  else if (*(int *)(local_c + 0x210) == 0) {
    local_8[0x13] = local_8[0x13] | 1;
  }
  else if (*(int *)(local_c + 0x210) == 1) {
    local_8[0x13] = local_8[0x13] | 2;
  }
  else if (*(int *)(local_c + 0x210) == 3) {
    local_8[0x13] = local_8[0x13] | 3;
  }
  if (*(int *)(local_c + 0xe4) == 0) {
    local_8[0x13] = local_8[0x13] | 4;
  }
  if (*(int *)(local_c + 0x188) != 0) {
    local_28 = FUN_00417f90();
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      if ((1 << ((byte)local_10 & 0x1f) & local_28) != 0) {
        local_18 = FUN_00417f60(local_10);
        if ((local_18 != 0) && (*(int *)(*(int *)(local_18 + 8) + 0xc) == 0x534e4950)) {
          local_8[0x13] = local_8[0x13] | 8;
        }
      }
    }
  }
  return;
}

