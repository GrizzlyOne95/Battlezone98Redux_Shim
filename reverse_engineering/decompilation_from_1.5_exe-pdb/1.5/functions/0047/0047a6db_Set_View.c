/*
 * Entry: 0047a6db
 * Name: Set_View
 * Namespace: Global
 * Signature: void Set_View(tagENTITY * param_1, GKCommandKey param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_View(tagENTITY *param_1,GKCommandKey param_2)

{
  uint uVar1;
  
  if (View_Record.Current_View != FSM_CAMERA_CONTROL) {
    uVar1 = 0;
    do {
      if (Int_View_Fnction_Table[uVar1].Code == param_2) {
        if (param_2 != This_View.Code) {
          if (This_View.Code == GK_TOGGLE_EDITMODE) {
            Exit_Edit_View(param_1);
          }
          else {
            Last_View.Code = This_View.Code;
            Last_View.fntc = This_View.fntc;
          }
          This_View.Code = Int_View_Fnction_Table[uVar1].Code;
          This_View.fntc = Int_View_Fnction_Table[uVar1].fntc;
        }
        (*This_View.fntc)(param_1);
        InvalidateAllBSPs();
        return;
      }
      uVar1 = uVar1 + 1;
    } while (uVar1 < 10);
  }
  return;
}
