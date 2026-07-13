/*
 * Entry: 004e4710
 * Name: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator*
 * Namespace: std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>
 * Signature: ScorePlayer * * operator*(_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScorePlayer ** __thiscall
std::_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::operator*
          (_Vector_iterator<ScorePlayer_*,std::allocator<ScorePlayer_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_004e422b;
    }
  }
  iVar2 = *piVar1;
LAB_004e422b:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(ScorePlayer ***)&this->field_0x4;
}
