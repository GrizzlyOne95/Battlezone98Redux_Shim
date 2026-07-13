/*
 * Entry: 005a7470
 * Name: vorbis_book_init_decode
 * Namespace: Global
 * Signature: int vorbis_book_init_decode(codebook * param_1, static_codebook * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

int __cdecl vorbis_book_init_decode(codebook *param_1,static_codebook *param_2)

{
  long *plVar1;
  char cVar2;
  codebook *pcVar3;
  static_codebook *psVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  float *pfVar9;
  int *piVar10;
  int iVar11;
  char *pcVar12;
  undefined1 *puVar13;
  uint uVar14;
  uint uVar15;
  codebook *pcVar16;
  uint uVar17;
  size_t asStackY_38 [3];
  codebook *local_10;
  int local_c;
  
  psVar4 = param_2;
  pcVar3 = param_1;
  pcVar16 = (codebook *)0x0;
  asStackY_38[2] = 0x5a7487;
  memset();
  iVar11 = param_2->entries;
  iVar5 = 0;
  if (0 < iVar11) {
    do {
      if ('\0' < *(char *)((int)param_2->lengthlist + iVar5)) {
        pcVar16 = (codebook *)((int)&pcVar16->dim + 1);
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < iVar11);
  }
  param_1->entries = iVar11;
  param_1->used_entries = (long)pcVar16;
  param_1->dim = param_2->dim;
  if (0 < (int)pcVar16) {
    asStackY_38[2] = 0x5a74cc;
    puVar6 = _make_words((char *)param_2->lengthlist,param_2->entries,(long)pcVar16);
    iVar11 = (int)pcVar16 * -4;
    if (puVar6 == (uint *)0x0) {
      *(codebook **)(&stack0xffffffdc + iVar11) = param_1;
      *(undefined4 *)(&stack0xffffffd8 + iVar11) = 0x5a74f3;
      vorbis_book_clear(*(codebook **)(&stack0xffffffdc + iVar11));
      return -1;
    }
    if (0 < (int)pcVar16) {
      puVar7 = puVar6;
      param_1 = pcVar16;
      do {
        uVar14 = *puVar7 << 0x10 | *puVar7 >> 0x10;
        uVar14 = (uVar14 >> 8 ^ uVar14 << 8) & 0xff00ff ^ uVar14 << 8;
        uVar14 = (uVar14 >> 4 ^ uVar14 << 4) & 0xf0f0f0f ^ uVar14 << 4;
        uVar14 = (uVar14 >> 2 ^ uVar14 * 4) & 0x33333333 ^ uVar14 * 4;
        *puVar7 = (uVar14 >> 1 ^ uVar14 * 2) & 0x55555555 ^ uVar14 * 2;
        *(uint **)(&stack0xffffffe0 + (iVar11 - (int)puVar6) + (int)puVar7) = puVar7;
        puVar7 = puVar7 + 1;
        param_1 = (codebook *)((int)&param_1[-1].delta + 3);
      } while (param_1 != (codebook *)0x0);
    }
    *(code **)(&stack0xffffffdc + iVar11) = sort32a;
    *(undefined4 *)(&stack0xffffffd8 + iVar11) = 4;
    *(codebook **)(&stack0xffffffd4 + iVar11) = pcVar16;
    asStackY_38[2 - (int)pcVar16] = (size_t)(&stack0xffffffe0 + iVar11);
    asStackY_38[1 - (int)pcVar16] = 0x5a7597;
    qsort((void *)asStackY_38[2 - (int)pcVar16],*(size_t *)(&stack0xffffffd4 + iVar11),
          *(size_t *)(&stack0xffffffd8 + iVar11),*(_PtFuncCompare **)(&stack0xffffffdc + iVar11));
    iVar5 = (int)pcVar16 * -8;
    piVar10 = (int *)(&stack0xffffffe0 + iVar5);
    *(undefined4 *)(&stack0xffffffdc + iVar11) = 0x5a75a2;
    *(int *)(&stack0xffffffdc + (int)pcVar16 * -8) = (int)pcVar16 * 4;
    *(undefined4 *)(&stack0xffffffd8 + (int)pcVar16 * -8) = 0x5a75af;
    puVar7 = malloc(*(size_t *)(&stack0xffffffdc + (int)pcVar16 * -8));
    pcVar3->codelist = puVar7;
    iVar8 = 0;
    if (0 < (int)pcVar16) {
      do {
        *(int *)(&stack0xffffffe0 +
                (*(int *)(&stack0xffffffe0 + iVar8 * 4 + iVar11) - (int)puVar6 >> 2) * 4 + iVar5) =
             iVar8;
        iVar8 = iVar8 + 1;
      } while (iVar8 < (int)pcVar16);
      if (0 < (int)pcVar16) {
        local_10 = pcVar16;
        do {
          iVar11 = *piVar10;
          puVar7 = (uint *)(((int)puVar6 - (int)(&stack0xffffffe0 + iVar5)) + (int)piVar10);
          piVar10 = piVar10 + 1;
          local_10 = (codebook *)((int)&local_10[-1].delta + 3);
          pcVar3->codelist[iVar11] = *puVar7;
        } while (local_10 != (codebook *)0x0);
      }
    }
    *(uint **)(&stack0xffffffdc + (int)pcVar16 * -8) = puVar6;
    *(undefined4 *)(&stack0xffffffd8 + (int)pcVar16 * -8) = 0x5a7614;
    free(*(void **)(&stack0xffffffdc + (int)pcVar16 * -8));
    *(undefined1 **)(&stack0xffffffd8 + (int)pcVar16 * -8) = &stack0xffffffe0 + iVar5;
    *(codebook **)(&stack0xffffffd4 + (int)pcVar16 * -8) = pcVar16;
    asStackY_38[(int)pcVar16 * -2 + 2] = (size_t)param_2;
    asStackY_38[(int)pcVar16 * -2 + 1] = 0x5a761f;
    pfVar9 = _book_unquantize((static_codebook *)asStackY_38[(int)pcVar16 * -2 + 2],
                              *(int *)(&stack0xffffffd4 + (int)pcVar16 * -8),
                              *(int **)(&stack0xffffffd8 + (int)pcVar16 * -8));
    asStackY_38[(int)pcVar16 * -2 + 1] = (int)pcVar16 * 4;
    pcVar3->valuelist = pfVar9;
    asStackY_38[(int)pcVar16 * -2] = 0x5a762c;
    piVar10 = malloc(asStackY_38[(int)pcVar16 * -2 + 1]);
    pcVar3->dec_index = piVar10;
    iVar11 = 0;
    iVar8 = 0;
    if (0 < param_2->entries) {
      do {
        if ('\0' < *(char *)(iVar11 + (int)param_2->lengthlist)) {
          pcVar3->dec_index[*(int *)(&stack0xffffffe0 + iVar8 * 4 + iVar5)] = iVar11;
          iVar8 = iVar8 + 1;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < param_2->entries);
    }
    *(int *)(&stack0xffffffdc + (int)pcVar16 * -8) = iVar8;
    *(undefined4 *)(&stack0xffffffd8 + (int)pcVar16 * -8) = 0x5a7663;
    pcVar12 = malloc(*(size_t *)(&stack0xffffffdc + (int)pcVar16 * -8));
    iVar11 = 0;
    pcVar3->dec_codelengths = pcVar12;
    plVar1 = &param_2->entries;
    param_2 = (static_codebook *)0x0;
    if (0 < *plVar1) {
      do {
        cVar2 = *(char *)(iVar11 + (int)psVar4->lengthlist);
        if ('\0' < cVar2) {
          iVar8 = (int)param_2 * 4;
          param_2 = (static_codebook *)((int)&param_2->dim + 1);
          pcVar3->dec_codelengths[*(int *)(&stack0xffffffe0 + iVar8 + iVar5)] = cVar2;
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < psVar4->entries);
    }
    iVar5 = 0;
    iVar11 = 0;
    for (uVar14 = pcVar3->used_entries; uVar14 != 0; uVar14 = uVar14 >> 1) {
      iVar11 = iVar11 + 1;
    }
    pcVar3->dec_firsttablen = iVar11 + -4;
    if (iVar11 + -4 < 5) {
      pcVar3->dec_firsttablen = 5;
    }
    if (8 < pcVar3->dec_firsttablen) {
      pcVar3->dec_firsttablen = 8;
    }
    iVar11 = 1 << ((byte)pcVar3->dec_firsttablen & 0x1f);
    *(undefined4 *)(&stack0xffffffdc + (int)pcVar16 * -8) = 4;
    *(int *)(&stack0xffffffd8 + (int)pcVar16 * -8) = iVar11;
    *(undefined4 *)(&stack0xffffffd4 + (int)pcVar16 * -8) = 0x5a76da;
    puVar6 = calloc(*(size_t *)(&stack0xffffffd8 + (int)pcVar16 * -8),
                    *(size_t *)(&stack0xffffffdc + (int)pcVar16 * -8));
    pcVar3->dec_firsttable = puVar6;
    pcVar3->dec_maxlength = 0;
    if (0 < (int)param_2) {
      do {
        iVar8 = (int)pcVar3->dec_codelengths[iVar5];
        if (pcVar3->dec_maxlength < iVar8) {
          pcVar3->dec_maxlength = iVar8;
        }
        cVar2 = pcVar3->dec_codelengths[iVar5];
        if ((int)cVar2 <= pcVar3->dec_firsttablen) {
          uVar14 = pcVar3->codelist[iVar5] << 0x10 | pcVar3->codelist[iVar5] >> 0x10;
          uVar14 = (uVar14 >> 8 ^ uVar14 << 8) & 0xff00ff ^ uVar14 << 8;
          uVar14 = (uVar14 >> 4 ^ uVar14 << 4) & 0xf0f0f0f ^ uVar14 << 4;
          uVar14 = (uVar14 >> 2 ^ uVar14 * 4) & 0x33333333 ^ uVar14 * 4;
          param_1 = (codebook *)0x0;
          if (0 < 1 << ((char)pcVar3->dec_firsttablen - cVar2 & 0x1fU)) {
            do {
              pcVar3->dec_firsttable
              [(int)param_1 << (pcVar3->dec_codelengths[iVar5] & 0x1fU) |
               (uVar14 >> 1 ^ uVar14 * 2) & 0x55555555 ^ uVar14 * 2] = iVar5 + 1;
              param_1 = (codebook *)((int)&param_1->dim + 1);
            } while ((int)param_1 <
                     1 << ((char)pcVar3->dec_firsttablen - pcVar3->dec_codelengths[iVar5] & 0x1fU));
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < (int)param_2);
    }
    iVar5 = pcVar3->dec_firsttablen;
    param_1 = (codebook *)0x0;
    local_c = 0;
    local_10 = (codebook *)0x0;
    if (0 < iVar11) {
      do {
        uVar17 = (int)local_10 << (0x20U - (char)pcVar3->dec_firsttablen & 0x1f);
        uVar15 = uVar17 << 0x10 | uVar17 >> 0x10;
        uVar14 = (uVar15 >> 8 ^ uVar15 << 8) & 0xff00ff ^ uVar15 << 8;
        uVar14 = (uVar14 >> 4 ^ uVar14 << 4) & 0xf0f0f0f ^ uVar14 << 4;
        uVar14 = (uVar14 >> 2 ^ uVar14 * 4) & 0x33333333 ^ uVar14 * 4;
        if (pcVar3->dec_firsttable[(uVar14 >> 1 ^ uVar14 * 2) & 0x55555555 ^ uVar14 * 2] == 0) {
          puVar13 = (undefined1 *)((int)&param_1->dim + 1);
          if ((int)puVar13 < (int)param_2) {
            puVar6 = pcVar3->codelist + (int)((int)&param_1->dim + 1);
            do {
              if (uVar17 < *puVar6) break;
              puVar13 = puVar13 + 1;
              param_1 = (codebook *)((int)&param_1->dim + 1);
              puVar6 = puVar6 + 1;
            } while ((int)puVar13 < (int)param_2);
          }
          if (local_c < (int)param_2) {
            puVar6 = pcVar3->codelist + local_c;
            do {
              if (uVar17 < (-2 << (0x1fU - (char)iVar5 & 0x1f) & *puVar6)) break;
              local_c = local_c + 1;
              puVar6 = puVar6 + 1;
            } while (local_c < (int)param_2);
          }
          uVar14 = (int)param_2 - local_c;
          pcVar16 = param_1;
          if ((codebook *)0x7fff < param_1) {
            pcVar16 = (codebook *)0x7fff;
          }
          if (0x7fff < uVar14) {
            uVar14 = 0x7fff;
          }
          uVar15 = (uVar15 >> 8 ^ uVar15 << 8) & 0xff00ff ^ uVar15 << 8;
          uVar15 = (uVar15 >> 4 ^ uVar15 << 4) & 0xf0f0f0f ^ uVar15 << 4;
          uVar15 = (uVar15 >> 2 ^ uVar15 * 4) & 0x33333333 ^ uVar15 * 4;
          pcVar3->dec_firsttable[(uVar15 >> 1 ^ uVar15 * 2) & 0x55555555 ^ uVar15 * 2] =
               ((uint)pcVar16 | 0xffff0000) << 0xf | uVar14;
        }
        local_10 = (codebook *)((int)local_10 + 1);
      } while ((int)local_10 < iVar11);
    }
  }
  return 0;
}
