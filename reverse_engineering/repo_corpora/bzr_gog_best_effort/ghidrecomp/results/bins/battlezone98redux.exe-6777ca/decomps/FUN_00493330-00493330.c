
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00493330(float *param_1,float param_2)

{
  int iVar1;
  float10 fVar2;
  float fVar3;
  
  fVar3 = ((float)_DAT_009173c0 * 5.0) / (param_2 * 5.0 + param_1[2]);
  fVar2 = (float10)FUN_00461fd0(*param_1 * fVar3 + 0.5);
  iVar1 = (int)fVar2 + DAT_008e7924;
  fVar2 = (float10)FUN_00461fd0(param_1[1] * fVar3 + 0.5);
  return CONCAT44(DAT_008e7928 - (int)fVar2,iVar1);
}

