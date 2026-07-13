/*
 * Entry: 0059af50
 * Name: _get_data
 * Namespace: Global
 * Signature: long _get_data(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl _get_data(OggVorbis_File *param_1)

{
  int *piVar1;
  uint uVar2;
  void *pvVar3;
  
  piVar1 = _errno();
  *piVar1 = 0;
  if ((param_1->callbacks).read_func == (_func___cdecl_uint_void_ptr_uint_uint_void_ptr *)0x0) {
    uVar2 = 0xffffffff;
  }
  else if (param_1->datasource == (void *)0x0) {
    uVar2 = 0;
  }
  else {
    pvVar3 = (void *)ogg_sync_buffer(&param_1->oy,0x800);
    uVar2 = (*(param_1->callbacks).read_func)(pvVar3,1,0x800,param_1->datasource);
    if (0 < (int)uVar2) {
      ogg_sync_wrote(&param_1->oy,uVar2);
    }
    if ((uVar2 == 0) && (piVar1 = _errno(), *piVar1 != 0)) {
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}
