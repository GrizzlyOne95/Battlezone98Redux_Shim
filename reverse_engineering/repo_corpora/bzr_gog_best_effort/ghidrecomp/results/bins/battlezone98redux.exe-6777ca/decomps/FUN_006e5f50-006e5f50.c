
void FUN_006e5f50(void)

{
  char cVar1;
  int iVar2;
  int unaff_EBP;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 auStack_2c [7];
  undefined4 uStack_10;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  if (*(char *)(unaff_EBP + 0xc) == '\0') {
    puVar3 = (undefined4 *)(unaff_EBP + -0x40);
    puVar4 = auStack_2c;
    for (iVar2 = 0xb; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
    std::numpunct<char>::_Getvals<char>
              (*(numpunct<char> **)(unaff_EBP + -0x70),0,*(undefined4 *)(unaff_EBP + -0x74));
  }
  else {
    uStack_10 = 0x6e5f75;
    cVar1 = std::_Maklocchr<char>('.',(char *)0x0,(_Cvtvec *)(unaff_EBP + -0x40));
    *(char *)(*(int *)(unaff_EBP + -0x70) + 0xc) = cVar1;
    uStack_10 = 0x6e5f8b;
    cVar1 = std::_Maklocchr<char>(',',(char *)0x0,(_Cvtvec *)(unaff_EBP + -0x40));
    *(char *)(*(int *)(unaff_EBP + -0x70) + 0xd) = cVar1;
  }
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  FUN_0083e885();
  return;
}

