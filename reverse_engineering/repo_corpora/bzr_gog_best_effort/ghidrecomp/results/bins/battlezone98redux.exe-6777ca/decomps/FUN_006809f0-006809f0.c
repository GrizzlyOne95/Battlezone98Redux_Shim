
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006809f0(int param_1)

{
  int iVar1;
  float *pfVar2;
  undefined4 uVar3;
  Quaternion local_58 [16];
  undefined1 local_48 [16];
  int local_38;
  int *local_34;
  int *local_30;
  int local_2c;
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
  local_2c = param_1;
  iVar1 = FUN_00684ca0(0);
  if (iVar1 != 0) {
    local_34 = *(int **)(local_2c + 0xd0);
    local_30 = *(int **)(local_2c + 0xcc);
    if ((local_34 == (int *)0x0) || (local_30 == (int *)0x0)) {
      if (*(char *)(*(int *)(*(int *)(local_2c + 0xc) + 0x34) + 0x84) != '\0') {
        FUN_0067ec70(local_2c);
        FUN_006804c0(local_2c);
      }
      local_34 = *(int **)(local_2c + 0xd0);
      local_30 = *(int **)(local_2c + 0xcc);
    }
    if ((local_34 != (int *)0x0) && (local_30 != (int *)0x0)) {
      (**(code **)(*local_30 + 0x84))(1);
      local_38 = *(int *)(local_2c + 0x14) + 0x20;
      pfVar2 = (float *)FUN_0081f1e0(local_48,local_38);
      local_28 = *pfVar2;
      local_24 = pfVar2[1];
      local_20 = pfVar2[2];
      local_1c = pfVar2[3];
      local_18 = local_28;
      local_14 = local_24;
      local_10 = local_20;
      local_c = local_1c;
      uVar3 = Ogre::Quaternion::Quaternion(local_58,local_1c,local_28,local_24,-local_20);
      (**(code **)(*local_34 + 0x24))(uVar3);
      (**(code **)(*local_34 + 0x2c))
                ((float)(*(double *)(local_38 + 0x28) - (double)_DAT_025f8e4c),
                 (float)*(double *)(local_38 + 0x30),
                 (float)(-*(double *)(local_38 + 0x38) - (double)_DAT_025f8e54));
      (**(code **)(*local_30 + 200))(7);
    }
  }
  FUN_0083e885();
  return;
}

