/*
 * Entry: 0040ba38
 * Name: AOI::LoadAll
 * Namespace: AOI
 * Signature: bool LoadAll(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl AOI::LoadAll(_iobuf *param_1)

{
  bool bVar1;
  int iVar2;
  int local_c;
  AOI *local_8;
  
  bVar1 = ::in(param_1,"[AOIs]");
  if ((bVar1) && (bVar1 = ::in(param_1,&local_c,4), bVar1)) {
    iVar2 = 0;
    do {
      if (local_c <= iVar2) {
        return true;
      }
      local_8 = operator_new(0x18);
      if (local_8 == (AOI *)0x0) {
        local_8 = (AOI *)0x0;
      }
      else {
        local_8->bDontSave = false;
      }
      bVar1 = Load(local_8,param_1);
      std::list<AOI_*,std::allocator<AOI_*>_>::push_back(&areas,&local_8);
      iVar2 = iVar2 + 1;
    } while (bVar1);
  }
  return false;
}
