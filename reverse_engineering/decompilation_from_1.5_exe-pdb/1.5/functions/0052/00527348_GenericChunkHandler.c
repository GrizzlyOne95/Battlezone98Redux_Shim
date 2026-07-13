/*
 * Entry: 00527348
 * Name: GenericChunkHandler
 * Namespace: Global
 * Signature: ChunkType * GenericChunkHandler(ChunkType * param_1, CHUNKDEF * param_2, long param_3, void * param_4, char * param_5, int param_6, void * param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ChunkType * __cdecl
GenericChunkHandler(ChunkType *param_1,CHUNKDEF *param_2,long param_3,void *param_4,char *param_5,
                   int param_6,void *param_7)

{
  uint uVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  long lVar5;
  int iVar6;
  long lVar7;
  CHUNKDEF *pCVar8;
  CHUNKDEF *pCVar9;
  ChunkType *pCVar10;
  char *pcVar11;
  bool bVar12;
  undefined1 local_20 [4];
  CHUNKDEF *local_1c;
  _func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *local_18;
  ChunkType *local_14;
  char local_10 [8];
  uint local_8;
  
  lVar5 = param_3;
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14 = param_1;
  local_10[0] = '\0';
  local_10[1] = 0;
  local_10[2] = 0;
  local_10[3] = 0;
  local_10[4] = 0;
  bVar2 = true;
  bVar3 = false;
  bVar4 = false;
  local_18 = (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0;
  local_20 = (undefined1  [4])0x0;
  pCVar8 = param_2;
LAB_005273b2:
  if (bVar2) {
    bVar2 = false;
  }
  else {
    iVar6 = GetNextSubChunk(param_1,&local_14,param_7);
    pCVar10 = local_14;
    param_1 = local_14;
    if (iVar6 == 0) goto LAB_0052764c;
  }
  iVar6 = 0;
  local_1c = (CHUNKDEF *)0x0;
  if (param_6 == 0) {
    bVar12 = param_3 == 0;
    pCVar8 = param_2;
    if (0 < param_3) {
      do {
        if ((param_1->ckID).longID == *(ulong *)pCVar8->id) break;
        iVar6 = iVar6 + 1;
        pCVar8 = pCVar8 + 1;
      } while (iVar6 < param_3);
      bVar12 = iVar6 == param_3;
    }
    if (bVar12) {
      strncpy(local_10,(char *)param_1,4);
      local_10[4] = 0;
      DEBUG_systemWarning(World2ErrUnknownChunk);
    }
    pCVar10 = param_1;
    if ((param_1->ckID).longID == 0x54495845) goto LAB_0052764c;
  }
  else {
    if ((param_1->ckID).longID == *(ulong *)pCVar8->id) {
      pCVar8->flags = pCVar8->flags | 0x80;
      goto LAB_0052749d;
    }
    if ((local_18 != (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) || (!bVar3)) {
      param_3 = param_3 + -1;
      pCVar10 = param_1;
      if (param_3 == 0) goto LAB_0052764c;
      pCVar8 = pCVar8 + 1;
      local_20 = (undefined1  [4])0x0;
      local_18 = (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0;
      if ((param_1->ckID).longID != 0x54495845) {
        bVar2 = true;
      }
      goto LAB_005273b2;
    }
    if ((pCVar8->flags & 4) != 0) {
      DEBUG_systemError(World2ErrNoChunk);
      goto LAB_0052749d;
    }
    iVar6 = 5;
    bVar12 = true;
    pCVar9 = pCVar8;
    pcVar11 = "EXIT";
    do {
      if (iVar6 == 0) break;
      iVar6 = iVar6 + -1;
      bVar12 = pCVar9->id[0] == *pcVar11;
      pCVar9 = (CHUNKDEF *)(pCVar9->id + 1);
      pcVar11 = pcVar11 + 1;
    } while (bVar12);
    param_1 = local_14;
    if (!bVar12) {
      if ((pCVar8->flags & 8) != 0) {
        DEBUG_systemWarning(World2ErrNoChunk);
      }
      if ((pCVar8->flags & 0x10) != 0) {
        return local_14;
      }
      pCVar10 = local_14;
      if ((pCVar8->flags & 0x20) != 0) {
        return (ChunkType *)0x0;
      }
LAB_0052764c:
      iVar6 = 0;
      if (0 < lVar5) {
        do {
          if (((param_2->flags & 0x40) != 0) && (-1 < (char)param_2->flags)) {
            strncpy(local_10,param_2->id,4);
            local_10[4] = 0;
            DEBUG_systemError(World2ErrNoChunk);
            return (ChunkType *)0x0;
          }
          iVar6 = iVar6 + 1;
          param_2 = param_2 + 1;
        } while (iVar6 < lVar5);
      }
      GetNextSubChunk(pCVar10,&local_14,param_7);
      return local_14;
    }
  }
LAB_0052749d:
  uVar1 = pCVar8->flags;
  if ((uVar1 & 0x100) == 0) {
    if ((uVar1 & 0x200) == 0) {
      if ((local_18 == (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) ||
         (local_20 == (undefined1  [4])0x0)) {
        if ((uVar1 & 0x400) != 0) {
          local_18 = (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x1;
        }
      }
      else {
        DEBUG_systemWarning(World2ErrNeedCountChunk);
      }
    }
    else if (local_18 == (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) {
      local_18 = (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x1;
      bVar3 = true;
      if (bVar4) {
        bVar4 = false;
      }
      else {
        local_20 = (undefined1  [4])0x0;
      }
    }
  }
  else {
    if (local_18 != (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) {
      DEBUG_systemWarning(World2ErrTooManyCountChunks);
    }
    local_1c = (CHUNKDEF *)local_20;
    bVar4 = true;
  }
  if ((pCVar8->flags & 0x800) != 0) {
    if (local_1c != (CHUNKDEF *)0x0) {
      DEBUG_systemWarning(World2ErrTooManyPassedVars);
    }
    local_1c = param_4;
  }
  pCVar9 = local_1c;
  if (((pCVar8->flags & 0x1000) != 0) && (pCVar9 = pCVar8, local_1c != (CHUNKDEF *)0x0)) {
    DEBUG_systemWarning(World2ErrTooManyPassedVars);
  }
  local_1c = pCVar9;
  if ((pCVar8->flags & 0x2000) != 0) {
    if (local_1c != (CHUNKDEF *)0x0) {
      DEBUG_systemWarning(World2ErrTooManyPassedVars);
    }
    local_1c = (CHUNKDEF *)param_5;
  }
  if ((pCVar8->chunkFunc != (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) &&
     (lVar7 = (*pCVar8->chunkFunc)(param_1 + (param_2->flags >> 1 & 1),local_1c,param_7), lVar7 == 0
     )) {
    if ((param_6 == 0) || ((param_1->ckID).longID != 0x54495845)) {
      if ((pCVar8->flags & 4) == 0) {
        iVar6 = 5;
        bVar12 = true;
        pCVar9 = pCVar8;
        pcVar11 = "EXIT";
        do {
          if (iVar6 == 0) break;
          iVar6 = iVar6 + -1;
          bVar12 = pCVar9->id[0] == *pcVar11;
          pCVar9 = (CHUNKDEF *)(pCVar9->id + 1);
          pcVar11 = pcVar11 + 1;
        } while (bVar12);
        param_1 = local_14;
        if (!bVar12) {
          if ((pCVar8->flags & 8) != 0) {
            DEBUG_systemWarning(World2ErrBadChunk);
          }
          uVar1 = pCVar8->flags;
          if ((uVar1 & 0x10) != 0) {
            return local_14;
          }
          if ((uVar1 & 0x20) != 0) {
            return (ChunkType *)0x0;
          }
          param_1 = local_14;
          if ((uVar1 & 0x200) == 0) goto LAB_005273b2;
        }
      }
      else {
        DEBUG_systemError(World2ErrBadChunk);
      }
    }
    local_18 = (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0;
    local_20 = (undefined1  [4])0x0;
  }
  if ((local_18 == (_func___cdecl_long_ChunkType_ptr_void_ptr_void_ptr *)0x0) && (param_6 != 0)) {
    param_3 = param_3 + -1;
    pCVar10 = param_1;
    if (param_3 == 0) goto LAB_0052764c;
    pCVar8 = pCVar8 + 1;
  }
  goto LAB_005273b2;
}
