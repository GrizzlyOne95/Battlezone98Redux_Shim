/*
 * Entry: 00525f58
 * Name: Process_OBJ__Chunk
 * Namespace: Global
 * Signature: long Process_OBJ__Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_OBJ__Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  short sVar1;
  long64 *plVar2;
  long lVar3;
  char *pcVar4;
  int iVar5;
  CLSN_BOXES *pCVar6;
  tagENTITY *ptVar7;
  StructObjectType *pSVar8;
  float fVar9;
  ENTITY_LOADER local_58;
  
  pSVar8 = (StructObjectType *)(param_1 + 1);
  if (((doload != 0) &&
      (((((iVar5 = param_1[0xc].ckSize, iVar5 == 5 || (iVar5 == 7)) || (iVar5 == 2)) ||
        ((iVar5 == 1 || (iVar5 == 6)))) || (iVar5 == 3)))) ||
     ((CreateBuildings == 0 &&
      (((iVar5 = param_1[0xc].ckSize, iVar5 == 5 || (iVar5 == 7)) || (iVar5 == 2)))))) {
    return 1;
  }
  plVar2 = (long64 *)PrjID2Filename(pSVar8->GeometryFile,(char *)0x0);
  sVar1 = objSeqNo;
  if (plVar2 == (long64 *)0x0) {
    DEBUG_systemWarning("Object found with no geometry, skipping");
LAB_00525fd0:
    lVar3 = 1;
  }
  else {
    if (objSeqNo == 0) {
      sVar1 = PrjID2SeqNo(pSVar8->GeometryFile);
    }
    else {
      objSeqNo = 0;
    }
    memset((short)&local_58,0,0x54);
    local_58.entObj = NewObj((_OBJ76 *)0x0,pSVar8,plVar2,1);
    if (local_58.entObj != (_OBJ76 *)0x0) {
      fVar9 = Terrain_FindFloor(((local_58.entObj)->transform).posit_x,
                                ((local_58.entObj)->transform).posit_z);
      ((local_58.entObj)->transform).posit_y = (double)fVar9;
      switch(param_1[0xc].ckSize) {
      case 1:
      case 3:
      case 6:
        pcVar4 = PrjID2Filename(pSVar8->GeometryFile,".vdf");
        iVar5 = LoadVehicle((ObjectType *)pSVar8,&local_58,pcVar4);
        break;
      case 2:
      case 5:
      case 7:
      case 8:
      case 10:
      case 0xf:
        pcVar4 = PrjID2Filename(pSVar8->GeometryFile,".sdf");
        iVar5 = LoadStructure(pSVar8,&local_58,pcVar4);
        break;
      default:
        iVar5 = 0;
      }
      if (iVar5 == 0) {
        ClassDelete(local_58.entObj);
        remove_obj(local_58.entObj,"objload");
      }
      else {
        if (local_58.clsnPlanesFound == 0) {
          pCVar6 = (CLSN_BOXES *)0x0;
        }
        else {
          pCVar6 = GetClsnPlanes(&local_58.clsnPlanes);
        }
        ptVar7 = add_entity(local_58.entObj,sVar1,pCVar6,
                            (float *)(-(uint)(local_58.lodRangesFound != 0) &
                                     (uint)local_58.lodRanges));
        if (ptVar7 != (tagENTITY *)0x0) goto LAB_00525fd0;
        DEBUG_systemError("BattleZone cannot create entity - The world is full!\n");
      }
    }
    lVar3 = 0;
  }
  return lVar3;
}
