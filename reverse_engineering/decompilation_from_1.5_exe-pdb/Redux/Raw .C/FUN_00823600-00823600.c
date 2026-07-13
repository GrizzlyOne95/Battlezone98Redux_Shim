
/* WARNING: Removing unreachable block (ram,0x008236a0) */

void FUN_00823600(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *local_10;
  
  iVar2 = *(int *)(param_1 + 8);
  strncpy((char *)(iVar2 + 0x10 + *(int *)(iVar2 + 0x108)),param_2,
          *(int *)(iVar2 + 0x104) - *(int *)(iVar2 + 0x108));
  *(uint *)(iVar2 + 0x120) = *(uint *)(iVar2 + 0x120) | 0x200;
  local_10 = (char *)(iVar2 + 0x10);
  do {
    cVar1 = *local_10;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  *(char **)(iVar2 + 0x10c) = local_10 + (-1 - (iVar2 + 0x11));
  *(int *)(iVar2 + 0x110) = *(int *)(iVar2 + 0x10c) + 1;
  *(undefined4 *)(iVar2 + 0x114) = 0;
  *(undefined4 *)(iVar2 + 0x118) = 0;
  FUN_00822f40(iVar2,*(undefined4 *)(iVar2 + 0x110));
  return;
}

