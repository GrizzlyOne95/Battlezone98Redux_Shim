/*
 * Entry: 005bd3d0
 * Name: DumpConstants
 * Namespace: Global
 * Signature: void DumpConstants(Proto * param_1, DumpState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DumpConstants(Proto *param_1,DumpState *param_2)

{
  int iVar1;
  int unaff_EBX;
  DumpState *unaff_ESI;
  int iVar2;
  TString *unaff_EDI;
  int *piVar3;
  undefined8 local_14;
  int local_c;
  int local_8;
  
  iVar1 = *(int *)(unaff_EBX + 0x28);
  DumpInt(iVar1,(DumpState *)&unaff_EDI->tsv);
  if (0 < iVar1) {
    local_8 = 0;
    local_c = iVar1;
    do {
      piVar3 = (int *)(*(int *)(unaff_EBX + 8) + local_8);
      DumpChar(piVar3[2],(DumpState *)&unaff_EDI->tsv);
      iVar1 = piVar3[2];
      if (iVar1 == 1) {
        DumpChar(*piVar3,(DumpState *)&unaff_EDI->tsv);
      }
      else if (iVar1 == 3) {
        local_14 = *(undefined8 *)piVar3;
        DumpBlock(&local_14,8,(DumpState *)&unaff_EDI->tsv);
      }
      else if (iVar1 == 4) {
        DumpString(unaff_EDI,unaff_ESI);
      }
      local_8 = local_8 + 0x10;
      local_c = local_c + -1;
    } while (local_c != 0);
  }
  iVar1 = *(int *)(unaff_EBX + 0x34);
  DumpInt(iVar1,(DumpState *)&unaff_EDI->tsv);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      DumpFunction(*(Proto **)(*(int *)(unaff_EBX + 0x10) + iVar2 * 4),
                   *(TString **)(unaff_EBX + 0x20),(DumpState *)param_1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}
