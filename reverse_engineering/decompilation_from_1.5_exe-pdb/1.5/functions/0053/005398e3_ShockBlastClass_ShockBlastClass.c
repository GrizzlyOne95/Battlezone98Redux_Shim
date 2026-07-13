/*
 * Entry: 005398e3
 * Name: ShockBlastClass::ShockBlastClass
 * Namespace: ShockBlastClass
 * Signature: ShockBlastClass * ShockBlastClass(ShockBlastClass * this, ShockBlastClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ShockBlastClass * __thiscall
ShockBlastClass::ShockBlastClass(ShockBlastClass *this,ShockBlastClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ExplosionClass::ExplosionClass
            ((ExplosionClass *)this,(ExplosionClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
