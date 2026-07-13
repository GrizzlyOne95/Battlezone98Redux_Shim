
bool __thiscall FUN_00461910(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *local_c;
  
  local_c = *(char **)(param_1 + 4);
  pcVar3 = local_c + 1;
  do {
    cVar1 = *local_c;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  iVar2 = _strnicmp(param_2,*(char **)(param_1 + 4),(int)local_c - (int)pcVar3);
  return iVar2 == 0;
}

