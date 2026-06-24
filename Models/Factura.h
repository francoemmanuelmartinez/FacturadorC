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
        property String^ ApellidoCliente;
        property String^ DniCliente;
        property String^ DireccionCliente;
        property int IdVendedor;
        property String^ NombreVendedor;
        property String^ ApellidoVendedor;
        property DateTime FechaEmision;
        property double Subtotal;
        property int DescuentoPorcentaje;
        property double ValorDescontado;
        property double TotalCompra;
        property List<DetalleFactura^>^ Detalles;
    };
}
