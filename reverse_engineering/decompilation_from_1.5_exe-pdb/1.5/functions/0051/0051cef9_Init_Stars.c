/*
 * Entry: 0051cef9
 * Name: Init_Stars
 * Namespace: Global
 * Signature: int Init_Stars(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Init_Stars(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  TEXTURE *pTVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  TEXTURE *pTVar12;
  float local_2c;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  StarSet.starCount = 0;
  StarSet.domeRadius = 0.0;
  memset(VisibleStar,0,0xb00);
  iVar4 = GetINIInt(starSec,"Radius",1000,missionName);
  StarSet.domeRadius = (float)iVar4;
  local_1c = 0;
  do {
    local_20 = 0;
    do {
      if (0x3f < StarSet.starCount) break;
      sprintf(local_18,"Texture%d%d",local_1c,local_20);
      GetINIString(starSec,local_18,"",VisibleStar[StarSet.starCount].name,0x10,missionName);
      sprintf(local_18,"Size%d%d",local_1c,local_20);
      iVar4 = GetINIInt(starSec,local_18,100,missionName);
      VisibleStar[StarSet.starCount].size = (float)iVar4;
      sprintf(local_18,"Azimuth%d%d",local_1c,local_20);
      iVar4 = GetINIInt(starSec,local_18,0,missionName);
      VisibleStar[StarSet.starCount].azimuth = (float)iVar4 * 0.017453292;
      sprintf(local_18,"Elevation%d%d",local_1c,local_20);
      iVar4 = GetINIInt(starSec,local_18,0x2d,missionName);
      VisibleStar[StarSet.starCount].elevation = (float)iVar4 * -0.017453292;
      sprintf(local_18,"Roll%d%d",local_1c,local_20);
      iVar4 = GetINIInt(starSec,local_18,0,missionName);
      VisibleStar[StarSet.starCount].roll = (float)iVar4 * -0.017453292;
      sprintf(local_18,"Alpha%d%d",local_1c,local_20);
      iVar4 = StarSet.starCount;
      iVar5 = GetINIInt(starSec,local_18,1,missionName);
      fVar1 = StarSet.domeRadius;
      VisibleStar[iVar4].rop = (-(uint)(iVar5 != 0) & 0x80) + 0x54;
      VisibleStar[iVar4].radius = fVar1;
      if (VisibleStar[iVar4].name[0] != '\0') {
        pTVar6 = TexCache_UseTexture(VisibleStar[iVar4].name);
        VisibleStar[StarSet.starCount].texture = pTVar6;
        if (pTVar6 != (TEXTURE *)0x0) {
          StarSet.starCount = StarSet.starCount + 1;
        }
      }
      local_20 = local_20 + 1;
    } while (local_20 < 10);
    local_1c = local_1c + 1;
  } while (local_1c < 7);
  iVar4 = GetINIInt(listSec,"Solid",0,missionName);
  iVar5 = GetINIInt(listSec,"LayerHeight",0x1e,missionName);
  GetINIString(listSec,"Texture","",VisibleStar[StarSet.starCount].name,0x10,missionName);
  if ((VisibleStar[StarSet.starCount].name[0] != '\0') &&
     (pTVar6 = TexCache_UseTexture(VisibleStar[StarSet.starCount].name), pTVar6 != (TEXTURE *)0x0))
  {
    local_20 = 0;
    local_2c = (float)iVar5 * -0.017453292 * 0.5;
    do {
      if (0x3f < StarSet.starCount) break;
      sprintf(local_18,"Size%d",local_20);
      iVar7 = GetINIInt(listSec,local_18,100,missionName);
      sprintf(local_18,"Start%d",local_20);
      iVar8 = GetINIInt(listSec,local_18,0,missionName);
      sprintf(local_18,"End%d",local_20);
      iVar9 = GetINIInt(listSec,local_18,0x168,missionName);
      sprintf(local_18,"Count%d",local_20);
      iVar10 = GetINIInt(listSec,local_18,-1,missionName);
      if (0 < iVar10) {
        fVar3 = 0.0;
        fVar1 = ((float)iVar9 * 0.017453292 - (float)iVar8 * 0.017453292) / (float)iVar10;
        fVar2 = fVar1 * 0.5 + (float)iVar8 * 0.017453292;
        local_1c = 0;
        if (0 < iVar10) {
          pfVar11 = &VisibleStar[StarSet.starCount].azimuth;
          do {
            if (0xc404b3 < (int)pfVar11) break;
            pfVar11[-1] = (float)iVar7;
            *pfVar11 = fVar2;
            pfVar11[1] = local_2c;
            pfVar11[2] = fVar3;
            pfVar11[3] = 1000.0;
            pTVar12 = pTVar6;
            if (iVar4 != 0) {
              pTVar12 = (TEXTURE *)0xf;
            }
            pfVar11[-3] = (float)pTVar12;
            fVar2 = fVar1 + fVar2;
            fVar3 = fVar3 + 0.7853981;
            StarSet.starCount = StarSet.starCount + 1;
            pfVar11[-2] = (float)((-(uint)(iVar4 != 0) & 0xffffff2c) + 0xd4);
            pfVar11 = pfVar11 + 0xb;
            local_1c = local_1c + 1;
          } while (local_1c < iVar10);
        }
      }
      local_20 = local_20 + 1;
      local_2c = local_2c + (float)iVar5 * -0.017453292;
    } while (local_20 < 9);
  }
  if (StarSet.starCount < 1) {
    StarSet.starCount = 0;
  }
  return StarSet.starCount;
}
