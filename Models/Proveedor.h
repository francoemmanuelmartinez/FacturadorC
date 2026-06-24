#pragma once

using namespace System;

namespace Models {
    public ref class Proveedor {
    public:
        property int Id;
        property String^ Nombre;
        property String^ Direccion;
        property String^ Telefono;
        property String^ Mail;
        property int Habilitado;
    };
}
