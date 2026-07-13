/*
 * Entry: 005b2970
 * Name: floor1_pack
 * Namespace: Global
 * Signature: void floor1_pack(void * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor1_pack(void *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  undefined4 *puVar7;
  int *local_10;
  int local_c;
  int local_8;
  int local_4;
  
  pvVar1 = param_1;
  iVar2 = *(int *)((int)param_1 + 0x348);
  local_c = 0;
  local_10 = (int *)0xffffffff;
  oggpack_write(param_2,*(undefined4 *)param_1,5);
  if (0 < *(int *)param_1) {
    iVar6 = 0;
    piVar5 = param_1;
    do {
      piVar5 = piVar5 + 1;
      oggpack_write(param_2,*piVar5,4);
      if ((int)local_10 < *piVar5) {
        local_10 = (int *)*piVar5;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)param_1);
  }
  local_8 = (int)local_10 + 1;
  if (0 < local_8) {
    local_10 = (int *)((int)param_1 + 0x140);
    piVar5 = (int *)((int)param_1 + 0xc0);
    do {
      oggpack_write(param_2,piVar5[-0x10] + -1,3);
      oggpack_write(param_2,*piVar5,2);
      if (*piVar5 != 0) {
        oggpack_write(param_2,piVar5[0x10],8);
      }
      iVar6 = 0;
      piVar4 = local_10;
      if (0 < 1 << ((byte)*piVar5 & 0x1f)) {
        do {
          oggpack_write(param_2,*piVar4 + 1,8);
          iVar6 = iVar6 + 1;
          piVar4 = piVar4 + 1;
        } while (iVar6 < 1 << ((byte)*piVar5 & 0x1f));
      }
      local_10 = local_10 + 8;
      piVar5 = piVar5 + 1;
      local_8 = local_8 + -1;
    } while (local_8 != 0);
  }
  oggpack_write(param_2,*(int *)((int)param_1 + 0x340) + -1,2);
  iVar6 = 0;
  if (iVar2 != 0) {
    for (uVar3 = iVar2 - 1; uVar3 != 0; uVar3 = uVar3 >> 1) {
      iVar6 = iVar6 + 1;
    }
  }
  oggpack_write(param_2,iVar6,4);
  local_4 = 0;
  if (iVar2 != 0) {
    local_4 = 0;
    for (uVar3 = iVar2 - 1; uVar3 != 0; uVar3 = uVar3 >> 1) {
      local_4 = local_4 + 1;
    }
  }
  iVar2 = 0;
  local_8 = 0;
  if (0 < *(int *)param_1) {
    do {
      param_1 = (void *)((int)param_1 + 4);
      local_c = local_c + *(int *)((int)pvVar1 + *(int *)param_1 * 4 + 0x80);
      if (iVar2 < local_c) {
        iVar6 = local_c - iVar2;
        puVar7 = (undefined4 *)((int)pvVar1 + iVar2 * 4 + 0x34c);
        iVar2 = iVar2 + iVar6;
        do {
          oggpack_write(param_2,*puVar7,local_4);
          puVar7 = puVar7 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      local_8 = local_8 + 1;
    } while (local_8 < *(int *)pvVar1);
  }
  return;
}
