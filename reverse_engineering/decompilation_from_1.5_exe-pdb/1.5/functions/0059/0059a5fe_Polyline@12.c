/*
 * Entry: 0059a5fe
 * Name: _Polyline@12
 * Namespace: Global
 * Signature: BOOL _Polyline@12(HDC hdc, POINT * apt, int cpt)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BOOL _Polyline_12(HDC hdc,POINT *apt,int cpt)

{
  BOOL BVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a5fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  BVar1 = Polyline(hdc,apt,cpt);
  return BVar1;
}
