/*
 * Entry: 0059c390
 * Name: ov_serialnumber
 * Namespace: Global
 * Signature: long ov_serialnumber(OggVorbis_File * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ov_serialnumber(OggVorbis_File *param_1,int param_2)

{
  long lVar1;
  
  if (param_2 < param_1->links) {
    if ((param_1->seekable == 0) && (-1 < param_2)) {
      lVar1 = ov_serialnumber(param_1,-1);
    }
    else if (param_2 < 0) {
      lVar1 = param_1->current_serialno;
    }
    else {
      lVar1 = param_1->serialnos[param_2];
    }
  }
  else {
    lVar1 = ov_serialnumber(param_1,param_1->links + -1);
  }
  return lVar1;
}
