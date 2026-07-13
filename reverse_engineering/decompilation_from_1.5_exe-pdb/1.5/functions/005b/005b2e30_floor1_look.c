/*
 * Entry: 005b2e30
 * Name: floor1_look
 * Namespace: Global
 * Signature: void * floor1_look(vorbis_dsp_state * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor1_look(vorbis_dsp_state *param_1,void *param_2)

{
  size_t _NumOfElements;
  void *pvVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_120;
  int *local_11c;
  int *local_118;
  int local_114;
  int local_110;
  int local_108;
  int local_104 [65];
  
  iVar5 = 0;
  iVar6 = 0;
  pvVar1 = calloc(1,0x520);
  *(undefined4 *)((int)pvVar1 + 0x508) = *(undefined4 *)((int)param_2 + 0x348);
  iVar3 = *(int *)param_2;
  iVar4 = 0;
  *(void **)((int)pvVar1 + 0x510) = param_2;
  if (1 < iVar3) {
    iVar3 = (iVar3 - 2U >> 1) + 1;
    iVar4 = iVar3 * 2;
    piVar2 = param_2;
    do {
      iVar5 = iVar5 + *(int *)((int)param_2 + piVar2[1] * 4 + 0x80);
      iVar6 = iVar6 + *(int *)((int)param_2 + piVar2[2] * 4 + 0x80);
      iVar3 = iVar3 + -1;
      piVar2 = piVar2 + 2;
    } while (iVar3 != 0);
  }
  iVar3 = 0;
  if (iVar4 < *(int *)param_2) {
    iVar3 = *(int *)((int)param_2 + *(int *)((int)param_2 + iVar4 * 4 + 4) * 4 + 0x80);
  }
  _NumOfElements = iVar3 + 2 + iVar6 + iVar5;
  iVar3 = 0;
  *(size_t *)((int)pvVar1 + 0x504) = _NumOfElements;
  if (0 < (int)_NumOfElements) {
    iVar4 = (int)param_2 + 0x344;
    do {
      local_104[iVar3] = iVar4;
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 < (int)_NumOfElements);
  }
  qsort(local_104,_NumOfElements,4,icomp);
  iVar3 = 0;
  if (0 < (int)_NumOfElements) {
    piVar2 = (int *)((int)pvVar1 + 0x104);
    do {
      *piVar2 = (local_104[iVar3] - (int)param_2) + -0x344 >> 2;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < (int)_NumOfElements);
  }
  iVar3 = 0;
  if (0 < (int)_NumOfElements) {
    piVar2 = (int *)((int)pvVar1 + 0x104);
    do {
      *(int *)((int)pvVar1 + *piVar2 * 4 + 0x208) = iVar3;
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < (int)_NumOfElements);
  }
  iVar3 = 0;
  if (0 < (int)_NumOfElements) {
    do {
      *(undefined4 *)((int)pvVar1 + iVar3 * 4) =
           *(undefined4 *)((int)param_2 + *(int *)((int)pvVar1 + iVar3 * 4 + 0x104) * 4 + 0x344);
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)_NumOfElements);
  }
  switch(*(undefined4 *)((int)param_2 + 0x340)) {
  case 1:
    *(undefined4 *)((int)pvVar1 + 0x50c) = 0x100;
    break;
  case 2:
    *(undefined4 *)((int)pvVar1 + 0x50c) = 0x80;
    break;
  case 3:
    *(undefined4 *)((int)pvVar1 + 0x50c) = 0x56;
    break;
  case 4:
    *(undefined4 *)((int)pvVar1 + 0x50c) = 0x40;
  }
  local_120 = _NumOfElements - 2;
  if (0 < local_120) {
    piVar2 = (int *)((int)pvVar1 + 0x30c);
    local_11c = (int *)((int)param_2 + 0x34c);
    iVar3 = 2;
    do {
      local_110 = *(int *)((int)pvVar1 + 0x508);
      iVar4 = 0;
      iVar5 = 0;
      local_114 = 0;
      local_108 = 1;
      if (0 < iVar3) {
        local_118 = (int *)((int)param_2 + 0x344);
        do {
          iVar6 = *local_118;
          if ((iVar4 < iVar6) && (iVar6 < *local_11c)) {
            iVar4 = iVar6;
            local_114 = iVar5;
          }
          if ((iVar6 < local_110) && (*local_11c < iVar6)) {
            local_110 = iVar6;
            local_108 = iVar5;
          }
          local_118 = local_118 + 1;
          iVar5 = iVar5 + 1;
        } while (iVar5 < iVar3);
      }
      local_11c = local_11c + 1;
      piVar2[0x3f] = local_114;
      *piVar2 = local_108;
      piVar2 = piVar2 + 1;
      iVar3 = iVar3 + 1;
      local_120 = local_120 + -1;
    } while (local_120 != 0);
  }
  return pvVar1;
}
