/*
 * Entry: 005a1110
 * Name: vorbis_analysis_wrote
 * Namespace: Global
 * Signature: int vorbis_analysis_wrote(vorbis_dsp_state * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */

int __cdecl vorbis_analysis_wrote(vorbis_dsp_state *param_1,int param_2)

{
  vorbis_info *pvVar1;
  void *pvVar2;
  int iVar3;
  int iVar4;
  vorbis_dsp_state *unaff_EDI;
  int iVar5;
  vorbis_dsp_state *in_stack_ffffff6c;
  
  pvVar1 = param_1->vi;
  pvVar2 = pvVar1->codec_setup;
  if (param_2 < 1) {
    if (param_1->preextrapolate == 0) {
      _preextrapolate_helper(in_stack_ffffff6c);
    }
    vorbis_analysis_buffer(param_1,*(int *)((int)pvVar2 + 4) * 3);
    param_1->eofflag = param_1->pcm_current;
    iVar5 = 0;
    param_1->pcm_current =
         param_1->pcm_current + *(int *)((int)pvVar2 + 4) * 2 + *(int *)((int)pvVar2 + 4);
    if (0 < pvVar1->channels) {
      do {
        iVar3 = param_1->eofflag;
        if (iVar3 < 0x41) {
          memset(param_1->pcm[iVar5] + iVar3,0,(param_1->pcm_current - iVar3) * 4);
        }
        else {
          iVar4 = iVar3;
          if (*(int *)((int)pvVar2 + 4) < iVar3) {
            iVar4 = *(int *)((int)pvVar2 + 4);
          }
          vorbis_lpc_from_data
                    (param_1->pcm[iVar5] + (iVar3 - iVar4),(float *)&stack0xffffff6c,iVar4,0x20);
          iVar3 = param_1->eofflag;
          vorbis_lpc_predict((float *)&stack0xffffff6c,param_1->pcm[iVar5] + iVar3 + -0x20,0x20,
                             param_1->pcm[iVar5] + iVar3,param_1->pcm_current - iVar3);
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < pvVar1->channels);
      return 0;
    }
  }
  else {
    iVar5 = param_2 + param_1->pcm_current;
    if (param_1->pcm_storage < iVar5) {
      return -0x83;
    }
    param_1->pcm_current = iVar5;
    if ((param_1->preextrapolate == 0) && (*(int *)((int)pvVar2 + 4) < iVar5 - param_1->centerW)) {
      _preextrapolate_helper(unaff_EDI);
    }
  }
  return 0;
}
