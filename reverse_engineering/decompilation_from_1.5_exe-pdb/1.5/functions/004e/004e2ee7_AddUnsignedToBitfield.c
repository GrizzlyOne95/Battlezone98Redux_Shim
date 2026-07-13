/*
 * Entry: 004e2ee7
 * Name: AddUnsignedToBitfield
 * Namespace: Global
 * Signature: void AddUnsignedToBitfield(int param_1, void * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddUnsignedToBitfield(int param_1,void *param_2,uint param_3,uint param_4)

{
  int iVar1;
  
  if (param_1 < 0) {
    param_1 = 0;
  }
  else {
    iVar1 = (1 << ((byte)param_4 & 0x1f)) + -1;
    if (iVar1 < param_1) {
      param_1 = iVar1;
    }
  }
  AddToBitfield(param_1,param_2,param_3,param_4);
  return;
}
