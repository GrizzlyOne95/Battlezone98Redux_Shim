/*
 * Entry: 004814e6
 * Name: GAS_DebugUpdate
 * Namespace: Global
 * Signature: void GAS_DebugUpdate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GAS_DebugUpdate(void)

{
  int iVar1;
  _gas_object *unaff_ESI;
  _gas_object *p_Var2;
  
  if ((GM != (GAS_MASTER *)0x0) && (iVar1 = Mono_IsActive(mHdl), iVar1 != 0)) {
    monoLine = 1;
    Mono_Line(mHdl,0,0,7,
              "Playing Sounds                                                                  ");
    for (p_Var2 = firstSound; iVar1 = monoLine, p_Var2 != (_gas_object *)0x0; p_Var2 = p_Var2->next)
    {
      if ((p_Var2->flags & 4) != 0) {
        GAS_ObjInfo(unaff_ESI);
      }
    }
    monoLine = monoLine + 1;
    Mono_Line(mHdl,0,(short)iVar1,7,
              "Copies                                                                          ");
    ClearCopies();
    iVar1 = monoLine;
    for (p_Var2 = firstSound; p_Var2 != (_gas_object *)0x0; p_Var2 = p_Var2->next) {
      monoLine = iVar1;
      iVar1 = IncCopy(unaff_ESI);
      if (iVar1 == 2) {
        GAS_ObjInfo(unaff_ESI);
      }
      iVar1 = monoLine;
    }
    monoLine = iVar1 + 1;
    Mono_Line(mHdl,0,(short)iVar1,7,
              "All Sounds                                                                      ");
    iVar1 = monoLine;
    for (p_Var2 = firstSound; monoLine = iVar1, p_Var2 != (_gas_object *)0x0; p_Var2 = p_Var2->next)
    {
      GAS_ObjInfo(unaff_ESI);
      iVar1 = monoLine;
    }
    if (iVar1 < lastMonoLine) {
      do {
        Mono_Line(mHdl,0,(short)iVar1,7,
                  "                                                                                "
                 );
        iVar1 = iVar1 + 1;
      } while (iVar1 < lastMonoLine);
    }
    lastMonoLine = monoLine;
  }
  return;
}
