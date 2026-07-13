/*
 * Entry: 004a5393
 * Name: Person::Explode
 * Namespace: Person
 * Signature: void Explode(Person * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Person::Explode(Person *this)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  int local_4;
  
  obj_set_flag((_OBJ76 *)this->_padding_,0x200);
  DeadMenDontUseCBs((_OBJ76 *)this->_padding_);
  VVar1.x = (float)this->_padding_;
  VVar1.y = (float)this->_padding_;
  VVar1.z = (float)this->_padding_;
  ChunkEffect::FullFragmentObject(&chunkEffect,(_OBJ76 *)this->_padding_,VVar1,false);
  Cache_Invalidate_Bsp((tagENTITY *)this->_padding_);
  local_4 = 10;
  do {
    VVar3.x = (float)this->_padding_;
    VVar3.y = (float)this->_padding_;
    VVar3.z = (float)this->_padding_;
    VVar2.x = (float)this->_padding_;
    VVar2.y = (float)this->_padding_;
    VVar2.z = (float)this->_padding_;
    ChunkEffect::CreateChunklet(&chunkEffect,VVar2,VVar3,false);
    local_4 = local_4 + -1;
  } while (local_4 != 0);
                    /* WARNING: Could not recover jumptable at 0x004a5423. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->_padding_ + 0x10))();
  return;
}
