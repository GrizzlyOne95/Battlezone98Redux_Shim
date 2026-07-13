/*
 * Entry: 005a1240
 * Name: vorbis_analysis_blockout
 * Namespace: Global
 * Signature: int vorbis_analysis_blockout(vorbis_dsp_state * param_1, vorbis_block * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_analysis_blockout(vorbis_dsp_state *param_1,vorbis_block *param_2)

{
  long64 *plVar1;
  int *piVar2;
  vorbis_info *pvVar3;
  int *piVar4;
  undefined4 *puVar5;
  float *pfVar6;
  int *piVar7;
  long64 lVar8;
  long64 lVar9;
  int iVar10;
  long lVar11;
  float **ppfVar12;
  void *pvVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  float fVar17;
  
  pvVar3 = param_1->vi;
  piVar4 = pvVar3->codec_setup;
  puVar5 = param_1->backend_state;
  pfVar6 = (float *)puVar5[0xf];
  piVar7 = param_2->internal;
  iVar10 = param_1->centerW - piVar4[param_1->W] / 2;
  if (param_1->preextrapolate == 0) {
    return 0;
  }
  if (param_1->eofflag == -1) {
    return 0;
  }
  lVar11 = _ve_envelope_search(param_1);
  if (lVar11 == -1) {
    if (param_1->eofflag == 0) {
      return 0;
    }
  }
  else if (*piVar4 != piVar4[1]) {
    param_1->nW = lVar11;
    goto LAB_005a12c1;
  }
  param_1->nW = 0;
LAB_005a12c1:
  iVar15 = piVar4[param_1->nW];
  iVar14 = ((int)(piVar4[param_1->W] + (piVar4[param_1->W] >> 0x1f & 3U)) >> 2) +
           ((int)(iVar15 + (iVar15 >> 0x1f & 3U)) >> 2) + param_1->centerW;
  if (param_1->pcm_current < iVar15 / 2 + iVar14) {
    return 0;
  }
  _vorbis_block_ripcord(param_2);
  param_2->lW = param_1->lW;
  param_2->W = param_1->W;
  param_2->nW = param_1->nW;
  if (param_1->W == 0) {
    iVar15 = _ve_envelope_mark(param_1);
    piVar7[2] = (uint)(iVar15 == 0);
  }
  else if ((param_1->lW == 0) || (param_1->nW == 0)) {
    piVar7[2] = 0;
  }
  else {
    piVar7[2] = 1;
  }
  param_2->vd = param_1;
  *(int *)&param_2->sequence = (int)param_1->sequence;
  *(undefined4 *)((int)&param_2->sequence + 4) = *(undefined4 *)((int)&param_1->sequence + 4);
  plVar1 = &param_1->sequence;
  lVar8 = *plVar1;
  *(int *)plVar1 = (int)*plVar1 + 1;
  lVar9 = param_1->granulepos;
  piVar2 = (int *)((int)&param_1->sequence + 4);
  *piVar2 = *piVar2 + (uint)(0xfffffffe < (uint)lVar8);
  *(int *)&param_2->granulepos = (int)lVar9;
  *(undefined4 *)((int)&param_2->granulepos + 4) = *(undefined4 *)((int)&param_1->granulepos + 4);
  param_2->pcmend = piVar4[param_1->W];
  if (*pfVar6 < (float)piVar7[1]) {
    *pfVar6 = (float)piVar7[1];
  }
  fVar17 = _vp_ampmax_decay(*pfVar6,param_1);
  *pfVar6 = fVar17;
  piVar7[1] = (int)fVar17;
  ppfVar12 = _vorbis_block_alloc(param_2,pvVar3->channels * 4);
  param_2->pcm = ppfVar12;
  pvVar13 = _vorbis_block_alloc(param_2,pvVar3->channels * 4);
  iVar15 = 0;
  *piVar7 = (int)pvVar13;
  if (0 < pvVar3->channels) {
    do {
      pvVar13 = _vorbis_block_alloc(param_2,(param_2->pcmend + iVar10) * 4);
      *(void **)(*piVar7 + iVar15 * 4) = pvVar13;
      memcpy(*(undefined4 *)(*piVar7 + iVar15 * 4),param_1->pcm[iVar15],
             (param_2->pcmend + iVar10) * 4);
      param_2->pcm[iVar15] = (float *)(*(int *)(*piVar7 + iVar15 * 4) + iVar10 * 4);
      iVar15 = iVar15 + 1;
    } while (iVar15 < pvVar3->channels);
  }
  if ((param_1->eofflag != 0) && (param_1->eofflag <= param_1->centerW)) {
    param_1->eofflag = -1;
    param_2->eofflag = 1;
    return 1;
  }
  iVar10 = piVar4[1] / 2;
  uVar16 = iVar14 - iVar10;
  if (0 < (int)uVar16) {
    _ve_envelope_shift((envelope_lookup *)*puVar5,uVar16);
    param_1->pcm_current = param_1->pcm_current - uVar16;
    iVar15 = 0;
    if (0 < pvVar3->channels) {
      do {
        memmove(param_1->pcm[iVar15],param_1->pcm[iVar15] + uVar16,param_1->pcm_current * 4);
        iVar15 = iVar15 + 1;
      } while (iVar15 < pvVar3->channels);
    }
    param_1->lW = param_1->W;
    param_1->W = param_1->nW;
    param_1->centerW = iVar10;
    if (param_1->eofflag != 0) {
      iVar15 = param_1->eofflag - uVar16;
      param_1->eofflag = iVar15;
      if (iVar15 < 1) {
        param_1->eofflag = -1;
      }
      if (param_1->eofflag <= iVar10) {
        uVar16 = (param_1->eofflag - iVar10) + uVar16;
        plVar1 = &param_1->granulepos;
        lVar8 = *plVar1;
        *(uint *)plVar1 = (int)*plVar1 + uVar16;
        piVar4 = (int *)((int)&param_1->granulepos + 4);
        *piVar4 = *piVar4 + ((int)uVar16 >> 0x1f) + (uint)CARRY4((uint)lVar8,uVar16);
        return 1;
      }
    }
    plVar1 = &param_1->granulepos;
    lVar8 = *plVar1;
    *(uint *)plVar1 = (int)*plVar1 + uVar16;
    piVar4 = (int *)((int)&param_1->granulepos + 4);
    *piVar4 = *piVar4 + ((int)uVar16 >> 0x1f) + (uint)CARRY4((uint)lVar8,uVar16);
  }
  return 1;
}
