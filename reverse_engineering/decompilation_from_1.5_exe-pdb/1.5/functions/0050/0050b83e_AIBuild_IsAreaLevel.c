/*
 * Entry: 0050b83e
 * Name: AIBuild_IsAreaLevel
 * Namespace: Global
 * Signature: int AIBuild_IsAreaLevel(int param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AIBuild_IsAreaLevel(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  tagMAP_ELEMENT *ptVar2;
  int iVar3;
  int local_8;
  
  if ((((param_1 < 0) || (mapsizex < param_3 + param_1)) || (param_2 < 0)) ||
     (mapsizey < param_2 + param_4)) {
LAB_0050b8d6:
    iVar3 = 0;
  }
  else {
    ptVar2 = Line_GetElement(param_1,param_2,".\\Schedule\\Aibuild.cpp",0x7f7);
    uVar1 = ptVar2->altitude;
    local_8 = 0;
    if (0 < param_4) {
      do {
        iVar3 = 0;
        if (0 < param_3) {
          do {
            ptVar2 = Line_GetElement(param_1 + iVar3,local_8 + param_2,".\\Schedule\\Aibuild.cpp",
                                     0x7fc);
            if (ptVar2->altitude != uVar1) goto LAB_0050b8d6;
            iVar3 = iVar3 + 1;
          } while (iVar3 < param_3);
        }
        local_8 = local_8 + 1;
      } while (local_8 < param_4);
    }
    iVar3 = 1;
  }
  return iVar3;
}
