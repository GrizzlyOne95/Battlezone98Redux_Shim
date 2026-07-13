/*
 * Entry: 0052f363
 * Name: ExplosionClass::ExplosionClass
 * Namespace: ExplosionClass
 * Signature: ExplosionClass * ExplosionClass(ExplosionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass * __thiscall ExplosionClass::ExplosionClass(ExplosionClass *this)

{
  vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this_00;
  ExplosionClass **ppEVar1;
  ExplosionClass *local_8;
  
  ppEVar1 = &local_8;
  this->_padding_ = (int)&_vftable_;
  local_8 = this;
  this_00 = GetProtoList();
  std::vector<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::push_back(this_00,ppEVar1);
  this->sig = 0x4558504c;
  this->label = "explosion";
  this->proto = this;
  *(undefined4 *)&this->cfg = 0;
  *(undefined4 *)((int)&this->cfg + 4) = 0;
  this->freeObj = (_OBJ76 *)0x0;
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
  this->frameRate = 1.1754944e-38;
  this->explRadius = 0.0;
  this->frameIndex = 0;
  this->frameCount = 0;
  this->explSound[0] = '\0';
  this->explSound[1] = '\0';
  this->explSound[2] = '\0';
  this->explSound[3] = '\0';
  this->explSound[4] = '\0';
  this->explSound[5] = '\0';
  this->explSound[6] = '\0';
  this->explSound[7] = '\0';
  this->explSound[8] = '\0';
  this->explSound[9] = '\0';
  this->explSound[10] = '\0';
  this->explSound[0xb] = '\0';
  this->explSound[0xc] = '\0';
  this->explSound[0xd] = '\0';
  this->explSound[0xe] = '\0';
  this->explSound[0xf] = '\0';
  this->damageRadius = 0.0;
  this->damageValue = 0.0;
  this->damageTypes = 0;
  this->omegaShake = 0.0;
  return this;
}
