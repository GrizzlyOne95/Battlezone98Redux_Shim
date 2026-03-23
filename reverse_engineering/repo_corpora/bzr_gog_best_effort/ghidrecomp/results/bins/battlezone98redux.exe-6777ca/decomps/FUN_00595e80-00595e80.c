
void __thiscall FUN_00595e80(int *param_1,int *param_2,int param_3,undefined4 param_4)

{
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  int local_24;
  undefined4 local_20;
  int *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_44 = DAT_00920ef4;
  if (param_3 == 0) {
    local_30 = 0x3f000000;
  }
  else {
    local_30 = 0x3ecccccd;
  }
  DAT_00920ef4 = local_30;
  local_1c = param_1;
  (**(code **)(*param_1 + 0x24))
            (*(undefined4 *)param_2[2],*(undefined4 *)(param_2[2] + 4),&local_20,&local_24);
  local_40 = local_20;
  local_3c = local_24;
  FUN_005953c0(local_20,local_24,3,&local_18,&local_14,&local_10,&local_c);
  if (param_3 == 0) {
    FUN_0068afb0(DAT_00917580,local_18,local_14,local_10,local_c,param_4,0);
  }
  else {
    FUN_0068b020(DAT_00917580,local_18,local_14,local_10,local_c,param_4,0);
  }
  for (local_8 = 1; local_8 < param_2[1]; local_8 = local_8 + 1) {
    (**(code **)(*local_1c + 0x24))
              (*(undefined4 *)(param_2[2] + local_8 * 8),
               *(undefined4 *)(param_2[2] + 4 + local_8 * 8),&local_28,&local_2c);
    FUN_0068af40(DAT_00917580,local_20,local_24,local_28,local_2c,param_4,0);
    FUN_005953c0(local_28,local_2c,3,&local_18,&local_14,&local_10,&local_c);
    if (param_3 == local_8) {
      FUN_0068afb0(DAT_00917580,local_18,local_14,local_10,local_c,param_4,0);
    }
    else {
      FUN_0068b020(DAT_00917580,local_18,local_14,local_10,local_c,param_4,0);
    }
    local_20 = local_28;
    local_24 = local_2c;
  }
  if (*param_2 != 0) {
    if (param_3 < 0) {
      local_34 = 0x3e4ccccd;
    }
    else {
      local_34 = 0x3e19999a;
    }
    DAT_00920ef4 = local_34;
    if (param_3 < 0) {
      local_38 = 2;
    }
    else {
      local_38 = 0;
    }
    FUN_004c0100(DAT_00917580,local_40,local_3c + 5,local_4c,local_48,*param_2,DAT_00917550,
                 DAT_0091755c,DAT_00917584,local_38,1,0);
  }
  DAT_00920ef4 = local_44;
  return;
}

