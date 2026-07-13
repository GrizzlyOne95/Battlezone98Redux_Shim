/*
 * Entry: 005a7bf0
 * Name: vorbis_staticbook_unpack
 * Namespace: Global
 * Signature: static_codebook * vorbis_staticbook_unpack(oggpack_buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

static_codebook * __cdecl vorbis_staticbook_unpack(oggpack_buffer *param_1)

{
  size_t _Size;
  static_codebook *psVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  long *plVar6;
  int iVar7;
  long lVar8;
  int local_4;
  
  psVar1 = calloc(1,0x28);
  psVar1->allocedp = 1;
  iVar2 = oggpack_read(param_1,0x18);
  if (iVar2 == 0x564342) {
    lVar3 = oggpack_read(param_1,0x10);
    psVar1->dim = lVar3;
    uVar4 = oggpack_read(param_1,0x18);
    psVar1->entries = uVar4;
    if (uVar4 != 0xffffffff) {
      iVar2 = _ilog(psVar1->dim);
      iVar5 = _ilog(uVar4);
      if (iVar2 + iVar5 < 0x19) {
        iVar2 = oggpack_read(param_1,1);
        if (iVar2 == 0) {
          iVar2 = oggpack_read(param_1,1);
          _Size = psVar1->entries;
          iVar5 = oggpack_bytes(param_1);
          if (param_1->storage - iVar5 < (int)(((uint)(iVar2 == 0) * 4 + 1) * _Size + 7) >> 3)
          goto LAB_005a7ec2;
          plVar6 = malloc(_Size);
          psVar1->lengthlist = plVar6;
          if (iVar2 == 0) {
            iVar2 = 0;
            if (0 < psVar1->entries) {
              do {
                iVar5 = oggpack_read(param_1,5);
                if (iVar5 == -1) goto LAB_005a7ec2;
                *(char *)(iVar2 + (int)psVar1->lengthlist) = (char)iVar5 + '\x01';
                iVar2 = iVar2 + 1;
              } while (iVar2 < psVar1->entries);
            }
          }
          else {
            iVar2 = 0;
            if (0 < psVar1->entries) {
              do {
                iVar5 = oggpack_read(param_1,1);
                if (iVar5 == 0) {
                  *(undefined1 *)(iVar2 + (int)psVar1->lengthlist) = 0;
                }
                else {
                  iVar5 = oggpack_read(param_1,5);
                  if (iVar5 == -1) goto LAB_005a7ec2;
                  *(char *)(iVar2 + (int)psVar1->lengthlist) = (char)iVar5 + '\x01';
                }
                iVar2 = iVar2 + 1;
              } while (iVar2 < psVar1->entries);
            }
          }
        }
        else {
          if (iVar2 != 1) goto LAB_005a7ec2;
          local_4 = oggpack_read(param_1,5);
          iVar2 = local_4 + 1;
          if (iVar2 == 0) goto LAB_005a7ec2;
          plVar6 = malloc(psVar1->entries);
          iVar5 = 0;
          psVar1->lengthlist = plVar6;
          if (0 < psVar1->entries) {
            do {
              iVar7 = _ilog(psVar1->entries - iVar5);
              iVar7 = oggpack_read(param_1,iVar7);
              if (((iVar7 == -1) || (0x1f < local_4)) || (psVar1->entries - iVar5 < iVar7))
              goto LAB_005a7ec2;
              if (0 < iVar7) {
                if (1 < iVar7 + -1 >> ((byte)local_4 & 0x1f)) goto LAB_005a7ec2;
                if (0 < iVar7) {
                  do {
                    *(char *)(iVar5 + (int)psVar1->lengthlist) = (char)iVar2;
                    iVar5 = iVar5 + 1;
                    iVar7 = iVar7 + -1;
                  } while (iVar7 != 0);
                }
              }
              local_4 = local_4 + 1;
              iVar2 = iVar2 + 1;
            } while (iVar5 < psVar1->entries);
          }
        }
        iVar2 = oggpack_read(param_1,4);
        psVar1->maptype = iVar2;
        if (iVar2 == 0) {
          return psVar1;
        }
        if (iVar2 - 1U < 2) {
          lVar3 = oggpack_read(param_1,0x20);
          psVar1->q_min = lVar3;
          lVar3 = oggpack_read(param_1,0x20);
          psVar1->q_delta = lVar3;
          iVar2 = oggpack_read(param_1,4);
          psVar1->q_quant = iVar2 + 1;
          iVar2 = oggpack_read(param_1,1);
          psVar1->q_sequencep = iVar2;
          if (iVar2 != -1) {
            lVar3 = 0;
            if (psVar1->maptype == 1) {
              if (psVar1->dim == 0) {
                lVar3 = 0;
              }
              else {
                lVar3 = _book_maptype1_quantvals(psVar1);
              }
            }
            else if (psVar1->maptype == 2) {
              lVar3 = psVar1->dim * psVar1->entries;
            }
            iVar2 = oggpack_bytes(param_1);
            if (psVar1->q_quant * lVar3 + 7 >> 3 <= param_1->storage - iVar2) {
              plVar6 = malloc(lVar3 * 4);
              iVar2 = 0;
              psVar1->quantlist = plVar6;
              if (0 < lVar3) {
                do {
                  lVar8 = oggpack_read(param_1,psVar1->q_quant);
                  psVar1->quantlist[iVar2] = lVar8;
                  iVar2 = iVar2 + 1;
                } while (iVar2 < lVar3);
              }
              if (lVar3 == 0) {
                return psVar1;
              }
              if (psVar1->quantlist[lVar3 + -1] != -1) {
                return psVar1;
              }
            }
          }
        }
      }
    }
  }
LAB_005a7ec2:
  vorbis_staticbook_destroy(psVar1);
  return (static_codebook *)0x0;
}
