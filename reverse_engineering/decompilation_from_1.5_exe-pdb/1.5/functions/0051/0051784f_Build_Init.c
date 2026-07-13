/*
 * Entry: 0051784f
 * Name: Build_Init
 * Namespace: Global
 * Signature: void Build_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Build_Init(void)

{
  uint *puVar1;
  tagBUILDINGTYPE *unaff_EBX;
  int iVar2;
  GameObjectClass *unaff_ESI;
  uint uVar3;
  
  maxbuildingtypes = (int)buildingClassList._Mylast - (int)buildingClassList._Myfirst >> 2;
  buildingtypes =
       operator_new__(-(uint)((int)((ulonglong)(uint)maxbuildingtypes * 0x80 >> 0x20) != 0) |
                      (uint)((ulonglong)(uint)maxbuildingtypes * 0x80));
  iVar2 = 0;
  memset(buildingtypes,0,maxbuildingtypes << 7);
  uVar3 = 0;
  if (0 < maxbuildingtypes) {
    do {
      std::vector<ObjectClassInfo_*,std::allocator<ObjectClassInfo_*>_>::operator[]
                (&buildingClassList,uVar3);
      Class2BuildingType(unaff_ESI,unaff_EBX);
      puVar1 = (uint *)((int)(buildingtypes->resource + -2) + iVar2);
      iVar2 = iVar2 + 0x80;
      *puVar1 = *puVar1 ^ (uVar3 << 10 ^ *puVar1) & 0x3fc00;
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < maxbuildingtypes);
  }
  return;
}
