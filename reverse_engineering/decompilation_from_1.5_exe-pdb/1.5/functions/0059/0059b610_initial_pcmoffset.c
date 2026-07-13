/*
 * Entry: 0059b610
 * Name: _initial_pcmoffset
 * Namespace: Global
 * Signature: long64 _initial_pcmoffset(OggVorbis_File * param_1, vorbis_info * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long64 __cdecl _initial_pcmoffset(OggVorbis_File *param_1,vorbis_info *param_2)

{
  int iVar1;
  long lVar2;
  uint uVar3;
  bool bVar4;
  long64 lVar5;
  longlong lVar6;
  int local_54;
  ogg_packet local_4c;
  uint local_2c;
  int local_28;
  long local_20;
  int local_1c;
  ogg_page local_18;
  long local_8;
  
  local_2c = 0;
  local_28 = 0;
  local_20 = -1;
  local_8 = (param_1->os).serialno;
  do {
    do {
      lVar5 = _get_next_page(param_1,&local_18,-1);
      lVar6 = CONCAT44(local_28,local_2c);
      local_54 = (int)((ulonglong)lVar5 >> 0x20);
      if ((local_54 < 1) && (lVar5 < 0)) goto LAB_0059b743;
      iVar1 = ogg_page_bos(&local_18);
      lVar6 = CONCAT44(local_28,local_2c);
      if (iVar1 != 0) goto LAB_0059b743;
      iVar1 = ogg_page_serialno(&local_18);
    } while (iVar1 != local_8);
    ogg_stream_pagein(&param_1->os,&local_18);
    lVar2 = local_20;
    while (local_20 = lVar2, local_1c = ogg_stream_packetout(&param_1->os,&local_4c), local_1c != 0)
    {
      lVar2 = local_20;
      if ((0 < local_1c) && (lVar2 = vorbis_packet_blocksize(param_2,&local_4c), local_20 != -1)) {
        uVar3 = local_20 + lVar2 >> 2;
        bVar4 = CARRY4(uVar3,local_2c);
        local_2c = uVar3 + local_2c;
        local_28 = local_28 + (local_20 + lVar2 >> 0x1f) + (uint)bVar4;
      }
    }
    lVar6 = ogg_page_granulepos(&local_18);
  } while (lVar6 == -1);
  lVar6 = ogg_page_granulepos(&local_18);
  lVar6 = lVar6 - CONCAT44(local_28,local_2c);
LAB_0059b743:
  local_28 = (int)((ulonglong)lVar6 >> 0x20);
  if ((local_28 < 1) && (lVar6 < 0)) {
    lVar6 = 0;
  }
  return lVar6;
}
