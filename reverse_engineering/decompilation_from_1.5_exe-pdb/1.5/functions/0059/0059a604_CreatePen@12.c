/*
 * Entry: 0059a604
 * Name: _CreatePen@12
 * Namespace: Global
 * Signature: HPEN _CreatePen@12(int iStyle, int cWidth, COLORREF color)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HPEN _CreatePen_12(int iStyle,int cWidth,COLORREF color)

{
  HPEN pHVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a604. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  pHVar1 = CreatePen(iStyle,cWidth,color);
  return pHVar1;
}
