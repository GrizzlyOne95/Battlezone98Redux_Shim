/*
 * Entry: 0052c2ce
 * Name: BulletClass::BulletClass
 * Namespace: BulletClass
 * Signature: BulletClass * BulletClass(BulletClass * this, BulletClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BulletClass * __thiscall
BulletClass::BulletClass(BulletClass *this,BulletClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  OrdnanceClass::OrdnanceClass
            ((OrdnanceClass *)this,(OrdnanceClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2))
  ;
  *(undefined ***)this = &_vftable_;
  return this;
}
