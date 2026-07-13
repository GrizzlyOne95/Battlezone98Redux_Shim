/*
 * Entry: 0054abd4
 * Name: LoadDefaultGame
 * Namespace: Global
 * Signature: int LoadDefaultGame(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl LoadDefaultGame(char *param_1)

{
  char cVar1;
  GameObject *pGVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  long lVar6;
  AiMission *pAVar7;
  UserProcess *this;
  GameObjectClass *pGVar8;
  MAT_3D *pMVar9;
  undefined4 *puVar10;
  MAT_3D *pMVar11;
  float fVar12;
  MAT_3D local_7c;
  VECTOR_3D local_3c;
  float local_30;
  float local_28;
  char local_24 [4];
  GameObjectClass *local_20;
  char local_1c [20];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar4 = param_1;
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)(local_1c + -(int)param_1)] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar4 = strrchr(local_1c,0x2e);
  if (pcVar4 != (char *)0x0) {
    *pcVar4 = '\0';
  }
  Close_Terrain_Texture_Info();
  TerrainSaveName(TerrainName);
  iVar5 = CreateTerrainTextureNames((char *)0x0);
  if (((iVar5 != 0) && (lVar6 = Init_Zone_Manager(TerrainName), lVar6 != 0)) &&
     (iVar5 = Terrain_Create(0,0,0.0), iVar5 != 0)) {
    Set_Terrain_Texture_Info();
    DisplayInterface_LoadColors();
    InitPathing();
    builtin_strncpy(local_24,"play",4);
    local_20 = (GameObjectClass *)0x7265;
    local_20 = GameObjectClass::Find(0x726579616c70);
    GetTerrainExtents(&local_3c);
    pMVar9 = &Identity_Matrix;
    pMVar11 = &local_7c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar11->right_x = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pMVar11 = (MAT_3D *)&pMVar11->right_y;
    }
    local_7c.posit_x = (double)((local_3c.x + local_30) * 0.5);
    local_7c.posit_z = (double)((local_3c.z + local_28) * 0.5);
    fVar12 = Terrain_FindFloor(local_7c.posit_x,local_7c.posit_z);
    local_7c.posit_y = (double)(fVar12 + 2.0);
    GameObjectClass::Build(local_20,&local_7c,1,1,-1,(char *)0x0);
    iVar5 = (int)&msn_filename - (int)param_1;
    do {
      cVar1 = *param_1;
      param_1[iVar5] = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
    pcVar4 = strrchr(&msn_filename,0x2e);
    if (pcVar4 == (char *)0x0) {
      puVar3 = (undefined4 *)((int)&gameWindow.bottom + 3);
      do {
        puVar10 = puVar3;
        puVar3 = (undefined4 *)((int)puVar10 + 1);
      } while (*(char *)((int)puVar10 + 1) != '\0');
      *(undefined4 *)((int)puVar10 + 1) = 0x6e7a622e;
      *(undefined1 *)((int)puVar10 + 5) = 0;
    }
    pGVar2 = GameObject::userObject;
    pAVar7 = AiMission::Create(local_1c);
    if (pGVar2 != (GameObject *)0x0) {
      this = operator_new(0x70);
      if (this != (UserProcess *)0x0) {
        UserProcess::UserProcess(this,pAVar7,pGVar2);
      }
      pGVar8 = GameObjectClass::Find(0x726573757361);
      pGVar2->curPilot = pGVar8;
    }
    AiMission::PostLoadMission();
    GameObject::PostLoadAll();
    Team::PostLoadAll();
    if (missionSave == false) {
      AiTask::PostLoadAll();
    }
    return 1;
  }
  return 0;
}
