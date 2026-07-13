/*
 * Entry: 0047e7eb
 * Name: Armory::CanSendReload
 * Namespace: Armory
 * Signature: bool CanSendReload(Armory * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Armory::CanSendReload(Armory *this)

{
  bool bVar1;
  long lVar2;
  long lVar3;
  
  lVar2 = AdjustedScrapCost(this->_padding_,this->reloadItem);
  if (((this->_padding_ == 2) && (bVar1 = Producer::IsBusy((Producer *)this), !bVar1)) &&
     (lVar3 = Team::GetScrap((Team *)this->_padding_), lVar2 <= lVar3)) {
    return true;
  }
  return false;
}
