
void __fastcall FUN_007f1bf0(int *param_1)

{
  if (*param_1 != 0) {
    Concurrency::details::CollectionTypes::Count::Increment((Count *)*param_1);
  }
  return;
}

