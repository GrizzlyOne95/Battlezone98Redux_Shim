/*
 * Entry: 005af7d0
 * Name: _ve_envelope_search
 * Namespace: Global
 * Signature: long _ve_envelope_search(vorbis_dsp_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl _ve_envelope_search(vorbis_dsp_state *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  void *pvVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  envelope_filter_state *unaff_EDI;
  int iVar11;
  uint local_c;
  
  piVar1 = *(int **)param_1->backend_state;
  piVar2 = param_1->vi->codec_setup;
  iVar5 = piVar1[0x2a] / piVar1[2];
  iVar6 = param_1->pcm_current / piVar1[2];
  iVar9 = iVar6 + -4;
  if (iVar5 < 0) {
    iVar5 = 0;
  }
  iVar6 = iVar6 + 2;
  if (piVar1[0x29] < iVar6) {
    piVar1[0x29] = iVar6;
    pvVar7 = realloc((void *)piVar1[0x28],iVar6 * 4);
    piVar1[0x28] = (int)pvVar7;
  }
  for (; iVar5 < iVar9; iVar5 = iVar5 + 1) {
    piVar1[0x27] = piVar1[0x27] + 1;
    uVar8 = 0;
    local_c = 0;
    if (0x18 < piVar1[0x27]) {
      piVar1[0x27] = 0x18;
    }
    iVar6 = 0;
    if (0 < *piVar1) {
      iVar10 = 0;
      do {
        uVar8 = _ve_amp((envelope_lookup *)(piVar2 + 0x2cd),
                        (vorbis_info_psy_global *)(param_1->pcm[iVar6] + piVar1[2] * iVar5),
                        (float *)(piVar1 + 10),(envelope_band *)(piVar1[0x26] + iVar10),unaff_EDI);
        uVar8 = local_c | uVar8;
        iVar6 = iVar6 + 1;
        iVar10 = iVar10 + 0x3f0;
        local_c = uVar8;
      } while (iVar6 < *piVar1);
    }
    *(undefined4 *)(piVar1[0x28] + 8 + iVar5 * 4) = 0;
    if ((uVar8 & 1) != 0) {
      *(undefined4 *)(piVar1[0x28] + iVar5 * 4) = 1;
      *(undefined4 *)(piVar1[0x28] + 4 + iVar5 * 4) = 1;
    }
    if (((uVar8 & 2) != 0) && (*(undefined4 *)(piVar1[0x28] + iVar5 * 4) = 1, 0 < iVar5)) {
      *(undefined4 *)(piVar1[0x28] + -4 + iVar5 * 4) = 1;
    }
    if ((uVar8 & 4) != 0) {
      piVar1[0x27] = -1;
    }
  }
  iVar6 = piVar1[2];
  iVar9 = iVar6 * iVar9;
  piVar1[0x2a] = iVar9;
  iVar5 = piVar2[param_1->W];
  iVar10 = param_1->centerW;
  iVar3 = piVar2[1];
  iVar4 = *piVar2;
  iVar11 = piVar1[0x2c];
  if (iVar11 < iVar9 - iVar6) {
    do {
      if (((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2) +
          iVar3 / 2 + iVar10 + ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2) <= iVar11) {
        return 1;
      }
      piVar1[0x2c] = iVar11;
      if ((*(int *)(piVar1[0x28] + (iVar11 / iVar6) * 4) != 0) && (iVar10 < iVar11)) {
        piVar1[0x2b] = iVar11;
        return 0;
      }
      iVar11 = iVar11 + iVar6;
    } while (iVar11 < piVar1[0x2a] - iVar6);
  }
  return -1;
}
