/*
 * Entry: 0059a850
 * Name: _ov_open1
 * Namespace: Global
 * Signature: int _ov_open1(void * param_1, OggVorbis_File * param_2, char * param_3, long param_4, ov_callbacks param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
_ov_open1(void *param_1,OggVorbis_File *param_2,char *param_3,long param_4,ov_callbacks param_5)

{
  undefined4 uVar1;
  vorbis_info *pvVar2;
  vorbis_comment *pvVar3;
  int iVar4;
  long *plVar5;
  long64 *plVar6;
  int in_stack_ffffffe4;
  long *local_10;
  int local_c;
  int local_8;
  
  if ((param_1 == (void *)0x0) ||
     (param_5.seek_func == (_func___cdecl_int_void_ptr_long64_int *)0x0)) {
    local_c = -1;
  }
  else {
    local_c = (*param_5.seek_func)(param_1,0x100000000,in_stack_ffffffe4);
  }
  local_10 = (long *)0x0;
  local_8 = 0;
  memset(param_2,0,0x2d0);
  param_2->datasource = param_1;
  (param_2->callbacks).read_func = param_5.read_func;
  (param_2->callbacks).seek_func = param_5.seek_func;
  (param_2->callbacks).close_func = param_5.close_func;
  (param_2->callbacks).tell_func = param_5.tell_func;
  ogg_sync_init(&param_2->oy);
  if (param_3 != (char *)0x0) {
    uVar1 = ogg_sync_buffer(&param_2->oy,param_4);
    memcpy(uVar1,param_3,param_4);
    ogg_sync_wrote(&param_2->oy,param_4);
  }
  if (local_c != -1) {
    param_2->seekable = 1;
  }
  param_2->links = 1;
  pvVar2 = calloc(param_2->links,0x20);
  param_2->vi = pvVar2;
  pvVar3 = calloc(param_2->links,0x10);
  param_2->vc = pvVar3;
  ogg_stream_init(&param_2->os,0xffffffff);
  iVar4 = _fetch_headers(param_2,param_2->vi,param_2->vc,&local_10,&local_8,(ogg_page *)0x0);
  if (iVar4 < 0) {
    param_2->datasource = (void *)0x0;
    ov_clear(param_2);
  }
  else {
    plVar5 = calloc(local_8 + 2,4);
    param_2->serialnos = plVar5;
    param_2->current_serialno = (param_2->os).serialno;
    *param_2->serialnos = param_2->current_serialno;
    param_2->serialnos[1] = local_8;
    memcpy(param_2->serialnos + 2,local_10,local_8 << 2);
    plVar6 = calloc(1,8);
    param_2->offsets = plVar6;
    plVar6 = calloc(1,8);
    param_2->dataoffsets = plVar6;
    plVar6 = param_2->offsets;
    *(undefined4 *)plVar6 = 0;
    *(undefined4 *)((int)plVar6 + 4) = 0;
    plVar6 = param_2->dataoffsets;
    *(int *)plVar6 = (int)param_2->offset;
    *(undefined4 *)((int)plVar6 + 4) = *(undefined4 *)((int)&param_2->offset + 4);
    param_2->ready_state = 1;
  }
  if (local_10 != (long *)0x0) {
    free(local_10);
  }
  return iVar4;
}
