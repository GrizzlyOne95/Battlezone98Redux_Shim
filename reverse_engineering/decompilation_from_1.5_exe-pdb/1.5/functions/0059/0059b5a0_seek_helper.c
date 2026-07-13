/*
 * Entry: 0059b5a0
 * Name: _seek_helper
 * Namespace: Global
 * Signature: int _seek_helper(OggVorbis_File * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _seek_helper(OggVorbis_File *param_1,long64 param_2)

{
  int iVar1;
  int unaff_EBP;
  undefined4 in_stack_00000008;
  
  if (param_1->datasource == (void *)0x0) {
    iVar1 = -0x81;
  }
  else {
    if (((param_1->callbacks).seek_func != (_func___cdecl_int_void_ptr_long64_int *)0x0) &&
       (iVar1 = (*(param_1->callbacks).seek_func)
                          (param_1->datasource,param_2 & 0xffffffff,unaff_EBP), iVar1 != -1)) {
      *(undefined4 *)&param_1->offset = in_stack_00000008;
      *(undefined4 *)((int)&param_1->offset + 4) = (undefined4)param_2;
      ogg_sync_reset(&param_1->oy);
      return 0;
    }
    iVar1 = -0x80;
  }
  return iVar1;
}
