/*
 * Entry: 0053004d
 * Name: GroundBlastClass::GroundBlastClass
 * Namespace: GroundBlastClass
 * Signature: GroundBlastClass * GroundBlastClass(GroundBlastClass * this, GroundBlastClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GroundBlastClass * __thiscall
GroundBlastClass::GroundBlastClass(GroundBlastClass *this,GroundBlastClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  ExplosionClass::ExplosionClass
            ((ExplosionClass *)this,(ExplosionClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
