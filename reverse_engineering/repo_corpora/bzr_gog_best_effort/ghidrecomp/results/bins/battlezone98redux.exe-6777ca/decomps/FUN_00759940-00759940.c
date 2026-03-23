
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00759940(int param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4,
                 undefined4 *param_5)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  bool bVar7;
  UINT aUStack_fc [2];
  DWORD aDStack_f4 [5];
  undefined1 local_e0 [32];
  undefined1 *local_c0;
  int local_bc;
  uint local_b8;
  byte *local_b4;
  undefined4 local_b0;
  uint local_ac;
  undefined1 *local_a8;
  int local_a4;
  undefined4 local_a0;
  byte *local_9c;
  byte *local_98;
  int local_94;
  byte *local_90;
  byte local_8b;
  byte local_8a;
  byte local_89;
  undefined1 local_88 [4];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  aDStack_f4[4] = 0x759958;
  FUN_006ae8d0();
  if ((param_1 == 2) || (param_1 == 0x17)) {
    local_b0 = 0x80;
    local_90 = param_2;
    local_b4 = param_2 + 1;
    do {
      local_8b = *local_90;
      local_90 = local_90 + 1;
    } while (local_8b != 0);
    local_bc = (int)local_90 - (int)(param_2 + 1);
    local_a4 = local_bc + 1;
    aDStack_f4[4] = 0x7599e7;
    iVar1 = local_a4 * -2;
    local_c0 = local_e0 + iVar1;
    local_a8 = local_e0 + iVar1;
    *(int *)(local_e0 + iVar1 + -4) = local_a4;
    *(undefined1 **)(local_e0 + iVar1 + -8) = local_a8;
    *(undefined4 *)((int)aDStack_f4 + iVar1 + 8) = 0xffffffff;
    *(byte **)((int)aDStack_f4 + iVar1 + 4) = param_2;
    *(undefined4 *)((int)aDStack_f4 + iVar1) = 0;
    *(undefined4 *)((int)aUStack_fc + iVar1 + 4) = 0;
    puVar5 = (undefined1 *)((int)aUStack_fc + iVar1);
    *(undefined4 *)((int)aUStack_fc + iVar1) = 0x759a17;
    MultiByteToWideChar(*(UINT *)((int)aUStack_fc + iVar1 + 4),*(DWORD *)((int)aDStack_f4 + iVar1),
                        *(LPCSTR *)((int)aDStack_f4 + iVar1 + 4),
                        *(int *)((int)aDStack_f4 + iVar1 + 8),*(LPWSTR *)(local_e0 + iVar1 + -8),
                        *(int *)(local_e0 + iVar1 + -4));
    *(undefined4 **)(puVar5 + -4) = param_5;
    *(undefined4 **)(puVar5 + -8) = &local_b0;
    *(undefined1 **)(puVar5 + -0xc) = local_88;
    *(undefined4 *)(puVar5 + -0x10) = 0;
    *(int *)(puVar5 + -0x14) = param_1;
    *(undefined1 **)(puVar5 + -0x18) = local_a8;
    puVar6 = (undefined4 *)(puVar5 + -0x1c);
    *(undefined4 *)(puVar5 + -0x1c) = 0x759a3c;
    uVar3 = WSAStringToAddressW();
    puVar6[-1] = uVar3;
    puVar6[-2] = 0x759a42;
    local_94 = FUN_006d8d90();
    if (param_1 == 2) {
      if (local_94 == -1) {
        local_98 = &DAT_0089b7e0;
        local_9c = param_2;
        do {
          local_89 = *local_9c;
          bVar7 = local_89 < *local_98;
          if (local_89 != *local_98) {
LAB_00759af4:
            local_ac = -(uint)bVar7 | 1;
            goto LAB_00759aff;
          }
          if (local_89 == 0) break;
          local_8a = local_9c[1];
          bVar7 = local_8a < local_98[1];
          if (local_8a != local_98[1]) goto LAB_00759af4;
          local_9c = local_9c + 2;
          local_98 = local_98 + 2;
        } while (local_8a != 0);
        local_ac = 0;
LAB_00759aff:
        local_b8 = local_ac;
        if (local_ac == 0) {
          *param_3 = 0xffffffff;
          *puVar6 = 0x759b28;
          puVar4 = (undefined4 *)FUN_004fbb60();
          uVar3 = puVar4[1];
          *param_5 = *puVar4;
          param_5[1] = uVar3;
        }
      }
      else {
        *param_3 = local_84;
        *puVar6 = 0x759a71;
        puVar4 = (undefined4 *)FUN_004fbb60();
        uVar3 = puVar4[1];
        *param_5 = *puVar4;
        param_5[1] = uVar3;
      }
    }
    else if (local_94 != -1) {
      *param_3 = local_80;
      param_3[1] = local_7c;
      param_3[2] = local_78;
      param_3[3] = local_74;
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = local_70;
      }
      *puVar6 = 0x759b73;
      puVar4 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar4[1];
      *param_5 = *puVar4;
      param_5[1] = uVar3;
    }
    if (local_94 == -1) {
      *puVar6 = 0x759b91;
      cVar2 = FUN_004c85a0();
      if (cVar2 != '\0') {
        *puVar6 = 0x2726;
        puVar6[-1] = 0x759ba5;
        FUN_006d8cf0();
      }
    }
    if (local_94 != -1) {
      *puVar6 = 0x759bb9;
      puVar4 = (undefined4 *)FUN_004fbb60();
      uVar3 = puVar4[1];
      *param_5 = *puVar4;
      param_5[1] = uVar3;
    }
    if (local_94 == -1) {
      local_a0 = 0xffffffff;
    }
    else {
      local_a0 = 1;
    }
  }
  else {
    aDStack_f4[4] = 0x273f;
    aDStack_f4[3] = 0x759971;
    FUN_006d8cf0();
  }
  aDStack_f4[4] = 0x759bfb;
  FUN_0083e885();
  return;
}

