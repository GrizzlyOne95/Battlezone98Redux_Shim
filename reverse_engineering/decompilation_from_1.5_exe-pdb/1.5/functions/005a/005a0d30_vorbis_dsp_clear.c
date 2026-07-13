/*
 * Entry: 005a0d30
 * Name: vorbis_dsp_clear
 * Namespace: Global
 * Signature: void vorbis_dsp_clear(vorbis_dsp_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl vorbis_dsp_clear(vorbis_dsp_state *param_1)

{
  vorbis_info *pvVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  code *pcVar6;
  void *pvVar7;
  
  if (param_1 != (vorbis_dsp_state *)0x0) {
    pvVar1 = param_1->vi;
    if (pvVar1 == (vorbis_info *)0x0) {
      pvVar7 = (void *)0x0;
    }
    else {
      pvVar7 = pvVar1->codec_setup;
    }
    puVar2 = param_1->backend_state;
    pcVar6 = free_exref;
    if (puVar2 != (undefined4 *)0x0) {
      if ((envelope_lookup *)*puVar2 != (envelope_lookup *)0x0) {
        _ve_envelope_clear((envelope_lookup *)*puVar2);
        pcVar6 = free_exref;
        free((void *)*puVar2);
      }
      if ((undefined4 *)puVar2[3] != (undefined4 *)0x0) {
        mdct_clear(*(mdct_lookup **)puVar2[3]);
        (*pcVar6)(*(undefined4 *)puVar2[3]);
        (*pcVar6)(puVar2[3]);
      }
      if ((undefined4 *)puVar2[4] != (undefined4 *)0x0) {
        mdct_clear(*(mdct_lookup **)puVar2[4]);
        (*pcVar6)(*(undefined4 *)puVar2[4]);
        (*pcVar6)(puVar2[4]);
      }
      if (puVar2[0xc] != 0) {
        if ((pvVar7 != (void *)0x0) && (iVar3 = 0, 0 < *(int *)((int)pvVar7 + 0x10))) {
          piVar4 = (int *)((int)pvVar7 + 800);
          do {
            (**(code **)(*(int *)(&_floor_P + *piVar4 * 4) + 0x10))
                      (*(undefined4 *)(puVar2[0xc] + iVar3 * 4));
            iVar3 = iVar3 + 1;
            piVar4 = piVar4 + 1;
            pcVar6 = free_exref;
          } while (iVar3 < *(int *)((int)pvVar7 + 0x10));
        }
        (*pcVar6)(puVar2[0xc]);
      }
      if (puVar2[0xd] != 0) {
        if ((pvVar7 != (void *)0x0) && (iVar3 = 0, 0 < *(int *)((int)pvVar7 + 0x14))) {
          piVar4 = (int *)((int)pvVar7 + 0x520);
          do {
            (**(code **)(*(int *)(&_residue_P + *piVar4 * 4) + 0x10))
                      (*(undefined4 *)(puVar2[0xd] + iVar3 * 4));
            iVar3 = iVar3 + 1;
            piVar4 = piVar4 + 1;
            pcVar6 = free_exref;
          } while (iVar3 < *(int *)((int)pvVar7 + 0x14));
        }
        (*pcVar6)(puVar2[0xd]);
      }
      if (puVar2[0xe] != 0) {
        if ((pvVar7 != (void *)0x0) && (iVar3 = 0, 0 < *(int *)((int)pvVar7 + 0x1c))) {
          iVar5 = 0;
          do {
            _vp_psy_clear((vorbis_look_psy *)(puVar2[0xe] + iVar5));
            iVar3 = iVar3 + 1;
            iVar5 = iVar5 + 0x34;
            pcVar6 = free_exref;
          } while (iVar3 < *(int *)((int)pvVar7 + 0x1c));
        }
        (*pcVar6)(puVar2[0xe]);
      }
      if ((vorbis_look_psy_global *)puVar2[0xf] != (vorbis_look_psy_global *)0x0) {
        _vp_global_free((vorbis_look_psy_global *)puVar2[0xf]);
      }
      vorbis_bitrate_clear((bitrate_manager_state *)(puVar2 + 0x14));
      drft_clear((drft_lookup *)(puVar2 + 5));
      drft_clear((drft_lookup *)(puVar2 + 8));
    }
    if (param_1->pcm != (float **)0x0) {
      if ((pvVar1 != (vorbis_info *)0x0) && (iVar3 = 0, 0 < pvVar1->channels)) {
        do {
          if (param_1->pcm[iVar3] != (float *)0x0) {
            (*pcVar6)(param_1->pcm[iVar3]);
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < pvVar1->channels);
      }
      (*pcVar6)(param_1->pcm);
      if (param_1->pcmret != (float **)0x0) {
        (*pcVar6)(param_1->pcmret);
      }
    }
    if (puVar2 != (undefined4 *)0x0) {
      if (puVar2[0x10] != 0) {
        (*pcVar6)(puVar2[0x10]);
      }
      if (puVar2[0x11] != 0) {
        (*pcVar6)(puVar2[0x11]);
      }
      if (puVar2[0x12] != 0) {
        (*pcVar6)(puVar2[0x12]);
      }
      (*pcVar6)(puVar2);
    }
    memset(param_1,0,0x70);
  }
  return;
}
