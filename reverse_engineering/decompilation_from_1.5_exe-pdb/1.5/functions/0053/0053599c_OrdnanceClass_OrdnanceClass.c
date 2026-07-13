/*
 * Entry: 0053599c
 * Name: OrdnanceClass::OrdnanceClass
 * Namespace: OrdnanceClass
 * Signature: OrdnanceClass * OrdnanceClass(OrdnanceClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass * __thiscall OrdnanceClass::OrdnanceClass(OrdnanceClass *this)

{
  vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_> *this_00;
  OrdnanceClass **ppOVar1;
  OrdnanceClass *local_8;
  
  ppOVar1 = &local_8;
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  this_00 = GetProtoList();
  std::vector<OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>::push_back(this_00,ppOVar1);
  this->proto = this;
  this->sig = 0x4f52444e;
  this->label = "ordnance";
  *(undefined4 *)&this->cfg = 0;
  *(undefined4 *)((int)&this->cfg + 4) = 0;
  this->odf[0] = '\0';
  this->odf[1] = '\0';
  this->odf[2] = '\0';
  this->odf[3] = '\0';
  this->odf[4] = '\0';
  this->odf[5] = '\0';
  this->odf[6] = '\0';
  this->odf[7] = '\0';
  this->odf[8] = '\0';
  this->odf[9] = '\0';
  this->odf[10] = '\0';
  this->odf[0xb] = '\0';
  this->odf[0xc] = '\0';
  this->odf[0xd] = '\0';
  this->odf[0xe] = '\0';
  this->odf[0xf] = '\0';
  this->lifeSpan = 1e+30;
  this->shotSpeed = 0.0;
  this->damageTypes = 0;
  this->damageValue = 0.0;
  this->ord = (_OBJ76 *)0x0;
  this->ent = (tagENTITY *)0x0;
  this->freeOrd = (_OBJ76 *)0x0;
  this->xplGround = (ExplosionClass *)0x0;
  this->xplVehicle = (ExplosionClass *)0x0;
  this->xplBuilding = (ExplosionClass *)0x0;
  this->ammoCost = 0;
  this->shotSound[0] = '\0';
  this->notifyRemote = false;
  return this;
}
