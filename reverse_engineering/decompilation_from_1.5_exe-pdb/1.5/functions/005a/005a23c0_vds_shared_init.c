/*
 * Entry: 005a23c0
 * Name: _vds_shared_init
 * Namespace: Global
 * Signature: int _vds_shared_init(vorbis_dsp_state * param_1, vorbis_info * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vds_shared_init(vorbis_dsp_state *param_1,vorbis_info *param_2,int param_3)

{
  int *piVar1;
  void *pvVar2;
  uint uVar3;
  void *pvVar4;
  float **ppfVar5;
  float *pfVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  code *pcVar10;
  int *piVar11;
  int local_c;
  int *local_8;
  int local_4;
  
  piVar1 = param_2->codec_setup;
  if (piVar1 == (int *)0x0) {
    return 1;
  }
  iVar9 = piVar1[0x392];
  memset(param_1,0,0x70);
  pcVar10 = calloc_exref;
  pvVar2 = calloc(1,0x88);
  param_1->backend_state = pvVar2;
  param_1->vi = param_2;
  iVar8 = 0;
  if (piVar1[2] != 0) {
    for (uVar3 = piVar1[2] - 1; uVar3 != 0; uVar3 = uVar3 >> 1) {
      iVar8 = iVar8 + 1;
    }
  }
  *(int *)((int)pvVar2 + 0x2c) = iVar8;
  pvVar4 = calloc(1,4);
  *(void **)((int)pvVar2 + 0xc) = pvVar4;
  pvVar4 = calloc(1,4);
  *(void **)((int)pvVar2 + 0x10) = pvVar4;
  pvVar4 = calloc(1,0x14);
  **(undefined4 **)((int)pvVar2 + 0xc) = pvVar4;
  pvVar4 = calloc(1,0x14);
  **(undefined4 **)((int)pvVar2 + 0x10) = pvVar4;
  mdct_init((mdct_lookup *)**(undefined4 **)((int)pvVar2 + 0xc),*piVar1 >> ((byte)iVar9 & 0x1f));
  mdct_init((mdct_lookup *)**(undefined4 **)((int)pvVar2 + 0x10),piVar1[1] >> ((byte)iVar9 & 0x1f));
  iVar9 = 0;
  if (*piVar1 != 0) {
    for (uVar3 = *piVar1 - 1; uVar3 != 0; uVar3 = uVar3 >> 1) {
      iVar9 = iVar9 + 1;
    }
  }
  *(int *)((int)pvVar2 + 4) = iVar9 + -6;
  iVar9 = 0;
  if (piVar1[1] != 0) {
    for (uVar3 = piVar1[1] - 1; uVar3 != 0; uVar3 = uVar3 >> 1) {
      iVar9 = iVar9 + 1;
    }
  }
  *(int *)((int)pvVar2 + 8) = iVar9 + -6;
  if (param_3 == 0) {
    if (piVar1[0x2c8] == 0) {
      pvVar4 = calloc(piVar1[6],0x38);
      piVar1[0x2c8] = (int)pvVar4;
      local_c = 0;
      if (0 < piVar1[6]) {
        local_4 = 0;
        piVar11 = piVar1 + 0x1c8;
        do {
          if (((static_codebook *)*piVar11 == (static_codebook *)0x0) ||
             (iVar9 = vorbis_book_init_decode
                                ((codebook *)(piVar1[0x2c8] + local_4),(static_codebook *)*piVar11),
             iVar9 != 0)) {
            iVar9 = 0;
            if (0 < piVar1[6]) {
              piVar11 = piVar1 + 0x1c8;
              do {
                if ((static_codebook *)*piVar11 != (static_codebook *)0x0) {
                  vorbis_staticbook_destroy((static_codebook *)*piVar11);
                  *piVar11 = 0;
                }
                iVar9 = iVar9 + 1;
                piVar11 = piVar11 + 1;
              } while (iVar9 < piVar1[6]);
            }
            vorbis_dsp_clear(param_1);
            return -1;
          }
          vorbis_staticbook_destroy((static_codebook *)*piVar11);
          local_4 = local_4 + 0x38;
          *piVar11 = 0;
          local_c = local_c + 1;
          piVar11 = piVar11 + 1;
          pcVar10 = calloc_exref;
        } while (local_c < piVar1[6]);
      }
    }
  }
  else {
    drft_init((drft_lookup *)((int)pvVar2 + 0x14),*piVar1);
    drft_init((drft_lookup *)((int)pvVar2 + 0x20),piVar1[1]);
    if (piVar1[0x2c8] == 0) {
      pvVar4 = calloc(piVar1[6],0x38);
      piVar1[0x2c8] = (int)pvVar4;
      local_c = 0;
      if (0 < piVar1[6]) {
        local_8 = piVar1 + 0x1c8;
        local_4 = 0;
        do {
          vorbis_book_init_encode((codebook *)(piVar1[0x2c8] + local_4),(static_codebook *)*local_8)
          ;
          local_8 = local_8 + 1;
          local_4 = local_4 + 0x38;
          local_c = local_c + 1;
        } while (local_c < piVar1[6]);
      }
    }
    pvVar4 = calloc(piVar1[7],0x34);
    *(void **)((int)pvVar2 + 0x38) = pvVar4;
    local_c = 0;
    if (0 < piVar1[7]) {
      iVar9 = 0;
      piVar11 = piVar1 + 0x2c9;
      do {
        _vp_psy_init((vorbis_look_psy *)(*(int *)((int)pvVar2 + 0x38) + iVar9),
                     (vorbis_info_psy *)*piVar11,(vorbis_info_psy_global *)(piVar1 + 0x2cd),
                     piVar1[((vorbis_info_psy *)*piVar11)->blockflag] / 2,param_2->rate);
        local_c = local_c + 1;
        piVar11 = piVar11 + 1;
        iVar9 = iVar9 + 0x34;
        pcVar10 = calloc_exref;
      } while (local_c < piVar1[7]);
    }
    param_1->analysisp = 1;
  }
  param_1->pcm_storage = piVar1[1];
  ppfVar5 = malloc(param_2->channels * 4);
  param_1->pcm = ppfVar5;
  ppfVar5 = malloc(param_2->channels * 4);
  param_1->pcmret = ppfVar5;
  local_4 = 0;
  if (0 < param_2->channels) {
    do {
      pfVar6 = (float *)(*pcVar10)(param_1->pcm_storage,4);
      param_1->pcm[local_4] = pfVar6;
      local_4 = local_4 + 1;
    } while (local_4 < param_2->channels);
  }
  param_1->lW = 0;
  param_1->W = 0;
  iVar9 = piVar1[1];
  param_1->centerW = iVar9 / 2;
  param_1->pcm_current = iVar9 / 2;
  uVar7 = (*pcVar10)(piVar1[4],4);
  *(undefined4 *)((int)pvVar2 + 0x30) = uVar7;
  uVar7 = (*pcVar10)(piVar1[5],4);
  *(undefined4 *)((int)pvVar2 + 0x34) = uVar7;
  local_c = 0;
  if (0 < piVar1[4]) {
    piVar11 = piVar1 + 200;
    do {
      uVar7 = (**(code **)(*(int *)(&_floor_P + *piVar11 * 4) + 8))(param_1,piVar11[0x40]);
      *(undefined4 *)((int)piVar11 + *(int *)((int)pvVar2 + 0x30) + (-800 - (int)piVar1)) = uVar7;
      local_c = local_c + 1;
      piVar11 = piVar11 + 1;
    } while (local_c < piVar1[4]);
  }
  local_c = 0;
  if (0 < piVar1[5]) {
    piVar11 = piVar1 + 0x148;
    do {
      uVar7 = (**(code **)(*(int *)(&_residue_P + *piVar11 * 4) + 8))(param_1,piVar11[0x40]);
      *(undefined4 *)(*(int *)((int)pvVar2 + 0x34) + (-0x520 - (int)piVar1) + (int)piVar11) = uVar7;
      local_c = local_c + 1;
      piVar11 = piVar11 + 1;
    } while (local_c < piVar1[5]);
  }
  return 0;
}
