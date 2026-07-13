/*
 * Entry: 005b4ec0
 * Name: floor0_inverse1
 * Namespace: Global
 * Signature: void * floor0_inverse1(vorbis_block * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor0_inverse1(vorbis_block *param_1,void *param_2)

{
  oggpack_buffer *poVar1;
  codebook *pcVar2;
  int iVar3;
  undefined4 uVar4;
  void *pvVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  long lVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  pvVar5 = param_2;
  iVar12 = *(int *)((int)param_2 + 0x14);
  poVar1 = &param_1->opb;
  iVar6 = oggpack_read(poVar1,*(undefined4 *)(iVar12 + 0xc));
  if (0 < iVar6) {
    uVar4 = *(undefined4 *)(iVar12 + 0xc);
    iVar3 = *(int *)(iVar12 + 0x10);
    iVar7 = _ilog(*(uint *)(iVar12 + 0x14));
    iVar7 = oggpack_read(poVar1,iVar7);
    if ((iVar7 != -1) && (iVar7 < *(int *)(iVar12 + 0x14))) {
      param_2 = (void *)0x0;
      pcVar2 = (codebook *)
               (*(int *)((int)param_1->vd->vi->codec_setup + 0xb20) +
               *(int *)(iVar12 + 0x18 + iVar7 * 4) * 0x38);
      pfVar8 = _vorbis_block_alloc(param_1,(*(int *)((int)pvVar5 + 4) + pcVar2->dim) * 4 + 4);
      lVar9 = vorbis_book_decodev_set(pcVar2,pfVar8,poVar1,*(int *)((int)pvVar5 + 4));
      if (lVar9 != -1) {
        iVar12 = *(int *)((int)pvVar5 + 4);
        iVar7 = 0;
        if (0 < iVar12) {
          do {
            iVar11 = 0;
            iVar10 = iVar7;
            if (iVar7 < iVar12) {
              do {
                iVar10 = iVar7;
                if (pcVar2->dim <= iVar11) break;
                iVar10 = iVar7 + 1;
                iVar11 = iVar11 + 1;
                pfVar8[iVar7] = pfVar8[iVar7] + (float)param_2;
                iVar7 = iVar10;
              } while (iVar10 < *(int *)((int)pvVar5 + 4));
            }
            iVar12 = *(int *)((int)pvVar5 + 4);
            param_2 = (void *)pfVar8[iVar10 + -1];
            iVar7 = iVar10;
          } while (iVar10 < iVar12);
        }
        pfVar8[*(int *)((int)pvVar5 + 4)] =
             ((float)iVar6 / (float)((1 << ((byte)uVar4 & 0x1f)) + -1)) * (float)iVar3;
        return pfVar8;
      }
    }
  }
  return (void *)0x0;
}
