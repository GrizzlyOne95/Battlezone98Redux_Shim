/*
 * Entry: 005a0280
 * Name: vorbis_synthesis_headerin
 * Namespace: Global
 * Signature: int vorbis_synthesis_headerin(vorbis_info * param_1, vorbis_comment * param_2, ogg_packet * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
vorbis_synthesis_headerin(vorbis_info *param_1,vorbis_comment *param_2,ogg_packet *param_3)

{
  undefined1 uVar1;
  int iVar2;
  oggpack_buffer *unaff_ESI;
  int iVar3;
  vorbis_info *unaff_EDI;
  int *piVar4;
  int local_1c;
  undefined2 local_18;
  vorbis_comment local_14;
  
  if (param_3 == (ogg_packet *)0x0) {
    return -0x85;
  }
  oggpack_readinit(&local_14,param_3->packet,param_3->bytes);
  iVar2 = oggpack_read(&local_14,8);
  local_1c = 0;
  local_18 = 0;
  iVar3 = 6;
  piVar4 = &local_1c;
  do {
    iVar3 = iVar3 + -1;
    uVar1 = oggpack_read(&local_14,8);
    *(undefined1 *)piVar4 = uVar1;
    piVar4 = (int *)((int)piVar4 + 1);
  } while (iVar3 != 0);
  if (((local_1c == 0x62726f76) && ((char)local_18 == 'i')) && (local_18._1_1_ == 's')) {
    if (iVar2 == 1) {
      if ((param_3->b_o_s != 0) && (param_1->rate == 0)) {
        iVar2 = _vorbis_unpack_info(unaff_EDI,unaff_ESI);
        return iVar2;
      }
    }
    else if (iVar2 == 3) {
      if (param_1->rate != 0) {
        iVar2 = _vorbis_unpack_comment(&local_14,(oggpack_buffer *)unaff_EDI);
        return iVar2;
      }
    }
    else if (((iVar2 == 5) && (param_1->rate != 0)) && (param_2->vendor != (char *)0x0)) {
      iVar2 = _vorbis_unpack_books(param_1,(oggpack_buffer *)unaff_EDI);
      return iVar2;
    }
    return -0x85;
  }
  return -0x84;
}
