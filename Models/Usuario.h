#pragma once

using namespace System;

namespace Models {
    public ref class Usuario {
    public:
        property String^ Id;
        property String^ Nombre;
        property String^ Apellido;
        property String^ Dni;
        property String^ Telefono;
        property String^ Direccion;
        property String^ Mail;
        property String^ Rol;
        property String^ Password;
        property int Habilitado;
    };
}
