
/* WARNING: Removing unreachable block (ram,0x00575392) */

void __thiscall
FUN_00574cb0(undefined4 param_1,undefined4 param_2,short param_3,char *param_4,uint param_5)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined1 *puVar7;
  int *piVar8;
  uint uVar9;
  undefined1 local_13c [16];
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined4 local_124;
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  undefined1 local_114 [4];
  undefined1 local_110 [4];
  undefined1 local_10c [4];
  undefined1 local_108 [4];
  undefined1 local_104 [4];
  undefined1 local_100 [4];
  undefined1 local_fc [4];
  undefined1 local_f8 [4];
  undefined1 local_f4 [4];
  undefined1 local_f0 [4];
  undefined1 local_ec [4];
  undefined4 local_e8;
  undefined4 local_e4;
  char *local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  char *local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  int local_c0;
  char *local_bc;
  uint *local_b8;
  uint local_b4;
  int local_b0;
  int local_ac;
  char *local_a8;
  undefined1 local_a4 [4];
  char *local_a0;
  undefined4 local_9c;
  int local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  byte *local_88;
  char *local_84;
  int local_80;
  undefined1 local_7c;
  undefined1 local_7b;
  undefined1 uStack_7a;
  undefined1 local_79;
  uint local_78;
  undefined1 local_68;
  undefined1 local_67;
  int local_64;
  int *local_60;
  undefined1 local_5a;
  undefined1 local_59;
  uint local_58;
  undefined1 local_54 [4];
  undefined1 local_50 [24];
  char local_38 [32];
  undefined1 uStack_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b840;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_124 = param_1;
  if (*param_4 == 'z') {
    local_80 = (byte)param_4[1] - 0x4c;
    switch(param_4[1]) {
    case 'L':
      local_a8 = param_4 + 2;
      local_a0 = param_4 + 4;
      local_d0 = param_4 + 5;
      if (7 < param_5) {
        strncpy(local_38,local_d0,0x21);
        local_9c = 0x20;
        uStack_18 = 0;
        FUN_00574b20(local_13c,&param_3);
        basic_string<>(local_38);
        local_8 = 1;
        FUN_00578500(local_13c,*(undefined2 *)local_a8,local_50,*local_a0);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      break;
    case 'R':
      local_ac = FUN_005771b0(param_3,local_14);
      if (local_ac != 0) {
        *(undefined1 *)(local_ac + 0x18) = 1;
      }
      break;
    case 'd':
      if (param_3 != DAT_009180d4) {
        local_bc = param_4 + 2;
        local_e0 = param_4 + 4;
        local_c4 = *(undefined4 *)local_e0;
        local_b0 = FUN_005771b0(*(undefined2 *)local_bc,local_14);
        if (local_b0 != 0) {
          FUN_00578ed0(&local_c4);
        }
      }
      break;
    case 'r':
      local_98 = FUN_007659f0();
      if ((local_98 != 0) && (local_64 = FUN_00578380(), local_64 != 0)) {
        FUN_00420260(local_54);
        FID_conflict_begin(local_a4);
        while (cVar1 = FUN_00420f10(local_a4), cVar1 != '\0') {
          vector<>();
          local_8 = 0;
          FUN_00422150();
          iVar5 = FUN_004bb390();
          FUN_00579020(iVar5 + 8);
          local_5a = 0x7a;
          puVar2 = (undefined4 *)FID_conflict_end(local_128);
          local_cc = *puVar2;
          FUN_00578fd0(local_f4,local_cc,&local_5a);
          local_59 = 0x75;
          puVar2 = (undefined4 *)FID_conflict_end(local_114);
          local_d8 = *puVar2;
          FUN_00578fd0(local_fc,local_d8,&local_59);
          puVar2 = (undefined4 *)FID_conflict_end(local_ec);
          local_dc = *puVar2;
          FUN_0057b140(local_104,local_dc,local_64 + 0x28,local_64 + 0x2a);
          puVar2 = (undefined4 *)FID_conflict_end(local_11c);
          local_d4 = *puVar2;
          iVar5 = FUN_00422150();
          iVar5 = iVar5 + 4;
          uVar4 = FUN_00422150(iVar5);
          FUN_0057b140(local_10c,local_d4,uVar4,iVar5);
          FUN_00422150();
          local_94 = FUN_004bb390();
          local_7c = (undefined1)((uint)local_94 >> 0x10);
          local_7b = (undefined1)((uint)local_94 >> 8);
          uStack_7a = (undefined1)local_94;
          puVar2 = (undefined4 *)FID_conflict_end(local_120);
          local_e4 = *puVar2;
          FUN_0057b140(local_f0,local_e4,&local_7c,&local_79);
          puVar2 = (undefined4 *)FID_conflict_end(local_f8);
          local_c8 = *puVar2;
          puVar7 = local_100;
          FUN_00422150(puVar7);
          puVar2 = (undefined4 *)FID_conflict_end(puVar7);
          uVar4 = *puVar2;
          puVar7 = local_108;
          FUN_00422150(puVar7,uVar4);
          puVar2 = (undefined4 *)FID_conflict_begin(puVar7);
          FUN_0057b1b0(local_110,local_c8,*puVar2,uVar4);
          FUN_00428570();
          cVar1 = FUN_004221b0(local_a4);
          local_b4 = (uint)(cVar1 != '\0');
          uVar9 = local_b4;
          uVar4 = FUN_004bb390(local_b4);
          uVar6 = get(uVar4);
          FUN_007596b0(param_3,uVar6,uVar4,uVar9);
          local_8 = 0xffffffff;
          FUN_00579000();
        }
        local_68 = 0x7a;
        local_67 = 0x52;
        FUN_007596b0(param_3,&local_68,2,1);
      }
      break;
    case 'u':
      if (param_3 != DAT_009180d4) {
        if (param_5 < 0xb) {
          FUN_007d6c70("Received Invalid Player Data Packet from %u, received size %lu\n",param_3,
                       param_5);
        }
        else {
          local_84 = param_4 + 2;
          local_b8 = (uint *)(param_4 + 4);
          local_88 = (byte *)(param_4 + 8);
          local_78 = (uint)*local_88 * 0x10000 + (uint)(byte)param_4[9] * 0x100 +
                     (uint)(byte)param_4[10] + 0xb;
          if (param_5 == local_78) {
            local_60 = (int *)(param_4 + 0xb);
            local_8c = param_5 - ((int)local_60 - (int)param_4);
            local_58 = *local_b8;
            local_90 = FUN_005771b0(*(undefined2 *)local_84,local_14);
            if (local_90 != 0) {
              FUN_00578e00(&local_58);
              FUN_0041ff50();
              puVar7 = local_118;
              FUN_00578e00(&local_58);
              puVar2 = (undefined4 *)FID_conflict_begin(puVar7);
              uVar4 = *puVar2;
              pcVar3 = (char *)((int)local_60 + local_8c);
              puVar7 = local_12c;
              piVar8 = local_60;
              local_e8 = uVar4;
              FUN_00578e00(&local_58);
              FUN_0057b140(puVar7,uVar4,piVar8,pcVar3);
              if (local_58 == 0xc) {
                FUN_00573930(param_3,local_8c,local_60);
              }
              else if (local_58 == 0xd) {
                FUN_004d22d0();
              }
              else if (local_58 == 0x13) {
                if (((local_8c == 4) && (*local_60 == 0)) &&
                   (local_c0 = FUN_005779d0(*(undefined2 *)local_84), local_c0 != 0)) {
                  uVar4 = FUN_0081cb40("multi_message","defeated");
                  FUN_0056fcb0("%s %s",local_c0,uVar4);
                }
              }
              else if ((local_58 != 0) && (iVar5 = FUN_0045ca50(), iVar5 != 0)) {
                FUN_004b77a0(*(undefined2 *)local_84,local_8c,local_58 & 0xffff,local_60);
              }
            }
          }
          else {
            FUN_007d6c70("Received Incomplete Player Data Packet from %u, received size %lu, expected %lu\n"
                         ,param_3,param_5,local_78);
          }
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

