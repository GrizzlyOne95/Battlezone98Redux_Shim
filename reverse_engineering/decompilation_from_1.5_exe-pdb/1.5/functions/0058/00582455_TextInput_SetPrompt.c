/*
 * Entry: 00582455
 * Name: TextInput_SetPrompt
 * Namespace: Global
 * Signature: void TextInput_SetPrompt(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_SetPrompt(void *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  size_t _Count;
  uint _Size;
  
  iVar2 = *(int *)((int)param_1 + 8);
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  _Count = (int)pcVar4 - (int)(param_2 + 1);
  _Size = (*(int *)(iVar2 + 0x10c) - *(int *)(iVar2 + 0x108)) + 1;
  if (0xf0 - _Count < _Size) {
    _Size = 0xf0 - _Count;
  }
  if (_Size != 0) {
    memmove((void *)(_Count + 0x10 + iVar2),(void *)(*(int *)(iVar2 + 0x108) + 0x10 + iVar2),_Size);
  }
  *(int *)(iVar2 + 0x10c) = *(int *)(iVar2 + 0x10c) + (_Count - *(int *)(iVar2 + 0x108));
  iVar3 = *(int *)(iVar2 + 0x10c);
  *(int *)(iVar2 + 0x110) = *(int *)(iVar2 + 0x110) + (_Count - *(int *)(iVar2 + 0x108));
  if (iVar3 + 1U < 0xf0) {
    memset(iVar3 + 0x11 + iVar2,0,0xef - iVar3);
  }
  pcVar4 = (char *)(iVar2 + 0x10);
  strncpy(pcVar4,param_2,_Count);
  *(undefined4 *)(iVar2 + 0x114) = 0;
  *(undefined4 *)(iVar2 + 0x118) = 0;
  *(size_t *)(iVar2 + 0x108) = _Count;
  TextInput_AdjustScrollPosRight(*(INPUT_REGION **)(iVar2 + 0x110),(ulong)pcVar4);
  *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
  return;
}
