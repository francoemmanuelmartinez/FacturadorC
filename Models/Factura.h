#pragma once
#include "DetalleFactura.h"

using namespace System;
using namespace System::Collections::Generic;

namespace Models {
    public ref class Factura {
    public:
        property int Id;
        property String^ NumeroFactura;
        property int IdCliente;
        property String^ NombreCliente;
        property int IdVendedor;
        property String^ NombreVendedor;
        property DateTime FechaEmision;
        property int Subtotal;
        property int DescuentoPorcentaje;
        property int ValorDescontado;
        property int TotalCompra;
        property List<DetalleFactura^>^ Detalles;
    };
}
