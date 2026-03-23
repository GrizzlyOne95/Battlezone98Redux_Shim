
/* WARNING: Removing unreachable block (ram,0x004e986d) */
/* WARNING: Removing unreachable block (ram,0x004e98a1) */
/* WARNING: Removing unreachable block (ram,0x004e988e) */
/* WARNING: Removing unreachable block (ram,0x004e98ab) */

void FUN_004e96d0(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  float10 fVar5;
  undefined1 local_168 [64];
  undefined1 local_128 [24];
  undefined1 local_110 [12];
  undefined4 *local_104;
  float local_100;
  float local_fc;
  int local_f8;
  int local_ec;
  int local_e4;
  int local_e0;
  int local_dc;
  float local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  undefined4 *local_bc;
  undefined4 *local_b8;
  int local_b4;
  undefined4 local_b0 [16];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  double local_44;
  undefined4 local_3c;
  undefined4 local_38;
  int aiStack_34 [8];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a55a;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_004a7a20(param_1,param_2);
  local_8 = 0;
  *local_b8 = HoverCraft::vftable;
  local_b8[6] = HoverCraft::vftable;
  iVar2 = FUN_0045c4f0();
  *(undefined4 *)(iVar2 + 0x114) = 1;
  local_b8[0x8d] = 0;
  if ((*(uint *)(local_b8[0x3d] + 0x14) & 0x20) == 0) {
    local_fc = *(float *)(param_2 + 0x34c);
    puVar3 = (undefined4 *)FUN_00447f60(local_128,local_b8[0x3d] + 0x20,uVar1);
    local_64 = *puVar3;
    local_60 = puVar3[1];
    local_5c = puVar3[2];
    local_58 = puVar3[3];
    local_44 = *(double *)(puVar3 + 2);
    local_54 = puVar3[4];
    local_50 = puVar3[5];
    local_4c = local_64;
    local_48 = local_60;
    local_3c = local_54;
    local_38 = local_50;
    fVar5 = (float10)FUN_0049c8f0(local_64,local_60,local_5c,local_58,local_54);
    local_100 = (float)fVar5;
    local_44 = (double)(local_100 + local_fc);
    FUN_0044b7d0(local_b8[0x3d] + 0x20);
    local_b8[0xaa] = 0;
  }
  else {
    local_b8[0xaa] = 0;
  }
  local_b8[0xae] = 0;
  local_b8[0xad] = 0;
  local_c8 = 0;
  local_d4 = 0;
  local_e0 = 0;
  local_b4 = local_b8[0x3d];
  do {
    while( true ) {
      local_dc = *(int *)(local_b4 + 0x84);
      if (local_dc == 0x43) {
        aiStack_34[local_c8] = local_b4;
        local_c8 = local_c8 + 1;
      }
      else if (local_dc == 0x4b) {
        local_d4 = local_d4 + 1;
      }
      else if (local_dc == 0x4d) {
        local_e0 = local_e0 + 1;
      }
      if (*(int *)(local_b4 + 0x80) == 0) break;
      local_b4 = *(int *)(local_b4 + 0x80);
    }
    do {
      if (*(int *)(local_b4 + 0x7c) != 0) break;
      local_b4 = *(int *)(local_b4 + 0x78);
    } while (local_b4 != 0);
    if (local_b4 == 0) {
      if (*(int *)(param_2 + 0x39c) == 0) {
        if (local_d4 == 0) {
          for (local_c4 = 0; local_c4 < local_c8; local_c4 = local_c4 + 1) {
            local_cc = aiStack_34[local_c4];
            local_d0 = local_cc + 0x20;
            local_d8 = *(float *)(local_cc + 0xb4);
            local_ec = FUN_0062ccc0(local_cc,"fun3d\\HoverCraft.cpp");
            *(undefined4 *)(local_ec + 0x84) = 0x4b;
            local_bc = (undefined4 *)(local_ec + 0x20);
            *local_bc = 0x3f800000;
            *(undefined4 *)(local_ec + 0x24) = 0;
            *(undefined4 *)(local_ec + 0x28) = 0;
            *(undefined4 *)(local_ec + 0x2c) = 0;
            *(undefined4 *)(local_ec + 0x30) = 0;
            *(undefined4 *)(local_ec + 0x34) = 0x3f800000;
            *(undefined4 *)(local_ec + 0x38) = 0;
            *(undefined4 *)(local_ec + 0x3c) = 0xbf800000;
            *(undefined4 *)(local_ec + 0x40) = 0;
            *(double *)(local_ec + 0x48) = (double)(local_d8 * *(float *)(local_d0 + 0xc));
            *(double *)(local_ec + 0x50) = (double)(local_d8 * *(float *)(local_d0 + 0x10));
            *(double *)(local_ec + 0x58) = (double)(local_d8 * *(float *)(local_d0 + 0x14));
          }
        }
      }
      else {
        for (local_c0 = 0; local_c0 < *(int *)(param_2 + 0x39c); local_c0 = local_c0 + 1) {
          local_b4 = local_b8[0x3d];
          while (iVar2 = _strnicmp((char *)(local_b4 + 8),(char *)(param_2 + 0x3a0 + local_c0 * 8),8
                                  ), iVar2 != 0) {
            if (*(int *)(local_b4 + 0x80) == 0) {
              do {
                if (*(int *)(local_b4 + 0x7c) != 0) break;
                local_b4 = *(int *)(local_b4 + 0x78);
              } while (local_b4 != 0);
              if (local_b4 == 0) goto LAB_004e9a31;
              local_b4 = *(int *)(local_b4 + 0x7c);
            }
            else {
              local_b4 = *(int *)(local_b4 + 0x80);
            }
          }
          local_e4 = FUN_0062ccc0(local_b4,"fun3d\\HoverCraft.cpp");
          *(undefined4 *)(local_e4 + 0x84) = 0x4b;
          local_104 = (undefined4 *)(local_e4 + 0x20);
          puVar3 = (undefined4 *)
                   FUN_0081ee70(local_168,*(undefined4 *)(param_2 + 0x4e0 + local_c0 * 0xc),
                                *(undefined4 *)(param_2 + 0x4e4 + local_c0 * 0xc),
                                *(undefined4 *)(param_2 + 0x4e8 + local_c0 * 0xc),
                                (double)*(float *)(param_2 + 0x420 + local_c0 * 0xc));
          puVar4 = local_b0;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
          puVar3 = local_b0;
          puVar4 = local_104;
          for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
            *puVar4 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar4 = puVar4 + 1;
          }
LAB_004e9a31:
        }
      }
      if (local_e0 == 0) {
        local_f8 = FUN_0062ccc0(*(undefined4 *)(local_b8[0x3d] + 0x80),"fun3d\\HoverCraft.cpp");
        *(undefined4 *)(local_f8 + 0x84) = 0x4d;
      }
      local_b8[0xab] = 0;
      puVar3 = (undefined4 *)FUN_00440000(local_110,0,0,0);
      local_70 = *puVar3;
      local_6c = puVar3[1];
      local_68 = puVar3[2];
      local_b8[0xb4] = local_70;
      local_b8[0xb5] = local_6c;
      local_b8[0xb6] = local_68;
      FUN_004ee890();
      local_8 = 0xffffffff;
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    local_b4 = *(int *)(local_b4 + 0x7c);
  } while( true );
}

