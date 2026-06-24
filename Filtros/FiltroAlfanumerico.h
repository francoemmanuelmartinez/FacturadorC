#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace Filtros {
    public ref class FiltroAlfanumerico {
    private:
        static void SoloAlfanumerico(Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsLetterOrDigit(e->KeyChar) && e->KeyChar != 8 && e->KeyChar != 32
                && e->KeyChar != 64 && e->KeyChar != 46 && e->KeyChar != 95 && e->KeyChar != 45) {
                e->Handled = true;
            }
        }
    public:
        static void Aplicar(TextBox^ tb) {
            tb->KeyPress += gcnew KeyPressEventHandler(&FiltroAlfanumerico::SoloAlfanumerico);
        }
    };
}
