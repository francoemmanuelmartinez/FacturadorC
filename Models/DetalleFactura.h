#pragma once
#include "Producto.h"

using namespace System;

namespace Models {
    public ref class DetalleFactura {
    public:
        property Producto^ Producto;
        property int Cantidad;
        property double PrecioUnitario;
        property int Descuento;
        property double Subtotal;
    };
}
