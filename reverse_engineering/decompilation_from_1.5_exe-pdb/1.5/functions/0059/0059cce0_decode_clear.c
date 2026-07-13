/*
 * Entry: 0059cce0
 * Name: _decode_clear
 * Namespace: Global
 * Signature: void _decode_clear(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _decode_clear(OggVorbis_File *param_1)

{
  vorbis_dsp_clear(&param_1->vd);
  vorbis_block_clear(&param_1->vb);
  param_1->ready_state = 2;
  return;
}
