/*
 * Entry: 004b2501
 * Name: dibs_textable
 * Namespace: Global
 * Signature: textab * dibs_textable(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

textab * __cdecl dibs_textable(char *param_1)

{
  int iVar1;
  textab *_Dest;
  int iVar2;
  char *_Dest_00;
  int iVar3;
  textab *unaff_ESI;
  char *unaff_EDI;
  
  _Dest = find_textable(unaff_EDI);
  iVar1 = tcacheFree;
  if (_Dest == (textab *)0x0) {
    iVar3 = tcacheFree * 0x34;
    _Dest = tcache + tcacheFree;
    iVar2 = IS_TEXTABLE(unaff_EDI);
    if (iVar2 == 0) {
      tcache[iVar1].num_dims = 1;
      tcache[iVar1].size_dims[0] = 1;
      _Dest_00 = operator_new__(0x10);
      tcache[iVar1].texture_array = _Dest_00;
      strncpy(_Dest_00,unaff_EDI,0xf);
      tcache[iVar1].usage_count = 0;
    }
    else {
      load_textable(unaff_EDI,unaff_ESI);
    }
    if (tcache[iVar1].usage_count == -1) {
      return (textab *)0x0;
    }
    strncpy(_Dest->group,unaff_EDI,0xf);
    tcacheFree = tcache[iVar1].next;
    tcache[iVar1].next = tcacheUsed;
    tcacheUsed = iVar3 / 0x34;
  }
  _Dest->usage_count = _Dest->usage_count + 1;
  return _Dest;
}
