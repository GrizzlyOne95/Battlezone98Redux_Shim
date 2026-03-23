
void FUN_005083a0(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined1 local_74 [12];
  undefined1 local_68 [12];
  undefined1 local_5c [12];
  undefined1 local_50 [12];
  undefined4 local_44;
  float *local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_40 = (float *)FUN_004ff820(param_1,1);
  local_44 = FUN_0082ba59(param_1,2,0);
  local_3c = FUN_00446460(local_44,0x811c9dc5);
  if (local_3c < 0x44e771bd) {
    if (local_3c == 0x44e771bc) {
      puVar1 = (undefined4 *)FUN_00439de0(local_74,local_40);
      local_2c = *puVar1;
      local_28 = puVar1[1];
      local_24 = puVar1[2];
      puVar1 = (undefined4 *)FUN_004ff7e0();
      *puVar1 = local_2c;
      puVar1[1] = local_28;
      puVar1[2] = local_24;
    }
    else if (local_3c < 0x24f7b5b6) {
      if (local_3c == 0x24f7b5b5) {
        FUN_0082cd58(param_1,(double)local_40[5]);
      }
      else if (local_3c == 0x21f7b0fc) {
        FUN_0082cd58(param_1,(double)local_40[4]);
      }
      else if (local_3c == 0x22f7b28f) {
        FUN_0082cd58(param_1,(double)local_40[3]);
      }
    }
    else if (local_3c == 0x43430b20) {
      puVar1 = (undefined4 *)FUN_004795e0(local_68,local_40);
      local_38 = *puVar1;
      local_34 = puVar1[1];
      local_30 = puVar1[2];
      puVar1 = (undefined4 *)FUN_004ff7e0();
      *puVar1 = local_38;
      puVar1[1] = local_34;
      puVar1[2] = local_30;
    }
  }
  else if (local_3c < 0xc6a81d48) {
    if (local_3c == 0xc6a81d47) {
      FUN_0082cd58(param_1,(double)local_40[6]);
    }
    else if (local_3c < 0xb86c3f83) {
      if (local_3c == 0xb86c3f82) {
        FUN_0082cd58(param_1,(double)*local_40);
      }
      else if (local_3c == 0x78e32de5) {
        puVar1 = (undefined4 *)FUN_00439d80(local_50,local_40);
        local_20 = *puVar1;
        local_1c = puVar1[1];
        local_18 = puVar1[2];
        puVar1 = (undefined4 *)FUN_004ff7e0();
        *puVar1 = local_20;
        puVar1[1] = local_1c;
        puVar1[2] = local_18;
      }
      else if (local_3c == 0xb66c3c5c) {
        FUN_0082cd58(param_1,(double)local_40[2]);
      }
    }
    else if (local_3c == 0xb96c4115) {
      FUN_0082cd58(param_1,(double)local_40[1]);
    }
    else if (local_3c == 0xc5a81bb4) {
      FUN_0082cd58(param_1,(double)local_40[7]);
    }
  }
  else if (local_3c < 0xebf98a61) {
    if (local_3c == 0xebf98a60) {
      FUN_0082cd58(param_1,*(undefined8 *)(local_40 + 0xc));
    }
    else if (local_3c == 0xc8a8206d) {
      FUN_0082cd58(param_1,(double)local_40[8]);
    }
    else if (local_3c == 0xe179dbd8) {
      puVar1 = (undefined4 *)FUN_004560b0(local_5c,local_40);
      local_14 = *puVar1;
      local_10 = puVar1[1];
      local_c = puVar1[2];
      puVar1 = (undefined4 *)FUN_004ff7e0();
      *puVar1 = local_14;
      puVar1[1] = local_10;
      puVar1[2] = local_c;
    }
  }
  else if (local_3c == 0xecf98bf3) {
    FUN_0082cd58(param_1,*(undefined8 *)(local_40 + 10));
  }
  else if (local_3c == 0xeef98f19) {
    FUN_0082cd58(param_1,*(undefined8 *)(local_40 + 0xe));
  }
  FUN_0083e885();
  return;
}

