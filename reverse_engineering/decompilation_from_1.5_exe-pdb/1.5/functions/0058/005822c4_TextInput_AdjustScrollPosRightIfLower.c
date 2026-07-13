/*
 * Entry: 005822c4
 * Name: TextInput_AdjustScrollPosRightIfLower
 * Namespace: Global
 * Signature: void TextInput_AdjustScrollPosRightIfLower(INPUT_REGION * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl TextInput_AdjustScrollPosRightIfLower(INPUT_REGION *param_1,ulong param_2)

{
  CHARACTER *pCVar1;
  char *pcVar2;
  int unaff_ESI;
  uint uVar3;
  uint uVar4;
  
  uVar3 = 0;
  for (pcVar2 = (char *)(unaff_ESI + 0x10 + *(int *)(unaff_ESI + 0x114));
      pcVar2 <= param_1->text + unaff_ESI; pcVar2 = pcVar2 + 1) {
    pCVar1 = GetCharacterAddress(Default_Font,(short)*pcVar2);
    uVar3 = uVar3 + pCVar1->Width;
    if (*(uint *)(unaff_ESI + 8) < uVar3) {
      return;
    }
  }
  do {
    uVar4 = uVar3;
    if (*(int *)(unaff_ESI + 0x114) == 0) {
      return;
    }
    *(int *)(unaff_ESI + 0x114) = *(int *)(unaff_ESI + 0x114) + -1;
    pCVar1 = GetCharacterAddress(Default_Font,
                                 (short)*(char *)(unaff_ESI + 0x10 + *(int *)(unaff_ESI + 0x114)));
    uVar3 = pCVar1->Width + uVar4;
  } while (uVar3 <= *(uint *)(unaff_ESI + 8));
  *(int *)(unaff_ESI + 0x114) = *(int *)(unaff_ESI + 0x114) + 1;
  *(uint *)(unaff_ESI + 0x118) = *(int *)(unaff_ESI + 8) - uVar4;
  return;
}
