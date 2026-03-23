
undefined4 * __fastcall FUN_008440c0(undefined4 *param_1)

{
  code *pcVar1;
  BOOL BVar2;
  undefined4 *puVar3;
  undefined4 *local_4;
  
  local_4 = param_1;
  BVar2 = CryptGenRandom(*(HCRYPTPROV *)*param_1,4,(BYTE *)&local_4);
  if (BVar2 != 0) {
    return local_4;
  }
  FUN_008440f0("error while reading");
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined4 *)(*pcVar1)();
  return puVar3;
}

