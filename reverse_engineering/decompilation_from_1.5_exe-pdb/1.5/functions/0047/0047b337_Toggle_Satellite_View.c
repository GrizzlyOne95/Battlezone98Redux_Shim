/*
 * Entry: 0047b337
 * Name: Toggle_Satellite_View
 * Namespace: Global
 * Signature: void Toggle_Satellite_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Toggle_Satellite_View(tagENTITY *param_1)

{
  if (View_Record.Current_View == OVER_VIEW) {
                    /* WARNING: Could not recover jumptable at 0x0047b340. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*Last_View.fntc)(param_1);
    return;
  }
  Apply_Satellite_View(param_1);
  return;
}
