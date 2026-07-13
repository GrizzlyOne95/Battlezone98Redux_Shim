/*
 * Entry: 0059f0c0
 * Name: _ov_initset
 * Namespace: Global
 * Signature: int _ov_initset(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ov_initset(OggVorbis_File *param_1)

{
  int iVar1;
  
  do {
    if (param_1->ready_state == 4) {
      return 0;
    }
    iVar1 = _fetch_and_process_packet(param_1,(ogg_packet *)0x0,1,0);
  } while ((-1 < iVar1) || (iVar1 == -3));
  return iVar1;
}
