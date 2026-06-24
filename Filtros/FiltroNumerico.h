#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace Filtros {
    public ref class FiltroNumerico {
    private:
        static void SoloNumeros(Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 8) {
                e->Handled = true;
            }
        }
    public:
        static void Aplicar(TextBox^ tb) {
            tb->KeyPress += gcnew KeyPressEventHandler(&SoloNumeros);
        }
    };
}
