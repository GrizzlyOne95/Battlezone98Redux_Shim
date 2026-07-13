/*
 * Entry: 004e08a0
 * Name: Net_Delete
 * Namespace: Global
 * Signature: void Net_Delete(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_Delete(void)

{
  Net *pNVar1;
  
  pNVar1 = theNet;
  if (theNet != (Net *)0x0) {
    Net::~Net(theNet);
    operator_delete(pNVar1);
    theNet = (Net *)0x0;
  }
  return;
}
