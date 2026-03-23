
void __fastcall FUN_0056bcd0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  float local_64;
  float local_60;
  int local_5c;
  float local_58;
  int *local_54;
  undefined4 local_50;
  undefined2 *local_4c;
  undefined1 local_48 [4];
  int local_44;
  int local_40;
  uint local_3c;
  int local_38;
  undefined1 local_34 [4];
  uint local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined2 local_1c;
  int local_1a [4];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = param_1;
  if (DAT_00917f4c == '\0') {
    local_3c = FUN_00822e60();
    local_30 = FUN_00822d90();
    if ((DAT_00917f44 < 1) && (cVar1 = FUN_0049a000(), cVar1 != '\0')) {
      local_30 = local_30 / 1000;
      if (local_30 + 2 < *(uint *)(local_2c + 0x44)) {
        *(uint *)(local_2c + 0x44) = local_30 - 1;
      }
      if (*(uint *)(local_2c + 0x44) < local_30) {
        FUN_004ff080(local_30,0x7fffffff,0x7fffffff);
        *(uint *)(local_2c + 0x44) = local_30;
      }
    }
    if ((*(int *)(local_2c + 0x18) != 0) && (local_40 = FUN_00417c70(), local_40 != 0)) {
      local_50 = (**(code **)(*(int *)(local_40 + 0x18) + 0xc))();
      local_38 = 0;
      FID_conflict_begin(local_34);
      while( true ) {
        uVar2 = FID_conflict_end(local_68);
        cVar1 = FID_conflict_operator__(uVar2);
        if (cVar1 == '\0') break;
        puVar3 = (undefined4 *)FUN_004221e0();
        local_28 = *puVar3;
        local_24 = 0;
        iVar4 = FUN_004221e0();
        local_20 = *(undefined4 *)(iVar4 + 4);
        fVar6 = (float10)FUN_00462010(&local_28,local_50);
        local_60 = (float)fVar6;
        local_58 = local_60;
        iVar4 = FUN_004221e0();
        iVar5 = FUN_004221e0();
        if (local_58 <= *(float *)(iVar4 + 8) * *(float *)(iVar5 + 8)) {
          local_38 = local_38 + 1;
        }
        FUN_0056cc10();
      }
      FID_conflict_begin(local_48);
      while( true ) {
        uVar2 = FID_conflict_end(local_6c);
        cVar1 = FID_conflict_operator__(uVar2);
        if (cVar1 == '\0') break;
        puVar3 = (undefined4 *)FUN_00421ec0(local_50);
        iVar4 = FUN_005cbfe0(*puVar3);
        if (iVar4 != 0) {
          local_38 = local_38 + 1;
        }
        FUN_00421ee0();
      }
      if (0 < local_38) {
        fVar6 = (float10)FUN_00822d70();
        local_64 = (float)fVar6;
        *(float *)(local_2c + 0x3c) = local_64 + *(float *)(local_2c + 0x3c);
        if (*(float *)(local_2c + 0x40) + 1.0 <= *(float *)(local_2c + 0x3c)) {
          FUN_00626070(*(float *)(local_2c + 0x3c) - *(float *)(local_2c + 0x40));
          *(undefined4 *)(local_2c + 0x40) = *(undefined4 *)(local_2c + 0x3c);
        }
      }
    }
    if ((*(int *)(local_2c + 0x34) != 0) && (iVar4 = FUN_004f6b10(), iVar4 != 0)) {
      *(undefined4 *)(local_2c + 0x34) = 0;
    }
    cVar1 = FUN_00571c30();
    if (cVar1 != '\0') {
      if ((DAT_00917f54 < 1) || (local_5c = FUN_00625f80(), local_5c < DAT_00917f54)) {
        if (0 < DAT_00917f44) {
          if (*(int *)(local_2c + 0x34) != 0) {
            *(undefined4 *)(local_2c + 0x34) = 0;
            FUN_004f6ae0(DAT_00917f44 * 0x3c,0x78,0x3c);
          }
          local_44 = FUN_004f6b10();
          if (local_44 < 1) {
            DAT_00917f4c = '\x01';
            FUN_005d48b0();
          }
          else {
            if (local_3c + 10000 < *(uint *)(local_2c + 0x38)) {
              *(uint *)(local_2c + 0x38) = local_3c;
            }
            if ((*(uint *)(local_2c + 0x38) < local_3c) || (local_44 < 1)) {
              *(uint *)(local_2c + 0x38) = local_3c + 10000;
              local_4c = &local_1c;
              local_1c = 0x5450;
              local_54 = local_1a;
              local_1a[0] = local_44;
              FUN_00575890(&local_1c,6,0,1);
            }
          }
        }
      }
      else {
        DAT_00917f4c = '\x01';
        FUN_005d48b0();
      }
    }
  }
  FUN_0083e885();
  return;
}

