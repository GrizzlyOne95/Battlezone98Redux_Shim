
/* Library Function - Single Match
    public: void __thiscall CMFCToolBarsCustomizeDialog::EnableUserDefinedToolbars(int)
   
   Library: Visual Studio 2010 Debug */

void __thiscall
CMFCToolBarsCustomizeDialog::EnableUserDefinedToolbars
          (CMFCToolBarsCustomizeDialog *this,int param_1)

{
  CMFCToolBarsListPropertyPage::EnableUserDefinedToolbars
            (*(CMFCToolBarsListPropertyPage **)(this + 0x150),param_1);
  return;
}

