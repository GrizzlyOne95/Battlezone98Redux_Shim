/*
 * Entry: 00526faa
 * Name: CheckRevision
 * Namespace: Global
 * Signature: long CheckRevision(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __cdecl CheckRevision(ChunkType *param_1,void *param_2,void *param_3)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  bool bVar7;
  char local_314 [4];
  ChunkType *local_310;
  void *local_30c;
  char local_308 [116];
  undefined1 local_294 [140];
  byte local_208 [256];
  char local_108 [4];
  undefined1 local_104;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_294;
  local_310 = param_1;
  local_30c = param_2;
  uVar6 = 0;
  while (uVar2 = MsnChunkRevInfos[uVar6].id,
        (((uint)(ushort)((short)uVar2 << 8) | uVar2 >> 8 & 0xff) << 0x10 | uVar2 >> 0x18 |
        uVar2 >> 8 & 0xff00) != (param_1->ckID).longID) {
    uVar6 = uVar6 + 1;
    if (6 < uVar6) {
      strncpy(local_108,(char *)param_1,4);
      DEBUG_systemWarning("Unknown revision chunk % found in %s");
      return 1;
    }
  }
  if (uVar6 != 0) {
    if (param_1[1].ckID.longID != MsnChunkRevInfos[uVar6].currentRev) {
      strncpy(local_108,(char *)param_1,4);
      local_104 = 0;
      DEBUG_systemWarning("Bad revision for %s chunk in file %s");
      return 0;
    }
    return 1;
  }
  _splitpath(param_2,local_314,local_108,local_308,(char *)local_208);
  uVar6 = 0;
  do {
    pbVar3 = (byte *)FileRevInfos[uVar6].extension;
    pbVar5 = local_208;
    do {
      bVar1 = *pbVar3;
      bVar7 = bVar1 < *pbVar5;
      if (bVar1 != *pbVar5) {
LAB_005270ae:
        iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
        goto LAB_005270b3;
      }
      if (bVar1 == 0) break;
      bVar1 = pbVar3[1];
      bVar7 = bVar1 < pbVar5[1];
      if (bVar1 != pbVar5[1]) goto LAB_005270ae;
      pbVar3 = pbVar3 + 2;
      pbVar5 = pbVar5 + 2;
    } while (bVar1 != 0);
    iVar4 = 0;
LAB_005270b3:
    if (iVar4 == 0) {
      if (local_310[1].ckID.longID == FileRevInfos[uVar6].currentRev) {
        return 1;
      }
      DEBUG_systemWarning("Bad BWD revision for file %s");
      return 0;
    }
    uVar6 = uVar6 + 1;
    if (9 < uVar6) {
      DEBUG_systemWarning("Unknown file type found: %s");
      return 1;
    }
  } while( true );
}
