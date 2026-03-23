
undefined4 * FUN_006e8040(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined1 *puVar4;
  undefined4 *puVar5;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined4 local_8;
  
  local_8 = param_2;
  iVar2 = operator-<>(&param_3,&param_2);
  if (2 < iVar2) {
    pcVar3 = (char *)FUN_006f25a0();
    if (*pcVar3 == '\r') {
      FID_conflict_operator_(local_c,1);
      pcVar3 = (char *)FUN_006f25a0();
      if (*pcVar3 == '\n') {
        FID_conflict_operator_(local_10,2);
        puVar4 = (undefined1 *)FUN_006f25a0();
        cVar1 = FUN_006b6850(*puVar4);
        if (cVar1 != '\0') {
          FUN_006f2550(3);
        }
      }
    }
  }
  puVar5 = (undefined4 *)FUN_006f7b20(local_14,local_8,param_3,FUN_006b6880);
  *param_1 = *puVar5;
  return param_1;
}

