/*
 * Entry: 005a7f90
 * Name: decode_packed_entry_number
 * Namespace: Global
 * Signature: long decode_packed_entry_number(codebook * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl decode_packed_entry_number(codebook *param_1,oggpack_buffer *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint unaff_EDI;
  
  iVar6 = param_1->dec_maxlength;
  iVar2 = oggpack_look(param_2,param_1->dec_firsttablen);
  if (iVar2 < 0) {
    iVar2 = param_1->used_entries;
    uVar7 = 0;
  }
  else {
    uVar4 = param_1->dec_firsttable[iVar2];
    if (-1 < (int)uVar4) {
      oggpack_adv(param_2,(int)param_1->dec_codelengths[uVar4 - 1]);
      return uVar4 - 1;
    }
    uVar7 = (int)uVar4 >> 0xf & 0x7fff;
    iVar2 = param_1->used_entries - (uVar4 & 0x7fff);
  }
  iVar3 = oggpack_look(param_2,iVar6);
  do {
    if (-1 < iVar3) {
LAB_005a801f:
      uVar4 = bitreverse(unaff_EDI);
      iVar3 = iVar2 - uVar7;
      if (1 < iVar3) {
        do {
          uVar5 = iVar3 >> 1;
          uVar1 = (uint)(uVar4 < param_1->codelist[uVar5 + uVar7]);
          iVar2 = iVar2 - (-uVar1 & uVar5);
          uVar7 = uVar7 + (uVar1 - 1 & uVar5);
          iVar3 = iVar2 - uVar7;
        } while (1 < iVar3);
      }
      if (iVar6 < param_1->dec_codelengths[uVar7]) {
        oggpack_adv(param_2,iVar6);
        return -1;
      }
      oggpack_adv(param_2,(int)param_1->dec_codelengths[uVar7]);
      return uVar7;
    }
    if (iVar6 < 2) {
      if (iVar3 < 0) {
        return -1;
      }
      goto LAB_005a801f;
    }
    iVar6 = iVar6 + -1;
    iVar3 = oggpack_look(param_2,iVar6);
  } while( true );
}
