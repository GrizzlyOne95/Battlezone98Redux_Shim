
void __fastcall FUN_005b6580(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  float10 fVar7;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined4 local_6c;
  int local_68;
  undefined *local_64;
  uint local_60;
  float local_5c;
  uint local_58;
  int local_54;
  undefined4 local_50;
  int local_4c;
  float local_48;
  undefined4 *local_44;
  int local_40;
  undefined4 local_3c;
  uint local_38;
  int local_34;
  undefined1 local_2e;
  char local_2d;
  int local_2c;
  char local_25;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  local_38 = (**(code **)(*(int *)(*(int *)(param_1 + 0x2c) + 0x18) + 4))();
  local_25 = '\x01';
  cVar1 = FUN_005b5100();
  if (cVar1 == '\0') {
    local_50 = FUN_00462590();
    cVar1 = FUN_005b5140();
    if (cVar1 != '\0') {
      iVar2 = FUN_005e10b0();
      iVar3 = FUN_005e1190();
      if (iVar3 <= iVar2) {
        *(undefined4 *)(local_24 + 0x4c) = 6;
        goto LAB_005b69c5;
      }
    }
    cVar1 = FUN_005b6fa0();
    if (cVar1 == '\0') {
      while( true ) {
        local_5c = 1e+30;
        local_40 = 0;
        puVar4 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_24 + 0x2c) + 0x18) + 0xc))();
        local_14 = *puVar4;
        local_10 = puVar4[1];
        local_c = puVar4[2];
        cVar1 = FUN_0041fc90();
        if (cVar1 != '\0') break;
        local_2e = FUN_0048fca0(local_14,local_c);
        local_64 = &DAT_025cf554;
        FUN_00422170();
        puVar4 = (undefined4 *)FID_conflict_begin(local_78);
        local_3c = *puVar4;
        while( true ) {
          uVar5 = FID_conflict_end(local_70);
          cVar1 = FID_conflict_operator__(uVar5);
          if (cVar1 == '\0') break;
          piVar6 = (int *)FUN_00421ec0();
          local_2c = *piVar6;
          if (local_25 == '\0') {
            if (*(char *)(local_2c + 0x238) == '\0') goto LAB_005b6761;
          }
          else {
            *(undefined1 *)(local_2c + 0x238) = 0;
LAB_005b6761:
            cVar1 = FUN_005b5040(local_38);
            if ((cVar1 != '\0') && (cVar1 = FUN_004625f0(local_38), cVar1 == '\0')) {
              local_44 = (undefined4 *)(**(code **)(*(int *)(local_2c + 0x18) + 0xc))();
              cVar1 = FUN_0058fd10(*local_44,local_44[2],local_2e);
              if (cVar1 == '\0') {
                *(undefined1 *)(local_2c + 0x238) = 1;
              }
              else {
                fVar7 = (float10)FUN_004620b0(*local_44,local_44[1],local_44[2],local_14,local_10,
                                              local_c);
                local_48 = (float)fVar7;
                if (local_48 < local_5c) {
                  local_40 = local_2c;
                  local_5c = local_48;
                }
              }
            }
          }
          FUN_0046b260(local_74,0);
        }
        local_25 = '\0';
        if (local_40 == 0) {
          if ((&DAT_02a13cd8)[local_38] != '\0') {
            FUN_005b6500(*(undefined4 *)(local_24 + 0x10));
            local_60 = local_38;
            if (0xf < local_38) {
              ___report_rangecheckfailure();
            }
            (&DAT_02a13cd8)[local_60] = 0;
          }
          cVar1 = FUN_005b5140();
          if (cVar1 == '\0') {
            *(undefined4 *)(local_24 + 0x4c) = 3;
          }
          else {
            *(undefined4 *)(local_24 + 0x4c) = 6;
          }
          goto LAB_005b69c5;
        }
        local_34 = local_40;
        puVar4 = (undefined4 *)(**(code **)(*(int *)(local_40 + 0x18) + 0xc))();
        local_20 = *puVar4;
        local_1c = puVar4[1];
        local_18 = puVar4[2];
        *(undefined4 *)(local_24 + 0x34) = local_20;
        *(undefined4 *)(local_24 + 0x38) = local_1c;
        *(undefined4 *)(local_24 + 0x3c) = local_18;
        local_68 = FUN_004666c0(*(undefined4 *)(local_24 + 0x2c),local_20,local_18);
        local_2d = *(int *)(local_68 + 0x10) != 3;
        local_58 = (uint)(byte)local_2d;
        local_54 = local_68;
        local_4c = local_68;
        if (local_68 == 0) {
          local_6c = 0;
        }
        else {
          local_6c = FUN_00460640(1);
        }
        if (local_2d != '\0') {
          (&DAT_02a13cd8)[local_38] = 1;
          puVar4 = (undefined4 *)(**(code **)(*(int *)(local_34 + 0x18) + 0xc))();
          *(undefined4 *)(local_24 + 0x34) = *puVar4;
          *(undefined4 *)(local_24 + 0x38) = puVar4[1];
          *(undefined4 *)(local_24 + 0x3c) = puVar4[2];
          uVar5 = FUN_00477590(local_34);
          *(undefined4 *)(local_24 + 0x40) = uVar5;
          *(undefined4 *)(local_24 + 0x4c) = 2;
          goto LAB_005b69c5;
        }
        *(undefined1 *)(local_34 + 0x238) = 1;
      }
      cVar1 = FUN_005b5140();
      if (cVar1 == '\0') {
        *(undefined4 *)(local_24 + 0x4c) = 3;
      }
      else {
        *(undefined4 *)(local_24 + 0x4c) = 6;
      }
    }
    else {
      *(undefined4 *)(local_24 + 0x4c) = 7;
    }
  }
  else {
    *(undefined4 *)(local_24 + 0x4c) = 3;
  }
LAB_005b69c5:
  FUN_0083e885();
  return;
}

