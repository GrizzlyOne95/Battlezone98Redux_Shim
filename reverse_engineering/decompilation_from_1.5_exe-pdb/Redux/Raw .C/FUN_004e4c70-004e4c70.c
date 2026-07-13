
void __fastcall FUN_004e4c70(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  undefined1 local_80 [12];
  undefined4 local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  float local_64;
  float local_60;
  void *local_5c;
  int local_58;
  undefined4 local_54;
  float local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a33c;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_48 = param_1;
  if (*(int *)(param_1 + 8) != 0xd) {
    local_4c = FUN_00462630(*(undefined4 *)(param_1 + 0x14),local_14);
    local_58 = 0;
    if ((local_4c != 0) &&
       (((cVar1 = FUN_004e4b90(local_4c,1,*(undefined4 *)(local_48 + 0x10)), cVar1 != '\0' ||
         (cVar1 = FUN_004e4b90(local_4c,2,*(undefined4 *)(local_48 + 0x10)), cVar1 != '\0')) ||
        (cVar1 = FUN_004e4b90(local_4c,3,*(undefined4 *)(local_48 + 0x10)), cVar1 != '\0')))) {
      local_58 = local_4c;
      local_4c = 0;
    }
    if ((local_4c == 0) || (*(char *)(local_4c + 0x239) != '\0')) {
      if (*(int *)(local_48 + 0x150) == 0) {
        uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0xc))(local_58);
        local_4c = FUN_004e4750(uVar2);
        if (local_4c == 0) {
          FUN_005f91e0(*(undefined4 *)(local_48 + 0x10),0xe,0);
          *(undefined4 *)(local_48 + 0xc) = 0xd;
        }
        else {
          uVar2 = FUN_00462380();
          *(undefined4 *)(local_48 + 0x14) = uVar2;
          FUN_00460600(*(undefined4 *)(local_48 + 0x134));
          *(undefined4 *)(local_48 + 0x134) = 0;
          *(undefined4 *)(local_48 + 8) = 1;
          *(undefined4 *)(local_48 + 0xc) = 1;
          puVar3 = (undefined4 *)(**(code **)(*(int *)(local_4c + 0x18) + 0xc))();
          *(undefined4 *)(local_48 + 0x140) = *puVar3;
          *(undefined4 *)(local_48 + 0x144) = puVar3[1];
          *(undefined4 *)(local_48 + 0x148) = puVar3[2];
          local_5c = operator_new(0x18);
          local_8 = 0;
          if (local_5c == (void *)0x0) {
            local_54 = 0;
          }
          else {
            iVar4 = local_48 + 0x140;
            uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0xc))(iVar4);
            local_54 = FUN_00460490(uVar2,iVar4);
          }
          local_68 = local_54;
          local_8 = 0xffffffff;
          *(undefined4 *)(local_48 + 0x134) = local_54;
          *(undefined1 *)(local_48 + 0x13c) = 1;
          *(undefined4 *)(local_48 + 0x138) = 0;
        }
      }
      else {
        *(undefined4 *)(local_48 + 0xc) = 0xd;
      }
    }
    else {
      *(int *)(local_48 + 0x80) = local_4c;
      uVar2 = FUN_004643e0(*(undefined4 *)(local_48 + 0x10),*(undefined4 *)(local_48 + 0x80));
      *(undefined4 *)(local_48 + 0x7c) = uVar2;
      if (*(int *)(local_48 + 0x7c) == 0) {
        *(undefined1 *)(local_48 + 0x14c) = 0;
      }
      else {
        uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x7c) + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(local_4c + 0x18) + 0xc))(uVar2);
        fVar5 = (float10)FUN_00462010(uVar2);
        local_6c = (float)fVar5;
        uVar2 = (**(code **)(*(int *)(local_4c + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0xc))(uVar2);
        fVar5 = (float10)FUN_00462010(uVar2);
        local_64 = (float)fVar5;
        uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x7c) + 0x18) + 0xc))();
        uVar2 = (**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0xc))(uVar2);
        fVar5 = (float10)FUN_00462010(uVar2);
        local_50 = (float)fVar5;
        if (((900.0 <= local_6c) || (local_64 <= local_50)) || (900.0 <= local_50)) {
          *(undefined1 *)(local_48 + 0x14c) = 0;
        }
        else if (*(char *)(local_48 + 0x14c) == '\0') {
          *(undefined1 *)(local_48 + 0x14c) = 1;
          FUN_005f91e0(*(undefined4 *)(local_48 + 0x10),0x1a,0);
        }
      }
      if (((*(char *)(local_48 + 0x14c) == '\0') && (*(int *)(local_48 + 0x40) != 0)) &&
         (*(int *)(local_48 + 0x44) == *(int *)(*(int *)(local_48 + 0x40) + 4) + -1)) {
        puVar3 = (undefined4 *)(**(code **)(*(int *)(*(int *)(local_48 + 0x10) + 0x18) + 0xc))();
        puVar3 = (undefined4 *)
                 (**(code **)(*(int *)(local_4c + 0x18) + 0xc))(*puVar3,puVar3[1],puVar3[2]);
        puVar3 = (undefined4 *)FUN_004401a0(local_8c,*puVar3,puVar3[1],puVar3[2]);
        local_2c = *puVar3;
        local_28 = puVar3[1];
        local_24 = puVar3[2];
        local_20 = local_2c;
        local_1c = local_28;
        local_18 = local_24;
        fVar5 = (float10)FUN_00462070(&local_20);
        local_60 = (float)fVar5;
        local_74 = 0x3d4ccccd;
        if (local_60 < 9.0) {
          fVar5 = (float10)FUN_004624d0();
          local_70 = (float)fVar5;
          if ((0.5 <= local_70) || (cVar1 = FUN_005af7b0(), cVar1 == '\0')) {
            *(undefined4 *)(local_48 + 100) = 0x3da3d70a;
            *(undefined4 *)(local_48 + 0x68) = 0x3dcccccd;
            puVar3 = (undefined4 *)FUN_00440000(local_80,0,0,0x3f800000);
            local_44 = *puVar3;
            local_40 = puVar3[1];
            local_3c = puVar3[2];
            FUN_006073a0(&local_44);
            FUN_00606f70(&local_20);
          }
          else {
            *(undefined4 *)(local_48 + 0xc) = 0xd;
          }
          goto LAB_004e5250;
        }
        if (local_60 < 64.0) {
          *(undefined4 *)(local_48 + 100) = 0x3da3d70a;
          *(undefined4 *)(local_48 + 0x68) = 0x3dcccccd;
          puVar3 = (undefined4 *)FUN_00440000(local_98,0,0,0x3f800000);
          local_38 = *puVar3;
          local_34 = puVar3[1];
          local_30 = puVar3[2];
          FUN_006073a0(&local_38);
          FUN_00606f70(&local_20);
          goto LAB_004e5250;
        }
      }
      *(undefined4 *)(local_48 + 0x18) = 0;
    }
  }
LAB_004e5250:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

