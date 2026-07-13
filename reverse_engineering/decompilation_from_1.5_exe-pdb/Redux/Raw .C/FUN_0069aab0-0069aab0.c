
undefined4
FUN_0069aab0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6)

{
  char cVar1;
  void *pvVar2;
  float10 fVar3;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  char *local_1c;
  char *local_18;
  char *local_14;
  char *local_10;
  undefined4 *local_c;
  undefined1 local_8;
  char local_7;
  char local_6;
  char local_5;
  
  local_20 = 0;
  if (*(char *)(param_5 + 0x50) == '\"') {
    local_c = (undefined4 *)FUN_006994c0(10,param_5);
    local_10 = (char *)(param_5 + 0x50);
    local_24 = param_5 + 0x51;
    do {
      local_5 = *local_10;
      local_10 = local_10 + 1;
    } while (local_5 != '\0');
    local_28 = (int)local_10 - local_24;
    pvVar2 = malloc(local_28 - 2);
    local_c[2] = pvVar2;
    local_14 = (char *)(param_5 + 0x50);
    local_2c = param_5 + 0x51;
    do {
      local_6 = *local_14;
      local_14 = local_14 + 1;
    } while (local_6 != '\0');
    local_30 = (int)local_14 - local_2c;
    local_c[3] = local_30 + -2;
    local_18 = (char *)(param_5 + 0x50);
    local_34 = param_5 + 0x51;
    do {
      local_7 = *local_18;
      local_18 = local_18 + 1;
    } while (local_7 != '\0');
    local_38 = (int)local_18 - local_34;
    strncpy((char *)local_c[2],(char *)(param_5 + 0x51),local_38 - 2);
    local_1c = (char *)(param_5 + 0x50);
    local_3c = param_5 + 0x51;
    do {
      cVar1 = *local_1c;
      local_1c = local_1c + 1;
    } while (cVar1 != '\0');
    local_40 = (int)local_1c - local_3c;
    *(undefined1 *)(local_c[2] + -3 + local_40) = 0;
    local_8 = 0;
  }
  else {
    local_c = (undefined4 *)FUN_006994c0(3,param_5);
    fVar3 = (float10)FUN_006978d0(param_1,1,param_2 + -1,param_3,param_4,param_5,param_6,&local_44,
                                  local_c + 3,&local_20);
    *(double *)(local_c + 4) = (double)fVar3;
    if (local_44 != 0) {
      *local_c = 1;
    }
  }
  FUN_00699650(param_1,local_c);
  return local_20;
}

