/*
 * Entry: 00536201
 * Name: Popper::Init
 * Namespace: Popper
 * Signature: void Init(Popper * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Popper::Init(Popper *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  Grenade::Init((Grenade *)this,param_1,param_2);
  if (*(short *)&this->field_0x7c == -0x5ff) {
    g_next_ordid = g_next_ordid + 1;
    *(ushort *)&this->field_0x7e = g_next_ordid;
  }
  return;
}
