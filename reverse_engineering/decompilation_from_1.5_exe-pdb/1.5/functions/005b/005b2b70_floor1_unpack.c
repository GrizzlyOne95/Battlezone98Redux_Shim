/*
 * Entry: 005b2b70
 * Name: floor1_unpack
 * Namespace: Global
 * Signature: void * floor1_unpack(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor1_unpack(vorbis_info *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  int *_Memory;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  size_t _NumOfElements;
  int iVar6;
  int *piVar7;
  int *local_11c;
  int local_114;
  undefined4 local_104 [65];
  
  pvVar1 = param_1->codec_setup;
  local_11c = (int *)0xffffffff;
  _Memory = calloc(1,0x460);
  iVar2 = oggpack_read(param_2,5);
  iVar6 = 0;
  *_Memory = iVar2;
  piVar5 = _Memory;
  if (0 < iVar2) {
    do {
      iVar2 = oggpack_read(param_2,4);
      piVar5[1] = iVar2;
      if (iVar2 < 0) goto LAB_005b2e04;
      if ((int)local_11c < iVar2) {
        local_11c = (int *)iVar2;
      }
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar6 < *_Memory);
  }
  iVar2 = (int)local_11c + 1;
  local_114 = 0;
  if (0 < iVar2) {
    local_11c = _Memory + 0x50;
    piVar5 = _Memory + 0x40;
    do {
      iVar6 = oggpack_read(param_2,3);
      piVar5[-0x20] = iVar6 + 1;
      iVar6 = oggpack_read(param_2,2);
      piVar5[-0x10] = iVar6;
      if (iVar6 < 0) goto LAB_005b2e04;
      if (iVar6 != 0) {
        iVar6 = oggpack_read(param_2,8);
        *piVar5 = iVar6;
      }
      if ((*piVar5 < 0) || (*(int *)((int)pvVar1 + 0x18) <= *piVar5)) goto LAB_005b2e04;
      iVar6 = 0;
      piVar7 = local_11c;
      if (0 < 1 << ((byte)piVar5[-0x10] & 0x1f)) {
        do {
          iVar3 = oggpack_read(param_2,8);
          iVar3 = iVar3 + -1;
          *piVar7 = iVar3;
          if ((iVar3 < -1) || (*(int *)((int)pvVar1 + 0x18) <= iVar3)) goto LAB_005b2e04;
          iVar6 = iVar6 + 1;
          piVar7 = piVar7 + 1;
        } while (iVar6 < 1 << ((byte)piVar5[-0x10] & 0x1f));
      }
      local_11c = local_11c + 8;
      local_114 = local_114 + 1;
      piVar5 = piVar5 + 1;
    } while (local_114 < iVar2);
  }
  iVar6 = 0;
  iVar2 = oggpack_read(param_2,2);
  _Memory[0xd0] = iVar2 + 1;
  iVar2 = oggpack_read(param_2,4);
  iVar3 = 0;
  if (iVar2 < 0) {
LAB_005b2e04:
    memset(_Memory,0,0x460);
    free(_Memory);
    return (void *)0x0;
  }
  local_114 = 0;
  local_11c = _Memory;
  if (0 < *_Memory) {
    do {
      local_11c = local_11c + 1;
      iVar6 = iVar6 + _Memory[*local_11c + 0x20];
      if (0x3f < iVar6) goto LAB_005b2e04;
      if (iVar3 < iVar6) {
        piVar5 = _Memory + iVar3 + 0xd3;
        do {
          iVar4 = oggpack_read(param_2,iVar2);
          *piVar5 = iVar4;
          if ((iVar4 < 0) || (1 << ((byte)iVar2 & 0x1f) <= iVar4)) goto LAB_005b2e04;
          iVar3 = iVar3 + 1;
          piVar5 = piVar5 + 1;
        } while (iVar3 < iVar6);
      }
      local_114 = local_114 + 1;
    } while (local_114 < *_Memory);
  }
  _NumOfElements = iVar6 + 2;
  piVar5 = _Memory + 0xd1;
  iVar6 = 0;
  *piVar5 = 0;
  _Memory[0xd2] = 1 << ((byte)iVar2 & 0x1f);
  if (0 < (int)_NumOfElements) {
    do {
      local_104[iVar6] = piVar5;
      iVar6 = iVar6 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar6 < (int)_NumOfElements);
  }
  qsort(local_104,_NumOfElements,4,icomp);
  iVar2 = 1;
  if (1 < (int)_NumOfElements) {
    do {
      if (*(int *)local_104[iVar2 + -1] == *(int *)local_104[iVar2]) goto LAB_005b2e04;
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)_NumOfElements);
  }
  return _Memory;
}
