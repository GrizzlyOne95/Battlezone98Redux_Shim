
void FUN_00823470(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  size_t _Count;
  size_t local_18;
  char *local_14;
  
  iVar2 = *(int *)(param_1 + 8);
  local_14 = param_2;
  do {
    cVar1 = *local_14;
    local_14 = local_14 + 1;
  } while (cVar1 != '\0');
  _Count = (int)local_14 - (int)(param_2 + 1);
  local_18 = (*(int *)(iVar2 + 0x10c) - *(int *)(iVar2 + 0x108)) + 1;
  if (0xf0 - _Count < local_18) {
    local_18 = 0xf0 - _Count;
  }
  if (local_18 != 0) {
    memmove((void *)(iVar2 + 0x10 + _Count),(void *)(iVar2 + 0x10 + *(int *)(iVar2 + 0x108)),
            local_18);
  }
  *(size_t *)(iVar2 + 0x10c) = (_Count - *(int *)(iVar2 + 0x108)) + *(int *)(iVar2 + 0x10c);
  *(size_t *)(iVar2 + 0x110) = (_Count - *(int *)(iVar2 + 0x108)) + *(int *)(iVar2 + 0x110);
  if (*(int *)(iVar2 + 0x10c) + 1U < 0xf0) {
    memset((void *)(iVar2 + 0x11 + *(int *)(iVar2 + 0x10c)),0,0xef - *(int *)(iVar2 + 0x10c));
  }
  strncpy((char *)(iVar2 + 0x10),param_2,_Count);
  *(size_t *)(iVar2 + 0x108) = _Count;
  *(undefined4 *)(iVar2 + 0x114) = 0;
  *(undefined4 *)(iVar2 + 0x118) = 0;
  FUN_00822f40(iVar2,*(undefined4 *)(iVar2 + 0x110));
  *(uint *)(iVar2 + 0x120) = *(uint *)(iVar2 + 0x120) | 0x200;
  return;
}

