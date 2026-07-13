/*
 * Entry: 0049520c
 * Name: GameObject::Remove
 * Namespace: GameObject
 * Signature: void Remove(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::Remove(GameObject *this)

{
  AiPath *pAVar1;
  Carrier *this_00;
  tagENTITY *ptVar2;
  AiMission *pAVar3;
  Weapon *this_01;
  uint uVar4;
  int local_8;
  
  pAVar3 = AiMission::GetCurrent();
  uVar4 = 0;
  if (pAVar3 != (AiMission *)0x0) {
    (**(code **)(pAVar3->_padding_ + 0x1c))(&this[-1].maxHealth);
  }
  GameFeature::DeleteObjectEvent((GameObject *)&this[-1].maxHealth);
  obj_set_flag((_OBJ76 *)(this->nextCmd).what,0x200);
  DistributedObject::Remove((DistributedObject *)this);
  pAVar1 = (this->nextCmd).where;
  if (pAVar1 != (AiPath *)0x0) {
    (**(code **)pAVar1->label)(1);
  }
  if (this->nameIndex != 0) {
    local_8 = 0x18;
    do {
      this_00 = (Carrier *)this->nameIndex;
      this_01 = Carrier::GetWeapon(this_00,uVar4);
      if (this_01 != (Weapon *)0x0) {
        if (uVar4 < 5) {
          *(undefined4 *)((int)this_00->hardpoint + local_8 + -4) = 0;
          this_00->existant = this_00->existant & ~(1 << ((byte)uVar4 & 0x1f));
        }
        Weapon::Remove(this_01);
      }
      local_8 = local_8 + 4;
      uVar4 = uVar4 + 1;
    } while (local_8 < 0x2c);
    ::operator_delete((void *)this->nameIndex);
    this->nameIndex = 0;
  }
  (**(code **)((int)this[-1].maxHealth + 8))();
  ptVar2 = (tagENTITY *)(this->nextCmd).priority;
  if (ptVar2 != (tagENTITY *)0x0) {
    del_entity(ptVar2);
  }
  remove_obj((_OBJ76 *)(this->nextCmd).what,".\\fun3d\\GameObject.cpp");
  return;
}
