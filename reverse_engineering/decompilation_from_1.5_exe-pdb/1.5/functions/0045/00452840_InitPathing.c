/*
 * Entry: 00452840
 * Name: InitPathing
 * Namespace: Global
 * Signature: void InitPathing(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitPathing(void)

{
  vector<Strip_*,std::allocator<Strip_*>_> *pvVar1;
  undefined4 *puVar2;
  
  pvVar1 = operator_new(0x18);
  if (pvVar1 == (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    pvVar1 = (vector<Strip_*,std::allocator<Strip_*>_> *)0x0;
  }
  else {
    puVar2 = operator_new(4);
    if (puVar2 == (undefined4 *)0x0) {
      pvVar1->_padding_ = 0;
      pvVar1->_Myfirst = (Strip **)0x0;
      pvVar1->_Mylast = (Strip **)0x0;
      pvVar1->_Myend = (Strip **)0x0;
    }
    else {
      *puVar2 = pvVar1;
      pvVar1->_padding_ = (int)puVar2;
      pvVar1->_Myfirst = (Strip **)0x0;
      pvVar1->_Mylast = (Strip **)0x0;
      pvVar1->_Myend = (Strip **)0x0;
    }
  }
  freeStrips = pvVar1;
  std::vector<Strip_*,std::allocator<Strip_*>_>::reserve(pvVar1,0x10000);
  pvVar1 = operator_new(0x18);
  if (pvVar1 == (vector<Strip_*,std::allocator<Strip_*>_> *)0x0) {
    pvVar1 = (vector<Strip_*,std::allocator<Strip_*>_> *)0x0;
  }
  else {
    puVar2 = operator_new(4);
    if (puVar2 == (undefined4 *)0x0) {
      pvVar1->_padding_ = 0;
      pvVar1->_Myfirst = (Strip **)0x0;
      pvVar1->_Mylast = (Strip **)0x0;
      pvVar1->_Myend = (Strip **)0x0;
    }
    else {
      *puVar2 = pvVar1;
      pvVar1->_padding_ = (int)puVar2;
      pvVar1->_Myfirst = (Strip **)0x0;
      pvVar1->_Mylast = (Strip **)0x0;
      pvVar1->_Myend = (Strip **)0x0;
    }
  }
  usedStrips = pvVar1;
  std::vector<Strip_*,std::allocator<Strip_*>_>::reserve(pvVar1,0x10000);
  stripSeqNo = 0;
  BlockedCellInit();
  longSearch = 0x400;
  return;
}
