
undefined4 *
FUN_006afec0(undefined4 *param_1,char *param_2,char *param_3,undefined4 param_4,undefined4 param_5,
            undefined4 *param_6)

{
  undefined4 uVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 *puVar4;
  undefined1 local_18 [8];
  undefined4 local_10;
  char *local_c;
  char *local_8;
  
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    local_8 = (char *)0x0;
  }
  else {
    local_8 = param_2;
  }
  pcVar3 = local_8;
  if ((param_3 == (char *)0x0) || (*param_3 == '\0')) {
    local_c = (char *)0x0;
  }
  else {
    local_c = param_3;
  }
  pcVar2 = local_c;
  FUN_006ae8d0();
  local_10 = getaddrinfo(pcVar3,pcVar2,param_4,param_5);
  puVar4 = (undefined4 *)FUN_006afd50(local_18,local_10);
  uVar1 = puVar4[1];
  *param_6 = *puVar4;
  param_6[1] = uVar1;
  uVar1 = param_6[1];
  *param_1 = *param_6;
  param_1[1] = uVar1;
  return param_1;
}

