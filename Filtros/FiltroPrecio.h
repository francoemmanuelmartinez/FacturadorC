#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace Filtros {
    public ref class FiltroPrecio {
    private:
        static void SoloPrecio(Object^ sender, KeyPressEventArgs^ e) {
            auto tb = safe_cast<TextBox^>(sender);
            if (Char::IsDigit(e->KeyChar) || e->KeyChar == 8) {
                return;
            }
            if (e->KeyChar == L'.' && !tb->Text->Contains(L".")) {
                return;
            }
            e->Handled = true;
        }

        static void ValidarDecimales(Object^ sender, EventArgs^ e) {
            auto tb = safe_cast<TextBox^>(sender);
            if (tb->Text->Contains(L".")) {
                int idx = tb->Text->LastIndexOf(L".");
                if (tb->Text->Length - idx - 1 > 2) {
                    tb->Text = tb->Text->Substring(0, idx + 3);
                    tb->SelectionStart = tb->Text->Length;
                }
            }
        }
    public:
        static void Aplicar(TextBox^ tb) {
            tb->KeyPress += gcnew KeyPressEventHandler(&FiltroPrecio::SoloPrecio);
            tb->TextChanged += gcnew EventHandler(&FiltroPrecio::ValidarDecimales);
        }
    };
}
