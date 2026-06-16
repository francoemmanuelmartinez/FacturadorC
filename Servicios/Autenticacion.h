#pragma once
#include "..\Models\Usuario.h"

using namespace System;
using namespace Models;

namespace Servicios {
    public ref class Autenticacion {
    private:
        String^ mail;
        String^ password;
    public:
        Autenticacion(String^ mail, String^ password) {
            this->mail = mail;
            this->password = password;
        }

        bool autenticar(Usuario^ usuario) {
            if (usuario->Mail == this->mail && usuario->Password == this->password) {
                return true;
            }
            return false;
        }
    };
}
