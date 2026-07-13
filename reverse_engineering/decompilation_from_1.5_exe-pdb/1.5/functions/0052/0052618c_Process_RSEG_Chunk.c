/*
 * Entry: 0052618c
 * Name: Process_RSEG_Chunk
 * Namespace: Global
 * Signature: long Process_RSEG_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_RSEG_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  ROAD_INFO *pRVar2;
  ROAD_INFO *pRVar3;
  uint uVar4;
  int iVar5;
  ROAD_INFO *pRVar6;
  ROAD_INFO *pRVar7;
  uint uVar8;
  int iVar9;
  int local_18;
  ChunkType *local_14;
  int local_8;
  
  pRVar7 = (ROAD_INFO *)0x0;
  uVar4 = param_1[1].ckSize - 1;
  for (uVar8 = uVar4; 0x18 < (int)uVar8; uVar8 = (uVar8 & 1) + ((int)uVar8 >> 1)) {
  }
  iVar5 = uVar4 - uVar8;
  local_18 = 0;
  pRVar2 = RoadList;
  if (4 < iVar5) {
    local_14 = param_1 + 2;
    pRVar6 = RoadList;
    local_8 = iVar5;
    do {
      pRVar7 = malloc(uVar8 * 0x18 + 0x44);
      iVar9 = road_id;
      if (pRVar7 == (ROAD_INFO *)0x0) {
        return 0;
      }
      pRVar7->next = (ROAD_INFO *)0x0;
      pRVar7->back = (ROAD_INFO *)0x0;
      pRVar7->Terminal_Segment = 0;
      pRVar7->road_id = iVar9;
      pRVar7->road_type = (long)param_1[1].ckID;
      pRVar7->num_pairs = uVar8 + 1;
      pRVar7->road_pts = (RoadPair *)(pRVar7 + 1);
      memcpy(pRVar7 + 1,local_14,uVar8 * 0x18 + 0x18);
      pRVar2 = pRVar7;
      pRVar3 = pRVar7;
      if (pRVar6 != (ROAD_INFO *)0x0) {
        pRVar2 = pRVar6;
        for (pRVar3 = pRVar6->next; pRVar3 != (ROAD_INFO *)0x0; pRVar3 = pRVar3->next) {
          pRVar2 = pRVar3;
        }
        pRVar2->next = pRVar7;
        pRVar7->back = pRVar2;
        pRVar2 = pRVar6;
        pRVar3 = RoadList;
      }
      RoadList = pRVar3;
      local_14 = local_14 + uVar8 * 3;
      local_8 = local_8 - uVar8;
      local_18 = local_18 + uVar8;
      pRVar6 = pRVar2;
    } while (4 < local_8);
  }
  iVar9 = uVar8 + (iVar5 - local_18);
  iVar5 = (iVar9 + 1) * 0x18;
  pRVar6 = RoadList;
  if (1 < iVar9) {
    pRVar7 = malloc(iVar5 + 0x2c);
    iVar1 = road_id;
    if (pRVar7 == (ROAD_INFO *)0x0) {
      return 0;
    }
    pRVar7->next = (ROAD_INFO *)0x0;
    pRVar7->back = (ROAD_INFO *)0x0;
    pRVar7->Terminal_Segment = 0;
    pRVar7->road_id = iVar1;
    pRVar7->road_type = (long)param_1[1].ckID;
    pRVar7->num_pairs = iVar9 + 1;
    pRVar7->road_pts = (RoadPair *)(pRVar7 + 1);
    memcpy(pRVar7 + 1,param_1 + local_18 * 3 + 2,iVar5);
    pRVar6 = pRVar7;
    if (pRVar2 != (ROAD_INFO *)0x0) {
      pRVar6 = pRVar2->next;
      while (pRVar3 = pRVar6, pRVar3 != (ROAD_INFO *)0x0) {
        pRVar2 = pRVar3;
        pRVar6 = pRVar3->next;
      }
      pRVar2->next = pRVar7;
      pRVar7->back = pRVar2;
      pRVar6 = RoadList;
    }
  }
  RoadList = pRVar6;
  if (pRVar7 != (ROAD_INFO *)0x0) {
    pRVar7->Terminal_Segment = 1;
  }
  road_id = road_id + 1;
  return 1;
}
