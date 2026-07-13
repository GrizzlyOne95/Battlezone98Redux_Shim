/*
 * Entry: 00517501
 * Name: Class2BuildingType
 * Namespace: Global
 * Signature: tagBUILDINGTYPE * Class2BuildingType(GameObjectClass * param_1, tagBUILDINGTYPE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagBUILDINGTYPE * __cdecl Class2BuildingType(GameObjectClass *param_1,tagBUILDINGTYPE *param_2)

{
  char cVar1;
  uint uVar2;
  bool bVar3;
  undefined2 uVar4;
  Attachment **ppAVar5;
  Attachment *pAVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  int unaff_EBX;
  Attachment unaff_ESI;
  
  ppAVar5 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                      ((vector<Attachment_*,std::allocator<Attachment_*>_> *)(unaff_EBX + 4),
                       attachIndex);
  pAVar6 = *ppAVar5;
  if (pAVar6 == (Attachment *)0x0) {
    if (unaff_ESI != (Attachment)0x0) {
      pAVar6 = operator_new(8);
      if (pAVar6 == (Attachment *)0x0) {
        pAVar6 = (Attachment *)0x0;
      }
      else {
        *pAVar6 = (Attachment)&BuildingTypeAttachment::_vftable_;
      }
      ppAVar5 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                          ((vector<Attachment_*,std::allocator<Attachment_*>_> *)(unaff_EBX + 4),
                           attachIndex);
      *ppAVar5 = pAVar6;
      pAVar6[1] = unaff_ESI;
      memset();
      pcVar8 = (char *)((int)unaff_ESI + 0x40);
      pcVar7 = (char *)(unaff_EBX + 0x38);
      iVar9 = (int)pcVar8 - (int)pcVar7;
      do {
        cVar1 = *pcVar7;
        pcVar7[iVar9] = cVar1;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      *(undefined1 *)((int)unaff_ESI + 0x48) = 0;
      iVar9 = (int)((int)unaff_ESI + 0x60) - (int)pcVar8;
      do {
        cVar1 = *pcVar8;
        pcVar8[iVar9] = cVar1;
        pcVar8 = pcVar8 + 1;
      } while (cVar1 != '\0');
      *(undefined4 *)((int)unaff_ESI + 0x20) = *(undefined4 *)(unaff_EBX + 0x50);
      uVar4 = (undefined2)defaultPrereqType;
      if (unitcycles == 0) {
        prereqTypeCount = prereqTypeCount + 1;
        uVar4 = (undefined2)prereqTypeCount;
      }
      *(uint *)((int)unaff_ESI + 0x24) = *(uint *)((int)unaff_ESI + 0x24) & 0xfffffffe;
      uVar2 = *(uint *)((int)unaff_ESI + 0x24);
      *(undefined2 *)unaff_ESI = uVar4;
      *(undefined2 *)((int)unaff_ESI + 0x16) = 0;
      *(undefined2 *)((int)unaff_ESI + 0x18) = 0;
      *(undefined2 *)((int)unaff_ESI + 0xe) = 0;
      *(undefined2 *)((int)unaff_ESI + 0x10) = 0;
      *(undefined2 *)((int)unaff_ESI + 0xc) = 0;
      bVar3 = BuildingVehicle(*(ulong *)(unaff_EBX + 0x20));
      *(undefined4 *)((int)unaff_ESI + 4) = 0;
      *(undefined4 *)((int)unaff_ESI + 8) = 0;
      *(undefined4 *)((int)unaff_ESI + 0x2c) = 0;
      *(undefined4 *)((int)unaff_ESI + 0x30) = 0;
      *(uint *)((int)unaff_ESI + 0x24) = (bVar3 | 0x1100000) * 2 | uVar2 & 0xfe23fffd;
      return (tagBUILDINGTYPE *)unaff_ESI;
    }
    if ((uint)(buildingClass._padding_ - buildingClass._padding_ >> 2) <= (uint)attachIndex) {
      return &defaultbuildingtype;
    }
    ppAVar5 = std::vector<Attachment_*,std::allocator<Attachment_*>_>::operator[]
                        ((vector<Attachment_*,std::allocator<Attachment_*>_> *)
                         &buildingClass._padding_,attachIndex);
    pAVar6 = *ppAVar5;
  }
  return (tagBUILDINGTYPE *)pAVar6[1];
}
