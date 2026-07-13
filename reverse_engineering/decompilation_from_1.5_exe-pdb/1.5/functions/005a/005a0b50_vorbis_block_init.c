/*
 * Entry: 005a0b50
 * Name: vorbis_block_init
 * Namespace: Global
 * Signature: int vorbis_block_init(vorbis_dsp_state * param_1, vorbis_block * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_block_init(vorbis_dsp_state *param_1,vorbis_block *param_2)

{
  void *pvVar1;
  void *pvVar2;
  int iVar3;
  
  iVar3 = 0;
  memset(param_2,0,0x70);
  param_2->vd = param_1;
  param_2->localalloc = 0;
  param_2->localstore = (void *)0x0;
  if (param_1->analysisp != 0) {
    pvVar1 = calloc(1,0x48);
    param_2->internal = pvVar1;
    *(undefined4 *)((int)pvVar1 + 4) = 0xc61c3c00;
    do {
      if (iVar3 == 7) {
        *(oggpack_buffer **)((int)pvVar1 + 0x28) = &param_2->opb;
      }
      else {
        pvVar2 = calloc(1,0x14);
        *(void **)((int)pvVar1 + iVar3 * 4 + 0xc) = pvVar2;
      }
      oggpack_writeinit(*(undefined4 *)((int)pvVar1 + iVar3 * 4 + 0xc));
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xf);
  }
  return 0;
}
