/*
 * Entry: 0049c3e0
 * Name: HoverCraft::Load
 * Namespace: HoverCraft
 * Signature: bool Load(HoverCraft * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HoverCraft::Load(HoverCraft *this,_iobuf *param_1)

{
  _iobuf *p_Var1;
  bool bVar2;
  
  p_Var1 = param_1;
  if (((0x17 < version - 0x3eaU) ||
      (((((((bVar2 = ::in(param_1,(float *)&param_1,4), bVar2 &&
            (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
           (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
          (((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
            (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
           ((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
            ((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
             (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)))))))) &&
         ((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
          (((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
            (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
           (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)))))) &&
        (((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
          (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
         (((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
           ((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
            (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)))) &&
          (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)))))) &&
       (((bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2 &&
         (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)) &&
        (bVar2 = ::in(p_Var1,(float *)&param_1,4), bVar2)))))) &&
     (bVar2 = Craft::Load((Craft *)this,p_Var1), bVar2)) {
    return true;
  }
  return false;
}
