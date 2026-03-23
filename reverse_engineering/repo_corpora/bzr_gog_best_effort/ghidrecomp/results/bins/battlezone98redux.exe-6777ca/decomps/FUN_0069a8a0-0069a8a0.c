
undefined4
FUN_0069a8a0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            ,int param_6,undefined4 param_7)

{
  char cVar1;
  float10 fVar2;
  undefined1 local_20 [4];
  int local_1c;
  undefined4 local_18;
  char *local_14;
  char *local_10;
  int *local_c;
  char local_5;
  
  local_18 = 0;
  local_c = (int *)FUN_006998c0(param_1,param_2);
  if (local_c == (int *)0x0) {
    local_18 = 0xfffffffe;
  }
  else {
    local_1c = *local_c + -1;
    switch(local_1c) {
    case 0:
      fVar2 = (float10)FUN_006978d0(param_1,1,param_3 + -1,param_4,param_5,param_6,param_7,local_20,
                                    local_c + 3,&local_18);
      *(double *)(local_c + 4) = (double)fVar2;
      break;
    case 1:
      fVar2 = (float10)FUN_006978d0(param_1,1,param_3 + -1,param_4,param_5,param_6,param_7,local_20,
                                    local_c + 3,&local_18);
      *(double *)(local_c + 4) = (double)fVar2;
      break;
    case 2:
      fVar2 = (float10)FUN_006978d0(param_1,1,param_3 + -1,param_4,param_5,param_6,param_7,local_20,
                                    local_c + 3,&local_18);
      *(double *)(local_c + 4) = (double)fVar2;
      break;
    case 3:
      local_c[3] = (int)*(char *)(param_6 + 0xa0);
      break;
    default:
      local_18 = 0xffffffff;
      break;
    case 9:
      local_10 = (char *)(param_6 + 0x50);
      do {
        local_5 = *local_10;
        local_10 = local_10 + 1;
      } while (local_5 != '\0');
      strncpy((char *)local_c[2],(char *)(param_6 + 0x51),
              (size_t)(local_10 + (-2 - (param_6 + 0x51))));
      local_14 = (char *)(param_6 + 0x50);
      do {
        cVar1 = *local_14;
        local_14 = local_14 + 1;
      } while (cVar1 != '\0');
      local_14[(local_c[2] + -2) - (param_6 + 0x51)] = '\0';
    }
  }
  return local_18;
}

