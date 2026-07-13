/*
 * Entry: 005a6af0
 * Name: _make_words
 * Namespace: Global
 * Signature: uint * _make_words(char * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint * __cdecl _make_words(char *param_1,long param_2,long param_3)

{
  char cVar1;
  uint uVar2;
  long lVar3;
  uint *_Memory;
  int iVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;
  uint *local_88;
  uint local_84 [33];
  
  lVar3 = param_3;
  if (param_3 == 0) {
    lVar3 = param_2;
  }
  _Memory = malloc(lVar3 * 4);
  memset(local_84,0,0x84);
  iVar10 = 0;
  puVar8 = _Memory;
  if (0 < param_2) {
    do {
      iVar7 = (int)param_1[iVar10];
      if (iVar7 < 1) {
        if (param_3 == 0) {
          puVar8 = puVar8 + 1;
        }
      }
      else {
        uVar5 = local_84[iVar7];
        if ((iVar7 < 0x20) && (uVar5 >> (param_1[iVar10] & 0x1fU) != 0)) {
          free(_Memory);
          return (uint *)0x0;
        }
        *puVar8 = uVar5;
        puVar8 = puVar8 + 1;
        iVar4 = iVar7;
        do {
          if ((local_84[iVar4] & 1) != 0) {
            if (iVar4 == 1) {
              local_84[1] = local_84[1] + 1;
            }
            else {
              local_84[iVar4] = local_84[iVar4 + -1] * 2;
            }
            break;
          }
          local_84[iVar4] = local_84[iVar4] + 1;
          iVar4 = iVar4 + -1;
        } while (0 < iVar4);
        while ((iVar4 = iVar7 + 1, iVar4 < 0x21 && (uVar2 = local_84[iVar4], uVar2 >> 1 == uVar5)))
        {
          local_84[iVar4] = local_84[iVar7] * 2;
          uVar5 = uVar2;
          iVar7 = iVar4;
        }
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < param_2);
  }
  if (param_3 != 1) {
    iVar10 = 1;
    do {
      if ((local_84[iVar10] & 0xffffffffU >> (0x20U - (char)iVar10 & 0x1f)) != 0) {
        free(_Memory);
        return (uint *)0x0;
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < 0x21);
  }
  iVar10 = 0;
  puVar8 = _Memory;
  local_88 = _Memory;
  if (0 < param_2) {
    do {
      cVar1 = param_1[iVar10];
      uVar5 = 0;
      iVar7 = 0;
      puVar9 = puVar8;
      if (0 < cVar1) {
        do {
          bVar6 = (byte)iVar7;
          iVar7 = iVar7 + 1;
          uVar5 = uVar5 * 2 | *puVar8 >> (bVar6 & 0x1f) & 1;
          puVar9 = local_88;
        } while (iVar7 < cVar1);
      }
      if ((param_3 == 0) || (cVar1 != '\0')) {
        *puVar9 = uVar5;
        puVar9 = puVar9 + 1;
        local_88 = puVar9;
      }
      iVar10 = iVar10 + 1;
      puVar8 = puVar9;
    } while (iVar10 < param_2);
  }
  return _Memory;
}
