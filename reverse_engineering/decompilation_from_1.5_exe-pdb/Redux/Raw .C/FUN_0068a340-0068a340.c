
/* WARNING: Restarted to delay deadcode elimination for space: ram */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_0068a340(undefined4 param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float10 fVar6;
  undefined1 local_dc [64];
  float local_9c;
  float local_98;
  undefined4 local_94;
  float local_90;
  float local_8c;
  int local_88;
  int local_84;
  float local_80;
  int local_7c;
  float local_78;
  undefined *local_74;
  int local_70;
  int local_6c;
  undefined4 local_68 [10];
  double local_40;
  double local_38;
  double local_30;
  float local_28;
  float local_24;
  float local_20;
  float afStack_1c [5];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_02bf0434 = 0;
  iVar3 = FUN_0068a110();
  if (iVar3 != 1) {
    puVar4 = (undefined4 *)FUN_0062e070(local_dc,param_1,0);
    puVar5 = local_68;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_70 = 0;
    local_84 = 4;
    if (DAT_02bf0430 < 4) {
      local_84 = DAT_02bf0430;
    }
    local_84 = local_84 + 1;
    afStack_1c[0] = -1e+20;
    local_74 = &DAT_02bf044c;
    for (local_6c = 0; local_6c < DAT_02bf0430; local_6c = local_6c + 1) {
      local_28 = (float)(local_40 - (double)*(float *)(*(int *)(local_74 + local_6c * 4) + 0x54));
      local_24 = (float)(local_38 - (double)*(float *)(*(int *)(local_74 + local_6c * 4) + 0x58));
      local_20 = (float)(local_30 - (double)*(float *)(*(int *)(local_74 + local_6c * 4) + 0x5c));
      local_80 = local_28 * local_28 + local_24 * local_24 + local_20 * local_20;
      local_78 = 1.0 / (local_80 * *(float *)(*(int *)(local_74 + local_6c * 4) + 0xc) + 1.0);
      if ((*(uint *)(*(int *)(local_74 + local_6c * 4) + 4) & 1) != 0) {
        fVar6 = (float10)FUN_00417910(local_80);
        local_9c = (float)fVar6;
        local_80 = 1.0 / (local_9c + 0.5);
        local_28 = local_28 * local_80;
        local_24 = local_24 * local_80;
        local_20 = local_20 * local_80;
        fVar6 = (float10)FUN_004428b0(*(int *)(local_74 + local_6c * 4) + 0x30,&local_28);
        local_90 = (float)fVar6;
        fVar6 = (float10)FUN_004178d0((1.0 - local_90) * 0.5,
                                      *(undefined4 *)(*(int *)(local_74 + local_6c * 4) + 8));
        local_98 = (float)fVar6;
        local_78 = local_98 * local_78;
      }
      if ((local_70 < local_84) || (iVar3 = local_70, afStack_1c[0] < local_78)) {
        afStack_1c[local_70] = local_78;
        fVar1 = afStack_1c[0];
        (&DAT_02bf0438)[local_70] = *(undefined4 *)(local_74 + local_6c * 4);
        iVar3 = local_70 + 1;
        local_7c = 0;
        local_78 = afStack_1c[0];
        local_94 = DAT_02bf0438;
        local_8c = local_78;
        for (local_88 = 1; local_88 < iVar3; local_88 = local_88 + 1) {
          if (afStack_1c[local_88] <= local_8c && local_8c != afStack_1c[local_88]) {
            local_8c = afStack_1c[local_88];
            local_7c = local_88;
          }
        }
        afStack_1c[0] = afStack_1c[local_7c];
        afStack_1c[local_7c] = fVar1;
        uVar2 = (&DAT_02bf0438)[local_7c];
        (&DAT_02bf0438)[local_7c] = DAT_02bf0438;
        DAT_02bf0438 = uVar2;
        if (iVar3 == local_84) {
          iVar3 = local_70;
        }
      }
      local_70 = iVar3;
    }
    DAT_02bf0434 = local_70;
  }
  FUN_0083e885();
  return;
}

