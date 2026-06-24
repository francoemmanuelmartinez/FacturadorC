#pragma once

using namespace System;

namespace Models {
    public ref class Producto {
    public:
        property int Id;
        property int Habilitado;
        property String^ Descripcion;
        property double Precio;
        property int Stock;
        property int IdProveedor;
        property String^ NombreProveedor;
    };
}
