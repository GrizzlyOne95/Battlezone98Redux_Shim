/*
 * Entry: 0050b7c5
 * Name: AIBuild_IsAreaFreeOfBuildings
 * Namespace: Global
 * Signature: int AIBuild_IsAreaFreeOfBuildings(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_IsAreaFreeOfBuildings(int param_1,int param_2,int param_3,int param_4)

{
  tagMAP_ELEMENT *ptVar1;
  int iVar2;
  int iVar3;
  
  if ((((param_1 < 0) || (mapsizex < param_1 + param_3)) || (param_2 < 0)) ||
     (mapsizey < param_2 + param_4)) {
LAB_0050b837:
    iVar2 = 0;
  }
  else {
    iVar2 = 0;
    if (0 < param_4) {
      do {
        iVar3 = 0;
        if (0 < param_3) {
          do {
            ptVar1 = Line_GetElement(param_1 + iVar3,iVar2 + param_2,".\\Schedule\\Aibuild.cpp",
                                     0x7df);
            if (ptVar1->effects != 0) goto LAB_0050b837;
            iVar3 = iVar3 + 1;
          } while (iVar3 < param_3);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < param_4);
    }
    iVar2 = 1;
  }
  return iVar2;
}
