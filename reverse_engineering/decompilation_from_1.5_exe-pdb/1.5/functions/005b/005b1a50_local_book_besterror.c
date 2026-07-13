/*
 * Entry: 005b1a50
 * Name: local_book_besterror
 * Namespace: Global
 * Signature: int local_book_besterror(codebook * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl local_book_besterror(codebook *param_1,int *param_2)

{
  static_codebook **ppsVar1;
  int iVar2;
  long *plVar3;
  int iVar4;
  codebook *pcVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  int local_64;
  int local_54;
  int local_40 [16];
  
  iVar15 = param_1->delta;
  iVar2 = param_1->dim;
  iVar13 = param_1->quantvals;
  iVar10 = param_1->minval;
  iVar12 = iVar13 >> 1;
  local_64 = 0;
  local_40[8] = 0;
  local_40[9] = 0;
  local_40[10] = 0;
  local_40[0xb] = 0;
  local_40[0xc] = 0;
  local_40[0xd] = 0;
  local_40[0xe] = 0;
  local_40[0xf] = 0;
  local_54 = iVar2;
  if (iVar15 == 1) {
    if (0 < iVar2) {
      piVar6 = local_40 + iVar2 + 8;
      do {
        piVar14 = (int *)((int)piVar6 + (int)param_2 + (-4 - (int)(local_40 + 8)));
        piVar6 = piVar6 + -1;
        iVar4 = *piVar14 - iVar10;
        if (iVar4 < iVar12) {
          iVar7 = (iVar12 - iVar4) * 2 + -1;
        }
        else {
          iVar7 = (iVar4 - iVar12) * 2;
        }
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        else if (iVar13 <= iVar7) {
          iVar7 = iVar13 + -1;
        }
        local_64 = local_64 * iVar13 + iVar7;
        local_54 = local_54 + -1;
        *piVar6 = iVar4 + iVar10;
      } while (local_54 != 0);
    }
  }
  else if (0 < iVar2) {
    piVar6 = local_40 + iVar2 + 8;
    do {
      piVar14 = (int *)((int)param_2 + (-4 - (int)(local_40 + 8)) + (int)piVar6);
      piVar6 = piVar6 + -1;
      iVar4 = ((*piVar14 - iVar10) + (iVar15 >> 1)) / iVar15;
      if (iVar4 < iVar12) {
        iVar7 = (iVar12 - iVar4) * 2 + -1;
      }
      else {
        iVar7 = (iVar4 - iVar12) * 2;
      }
      if (iVar7 < 0) {
        iVar7 = 0;
      }
      else if (iVar13 <= iVar7) {
        iVar7 = iVar13 + -1;
      }
      local_64 = local_64 * iVar13 + iVar7;
      local_54 = local_54 + -1;
      *piVar6 = iVar4 * iVar15 + iVar10;
    } while (local_54 != 0);
  }
  ppsVar1 = &param_1->c;
  if (*(char *)((int)(*ppsVar1)->lengthlist + local_64) < '\x01') {
    iVar12 = param_1->entries;
    iVar10 = (iVar13 + -1) * iVar15 + iVar10;
    param_1 = (codebook *)0xffffffff;
    local_40[0] = 0;
    local_40[1] = 0;
    local_40[2] = 0;
    local_40[3] = 0;
    local_40[4] = 0;
    local_40[5] = 0;
    local_40[6] = 0;
    local_40[7] = 0;
    local_54 = 0;
    if (0 < iVar12) {
      plVar3 = (*ppsVar1)->lengthlist;
      do {
        iVar13 = 0;
        if ('\0' < *(char *)((int)plVar3 + local_54)) {
          iVar7 = 0;
          iVar4 = 0;
          if (1 < iVar2) {
            iVar11 = (iVar2 - 2U >> 1) + 1;
            iVar4 = iVar11 * 2;
            piVar6 = param_2;
            do {
              iVar8 = *(int *)((int)local_40 + -(int)param_2 + (int)piVar6) - *piVar6;
              iVar9 = *(int *)((int)local_40 + -(int)param_2 + -4 + (int)(piVar6 + 2)) - piVar6[1];
              iVar13 = iVar13 + iVar8 * iVar8;
              iVar7 = iVar7 + iVar9 * iVar9;
              iVar11 = iVar11 + -1;
              piVar6 = piVar6 + 2;
            } while (iVar11 != 0);
          }
          iVar11 = 0;
          if (iVar4 < iVar2) {
            iVar11 = (local_40[iVar4] - param_2[iVar4]) * (local_40[iVar4] - param_2[iVar4]);
          }
          pcVar5 = (codebook *)(iVar11 + iVar7 + iVar13);
          if ((param_1 == (codebook *)0xffffffff) || ((int)pcVar5 < (int)param_1)) {
            piVar6 = local_40;
            piVar14 = local_40 + 8;
            for (iVar13 = 8; param_1 = pcVar5, local_64 = local_54, iVar13 != 0;
                iVar13 = iVar13 + -1) {
              *piVar14 = *piVar6;
              piVar6 = piVar6 + 1;
              piVar14 = piVar14 + 1;
            }
          }
        }
        iVar13 = 0;
        if (iVar10 <= local_40[0]) {
          piVar6 = local_40;
          do {
            iVar13 = iVar13 + 1;
            *piVar6 = 0;
            piVar6 = local_40 + iVar13;
          } while (iVar10 <= local_40[iVar13]);
        }
        piVar6 = local_40 + iVar13;
        if (-1 < local_40[iVar13]) {
          *piVar6 = local_40[iVar13] + iVar15;
        }
        local_54 = local_54 + 1;
        *piVar6 = -*piVar6;
      } while (local_54 < iVar12);
    }
  }
  iVar15 = 0;
  if ((-1 < local_64) && (0 < iVar2)) {
    do {
      *param_2 = *param_2 - local_40[iVar15 + 8];
      iVar15 = iVar15 + 1;
      param_2 = param_2 + 1;
    } while (iVar15 < iVar2);
  }
  return local_64;
}
