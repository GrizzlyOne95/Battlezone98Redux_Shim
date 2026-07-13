/*
 * Entry: 00582248
 * Name: TextInput_AdjustScrollPosRight
 * Namespace: Global
 * Signature: void TextInput_AdjustScrollPosRight(INPUT_REGION * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_AdjustScrollPosRight(INPUT_REGION *param_1,ulong param_2)

{
  char cVar1;
  CHARACTER *pCVar2;
  char *pcVar3;
  int unaff_ESI;
  uint uVar4;
  
  uVar4 = 0;
  *(undefined4 *)(unaff_ESI + 0x118) = 0;
  for (pcVar3 = (char *)(*(int *)(unaff_ESI + 0x114) + 0x10 + unaff_ESI);
      pcVar3 <= param_1->text + unaff_ESI; pcVar3 = pcVar3 + 1) {
    pCVar2 = GetCharacterAddress(Default_Font,(short)*pcVar3);
    uVar4 = uVar4 + pCVar2->Width;
    if (*(uint *)(unaff_ESI + 8) < uVar4) {
      cVar1 = *(char *)(*(int *)(unaff_ESI + 0x114) + 0x10 + unaff_ESI);
      *(int *)(unaff_ESI + 0x114) = *(int *)(unaff_ESI + 0x114) + 1;
      pCVar2 = GetCharacterAddress(Default_Font,(short)cVar1);
      uVar4 = uVar4 - pCVar2->Width;
      *(uint *)(unaff_ESI + 0x118) = *(int *)(unaff_ESI + 8) - uVar4;
    }
  }
  return;
}
