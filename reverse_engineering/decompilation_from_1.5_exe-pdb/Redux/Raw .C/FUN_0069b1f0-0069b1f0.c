
undefined4
FUN_0069b1f0(undefined4 param_1,float *param_2,int param_3,undefined4 param_4,int param_5,
            int param_6,undefined4 param_7,int *param_8)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  float10 fVar4;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  float local_1c;
  int local_18;
  char *local_14;
  char *local_10;
  int local_c;
  char local_5;
  
  for (local_c = *param_8;
      (*(char *)(local_c * 0x50 + param_6) != ';' && (*(char *)(local_c * 0x50 + param_6) != ','));
      local_c = local_c + 1) {
  }
  local_18 = param_3 + -1;
  switch(local_18) {
  case 0:
    FUN_006978d0(param_1,*param_8,local_c + -1,param_4,param_5,param_6,param_7,local_24,&local_1c,
                 local_20);
    *param_2 = local_1c;
    *param_8 = local_c + 1;
    break;
  case 1:
    fVar4 = (float10)FUN_006978d0(param_1,*param_8,local_c + -1,param_4,param_5,param_6,param_7,
                                  local_24,&local_1c,local_20);
    *param_2 = (float)fVar4;
    *param_8 = local_c + 1;
    break;
  case 2:
    FUN_006978d0(param_1,*param_8,local_c + -1,param_4,param_5,param_6,param_7,local_24,&local_1c,
                 local_20);
    iVar2 = *param_8;
    *param_2 = *(float *)(param_5 + iVar2 * 8);
    param_2[1] = *(float *)(param_5 + 4 + iVar2 * 8);
    *param_8 = local_c + 1;
    break;
  case 3:
    *param_8 = *param_8 + 1;
    *(undefined1 *)param_2 = *(undefined1 *)(*param_8 * 0x50 + param_6);
    *param_8 = *param_8 + 2;
    *param_8 = *param_8 + 1;
    break;
  default:
    return 0xffffffff;
  case 9:
    local_10 = (char *)(*param_8 * 0x50 + param_6);
    pcVar3 = local_10 + 1;
    do {
      local_5 = *local_10;
      local_10 = local_10 + 1;
    } while (local_5 != '\0');
    strncpy((char *)param_2,(char *)(*param_8 * 0x50 + param_6 + 1),
            (size_t)(local_10 + (-2 - (int)pcVar3)));
    local_14 = (char *)(*param_8 * 0x50 + param_6);
    pcVar3 = local_14 + 1;
    do {
      cVar1 = *local_14;
      local_14 = local_14 + 1;
    } while (cVar1 != '\0');
    *(char *)((int)param_2 + (int)(local_14 + (-2 - (int)pcVar3))) = '\0';
    *param_8 = *param_8 + 1;
    *param_8 = *param_8 + 1;
  }
  return 0;
}

