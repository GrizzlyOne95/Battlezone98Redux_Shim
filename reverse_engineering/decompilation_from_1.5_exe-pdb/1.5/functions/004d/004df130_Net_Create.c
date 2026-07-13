/*
 * Entry: 004df130
 * Name: Net_Create
 * Namespace: Global
 * Signature: void Net_Create(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_Create(void)

{
  Net *this;
  
  this = operator_new(0x868);
  if (this != (Net *)0x0) {
    theNet = Net::Net(this);
    return;
  }
  theNet = (Net *)0x0;
  return;
}
