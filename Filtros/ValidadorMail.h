#pragma once

using namespace System;
using namespace System::Text::RegularExpressions;

namespace Filtros {
    public ref class ValidadorMail {
    public:
        static bool esValido(String^ mail) {
            if (String::IsNullOrEmpty(mail)) return false;
            return Regex::IsMatch(mail, L"^[\\w.-]+@[\\w.-]+\\.\\w{2,}$");
        }
    };
}
