/*
 * Entry: 005b2060
 * Name: _01forward
 * Namespace: Global
 * Signature: int _01forward(oggpack_buffer * param_1, void * param_2, int * * param_3, int param_4, long * * param_5, _func___cdecl_int_oggpack_buffer_ptr_int_ptr_int_codebook_ptr * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
_01forward(oggpack_buffer *param_1,void *param_2,int **param_3,int param_4,long **param_5,
          _func___cdecl_int_oggpack_buffer_ptr_int_ptr_int_codebook_ptr *param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  codebook *pcVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  long **pplVar12;
  int iVar13;
  int local_42c;
  int local_428;
  int local_418;
  int local_400 [128];
  int local_200 [128];
  
  piVar1 = *(int **)param_2;
  iVar2 = piVar1[3];
  iVar3 = **(int **)((int)param_2 + 0x10);
  iVar4 = piVar1[2];
  iVar7 = (piVar1[1] - *piVar1) / iVar4;
  memset(local_200,0,0x200);
  memset(local_400,0,0x200);
  local_42c = 0;
  if (0 < *(int *)((int)param_2 + 8)) {
    do {
      iVar13 = 0;
      if (0 < iVar7) {
        do {
          if ((local_42c == 0) && (local_428 = 0, 0 < param_4)) {
            do {
              piVar11 = param_5[local_428] + iVar13;
              iVar8 = *piVar11;
              iVar10 = 1;
              if (1 < iVar3) {
                do {
                  piVar11 = piVar11 + 1;
                  iVar8 = iVar8 * iVar2;
                  if (iVar10 + iVar13 < iVar7) {
                    iVar8 = iVar8 + *piVar11;
                  }
                  iVar10 = iVar10 + 1;
                } while (iVar10 < iVar3);
              }
              if (iVar8 < (*(codebook **)((int)param_2 + 0x10))->entries) {
                iVar8 = vorbis_book_encode(*(codebook **)((int)param_2 + 0x10),iVar8,param_1);
                *(int *)((int)param_2 + 0x24) = *(int *)((int)param_2 + 0x24) + iVar8;
              }
              local_428 = local_428 + 1;
            } while (local_428 < param_4);
          }
          local_418 = 0;
          if (0 < iVar3) {
            iVar8 = iVar13 * iVar4;
            do {
              if (iVar7 <= iVar13) goto LAB_005b228a;
              iVar10 = *piVar1;
              bVar6 = (byte)local_42c & 0x1f;
              if (0 < param_4) {
                local_428 = param_4;
                pplVar12 = param_5;
                do {
                  if (local_42c == 0) {
                    local_400[(*pplVar12)[iVar13]] = local_400[(*pplVar12)[iVar13]] + iVar4;
                  }
                  if (((piVar1[(*pplVar12)[iVar13] + 6] & (1 << bVar6 | 1U >> 0x20 - bVar6)) != 0)
                     && (pcVar5 = *(codebook **)
                                   (*(int *)(*(int *)((int)param_2 + 0x14) + (*pplVar12)[iVar13] * 4
                                            ) + local_42c * 4), pcVar5 != (codebook *)0x0)) {
                    iVar9 = (*param_6)(param_1,(int *)(*(int *)(((int)param_3 - (int)param_5) +
                                                               (int)pplVar12) + (iVar10 + iVar8) * 4
                                                      ),iVar4,pcVar5);
                    *(int *)((int)param_2 + 0x20) = *(int *)((int)param_2 + 0x20) + iVar9;
                    local_200[(*pplVar12)[iVar13]] = local_200[(*pplVar12)[iVar13]] + iVar9;
                  }
                  pplVar12 = pplVar12 + 1;
                  local_428 = local_428 + -1;
                } while (local_428 != 0);
              }
              iVar8 = iVar8 + iVar4;
              local_418 = local_418 + 1;
              iVar13 = iVar13 + 1;
            } while (local_418 < iVar3);
          }
        } while (iVar13 < iVar7);
      }
LAB_005b228a:
      local_42c = local_42c + 1;
    } while (local_42c < *(int *)((int)param_2 + 8));
  }
  return 0;
}
