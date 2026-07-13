/*
 * Entry: 005a01e0
 * Name: vorbis_synthesis_idheader
 * Namespace: Global
 * Signature: int vorbis_synthesis_idheader(ogg_packet * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl vorbis_synthesis_idheader(ogg_packet *param_1)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  int local_1c;
  undefined2 local_18;
  undefined1 local_14 [20];
  
  if (param_1 != (ogg_packet *)0x0) {
    oggpack_readinit(local_14,param_1->packet,param_1->bytes);
    if (param_1->b_o_s != 0) {
      iVar2 = oggpack_read(local_14,8);
      if (iVar2 == 1) {
        local_1c = 0;
        local_18 = 0;
        iVar2 = 6;
        piVar3 = &local_1c;
        do {
          iVar2 = iVar2 + -1;
          uVar1 = oggpack_read(local_14,8);
          *(undefined1 *)piVar3 = uVar1;
          piVar3 = (int *)((int)piVar3 + 1);
        } while (iVar2 != 0);
        if (((local_1c == 0x62726f76) && ((char)local_18 == 'i')) && (local_18._1_1_ == 's')) {
          return 1;
        }
      }
    }
  }
  return 0;
}
