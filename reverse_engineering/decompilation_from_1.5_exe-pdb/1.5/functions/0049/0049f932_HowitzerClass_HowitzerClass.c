/*
 * Entry: 0049f932
 * Name: HowitzerClass::HowitzerClass
 * Namespace: HowitzerClass
 * Signature: HowitzerClass * HowitzerClass(HowitzerClass * this, HowitzerClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HowitzerClass * __thiscall
HowitzerClass::HowitzerClass(HowitzerClass *this,HowitzerClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  TurretTankClass::TurretTankClass
            ((TurretTankClass *)this,(TurretTankClass *)param_1,
             CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
