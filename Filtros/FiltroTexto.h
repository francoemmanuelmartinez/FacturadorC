#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace Filtros {
    public ref class FiltroTexto {
    private:
        static void SoloTexto(Object^ sender, KeyPressEventArgs^ e) {
            if (!Char::IsLetter(e->KeyChar) && e->KeyChar != 8 && e->KeyChar != 32) {
                e->Handled = true;
            }
        }
    public:
        static void Aplicar(TextBox^ tb) {
            tb->KeyPress += gcnew KeyPressEventHandler(&FiltroTexto::SoloTexto);
        }
    };
}
