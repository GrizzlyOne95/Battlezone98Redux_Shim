/*
 * Entry: 005b1590
 * Name: res0_pack
 * Namespace: Global
 * Signature: void res0_pack(void * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl res0_pack(void *param_1,oggpack_buffer *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int local_4;
  
  iVar3 = 0;
  local_4 = 0;
  oggpack_write(param_2,*(undefined4 *)param_1,0x18);
  oggpack_write(param_2,*(undefined4 *)((int)param_1 + 4),0x18);
  oggpack_write(param_2,*(int *)((int)param_1 + 8) + -1,0x18);
  oggpack_write(param_2,*(int *)((int)param_1 + 0xc) + -1,6);
  oggpack_write(param_2,*(undefined4 *)((int)param_1 + 0x14),8);
  iVar5 = 0;
  if (0 < *(int *)((int)param_1 + 0xc)) {
    puVar4 = (uint *)((int)param_1 + 0x18);
    do {
      uVar2 = *puVar4;
      iVar3 = 0;
      uVar1 = uVar2;
      if (uVar2 == 0) {
LAB_005b1630:
        oggpack_write(param_2,uVar2,4);
      }
      else {
        do {
          iVar3 = iVar3 + 1;
          uVar1 = uVar1 >> 1;
        } while (uVar1 != 0);
        if (iVar3 < 4) goto LAB_005b1630;
        oggpack_write(param_2,uVar2,3);
        oggpack_write(param_2,1,1);
        oggpack_write(param_2,(int)*puVar4 >> 3,5);
      }
      iVar3 = 0;
      for (uVar2 = *puVar4; uVar2 != 0; uVar2 = uVar2 >> 1) {
        iVar3 = iVar3 + (uVar2 & 1);
      }
      iVar3 = local_4 + iVar3;
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 1;
      local_4 = iVar3;
    } while (iVar5 < *(int *)((int)param_1 + 0xc));
  }
  if (0 < iVar3) {
    puVar6 = (undefined4 *)((int)param_1 + 0x118);
    do {
      oggpack_write(param_2,*puVar6,8);
      puVar6 = puVar6 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}
