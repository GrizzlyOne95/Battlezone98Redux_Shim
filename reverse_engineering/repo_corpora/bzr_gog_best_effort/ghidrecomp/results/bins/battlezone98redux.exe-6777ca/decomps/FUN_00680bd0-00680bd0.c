
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00680bd0(int *param_1)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  Quaternion local_9c [16];
  undefined1 local_8c [16];
  int local_7c;
  undefined4 local_78;
  undefined4 *local_74;
  undefined4 local_70;
  void *local_6c;
  int local_68;
  int *local_64;
  int local_60;
  int *local_5c;
  int *local_58;
  int local_54;
  int local_50;
  int *local_4c;
  undefined4 *local_48;
  float local_44;
  int local_40;
  int local_3c;
  int *local_38;
  char local_31;
  int *local_30;
  char local_29;
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
  iVar2 = FUN_00684ca0(0);
  if (iVar2 != 0) {
    local_38 = (int *)param_1[0x26];
    local_30 = (int *)param_1[0x25];
    if ((local_38 == (int *)0x0) && ((char)param_1[0x1d] != '\0')) {
      local_70 = FUN_00479f30(*param_1);
      FUN_0067f480(param_1);
      FUN_006802b0(local_70);
      local_38 = (int *)param_1[0x26];
      local_30 = (int *)param_1[0x25];
    }
    if (local_38 != (int *)0x0) {
      local_3c = *param_1 + 0x20;
      pfVar3 = (float *)FUN_0081f1e0(local_8c,local_3c);
      local_28 = *pfVar3;
      local_24 = pfVar3[1];
      local_20 = pfVar3[2];
      local_1c = pfVar3[3];
      local_18 = local_28;
      local_14 = local_24;
      local_10 = local_20;
      local_c = local_1c;
      uVar4 = Ogre::Quaternion::Quaternion(local_9c,local_1c,local_28,local_24,-local_20);
      (**(code **)(*local_38 + 0x24))(uVar4);
      (**(code **)(*local_38 + 0x2c))
                ((float)(*(double *)(local_3c + 0x28) - (double)_DAT_025f8e4c),
                 (float)*(double *)(local_3c + 0x30),
                 (float)(-*(double *)(local_3c + 0x38) - (double)_DAT_025f8e54));
      piVar5 = (int *)FUN_0062c840();
      if ((param_1 == piVar5) && (iVar2 = ___scrt_is_user_matherr_present(), iVar2 == 0)) {
        local_29 = '\x01';
      }
      else {
        local_29 = '\0';
      }
      local_31 = local_29;
      if (local_29 == '\0') {
        (**(code **)(*local_30 + 200))(7);
        local_4c = (int *)param_1[0x32];
        if (local_4c != (int *)0x0) {
          (**(code **)(*local_4c + 0x1a8))(0,1);
        }
        cVar1 = FUN_005ddde0();
        if (((((cVar1 != '\0') && (local_5c = (int *)FUN_005dddf0(), local_5c != (int *)0x0)) &&
             (local_50 = *(int *)(*param_1 + 0x8c), local_50 != 0)) &&
            ((local_64 = (int *)FUN_0062c840(), local_64 != (int *)0x0 &&
             (local_60 = *local_64, local_60 != 0)))) &&
           ((local_54 = *(int *)(local_60 + 0x8c), local_54 != 0 && (local_5c == param_1)))) {
          iVar2 = (**(code **)(*(int *)(local_50 + 0x18) + 4))();
          iVar6 = (**(code **)(*(int *)(local_54 + 0x18) + 4))();
          if ((iVar2 == iVar6) && (local_58 = (int *)local_5c[0x25], local_58 != (int *)0x0)) {
            (**(code **)(*local_58 + 200))(5);
          }
        }
      }
      else {
        (**(code **)(*local_30 + 200))(6);
      }
      local_44 = *(float *)(*param_1 + 0xd0);
      if ((*(uint *)(*param_1 + 0x14) & 0x50000000) == 0) {
        if ((local_44 < 0.001) || (0.999 < local_44)) {
          if (param_1[0x27] != 0) {
            local_74 = (undefined4 *)param_1[0x27];
            local_48 = local_74;
            if (local_74 == (undefined4 *)0x0) {
              local_78 = 0;
            }
            else {
              local_78 = (**(code **)*local_74)(1);
            }
            param_1[0x27] = 0;
          }
          if (0.999 < local_44) {
            (**(code **)(*local_30 + 200))(0);
          }
        }
        else {
          local_40 = param_1[0x27];
          if (local_40 == 0) {
            local_6c = operator_new(0x14);
            if (local_6c == (void *)0x0) {
              local_68 = 0;
            }
            else {
              local_68 = FUN_006616a0(local_30);
            }
            local_7c = local_68;
            local_40 = local_68;
            param_1[0x27] = local_68;
          }
          FUN_006618b0(local_44);
        }
      }
      else {
        (**(code **)(*local_30 + 200))(0);
      }
    }
  }
  FUN_0083e885();
  return;
}

