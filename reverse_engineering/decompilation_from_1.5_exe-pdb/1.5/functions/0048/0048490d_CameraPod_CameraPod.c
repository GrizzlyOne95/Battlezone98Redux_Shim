/*
 * Entry: 0048490d
 * Name: CameraPod::CameraPod
 * Namespace: CameraPod
 * Signature: CameraPod * CameraPod(CameraPod * this, _OBJ76 * param_1, CameraPodClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

CameraPod * __thiscall CameraPod::CameraPod(CameraPod *this,_OBJ76 *param_1,CameraPodClass *param_2)

{
  float fVar1;
  float fVar2;
  Scanner *pSVar3;
  _OBJ76 *p_Var4;
  
  PowerUp::PowerUp((PowerUp *)this,param_1,(PowerUpClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  if (0.0 < param_2->rangeScan) {
    pSVar3 = operator_new(0x14);
    if (pSVar3 == (Scanner *)0x0) {
      pSVar3 = (Scanner *)0x0;
    }
    else {
      pSVar3 = Scanner::Scanner(pSVar3,(GameObject *)this);
    }
    *(Scanner **)&this->field_0x190 = pSVar3;
    pSVar3->range = param_2->rangeScan;
    *(float *)(*(int *)&this->field_0x190 + 4) = param_2->periodScan;
  }
  p_Var4 = obj_find_class(param_1,CLASS_ID_EYEPOINT);
  if (p_Var4 == (_OBJ76 *)0x0) {
    p_Var4 = create_obj(param_1,".\\fun3d\\CameraPod.cpp");
    *(undefined4 *)&p_Var4->id = 0x70657965;
    *(undefined4 *)((int)&p_Var4->id + 4) = 0x746e696f;
    fVar1 = *(float *)(*(int *)&this->field_0xe4 + 0x14);
    fVar2 = *(float *)(*(int *)&this->field_0xe4 + 0xc);
    p_Var4->class_id = CLASS_ID_EYEPOINT;
    (p_Var4->transform).posit_y = (double)(fVar1 * 0.8 + fVar2);
  }
  return this;
}
