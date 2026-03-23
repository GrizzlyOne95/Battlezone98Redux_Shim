
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004c12f0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  float10 fVar7;
  float10 fVar8;
  float fVar9;
  float fVar10;
  float local_a0;
  float local_9c;
  float local_98;
  int local_94;
  int local_90;
  undefined4 local_88 [16];
  undefined1 local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0x41000000;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0x3f060a92;
  *(undefined4 *)(param_1 + 0x60) = 0x3f060a92;
  puVar4 = (undefined4 *)FUN_004c6a10(local_48);
  puVar6 = local_88;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  *(undefined ***)(param_1 + 8) = &PTR_PTR_008e8204;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 1000;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  _DAT_008e81f0 = FUN_0068bed0(PTR_s_edit_arw_008e81e0);
  *(undefined4 *)(param_1 + 0x80) = 0x80;
  *(undefined4 *)(param_1 + 0x84) = 0x80;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0x144) = 0xbf800000;
  *(undefined4 *)(param_1 + 0x13c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x140) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x4148) = 0;
  *(undefined4 *)(param_1 + 0x414c) = 0;
  *(undefined4 *)(param_1 + 0x4150) = 0;
  *(undefined4 *)(param_1 + 0x4154) = 0;
  *(undefined4 *)(param_1 + 0x4158) = 0;
  *(undefined4 *)(param_1 + 0x415c) = 0;
  *(undefined4 *)(param_1 + 0x1c460) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c464) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x20468) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x2046c) = 0x40c00000;
  local_98 = 0.0;
  fVar9 = 6.0 / *(float *)(param_1 + 0x2046c);
  fVar10 = 6.0 / *(float *)(param_1 + 0x2046c);
  fVar1 = *(float *)(param_1 + 0x20468);
  fVar2 = *(float *)(param_1 + 0x20468);
  fVar7 = (float10)FUN_00417910(0x40c90fdb);
  fVar3 = *(float *)(param_1 + 0x20468);
  local_a0 = -fVar10 * 0.5 * *(float *)(param_1 + 0x2046c);
  for (local_94 = 0; (float)local_94 <= *(float *)(param_1 + 0x2046c); local_94 = local_94 + 1) {
    local_9c = -fVar9 * 0.5 * *(float *)(param_1 + 0x2046c);
    for (local_90 = 0; (float)local_90 <= *(float *)(param_1 + 0x2046c); local_90 = local_90 + 1) {
      fVar8 = (float10)FUN_0045c400((local_9c * local_9c + local_a0 * local_a0) *
                                    (-1.0 / (fVar1 * 2.0 * fVar2)));
      *(float *)(param_1 + 0x20470 + local_94 * 0x44 + local_90 * 4) =
           (float)fVar8 * (1.0 / ((float)fVar7 * fVar3));
      local_98 = local_98 + *(float *)(param_1 + 0x20470 + local_94 * 0x44 + local_90 * 4);
      local_9c = local_9c + fVar9;
    }
    local_a0 = local_a0 + fVar10;
  }
  for (local_94 = 0; (float)local_94 <= *(float *)(param_1 + 0x2046c); local_94 = local_94 + 1) {
    for (local_90 = 0; (float)local_90 <= *(float *)(param_1 + 0x2046c); local_90 = local_90 + 1) {
      *(float *)(param_1 + 0x20470 + local_94 * 0x44 + local_90 * 4) =
           *(float *)(param_1 + 0x20470 + local_94 * 0x44 + local_90 * 4) * (1.0 / local_98);
    }
  }
  FUN_0083e885();
  return;
}

