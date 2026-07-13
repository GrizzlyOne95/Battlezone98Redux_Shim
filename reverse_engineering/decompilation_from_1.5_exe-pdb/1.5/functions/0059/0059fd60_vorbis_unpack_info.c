/*
 * Entry: 0059fd60
 * Name: _vorbis_unpack_info
 * Namespace: Global
 * Signature: int _vorbis_unpack_info(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_unpack_info(vorbis_info *param_1,oggpack_buffer *param_2)

{
  int *piVar1;
  byte bVar2;
  int iVar3;
  long lVar4;
  vorbis_info *unaff_EDI;
  
  piVar1 = unaff_EDI->codec_setup;
  if (piVar1 == (int *)0x0) {
    return -0x81;
  }
  iVar3 = oggpack_read();
  unaff_EDI->version = iVar3;
  if (iVar3 != 0) {
    return -0x86;
  }
  iVar3 = oggpack_read();
  unaff_EDI->channels = iVar3;
  lVar4 = oggpack_read();
  unaff_EDI->rate = lVar4;
  lVar4 = oggpack_read();
  unaff_EDI->bitrate_upper = lVar4;
  lVar4 = oggpack_read();
  unaff_EDI->bitrate_nominal = lVar4;
  lVar4 = oggpack_read();
  unaff_EDI->bitrate_lower = lVar4;
  bVar2 = oggpack_read();
  *piVar1 = 1 << (bVar2 & 0x1f);
  bVar2 = oggpack_read();
  iVar3 = 1 << (bVar2 & 0x1f);
  piVar1[1] = iVar3;
  if ((((0 < unaff_EDI->rate) && (0 < unaff_EDI->channels)) && (0x3f < *piVar1)) &&
     ((*piVar1 <= iVar3 && (iVar3 < 0x2001)))) {
    iVar3 = oggpack_read();
    if (iVar3 == 1) {
      return 0;
    }
  }
  vorbis_info_clear(unaff_EDI);
  return -0x85;
}
