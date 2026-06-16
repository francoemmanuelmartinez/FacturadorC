#pragma once

using namespace System;

namespace Models {
    public ref class Cliente {
    public:
        property int Id;
        property String^ Nombre;
        property String^ Apellido;
        property String^ Dni;
        property String^ Telefono;
        property String^ Direccion;
        property String^ Mail;
        property int Habilitado;
    };
}
