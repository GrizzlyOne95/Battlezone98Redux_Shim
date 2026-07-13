
void FUN_007abae0(undefined4 param_1,undefined4 param_2,undefined4 param_3,int *param_4,int *param_5
                 ,int *param_6,int *param_7,int *param_8,int *param_9)

{
  undefined1 *local_44;
  undefined1 *local_40;
  undefined1 *local_3c;
  undefined1 *local_38;
  undefined1 *local_34;
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined1 *local_28;
  undefined1 *local_24;
  undefined1 *local_20;
  undefined1 local_5;
  
  if (param_4 == (int *)0x0) {
    local_20 = (undefined1 *)0x0;
  }
  else {
    local_20 = (undefined1 *)FUN_0041eda0(param_1,param_2,param_3,0);
  }
  if (param_5 == (int *)0x0) {
    local_24 = (undefined1 *)0x0;
  }
  else {
    local_24 = (undefined1 *)FUN_0041eda0(param_1,param_2,param_3,1);
  }
  if (param_6 == (int *)0x0) {
    local_28 = (undefined1 *)0x0;
  }
  else {
    local_28 = (undefined1 *)FUN_0041eda0(param_1,param_2,param_3,2);
  }
  if (param_7 == (int *)0x0) {
    local_2c = (undefined1 *)0x0;
  }
  else {
    local_2c = (undefined1 *)FUN_0041eda0(param_1,param_2,param_3,3);
  }
  if (param_8 == (int *)0x0) {
    local_30 = (undefined1 *)0x0;
  }
  else {
    local_30 = (undefined1 *)FUN_0041eda0(param_1,param_2,param_3,4);
  }
  if (param_4 != (int *)0x0) {
    if (local_20 == (undefined1 *)0x0) {
      local_34 = &DAT_008a1ad8;
    }
    else {
      local_34 = local_20;
    }
    (**(code **)(*param_4 + 0x3c))(local_34);
  }
  if (param_5 != (int *)0x0) {
    if (local_24 == (undefined1 *)0x0) {
      local_38 = &DAT_008a1ad8;
    }
    else {
      local_38 = local_24;
    }
    (**(code **)(*param_5 + 0x3c))(local_38);
  }
  if (param_6 != (int *)0x0) {
    if (local_28 == (undefined1 *)0x0) {
      local_3c = &DAT_008a1ad8;
    }
    else {
      local_3c = local_28;
    }
    (**(code **)(*param_6 + 0x3c))(local_3c);
  }
  if (param_7 != (int *)0x0) {
    if (local_2c == (undefined1 *)0x0) {
      local_40 = &DAT_008a1ad8;
    }
    else {
      local_40 = local_2c;
    }
    (**(code **)(*param_7 + 0x3c))(local_40);
  }
  if (param_8 != (int *)0x0) {
    if (local_30 == (undefined1 *)0x0) {
      local_44 = &DAT_008a1ad8;
    }
    else {
      local_44 = local_30;
    }
    (**(code **)(*param_8 + 0x3c))(local_44);
  }
  if (param_9 != (int *)0x0) {
    if ((((local_20 == (undefined1 *)0x0) && (local_24 == (undefined1 *)0x0)) &&
        (local_28 == (undefined1 *)0x0)) &&
       ((local_2c == (undefined1 *)0x0 && (local_30 == (undefined1 *)0x0)))) {
      local_5 = 0;
    }
    else {
      local_5 = 1;
    }
    (**(code **)(*param_9 + 0x24))(local_5);
  }
  return;
}

