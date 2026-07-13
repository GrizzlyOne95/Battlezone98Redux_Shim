/*
 * Entry: 00582524
 * Name: TextInput_SetString
 * Namespace: Global
 * Signature: void TextInput_SetString(void * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_SetString(void *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  INPUT_REGION *pIVar4;
  ulong unaff_ESI;
  
  iVar2 = *(int *)((int)param_1 + 8);
  strncpy((char *)(*(int *)(iVar2 + 0x108) + 0x10 + iVar2),param_2,
          *(int *)(iVar2 + 0x104) - *(int *)(iVar2 + 0x108));
  pcVar3 = (char *)(iVar2 + 0x10);
  *(uint *)(iVar2 + 0x124) = *(uint *)(iVar2 + 0x124) | 0x200;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(iVar2 + 0x114) = 0;
  *(undefined4 *)(iVar2 + 0x118) = 0;
  pIVar4 = (INPUT_REGION *)(pcVar3 + -(iVar2 + 0x11));
  *(undefined1 **)(iVar2 + 0x10c) = (undefined1 *)((int)&pIVar4[-1].updown_callback + 3);
  *(INPUT_REGION **)(iVar2 + 0x110) = pIVar4;
  TextInput_AdjustScrollPosRight(pIVar4,unaff_ESI);
  return;
}
