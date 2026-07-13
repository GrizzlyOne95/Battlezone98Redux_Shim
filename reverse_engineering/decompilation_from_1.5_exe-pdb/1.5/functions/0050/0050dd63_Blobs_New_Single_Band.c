/*
 * Entry: 0050dd63
 * Name: Blobs_New_Single_Band
 * Namespace: Global
 * Signature: ushort * * Blobs_New_Single_Band(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort ** __cdecl Blobs_New_Single_Band(int param_1,int param_2)

{
  ushort **ppuVar1;
  
  ppuVar1 = NR_Smatrix(0,param_1 + -1,0,param_2 + -1);
  return ppuVar1;
}
