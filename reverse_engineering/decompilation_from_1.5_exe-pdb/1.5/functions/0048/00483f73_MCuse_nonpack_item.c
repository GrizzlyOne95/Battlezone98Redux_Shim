/*
 * Entry: 00483f73
 * Name: MCuse_nonpack_item
 * Namespace: Global
 * Signature: void * MCuse_nonpack_item(MULTICACHE * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void * __cdecl MCuse_nonpack_item(MULTICACHE *param_1,char *param_2)

{
  cachenode *pcVar1;
  char cVar2;
  float fVar3;
  cachenode *pcVar4;
  ulong uVar5;
  FILE *pFVar6;
  int iVar7;
  char *pcVar8;
  MULTICACHE *unaff_EDI;
  int local_10 [2];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  nCacheAccesses = nCacheAccesses + 1;
  if (param_1 == (MULTICACHE *)0x0) {
    param_1 = &GlobalCache;
  }
  pcVar4 = MCFindItem(param_1,param_2);
  if (pcVar4 == (cachenode *)0x0) {
    num_purges_temp = 0;
    if (param_1->MaxCacheSize <= param_1->CacheSize) {
      if (param_1->PurgeHead == (cachenode *)0x0) {
        DEBUG_systemWarning("BattleZone Memory running low (2)");
      }
      else {
        MCReallyNukeItem(param_1,param_1->PurgeHead);
      }
    }
    uVar5 = zixGetFileSize(param_2);
    if ((int)uVar5 < 1) {
      pFVar6 = fopen("symlog.txt","a");
      if (pFVar6 != (FILE *)0x0) {
        fprintf(pFVar6,"%s\n",&zfserr);
        fclose(pFVar6);
      }
      TraceWarning("%s\n");
    }
    else {
      strstr(param_2,".pak");
      while (pcVar4 = calloc(1,uVar5 + 0x29), pcVar4 == (cachenode *)0x0) {
        if (param_1->PurgeHead == (cachenode *)0x0) {
          dump_cache_contents(unaff_EDI);
          DEBUG_systemWarning("BattleZone Memory running low (1)");
          goto LAB_00484076;
        }
        MCReallyNukeItem(param_1,param_1->PurgeHead);
      }
      fVar3 = (float)(int)num_purges_temp;
      if ((int)num_purges_temp < 0) {
        fVar3 = fVar3 + 4.2949673e+09;
      }
      pcVar1 = pcVar4 + 1;
      nCachePurgesPerAlloc = nCachePurgesPerAlloc * 0.9 + fVar3 * 0.1;
      iVar7 = zixReadFileToBuffer(param_2,local_10,pcVar1,uVar5);
      if (iVar7 != 0) {
        iVar7 = compute_hash(param_2);
        pcVar4->Next = param_1->Cache[iVar7];
        param_1->Cache[iVar7] = pcVar4;
        pcVar4->Lock = 1;
        strncpy(pcVar4->assetname,param_2,0xf);
        pcVar4->PurgeNext = (cachenode *)0x0;
        pcVar4->size = uVar5;
        pcVar4->PurgePrev = (cachenode *)0x0;
        pcVar4->protect = false;
        pcVar8 = param_2;
        do {
          cVar2 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        if (3 < (uint)((int)pcVar8 - (int)(param_2 + 1))) {
          pcVar8 = param_2 + (((int)pcVar8 - (int)(param_2 + 1)) - 4);
          iVar7 = (int)local_10 - (int)pcVar8;
          do {
            cVar2 = *pcVar8;
            pcVar8[iVar7] = cVar2;
            pcVar8 = pcVar8 + 1;
          } while (cVar2 != '\0');
          _strlwr((char *)local_10);
          pcVar8 = strstr(".vdf.sdf.odf.stb.vxt.lgt.bzn.mat.hgt.trn",(char *)local_10);
          pcVar4->protect = pcVar8 != (char *)0x0;
          if (pcVar8 != (char *)0x0) {
            uVar5 = crc32((uchar *)pcVar1,uVar5);
            pcVar4->crc32 = uVar5;
          }
        }
        param_1->CacheSize = param_1->CacheSize + 1;
        nCacheMisses = nCacheMisses + 1;
        return pcVar1;
      }
      pFVar6 = fopen("symlog.txt","a");
      if (pFVar6 != (FILE *)0x0) {
        fprintf(pFVar6,"%s\n",&zfserr);
      }
      fclose(pFVar6);
    }
    if (AddonFirst == 0) {
      DEBUG_systemWarning("%s\n");
    }
LAB_00484076:
    pcVar4 = (cachenode *)0x0;
  }
  else {
    if (pcVar4->Lock == 0) {
      MCremove_from_purge(param_1,pcVar4);
    }
    pcVar4->Lock = pcVar4->Lock + 1;
    nCacheHits = nCacheHits + 1;
    if ((pcVar4->protect != false) &&
       (uVar5 = crc32((uchar *)(pcVar4 + 1),pcVar4->size), pcVar4->crc32 != uVar5)) {
                    /* WARNING: Subroutine does not return */
      exit(1);
    }
    pcVar4 = pcVar4 + 1;
  }
  return pcVar4;
}
