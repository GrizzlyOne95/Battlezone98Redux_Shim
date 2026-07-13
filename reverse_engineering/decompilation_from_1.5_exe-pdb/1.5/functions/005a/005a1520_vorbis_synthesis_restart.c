/*
 * Entry: 005a1520
 * Name: vorbis_synthesis_restart
 * Namespace: Global
 * Signature: int vorbis_synthesis_restart(vorbis_dsp_state * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_restart(vorbis_dsp_state *param_1)

{
  void *pvVar1;
  void *pvVar2;
  byte bVar3;
  int iVar4;
  
  pvVar1 = param_1->backend_state;
  if (((pvVar1 != (void *)0x0) && (param_1->vi != (vorbis_info *)0x0)) &&
     (pvVar2 = param_1->vi->codec_setup, pvVar2 != (void *)0x0)) {
    bVar3 = (byte)*(undefined4 *)((int)pvVar2 + 0xe48);
    iVar4 = *(int *)((int)pvVar2 + 4) >> (bVar3 + 1 & 0x1f);
    param_1->eofflag = 0;
    param_1->centerW = iVar4;
    param_1->pcm_returned = -1;
    *(undefined4 *)&param_1->granulepos = 0xffffffff;
    param_1->pcm_current = iVar4 >> (bVar3 & 0x1f);
    *(undefined4 *)((int)&param_1->granulepos + 4) = 0xffffffff;
    *(undefined4 *)&param_1->sequence = 0xffffffff;
    *(undefined4 *)((int)&param_1->sequence + 4) = 0xffffffff;
    *(undefined4 *)((int)pvVar1 + 0x80) = 0xffffffff;
    *(undefined4 *)((int)pvVar1 + 0x84) = 0xffffffff;
    return 0;
  }
  return -1;
}
