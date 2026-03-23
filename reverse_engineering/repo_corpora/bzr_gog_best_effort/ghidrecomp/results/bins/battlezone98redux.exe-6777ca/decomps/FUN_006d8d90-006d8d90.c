
undefined4 FUN_006d8d90(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = FUN_006abbb0();
  iVar2 = WSAGetLastError();
  puVar3 = (undefined4 *)FUN_00416430(iVar2,uVar1);
  uVar1 = puVar3[1];
  *param_2 = *puVar3;
  param_2[1] = uVar1;
  return param_1;
}

