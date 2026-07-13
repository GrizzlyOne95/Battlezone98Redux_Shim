/*
 * Entry: 0047f0ee
 * Name: ArmoryClass::ArmoryClass
 * Namespace: ArmoryClass
 * Signature: ArmoryClass * ArmoryClass(ArmoryClass * this, ArmoryClass * param_1, long64 param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArmoryClass * __thiscall
ArmoryClass::ArmoryClass(ArmoryClass *this,ArmoryClass *param_1,long64 param_2)

{
  bool bVar1;
  GameObjectClass *pGVar2;
  uint unaff_ESI;
  undefined4 unaff_EDI;
  GameObjectClass **ppGVar3;
  int local_10;
  uint local_c;
  ArmoryClass *local_8;
  
  local_8 = this;
  ProducerClass::ProducerClass
            ((ProducerClass *)this,(ProducerClass *)param_1,CONCAT44(unaff_EDI,(undefined4)param_2))
  ;
  this->_padding_ = (int)&_vftable_;
  ParameterDB::ParameterDB((ParameterDB *)&param_2,(char *)&this->_padding_);
  param_1 = (ArmoryClass *)0x0;
  ppGVar3 = this->cannonItem + 2;
  do {
    ParameterDB::Get((ParameterDB *)&param_2,0xed18adf9,
                     ((byte)((char)param_1 + 0x31) ^ 0x4549b5d3) * 0x1000193,(long64 *)&local_10,
                     (ulonglong)unaff_ESI << 0x20);
    if (local_10 == 0 && local_c == 0) {
      *ppGVar3 = (GameObjectClass *)0x0;
    }
    else {
      unaff_ESI = local_c;
      pGVar2 = GameObjectClass::Find(CONCAT44(local_c,local_10));
      *ppGVar3 = pGVar2;
    }
    param_1 = (ArmoryClass *)((int)&param_1->_padding_ + 1);
    ppGVar3 = ppGVar3 + 1;
  } while ((int)param_1 < 9);
  param_1 = (ArmoryClass *)0x0;
  ppGVar3 = local_8->rocketItem + 2;
  do {
    ParameterDB::Get((ParameterDB *)&param_2,0xed18adf9,
                     ((byte)((char)param_1 + 0x31) ^ 0xae0b29d6) * 0x1000193,(long64 *)&local_10,
                     (ulonglong)unaff_ESI << 0x20);
    if (local_10 == 0 && local_c == 0) {
      *ppGVar3 = (GameObjectClass *)0x0;
    }
    else {
      unaff_ESI = local_c;
      pGVar2 = GameObjectClass::Find(CONCAT44(local_c,local_10));
      *ppGVar3 = pGVar2;
    }
    param_1 = (ArmoryClass *)((int)&param_1->_padding_ + 1);
    ppGVar3 = ppGVar3 + 1;
  } while ((int)param_1 < 9);
  param_1 = (ArmoryClass *)0x0;
  ppGVar3 = local_8->mortarItem + 2;
  do {
    ParameterDB::Get((ParameterDB *)&param_2,0xed18adf9,
                     ((byte)((char)param_1 + 0x31) ^ 0xd238f033) * 0x1000193,(long64 *)&local_10,
                     (ulonglong)unaff_ESI << 0x20);
    if (local_10 == 0 && local_c == 0) {
LAB_0047f256:
      *ppGVar3 = (GameObjectClass *)0x0;
    }
    else {
      unaff_ESI = local_c;
      pGVar2 = GameObjectClass::Find(CONCAT44(local_c,local_10));
      *ppGVar3 = pGVar2;
      if (pGVar2 != (GameObjectClass *)0x0) {
        unaff_ESI = 0x47f21b;
        bVar1 = Net::IsNetGame();
        if ((((bVar1) && ((*ppGVar3)->sig == 0x5745504e)) && (Net::bSplint == false)) &&
           (((local_10 == 0x70737061 && (local_c == 0x6e6c)) ||
            ((local_10 == 0x70737073 && (local_c == 0x6e6c)))))) goto LAB_0047f256;
      }
    }
    param_1 = (ArmoryClass *)((int)&param_1->_padding_ + 1);
    ppGVar3 = ppGVar3 + 1;
    if (8 < (int)param_1) {
      param_1 = (ArmoryClass *)0x0;
      ppGVar3 = local_8->specialItem + 2;
      do {
        ParameterDB::Get((ParameterDB *)&param_2,0xed18adf9,
                         ((byte)((char)param_1 + 0x31) ^ 0xe01161ff) * 0x1000193,(long64 *)&local_10
                         ,(ulonglong)unaff_ESI << 0x20);
        if (local_10 == 0 && local_c == 0) {
          *ppGVar3 = (GameObjectClass *)0x0;
        }
        else {
          unaff_ESI = local_c;
          pGVar2 = GameObjectClass::Find(CONCAT44(local_c,local_10));
          *ppGVar3 = pGVar2;
        }
        param_1 = (ArmoryClass *)((int)&param_1->_padding_ + 1);
        ppGVar3 = ppGVar3 + 1;
      } while ((int)param_1 < 9);
      ParameterDB::~ParameterDB((ParameterDB *)&param_2);
      return local_8;
    }
  } while( true );
}
