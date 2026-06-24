#pragma once

using namespace System;
using namespace System::Text;

namespace Filtros {
    public ref class ValidadorCampos {
    public:
        static String^ validarRequeridos(... array<Object^>^ args) {
            StringBuilder^ faltan = gcnew StringBuilder();
            for (int i = 0; i < args->Length; i += 2) {
                String^ nombre = safe_cast<String^>(args[i]);
                String^ valor = safe_cast<String^>(args[i + 1]);
                if (String::IsNullOrEmpty(valor) || valor->Trim()->Length == 0) {
                    if (faltan->Length > 0) faltan->Append(L", ");
                    faltan->Append(nombre);
                }
            }
            if (faltan->Length > 0) return faltan->ToString();
            return nullptr;
        }
    };
}
