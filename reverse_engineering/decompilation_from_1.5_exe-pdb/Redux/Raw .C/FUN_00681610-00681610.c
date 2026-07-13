
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00681610(int *param_1)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int *piVar5;
  Quaternion local_80 [16];
  undefined1 local_70 [16];
  int local_60;
  undefined4 *local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  void *local_4c;
  int local_48;
  undefined4 *local_44;
  float local_40;
  int local_3c;
  int local_38;
  int *local_34;
  char local_2e;
  char local_2d;
  int *local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((param_1 != (int *)0x0) && (iVar2 = FUN_00684ca0(0), iVar2 != 0)) {
    local_58 = param_1[0x26];
    local_60 = param_1[0x25];
    if (local_58 != 0) {
      local_2c = (int *)param_1[0x32];
      local_34 = (int *)param_1[0x30];
      if (local_2c != (int *)0x0) {
        local_38 = *param_1 + 0x20;
        pfVar3 = (float *)FUN_0081f1e0(local_70,local_38);
        local_28 = *pfVar3;
        local_24 = pfVar3[1];
        local_20 = pfVar3[2];
        local_1c = pfVar3[3];
        local_18 = local_28;
        local_14 = local_24;
        local_10 = local_20;
        local_c = local_1c;
        uVar4 = Ogre::Quaternion::Quaternion(local_80,local_1c,local_28,local_24,-local_20);
        (**(code **)(*local_2c + 0x24))(uVar4);
        (**(code **)(*local_2c + 0x2c))
                  ((float)(*(double *)(local_38 + 0x28) - (double)_DAT_025f8e4c),
                   (float)*(double *)(local_38 + 0x30),
                   (float)(-*(double *)(local_38 + 0x38) - (double)_DAT_025f8e54));
        piVar5 = (int *)FUN_0062c840();
        if ((param_1 == piVar5) && (iVar2 = ___scrt_is_user_matherr_present(), iVar2 == 0)) {
          local_2d = '\x01';
        }
        else {
          local_2d = '\0';
        }
        local_2e = local_2d;
        if (((DAT_008ead0c == 0) || (local_2d == '\0')) ||
           ((cVar1 = FUN_004e9690(), cVar1 == '\0' && (*(int *)(*param_1 + 0x84) != 4)))) {
          (**(code **)(*local_2c + 0x1a8))(0,1);
        }
        else {
          local_40 = *(float *)(*param_1 + 0xd0);
          if ((*(uint *)(*param_1 + 0x14) & 0x50000000) == 0) {
            if ((local_40 < 0.001) || (0.999 < local_40)) {
              if (param_1[0x28] != 0) {
                local_5c = (undefined4 *)param_1[0x28];
                local_44 = local_5c;
                if (local_5c == (undefined4 *)0x0) {
                  local_50 = 0;
                }
                else {
                  local_50 = (**(code **)*local_5c)(1);
                }
                param_1[0x28] = 0;
              }
              if (local_40 <= 0.999) {
                (**(code **)(*local_2c + 0x1a8))(1,1);
                (**(code **)(*local_34 + 0xa8))(DAT_008ed6a8);
              }
              else {
                (**(code **)(*local_2c + 0x1a8))(0,1);
              }
            }
            else {
              (**(code **)(*local_34 + 0xa8))(DAT_008ed0e4);
              (**(code **)(*local_2c + 0x1a8))(1,1);
              local_3c = param_1[0x28];
              if (local_3c == 0) {
                local_4c = operator_new(0x14);
                if (local_4c == (void *)0x0) {
                  local_48 = 0;
                }
                else {
                  local_48 = FUN_006616a0(local_34);
                }
                local_54 = local_48;
                local_3c = local_48;
                param_1[0x28] = local_48;
              }
              FUN_006618b0(local_40);
            }
          }
          else {
            (**(code **)(*local_2c + 0x1a8))(0,1);
          }
        }
        (**(code **)(*local_34 + 200))(1);
      }
    }
  }
  FUN_0083e885();
  return;
}

