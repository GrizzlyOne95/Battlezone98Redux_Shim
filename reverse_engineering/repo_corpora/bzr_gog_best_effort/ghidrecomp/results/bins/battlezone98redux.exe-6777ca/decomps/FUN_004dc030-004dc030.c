
void __thiscall FUN_004dc030(int param_1,float param_2)

{
  int iVar1;
  float10 fVar2;
  
  fVar2 = (float10)FUN_004624f0();
  if (0.0 < (float)fVar2) {
    if (((param_1 + -0x18 == DAT_00917afc) && (param_2 <= 0.0)) &&
       (iVar1 = FUN_004a7850(), iVar1 != 0)) {
      return;
    }
    fVar2 = (float10)FUN_0046fbd0();
    fVar2 = (float10)FUN_004624f0((float)fVar2 + param_2);
    fVar2 = (float10)FUN_00456080((float)fVar2);
    FUN_004a76a0((float)fVar2);
  }
  return;
}

