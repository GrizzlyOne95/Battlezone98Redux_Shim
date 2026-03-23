
void FUN_00835822(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int *piVar1;
  char cVar2;
  char *pcVar3;
  undefined *puVar4;
  undefined4 uVar5;
  int local_8;
  
  pcVar3 = (char *)FUN_0082ba59(param_1,param_3,&local_8);
  piVar1 = param_2 + 0x83;
  if (piVar1 <= (int *)*param_2) {
    FUN_0082c2ac(param_2);
  }
  *(undefined1 *)*param_2 = 0x22;
  *param_2 = *param_2 + 1;
  do {
    if (local_8 == 0) {
      local_8 = -1;
      if (piVar1 <= (int *)*param_2) {
        FUN_0082c2ac(param_2);
      }
      *(undefined1 *)*param_2 = 0x22;
      *param_2 = *param_2 + 1;
      return;
    }
    local_8 = local_8 + -1;
    cVar2 = *pcVar3;
    if (cVar2 == '\0') {
      uVar5 = 4;
      puVar4 = &DAT_0086f9e8;
LAB_008358ab:
      FUN_0082b81b(param_2,puVar4,uVar5);
    }
    else {
      if (cVar2 == '\n') {
LAB_00835874:
        if (piVar1 <= (int *)*param_2) {
          FUN_0082c2ac(param_2);
        }
        *(undefined1 *)*param_2 = 0x5c;
        *param_2 = *param_2 + 1;
      }
      else {
        if (cVar2 == '\r') {
          uVar5 = 2;
          puVar4 = &DAT_008a1b74;
          goto LAB_008358ab;
        }
        if ((cVar2 == '\"') || (cVar2 == '\\')) goto LAB_00835874;
      }
      if (piVar1 <= (int *)*param_2) {
        FUN_0082c2ac(param_2);
      }
      *(char *)*param_2 = *pcVar3;
      *param_2 = *param_2 + 1;
    }
    pcVar3 = pcVar3 + 1;
  } while( true );
}

