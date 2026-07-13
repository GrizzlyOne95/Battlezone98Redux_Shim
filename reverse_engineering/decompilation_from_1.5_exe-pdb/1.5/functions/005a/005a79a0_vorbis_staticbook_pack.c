/*
 * Entry: 005a79a0
 * Name: vorbis_staticbook_pack
 * Namespace: Global
 * Signature: int vorbis_staticbook_pack(static_codebook * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_staticbook_pack(static_codebook *param_1,oggpack_buffer *param_2)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  static_codebook *psVar4;
  int iVar5;
  int iVar6;
  long *plVar7;
  uint uVar8;
  int iVar9;
  long lVar10;
  
  psVar4 = param_1;
  oggpack_write(param_2,0x564342,0x18);
  oggpack_write(param_2,param_1->dim,0x10);
  oggpack_write(param_2,param_1->entries,0x18);
  iVar9 = param_1->entries;
  iVar5 = 1;
  if (1 < iVar9) {
    plVar7 = param_1->lengthlist;
    do {
      if (((char)*plVar7 == '\0') ||
         (*(char *)((int)param_1->lengthlist + iVar5) <
          *(char *)((int)param_1->lengthlist + iVar5 + -1))) break;
      iVar5 = iVar5 + 1;
      plVar7 = (long *)((int)plVar7 + 1);
    } while (iVar5 < iVar9);
  }
  if (iVar5 == iVar9) {
    iVar9 = 0;
    oggpack_write(param_2,1,1);
    oggpack_write(param_2,(char)*param_1->lengthlist + -1,5);
    iVar5 = 1;
    if (1 < param_1->entries) {
      do {
        pcVar1 = (char *)((int)psVar4->lengthlist + iVar5);
        cVar2 = *pcVar1;
        cVar3 = pcVar1[-1];
        if (cVar3 < cVar2) {
          if ((int)cVar3 < (int)cVar2) {
            param_1 = (static_codebook *)((int)cVar2 - (int)cVar3);
            do {
              iVar6 = _ilog(psVar4->entries - iVar9);
              oggpack_write(param_2,iVar5 - iVar9,iVar6);
              param_1 = (static_codebook *)((int)&param_1[-1].allocedp + 3);
              iVar9 = iVar5;
            } while (param_1 != (static_codebook *)0x0);
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < psVar4->entries);
    }
    iVar6 = _ilog(psVar4->entries - iVar9);
    oggpack_write(param_2,iVar5 - iVar9,iVar6);
  }
  else {
    oggpack_write(param_2,0,1);
    iVar9 = param_1->entries;
    iVar5 = 0;
    if (0 < iVar9) {
      do {
        if (*(char *)((int)param_1->lengthlist + iVar5) == '\0') break;
        iVar5 = iVar5 + 1;
      } while (iVar5 < iVar9);
    }
    if (iVar5 == iVar9) {
      oggpack_write(param_2,0,1);
      iVar9 = 0;
      if (0 < param_1->entries) {
        do {
          oggpack_write(param_2,*(char *)((int)param_1->lengthlist + iVar9) + -1,5);
          iVar9 = iVar9 + 1;
        } while (iVar9 < param_1->entries);
      }
    }
    else {
      oggpack_write(param_2,1,1);
      iVar9 = 0;
      if (0 < param_1->entries) {
        do {
          if (*(char *)(iVar9 + (int)param_1->lengthlist) == '\0') {
            oggpack_write(param_2,0,1);
          }
          else {
            oggpack_write(param_2,1,1);
            oggpack_write(param_2,*(char *)((int)param_1->lengthlist + iVar9) + -1,5);
          }
          iVar9 = iVar9 + 1;
        } while (iVar9 < param_1->entries);
      }
    }
  }
  oggpack_write(param_2,psVar4->maptype,4);
  if (psVar4->maptype != 0) {
    if ((1 < psVar4->maptype - 1U) || (psVar4->quantlist == (long *)0x0)) {
      return -1;
    }
    oggpack_write(param_2,psVar4->q_min,0x20);
    oggpack_write(param_2,psVar4->q_delta,0x20);
    oggpack_write(param_2,psVar4->q_quant + -1,4);
    oggpack_write(param_2,psVar4->q_sequencep,1);
    if (psVar4->maptype == 1) {
      lVar10 = _book_maptype1_quantvals(psVar4);
    }
    else if (psVar4->maptype == 2) {
      lVar10 = psVar4->entries * psVar4->dim;
    }
    else {
      lVar10 = -1;
    }
    iVar9 = 0;
    if (0 < lVar10) {
      do {
        uVar8 = psVar4->quantlist[iVar9] >> 0x1f;
        oggpack_write(param_2,(psVar4->quantlist[iVar9] ^ uVar8) - uVar8,psVar4->q_quant);
        iVar9 = iVar9 + 1;
      } while (iVar9 < lVar10);
    }
  }
  return 0;
}
