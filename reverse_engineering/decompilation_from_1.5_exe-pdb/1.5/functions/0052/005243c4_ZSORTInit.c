/*
 * Entry: 005243c4
 * Name: ZSORTInit
 * Namespace: Global
 * Signature: int ZSORTInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ZSORTInit(void)

{
  SortingTableCurrent = VirtualAlloc((LPVOID)0x0,0x400000,0x3000,4);
  SortingTableEnd = SortingTableCurrent + 0x24900;
  SortingTableLift = SortingTableCurrent;
  SortingTable = SortingTableCurrent;
  SortingTableIndexLift = VirtualAlloc((LPVOID)0x0,0xc000,0x3000,4);
  SortingTableIndex = SortingTableIndexLift;
  ZSORTReset();
  memset(&LODInfo,0xff,100);
  LODInfo.lightCount = 0;
  LODInfo.lightRange = 0;
  LODInfo.bspRange = 1000;
  LODInfo.lightRadius = 1000;
  LODInfo.shadowRange = 100;
  LODInfo.shadowRadius = 100;
  LODInfo.bspCount = 100;
  LODInfo.bspRadius = 100;
  LODInfo.textureCount = 0xf;
  LODInfo.textureRange = 200;
  LODInfo.textureRadius = 0x1e;
  LODInfo.shadowCount = 10;
  LODInfo.fillCount = 0x1e;
  LODInfo.fillRange = 0xfa;
  LODInfo.fillRadius = 10;
  LODInfo.lodCount = 10;
  LODInfo.lodRange = 0x1e;
  LODInfo.lodRadius = 0x28;
  LODInfo.subdivideDepth = 1;
  LODInfo.spriteRangeOff = 5;
  LODInfo.spriteRadiusOff = 0x100;
  LODInfo.spriteRangeSolid = 0xfa;
  LODInfo.spriteRadiusSolid = 8;
  LODInfo.mergeBSP = 7;
  LODInfo.textureCount = GetPrivateProfileIntA(secStr,"textureCount",0xf,&cfgFileName);
  LODInfo.textureRange =
       GetPrivateProfileIntA(secStr,"textureRange",LODInfo.textureRange,&cfgFileName);
  LODInfo.textureRadius =
       GetPrivateProfileIntA(secStr,"textureRadius",LODInfo.textureRadius,&cfgFileName);
  LODInfo.shadowCount = GetPrivateProfileIntA(secStr,"shadowCount",LODInfo.shadowCount,&cfgFileName)
  ;
  LODInfo.shadowRange = GetPrivateProfileIntA(secStr,"shadowRange",LODInfo.shadowRange,&cfgFileName)
  ;
  LODInfo.shadowRadius =
       GetPrivateProfileIntA(secStr,"shadowRadius",LODInfo.shadowRadius,&cfgFileName);
  LODInfo.bspCount = GetPrivateProfileIntA(secStr,"bspCount",LODInfo.bspCount,&cfgFileName);
  LODInfo.bspRange = GetPrivateProfileIntA(secStr,"bspRange",LODInfo.bspRange,&cfgFileName);
  LODInfo.bspRadius = GetPrivateProfileIntA(secStr,"bspRadius",LODInfo.bspRadius,&cfgFileName);
  LODInfo.fillCount = GetPrivateProfileIntA(secStr,"fillCount",LODInfo.fillCount,&cfgFileName);
  LODInfo.fillRange = GetPrivateProfileIntA(secStr,"fillRange",LODInfo.fillRange,&cfgFileName);
  LODInfo.fillRadius = GetPrivateProfileIntA(secStr,"fillRadius",LODInfo.fillRadius,&cfgFileName);
  LODInfo.lightCount = GetPrivateProfileIntA(secStr,"lightCount",LODInfo.lightCount,&cfgFileName);
  LODInfo.lightRange = GetPrivateProfileIntA(secStr,"lightRange",LODInfo.lightRange,&cfgFileName);
  LODInfo.lightRadius = GetPrivateProfileIntA(secStr,"lightRadius",LODInfo.lightRadius,&cfgFileName)
  ;
  LODInfo.lodCount = GetPrivateProfileIntA(secStr,"lodCount",LODInfo.lodCount,&cfgFileName);
  LODInfo.lodRange = GetPrivateProfileIntA(secStr,"lodRange",LODInfo.lodRange,&cfgFileName);
  LODInfo.lodRadius = GetPrivateProfileIntA(secStr,"lodRadius",LODInfo.lodRadius,&cfgFileName);
  LODInfo.subdivideDepth =
       GetPrivateProfileIntA(secStr,"subdivideDepth",LODInfo.subdivideDepth,&cfgFileName);
  LODInfo.spriteRangeOff =
       GetPrivateProfileIntA(secStr,"spriteRangeOff",LODInfo.spriteRangeOff,&cfgFileName);
  LODInfo.spriteRadiusOff =
       GetPrivateProfileIntA(secStr,"spriteRadiusOff",LODInfo.spriteRadiusOff,&cfgFileName);
  LODInfo.spriteRangeSolid =
       GetPrivateProfileIntA(secStr,"spriteRangeSolid",LODInfo.spriteRangeSolid,&cfgFileName);
  LODInfo.spriteRadiusSolid =
       GetPrivateProfileIntA(secStr,"spriteRadiusSolid",LODInfo.spriteRadiusSolid,&cfgFileName);
  LODInfo.mergeBSP = GetPrivateProfileIntA(secStr,"mergeBSP",LODInfo.mergeBSP,&cfgFileName);
  return 1;
}
