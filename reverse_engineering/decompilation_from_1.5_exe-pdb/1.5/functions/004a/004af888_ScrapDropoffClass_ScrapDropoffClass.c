/*
 * Entry: 004af888
 * Name: ScrapDropoffClass::ScrapDropoffClass
 * Namespace: ScrapDropoffClass
 * Signature: ScrapDropoffClass * ScrapDropoffClass(ScrapDropoffClass * this, ScrapDropoffClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScrapDropoffClass * __thiscall
ScrapDropoffClass::ScrapDropoffClass
          (ScrapDropoffClass *this,ScrapDropoffClass *param_1,long64 param_2)

{
  undefined4 unaff_ESI;
  
  PowerUpClass::PowerUpClass
            ((PowerUpClass *)this,(PowerUpClass *)param_1,CONCAT44(unaff_ESI,(undefined4)param_2));
  *(undefined ***)this = &_vftable_;
  return this;
}
