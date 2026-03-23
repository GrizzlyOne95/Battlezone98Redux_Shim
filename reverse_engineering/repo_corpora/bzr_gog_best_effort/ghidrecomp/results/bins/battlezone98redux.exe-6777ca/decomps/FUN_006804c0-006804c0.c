
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006804c0(int param_1)

{
  float *pfVar1;
  undefined4 uVar2;
  Quaternion local_58 [16];
  undefined1 local_48 [16];
  int local_38;
  int local_34;
  int local_30;
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
  local_34 = param_1;
  local_38 = *(int *)(param_1 + 0x14);
  local_2c = *(int **)(param_1 + 0xd0);
  if (local_2c != (int *)0x0) {
    local_30 = local_38 + 0x20;
    pfVar1 = (float *)FUN_0081f1e0(local_48,local_30);
    local_28 = *pfVar1;
    local_24 = pfVar1[1];
    local_20 = pfVar1[2];
    local_1c = pfVar1[3];
    local_18 = local_28;
    local_14 = local_24;
    local_10 = local_20;
    local_c = local_1c;
    uVar2 = Ogre::Quaternion::Quaternion(local_58,local_1c,local_28,local_24,-local_20);
    (**(code **)(*local_2c + 0x24))(uVar2);
    (**(code **)(*local_2c + 0x2c))
              ((float)(*(double *)(local_30 + 0x28) - (double)_DAT_025f8e4c),
               (float)(*(double *)(local_30 + 0x30) - (double)_DAT_025f8e50),
               (float)(-*(double *)(local_30 + 0x38) - (double)_DAT_025f8e54));
    DAT_00920e94 = DAT_00920e94 + 1;
  }
  FUN_0083e885();
  return;
}

