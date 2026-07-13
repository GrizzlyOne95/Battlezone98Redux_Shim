
void __fastcall FUN_0049e3d0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  float10 fVar5;
  undefined1 local_90 [12];
  undefined1 local_84 [12];
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  float local_58;
  float local_54;
  float local_50;
  float *local_4c;
  float *local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float *local_34;
  float *local_30;
  float *local_2c;
  int *local_28;
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
  if (*(int *)(param_1 + 8) != 0xd) {
    *(undefined4 *)(param_1 + 0x18) = 0;
    *(undefined4 *)(param_1 + 0x7c) = 0;
    local_28 = *(int **)(param_1 + 0x10);
    local_5c = *(undefined4 *)(param_1 + 0x14c);
    switch(local_5c) {
    case 0:
      cVar1 = (**(code **)(*local_28 + 0x6c))();
      if (cVar1 != '\0') {
        local_34 = (float *)(**(code **)(*(int *)(*(int *)(local_24 + 0x10) + 0x18) + 0xc))();
        fVar5 = (float10)FUN_00462010(local_24 + 0x34,local_34);
        local_60 = (float)fVar5;
        iVar2 = FUN_0049c590();
        local_38 = *(float *)(iVar2 + 0xc);
        if (local_38 * local_38 <= local_60) {
          *(undefined4 *)(local_24 + 0x14c) = 1;
        }
        else {
          *(undefined1 *)(local_24 + 0x13d) = 1;
          local_68 = local_38 + 5.0;
          fVar5 = (float10)FUN_00417910(local_60);
          local_64 = (float)fVar5;
          local_58 = local_68 / local_64;
          local_44 = *(float *)(local_24 + 0x34) +
                     (*local_34 - *(float *)(local_24 + 0x34)) * local_58;
          *(float *)(*(int *)(*(int *)(local_24 + 0x40) + 8) + -8 +
                    *(int *)(*(int *)(local_24 + 0x40) + 4) * 8) = local_44;
          *(float *)(local_24 + 0x34) = local_44;
          local_54 = *(float *)(local_24 + 0x3c) +
                     (local_34[2] - *(float *)(local_24 + 0x3c)) * local_58;
          *(float *)(*(int *)(*(int *)(local_24 + 0x40) + 8) + -4 +
                    *(int *)(*(int *)(local_24 + 0x40) + 4) * 8) = local_54;
          *(float *)(local_24 + 0x34) = local_54;
          *(undefined4 *)(local_24 + 0x14c) = 4;
        }
      }
      FUN_00602420();
      break;
    case 1:
      local_30 = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      fVar5 = (float10)FUN_00462010(local_24 + 0x140,local_30);
      local_3c = (float)fVar5;
      if (*(float *)(local_24 + 0x154) <= local_3c) {
        uVar4 = FUN_004643e0(*(undefined4 *)(local_24 + 0x10),0);
        *(undefined4 *)(local_24 + 0x7c) = uVar4;
      }
      else {
        FUN_00602420();
        puVar3 = (undefined4 *)
                 FUN_00440000(local_84,*(float *)(local_24 + 0x140) - *local_30,0,
                              *(float *)(local_24 + 0x148) - local_30[2]);
        local_14 = *puVar3;
        local_10 = puVar3[1];
        local_c = puVar3[2];
        FUN_00607320(&local_14);
        local_4c = (float *)FUN_00462490();
        local_6c = (*(float *)(local_24 + 0x140) - *local_30) * *local_4c +
                   (*(float *)(local_24 + 0x148) - local_30[2]) * local_4c[2];
        fVar5 = (float10)FUN_00417910(local_3c);
        local_70 = (float)fVar5;
        if (local_70 * 0.9 < local_6c) {
          (**(code **)(*local_28 + 0x60))();
          *(undefined4 *)(local_24 + 0x14c) = 2;
        }
      }
      break;
    case 2:
      cVar1 = (**(code **)(*local_28 + 0x68))();
      if (cVar1 != '\0') {
        *(undefined4 *)(local_24 + 0x14c) = 3;
      }
      break;
    case 3:
      cVar1 = FUN_004723d0();
      if (cVar1 == '\0') {
        (**(code **)(*local_28 + 100))();
        *(undefined4 *)(local_24 + 0xc) = 0xd;
      }
      FUN_00602420();
      break;
    case 4:
      local_2c = (float *)(**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x18) + 0xc))();
      fVar5 = (float10)FUN_00462010(local_24 + 0x140,local_2c);
      local_50 = (float)fVar5;
      iVar2 = FUN_0049c590();
      local_40 = *(float *)(iVar2 + 0xc);
      if (local_50 <= local_40 * local_40) {
        uVar4 = FUN_004643e0(*(undefined4 *)(local_24 + 0x10),0);
        *(undefined4 *)(local_24 + 0x7c) = uVar4;
      }
      else {
        FUN_00602420();
        puVar3 = (undefined4 *)
                 FUN_00440000(local_90,*(float *)(local_24 + 0x140) - *local_2c,0,
                              *(float *)(local_24 + 0x148) - local_2c[2]);
        local_20 = *puVar3;
        local_1c = puVar3[1];
        local_18 = puVar3[2];
        FUN_00607320(&local_20);
        local_48 = (float *)FUN_00462490();
        local_74 = (*(float *)(local_24 + 0x140) - *local_2c) * *local_48 +
                   (*(float *)(local_24 + 0x148) - local_2c[2]) * local_48[2];
        fVar5 = (float10)FUN_00417910(local_50);
        local_78 = (float)fVar5;
        if (local_78 * 0.9 < local_74) {
          (**(code **)(*local_28 + 0x60))();
          *(undefined4 *)(local_24 + 0x14c) = 2;
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

