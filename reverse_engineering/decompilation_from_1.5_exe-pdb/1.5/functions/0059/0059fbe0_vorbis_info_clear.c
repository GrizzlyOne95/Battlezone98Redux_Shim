/*
 * Entry: 0059fbe0
 * Name: vorbis_info_clear
 * Namespace: Global
 * Signature: void vorbis_info_clear(vorbis_info * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_info_clear(vorbis_info *param_1)

{
  void *_Memory;
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  _Memory = param_1->codec_setup;
  if (_Memory != (void *)0x0) {
    iVar3 = 0;
    if (0 < *(int *)((int)_Memory + 8)) {
      puVar1 = (undefined4 *)((int)_Memory + 0x20);
      do {
        if ((void *)*puVar1 != (void *)0x0) {
          free((void *)*puVar1);
        }
        iVar3 = iVar3 + 1;
        puVar1 = puVar1 + 1;
      } while (iVar3 < *(int *)((int)_Memory + 8));
    }
    iVar3 = 0;
    if (0 < *(int *)((int)_Memory + 0xc)) {
      piVar4 = (int *)((int)_Memory + 0x220);
      do {
        if (*piVar4 != 0) {
          (**(code **)(*(int *)(&_mapping_P + piVar4[-0x40] * 4) + 8))(*piVar4);
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < *(int *)((int)_Memory + 0xc));
    }
    iVar3 = 0;
    if (0 < *(int *)((int)_Memory + 0x10)) {
      piVar4 = (int *)((int)_Memory + 0x420);
      do {
        if (*piVar4 != 0) {
          (**(code **)(*(int *)(&_floor_P + piVar4[-0x40] * 4) + 0xc))(*piVar4);
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < *(int *)((int)_Memory + 0x10));
    }
    if (0 < *(int *)((int)_Memory + 0x14)) {
      piVar4 = (int *)((int)_Memory + 0x620);
      iVar3 = 0;
      do {
        if (*piVar4 != 0) {
          (**(code **)(*(int *)(&_residue_P + piVar4[-0x40] * 4) + 0xc))(*piVar4);
        }
        iVar3 = iVar3 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar3 < *(int *)((int)_Memory + 0x14));
    }
    iVar3 = 0;
    if (0 < *(int *)((int)_Memory + 0x18)) {
      iVar2 = 0;
      puVar1 = (undefined4 *)((int)_Memory + 0x720);
      do {
        if ((static_codebook *)*puVar1 != (static_codebook *)0x0) {
          vorbis_staticbook_destroy((static_codebook *)*puVar1);
        }
        if (*(int *)((int)_Memory + 0xb20) != 0) {
          vorbis_book_clear((codebook *)(*(int *)((int)_Memory + 0xb20) + iVar2));
        }
        iVar3 = iVar3 + 1;
        puVar1 = puVar1 + 1;
        iVar2 = iVar2 + 0x38;
      } while (iVar3 < *(int *)((int)_Memory + 0x18));
    }
    if (*(void **)((int)_Memory + 0xb20) != (void *)0x0) {
      free(*(void **)((int)_Memory + 0xb20));
    }
    iVar3 = 0;
    if (0 < *(int *)((int)_Memory + 0x1c)) {
      puVar1 = (undefined4 *)((int)_Memory + 0xb24);
      do {
        _vi_psy_free((vorbis_info_psy *)*puVar1);
        iVar3 = iVar3 + 1;
        puVar1 = puVar1 + 1;
      } while (iVar3 < *(int *)((int)_Memory + 0x1c));
    }
    free(_Memory);
  }
  param_1->version = 0;
  param_1->channels = 0;
  param_1->rate = 0;
  param_1->bitrate_upper = 0;
  param_1->bitrate_nominal = 0;
  param_1->bitrate_lower = 0;
  param_1->bitrate_window = 0;
  param_1->codec_setup = (void *)0x0;
  return;
}
