
void FUN_0082ff43(int param_1,int param_2)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  
  cVar2 = *(char *)(param_2 + 4);
  if (cVar2 == '\x04') {
    piVar1 = (int *)(*(int *)(param_1 + 0x10) + 4);
    *piVar1 = *piVar1 + -1;
    iVar3 = *(int *)(param_2 + 0xc) + 0x11;
  }
  else {
    if (cVar2 == '\x05') {
      FUN_00830d93(param_1,param_2);
      return;
    }
    if (cVar2 == '\x06') {
      FUN_0082fa32(param_1,param_2);
      return;
    }
    if (cVar2 != '\a') {
      if (cVar2 == '\b') {
        FUN_0082d672(param_1,param_2);
        return;
      }
      if (cVar2 != '\t') {
        if (cVar2 != '\n') {
          return;
        }
        FUN_0082fae9(param_1,param_2);
        return;
      }
      FUN_0082fa62(param_1,param_2);
      return;
    }
    iVar3 = *(int *)(param_2 + 0x10) + 0x18;
  }
  FUN_00838869(param_1,param_2,iVar3,0);
  return;
}

