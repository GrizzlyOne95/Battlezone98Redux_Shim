/*
 * Entry: 005b0210
 * Name: mapping0_pack
 * Namespace: Global
 * Signature: void mapping0_pack(vorbis_info * param_1, void * param_2, oggpack_buffer * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mapping0_pack(vorbis_info *param_1,void *param_2,oggpack_buffer *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  
  if (*(int *)param_2 < 2) {
    oggpack_write(param_3,0,1);
  }
  else {
    oggpack_write(param_3,1,1);
    oggpack_write(param_3,*(int *)param_2 + -1,4);
  }
  if (*(int *)((int)param_2 + 0x484) < 1) {
    oggpack_write(param_3,0,1);
  }
  else {
    oggpack_write(param_3,1,1);
    oggpack_write(param_3,*(int *)((int)param_2 + 0x484) + -1,8);
    iVar3 = 0;
    if (0 < *(int *)((int)param_2 + 0x484)) {
      puVar4 = (undefined4 *)((int)param_2 + 0x888);
      do {
        iVar1 = 0;
        if (param_1->channels != 0) {
          for (uVar2 = param_1->channels - 1; uVar2 != 0; uVar2 = uVar2 >> 1) {
            iVar1 = iVar1 + 1;
          }
        }
        oggpack_write(param_3,puVar4[-0x100],iVar1);
        iVar1 = 0;
        if ((param_1->channels != 0) && (uVar2 = param_1->channels - 1, uVar2 != 0)) {
          iVar1 = 0;
          do {
            iVar1 = iVar1 + 1;
            uVar2 = uVar2 >> 1;
          } while (uVar2 != 0);
        }
        oggpack_write(param_3,*puVar4,iVar1);
        iVar3 = iVar3 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar3 < *(int *)((int)param_2 + 0x484));
    }
  }
  oggpack_write(param_3,0,2);
  if ((1 < *(int *)param_2) && (iVar3 = 0, puVar4 = param_2, 0 < param_1->channels)) {
    do {
      oggpack_write(param_3,puVar4[1],4);
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < param_1->channels);
  }
  iVar3 = 0;
  if (0 < *(int *)param_2) {
    puVar4 = (undefined4 *)((int)param_2 + 0x444);
    do {
      oggpack_write(param_3,0,8);
      oggpack_write(param_3,puVar4[-0x10],8);
      oggpack_write(param_3,*puVar4,8);
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < *(int *)param_2);
  }
  return;
}
