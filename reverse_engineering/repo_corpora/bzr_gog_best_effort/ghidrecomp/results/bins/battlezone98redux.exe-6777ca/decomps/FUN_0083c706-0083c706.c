
uint FUN_0083c706(int param_1,int *param_2)

{
  uint uVar1;
  uint *puVar2;
  uint local_24 [2];
  undefined4 local_1c;
  uint local_14 [2];
  undefined4 local_c;
  
  FUN_0083c835();
  if (*param_2 < 1) goto LAB_0083c733;
  local_c = 5;
  if (*param_2 < 4) {
LAB_0083c74e:
    if (0xff < *(int *)(param_1 + 0x28)) goto LAB_0083c733;
    if (*param_2 == 1) {
      local_14[0] = *(uint *)(param_1 + 4);
      local_1c = 0;
      puVar2 = local_24;
LAB_0083c799:
      uVar1 = FUN_0083bd73(param_1,local_14,puVar2);
    }
    else {
      if (*param_2 != 5) {
        local_c = 1;
        local_14[0] = (uint)(*param_2 == 2);
        puVar2 = local_14;
        goto LAB_0083c799;
      }
      uVar1 = FUN_0083ca81(param_1,*(undefined8 *)(param_2 + 2));
    }
    param_2[2] = uVar1;
    *param_2 = 4;
LAB_0083c7b0:
    uVar1 = uVar1 | 0x100;
  }
  else {
    if (*param_2 == 4) {
      uVar1 = param_2[2];
      if ((int)uVar1 < 0x100) goto LAB_0083c7b0;
    }
    else if (*param_2 == 5) goto LAB_0083c74e;
LAB_0083c733:
    uVar1 = FUN_0083c7b7(param_1,param_2);
  }
  return uVar1;
}

