/*
 * Entry: 0059a37c
 * Name: _MulDiv@12
 * Namespace: Global
 * Signature: int _MulDiv@12(int nNumber, int nNumerator, int nDenominator)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int _MulDiv_12(int nNumber,int nNumerator,int nDenominator)

{
  int iVar1;
  
                    /* WARNING: Could not recover jumptable at 0x0059a37c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  iVar1 = MulDiv(nNumber,nNumerator,nDenominator);
  return iVar1;
}
