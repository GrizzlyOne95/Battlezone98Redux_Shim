/*
 * Entry: 00480eef
 * Name: CheckWave
 * Namespace: Global
 * Signature: int CheckWave(_gas_object * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckWave(_gas_object *param_1)

{
  void *pvVar1;
  undefined4 extraout_EAX;
  int iVar2;
  int unaff_EBX;
  GAS_PREP_INFO *unaff_ESI;
  int *piVar3;
  GAS_PREP_INFO *unaff_EDI;
  int *piVar4;
  
  if ((*(uint *)(unaff_EBX + 0x78) & 0x200) == 0) {
    pvVar1 = UseItem((char *)(unaff_EBX + 4));
    *(void **)(unaff_EBX + 0x4c) = pvVar1;
  }
  else {
    pvVar1 = *(void **)(unaff_EBX + 0x4c);
  }
  *(void **)(unaff_EBX + 0x50) = pvVar1;
  if (pvVar1 == (void *)0x0) {
    return 0;
  }
  if (**(int **)(unaff_EBX + 0x4c) == 0x30534147) {
    *(int *)(unaff_EBX + 0x50) = *(int *)(unaff_EBX + 0x50) + 0x1c;
    piVar3 = *(int **)(unaff_EBX + 0x4c);
    piVar4 = (int *)(unaff_EBX + 0x30);
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar4 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar4 = piVar4 + 1;
    }
    ConvertFileGPI(unaff_EDI,unaff_ESI);
  }
  *(undefined1 *)(unaff_EBX + 0x77) = *(undefined1 *)(unaff_EBX + 0x34);
  if ((*(uint *)(unaff_EBX + 0x78) & 0x200) == 0) {
    UnlockItem((char *)(unaff_EBX + 4));
    *(undefined4 *)(unaff_EBX + 0x4c) = 0;
    *(undefined4 *)(unaff_EBX + 0x50) = 0;
  }
  if ((*(uint *)(unaff_EBX + 0x14) & 0x7800) == 0x1800) {
    _ftol2_sse();
    *(undefined4 *)(unaff_EBX + 0x40) = extraout_EAX;
  }
  return 1;
}
