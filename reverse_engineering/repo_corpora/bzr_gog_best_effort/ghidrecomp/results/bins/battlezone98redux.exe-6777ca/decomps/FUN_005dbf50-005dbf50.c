
bool FUN_005dbf50(int *param_1,undefined4 *param_2,undefined4 *param_3,int *param_4,
                 undefined4 *param_5,undefined4 *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  undefined4 local_58;
  int local_4c;
  int local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  uint local_28;
  uint local_10;
  int local_8;
  
  *param_1 = 0;
  *param_4 = 0;
  *param_2 = DAT_0091755c;
  *param_5 = DAT_0091755c;
  *param_3 = 0;
  *param_6 = 0;
  iVar1 = FUN_00417c70();
  if (iVar1 != 0) {
    iVar1 = FUN_00417ca0();
    if (iVar1 == 0) {
      local_28 = 0;
      local_2c = 0;
    }
    else {
      local_28 = FUN_00417f90();
      local_2c = FUN_00417fb0();
    }
    iVar2 = FUN_00417c80();
    local_10 = 0;
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      if (iVar1 == 0) {
        local_30 = 0;
      }
      else {
        local_30 = FUN_00417f40(local_8);
      }
      if (local_30 == 0) {
        *param_3 = 0;
      }
      else if ((*(int *)(local_30 + 0x84) < 0x46) || (0x4a < *(int *)(local_30 + 0x84))) {
        *param_3 = 0;
      }
      else {
        *param_3 = *(undefined4 *)(&DAT_008ea39c + (*(int *)(local_30 + 0x84) + -0x46) * 8);
      }
      if (iVar1 == 0) {
        local_34 = 0;
      }
      else {
        local_34 = FUN_00417f60(local_8);
      }
      if (local_34 == 0) {
        *param_1 = 0;
        local_38 = 0;
      }
      else {
        *param_1 = *(int *)(local_34 + 8) + 0x38;
        iVar3 = FUN_0081cb40("names",*param_1);
        *param_1 = iVar3;
        local_38 = *(int *)(local_34 + 0xb0);
      }
      bVar4 = (byte)local_8;
      if (iVar2 < local_38) {
        local_10 = 1 << (bVar4 & 0x1f) | local_10;
      }
      if ((1 << (bVar4 & 0x1f) & local_28) != 0) {
        if ((~local_10 & local_2c & 1 << (bVar4 & 0x1f)) == 0) {
          local_3c = DAT_0091755c;
        }
        else {
          local_3c = DAT_00917560;
        }
        *param_2 = local_3c;
        break;
      }
      *param_1 = 0;
    }
    do {
      local_8 = local_8 + 1;
      if (4 < local_8) break;
      if (iVar1 == 0) {
        local_40 = 0;
      }
      else {
        local_40 = FUN_00417f40(local_8);
      }
      if (local_40 == 0) {
        *param_6 = 0;
      }
      else if ((*(int *)(local_40 + 0x84) < 0x46) || (0x4a < *(int *)(local_40 + 0x84))) {
        *param_6 = 0;
      }
      else {
        *param_6 = *(undefined4 *)(&DAT_008ea39c + (*(int *)(local_40 + 0x84) + -0x46) * 8);
      }
      if (iVar1 == 0) {
        local_44 = 0;
      }
      else {
        local_44 = FUN_00417f60(local_8);
      }
      if (local_44 == 0) {
        *param_4 = 0;
        local_4c = 0;
      }
      else {
        *param_4 = *(int *)(local_44 + 8) + 0x38;
        iVar3 = FUN_0081cb40("names",*param_4);
        *param_4 = iVar3;
        local_4c = *(int *)(local_44 + 0xb0);
      }
      bVar4 = (byte)local_8;
      if (iVar2 < local_4c) {
        local_10 = 1 << (bVar4 & 0x1f) | local_10;
      }
      if ((1 << (bVar4 & 0x1f) & local_28) != 0) {
        if ((~local_10 & local_2c & 1 << (bVar4 & 0x1f)) == 0) {
          local_58 = DAT_0091755c;
        }
        else {
          local_58 = DAT_00917560;
        }
        *param_5 = local_58;
        break;
      }
      *param_4 = 0;
    } while( true );
  }
  return *param_1 != 0;
}

