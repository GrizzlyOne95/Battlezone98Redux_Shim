
bool __thiscall
FUN_007f5bc0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_7;
  
  uVar3 = 0;
  puVar2 = (undefined4 *)FUN_004324a0(param_2,param_3,param_4);
  cVar1 = FUN_007f6450(param_1,local_7,*puVar2,puVar2[1],puVar2[2],uVar3);
  return cVar1 == '\0';
}

