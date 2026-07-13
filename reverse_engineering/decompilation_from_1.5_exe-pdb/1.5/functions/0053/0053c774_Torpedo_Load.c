/*
 * Entry: 0053c774
 * Name: Torpedo::Load
 * Namespace: Torpedo
 * Signature: bool Load(Torpedo * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Torpedo::Load(Torpedo *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  VECTOR_3D local_4c [6];
  
  p_Var1 = param_1;
  if (version < 0x407) {
    if (version < 0x3fb) {
      bVar2 = ::in(param_1,(int *)&param_1,4);
      if ((((!bVar2) || (bVar2 = ::in(p_Var1,(int *)&param_1,4), !bVar2)) ||
          (bVar2 = ::in(p_Var1,(int *)&param_1,4), !bVar2)) ||
         (((bVar2 = ::in(p_Var1,(int *)&param_1,4), !bVar2 ||
           (bVar2 = ::in(p_Var1,(int *)&param_1,4), !bVar2)) ||
          ((bVar2 = ::in(p_Var1,(int *)&param_1,4), !bVar2 ||
           (bVar2 = ::in(p_Var1,local_4c,0x48), !bVar2)))))) {
        return false;
      }
    }
    else {
      if (version < 0x404) {
        bVar2 = true;
      }
      else {
        bVar2 = ::in(param_1,(int *)&param_1,4);
      }
      if (bVar2 == false) {
        return false;
      }
    }
    bVar2 = GameObject::Load((GameObject *)this,p_Var1);
  }
  else {
    bVar2 = PowerUp::Load((PowerUp *)this,param_1);
  }
  return bVar2;
}
