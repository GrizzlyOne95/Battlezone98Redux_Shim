
void FUN_006cb2b0(void)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  undefined1 local_18 [8];
  undefined1 local_10 [8];
  allocator<char> *local_8;
  
  FUN_004fbb60();
  puVar3 = local_10;
  uVar1 = std::allocator<char>::allocator<char>(local_8);
  puVar2 = local_18;
  FUN_006cf300(puVar2,uVar1,puVar3);
  FUN_006cf850(puVar2,uVar1,puVar3);
  FUN_006aba00(local_10,"close");
  return;
}

