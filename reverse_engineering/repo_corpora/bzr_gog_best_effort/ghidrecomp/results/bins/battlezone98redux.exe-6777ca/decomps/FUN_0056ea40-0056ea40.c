
undefined4 __thiscall FUN_0056ea40(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *local_c;
  
  local_c = *(char **)(param_1 + 4);
  pcVar4 = local_c + 1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  iVar2 = _strnicmp(param_2,*(char **)(param_1 + 4),(int)local_c - (int)pcVar4);
  if (iVar2 == 0) {
    uVar3 = 1;
  }
  else {
    iVar2 = _strnicmp(param_2,"mult02",6);
    if (iVar2 == 0) {
      uVar3 = 1;
    }
    else {
      iVar2 = _strnicmp(param_2,"mult04",6);
      if (iVar2 == 0) {
        uVar3 = 1;
      }
      else {
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}

