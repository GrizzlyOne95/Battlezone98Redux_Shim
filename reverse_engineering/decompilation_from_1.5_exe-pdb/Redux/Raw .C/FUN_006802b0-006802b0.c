
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_006802b0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float *pfVar3;
  Quaternion local_6c [16];
  undefined1 local_5c [16];
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int *local_34;
  char local_2d;
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
  local_4c = (*(code *)**(undefined4 **)(param_1 + 0x18))();
  local_4c = local_4c + 0x38;
  local_3c = (**(code **)(*(int *)(local_2c + 0x18) + 0x2c))();
  local_2d = '\x01';
  iVar1 = (*(code *)**(undefined4 **)(local_2c + 0x18))();
  local_48 = *(int *)(iVar1 + 0x1c);
  if (local_48 == 4) {
    local_2d = '\0';
  }
  if (local_2d != '\0') {
    local_44 = *(int *)(local_3c + 0xa4);
    if (local_44 != 0) {
      uVar2 = (**(code **)(*(int *)(local_2c + 0x18) + 0x30))(local_44,0);
      FUN_0067e260(uVar2);
    }
    local_40 = *(int *)(local_3c + 0xcc);
    if (local_40 != 0) {
      uVar2 = (**(code **)(*(int *)(local_2c + 0x18) + 0x30))(local_40,0);
      FUN_0067e430(uVar2);
    }
  }
  local_34 = *(int **)(local_3c + 0x98);
  if (local_34 != (int *)0x0) {
    local_38 = FUN_0045c4d0();
    pfVar3 = (float *)FUN_0081f1e0(local_5c,local_38);
    local_28 = *pfVar3;
    local_24 = pfVar3[1];
    local_20 = pfVar3[2];
    local_1c = pfVar3[3];
    local_18 = local_28;
    local_14 = local_24;
    local_10 = local_20;
    local_c = local_1c;
    uVar2 = Ogre::Quaternion::Quaternion(local_6c,local_1c,local_28,local_24,-local_20);
    (**(code **)(*local_34 + 0x24))(uVar2);
    (**(code **)(*local_34 + 0x2c))
              ((float)(*(double *)(local_38 + 0x28) - (double)_DAT_025f8e4c),
               (float)(*(double *)(local_38 + 0x30) - (double)_DAT_025f8e50),
               (float)(-*(double *)(local_38 + 0x38) - (double)_DAT_025f8e54));
    DAT_00920e94 = DAT_00920e94 + 1;
  }
  FUN_0083e885();
  return;
}

