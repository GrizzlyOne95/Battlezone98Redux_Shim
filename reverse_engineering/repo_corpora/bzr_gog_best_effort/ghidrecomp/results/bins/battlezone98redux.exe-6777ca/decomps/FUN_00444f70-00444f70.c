
void FUN_00444f70(int param_1,double param_2,double param_3,double param_4,float *param_5,
                 undefined4 *param_6,int *param_7)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined8 uVar4;
  undefined1 local_80 [12];
  float local_74;
  float local_70;
  float local_6c;
  undefined4 local_68;
  float local_64;
  undefined8 local_60;
  int local_58;
  float local_54;
  int local_50;
  float local_4c;
  undefined4 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_70 = (float)param_2;
  local_6c = (float)param_4;
  FUN_00785730(param_2,param_4,&local_4c,&local_14);
  local_58 = 0;
  for (local_48 = DAT_0260d0f8; local_48 != (undefined4 *)0x0; local_48 = (undefined4 *)*local_48) {
    local_50 = local_48[2];
    if (local_50 != param_1) {
      puVar1 = (undefined4 *)FUN_0062caa0(local_80,local_50);
      local_20 = *puVar1;
      local_1c = puVar1[1];
      local_18 = (float)puVar1[2];
      uVar4 = FUN_00444e40(local_70,local_6c,local_20,local_1c);
      local_60 = uVar4;
      fVar3 = (float10)FUN_00444e70(uVar4,uVar4);
      local_74 = (float)fVar3;
      if (local_74 <= local_18 * local_18) {
        local_38 = (float)param_2;
        local_34 = (float)param_3 + 1.0;
        local_30 = (float)param_4;
        local_2c = 0;
        local_28 = 0xbf800000;
        local_24 = 0;
        local_68 = 0;
        local_64 = 3.4028235e+38;
        iVar2 = FUN_00445380(local_38,local_34,local_30,0,0xbf800000,0,local_50,local_34 - local_4c,
                             &local_68,&local_64,&local_44,0,1);
        if (((iVar2 != 0) && (local_54 = local_34 - local_64, (double)local_54 < param_3 + 1.0)) &&
           (local_4c < local_54)) {
          local_14 = local_44;
          local_10 = local_40;
          local_c = local_3c;
          local_58 = local_50;
          local_4c = local_54;
        }
      }
    }
  }
  if (param_5 != (float *)0x0) {
    *param_5 = local_4c;
  }
  if (param_6 != (undefined4 *)0x0) {
    *param_6 = local_14;
    param_6[1] = local_10;
    param_6[2] = local_c;
  }
  if (param_7 != (int *)0x0) {
    *param_7 = local_58;
  }
  FUN_0083e885();
  return;
}

