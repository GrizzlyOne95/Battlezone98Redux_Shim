/*
 * Entry: 0059aa90
 * Name: _fetch_headers
 * Namespace: Global
 * Signature: int _fetch_headers(OggVorbis_File * param_1, vorbis_info * param_2, vorbis_comment * param_3, long * * param_4, int * param_5, ogg_page * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
_fetch_headers(OggVorbis_File *param_1,vorbis_info *param_2,vorbis_comment *param_3,long **param_4,
              int *param_5,ogg_page *param_6)

{
  int iVar1;
  undefined4 uVar2;
  long64 lVar3;
  int local_5c;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  ogg_packet local_44;
  ogg_page local_20;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  if (param_6 == (ogg_page *)0x0) {
    lVar3 = _get_next_page(param_1,&local_20,0x10000);
    local_4c = (int)lVar3;
    local_48 = (int)((ulonglong)lVar3 >> 0x20);
    if ((local_4c == -0x80) && (local_48 == -1)) {
      return -0x80;
    }
    if ((local_48 < 1) && (lVar3 < 0)) {
      return -0x84;
    }
    param_6 = &local_20;
  }
  vorbis_info_init(param_2);
  vorbis_comment_init(param_3);
  param_1->ready_state = 2;
  do {
    iVar1 = ogg_page_bos(param_6);
    if (iVar1 == 0) goto LAB_0059acb4;
    if (param_4 != (long **)0x0) {
      iVar1 = _lookup_page_serialno(param_6,*param_4,*param_5);
      if (iVar1 != 0) {
        if (*param_4 != (long *)0x0) {
          free(*param_4);
        }
        *param_4 = (long *)0x0;
        *param_5 = 0;
        local_10 = -0x85;
        goto LAB_0059adef;
      }
      _add_serialno(param_6,param_4,param_5);
    }
    if (param_1->ready_state < 3) {
      uVar2 = ogg_page_serialno(param_6);
      ogg_stream_reset_serialno(&param_1->os,uVar2);
      ogg_stream_pagein(&param_1->os,param_6);
      iVar1 = ogg_stream_packetout(&param_1->os,&local_44);
      if ((0 < iVar1) && (iVar1 = vorbis_synthesis_idheader(&local_44), iVar1 != 0)) {
        param_1->ready_state = 3;
        local_10 = vorbis_synthesis_headerin(param_2,param_3,&local_44);
        if (local_10 != 0) {
          local_10 = -0x85;
          goto LAB_0059adef;
        }
      }
    }
    lVar3 = _get_next_page(param_1,param_6,0x10000);
    local_54 = (int)lVar3;
    local_50 = (int)((ulonglong)lVar3 >> 0x20);
    if ((local_54 == -0x80) && (local_50 == -1)) {
      local_10 = -0x80;
      goto LAB_0059adef;
    }
    if ((local_50 < 1) && (lVar3 < 0)) {
      local_10 = -0x84;
      goto LAB_0059adef;
    }
  } while ((param_1->ready_state != 3) ||
          (iVar1 = ogg_page_serialno(param_6), (param_1->os).serialno != iVar1));
  ogg_stream_pagein(&param_1->os,param_6);
LAB_0059acb4:
  if (param_1->ready_state == 3) {
    local_8 = 0;
LAB_0059acdd:
    if (local_8 < 2) {
      while ((local_8 < 2 && (iVar1 = ogg_stream_packetout(&param_1->os,&local_44), iVar1 != 0))) {
        if (iVar1 == -1) {
          local_10 = -0x85;
          goto LAB_0059adef;
        }
        local_10 = vorbis_synthesis_headerin(param_2,param_3,&local_44);
        if (local_10 != 0) goto LAB_0059adef;
        local_8 = local_8 + 1;
        local_10 = 0;
      }
      while (local_8 < 2) {
        lVar3 = _get_next_page(param_1,param_6,0x10000);
        local_5c = (int)((ulonglong)lVar3 >> 0x20);
        if ((local_5c < 1) && (lVar3 < 0)) {
          local_10 = -0x85;
          goto LAB_0059adef;
        }
        iVar1 = ogg_page_serialno(param_6);
        if ((param_1->os).serialno == iVar1) {
          ogg_stream_pagein(&param_1->os,param_6);
          break;
        }
        iVar1 = ogg_page_bos(param_6);
        if (iVar1 != 0) {
          if (local_c != 0) {
            local_10 = -0x85;
            goto LAB_0059adef;
          }
          local_c = 1;
        }
      }
      goto LAB_0059acdd;
    }
    local_10 = 0;
  }
  else {
    local_10 = -0x84;
LAB_0059adef:
    vorbis_info_clear(param_2);
    vorbis_comment_clear(param_3);
    param_1->ready_state = 2;
  }
  return local_10;
}
