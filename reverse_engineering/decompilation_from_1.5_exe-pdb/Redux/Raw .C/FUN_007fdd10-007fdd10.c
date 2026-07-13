
undefined4 FUN_007fdd10(int *param_1,char *param_2,char *param_3,undefined1 param_4)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  int *local_10;
  
  if (param_2 == param_3) {
    uVar3 = 0;
  }
  else {
    local_10 = param_1;
    while( true ) {
      while( true ) {
        cVar1 = *param_2;
        if (*local_10 == 0) {
          iVar4 = FUN_007fe220(cVar1);
          *local_10 = iVar4;
        }
        pcVar2 = (char *)*local_10;
        if (cVar1 == *pcVar2) break;
        if (cVar1 < *pcVar2) {
          local_10 = (int *)(pcVar2 + 8);
        }
        else {
          local_10 = (int *)(pcVar2 + 0x10);
        }
      }
      param_2 = param_2 + 1;
      if (param_2 == param_3) break;
      local_10 = (int *)(pcVar2 + 0xc);
    }
    if (*(int *)(pcVar2 + 4) == 0) {
      uVar3 = FUN_007fe2a0(param_4);
      *(undefined4 *)(pcVar2 + 4) = uVar3;
    }
    uVar3 = *(undefined4 *)(pcVar2 + 4);
  }
  return uVar3;
}

