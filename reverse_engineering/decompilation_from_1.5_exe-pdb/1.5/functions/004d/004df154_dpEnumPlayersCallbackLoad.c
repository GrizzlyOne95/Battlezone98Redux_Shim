/*
 * Entry: 004df154
 * Name: dpEnumPlayersCallbackLoad
 * Namespace: Global
 * Signature: void dpEnumPlayersCallbackLoad(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpEnumPlayersCallbackLoad(ushort param_1,char *param_2,long param_3,void *param_4)

{
  bool bVar1;
  ushort unaff_SI;
  
  if ((param_1 != 0xfa01) && (Net::myPlayerID != param_1)) {
    bVar1 = IsHost(unaff_SI);
    if (bVar1) {
      DistributedObject_ReadPermStateGlobal(param_1);
    }
    DistributedObject_ReadPermStateLocal(param_1);
  }
  return;
}
