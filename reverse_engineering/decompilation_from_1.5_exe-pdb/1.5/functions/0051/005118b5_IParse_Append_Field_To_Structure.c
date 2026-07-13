/*
 * Entry: 005118b5
 * Name: IParse_Append_Field_To_Structure
 * Namespace: Global
 * Signature: void IParse_Append_Field_To_Structure(_struct_list_element * param_1, int * param_2, int param_3, char[80] * param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
IParse_Append_Field_To_Structure
          (_struct_list_element *param_1,int *param_2,int param_3,char (*param_4) [80],int param_5,
          int param_6)

{
  int iVar1;
  _field_def *p_Var2;
  _field_def *p_Var3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  p_Var2 = IParse_Get_New_Field(param_5,param_4[*param_2 + 1]);
  param_1->struct_length = param_1->struct_length + param_6;
  p_Var2->field_length = param_6;
  p_Var3 = param_1->the_definition;
  if (p_Var3 == (_field_def *)0x0) {
    param_1->the_definition = p_Var2;
  }
  else {
    for (; p_Var3->next_field != (_field_def *)0x0; p_Var3 = p_Var3->next_field) {
    }
    p_Var3->next_field = p_Var2;
  }
  do {
    iVar1 = *param_2;
    *param_2 = iVar1 + 1;
    iVar4 = 2;
    bVar7 = true;
    pcVar5 = param_4[iVar1];
    pcVar6 = ";";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pcVar5 == *pcVar6;
      pcVar5 = pcVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (bVar7) {
      return;
    }
  } while( true );
}
