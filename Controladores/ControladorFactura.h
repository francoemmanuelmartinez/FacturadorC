#pragma once
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaFactura.h"
#include "..\Vistas\VistaDetallesFactura.h"
#include "..\Vistas\VistaClienteABM.h"

namespace Controladores { ref class ControladorClienteABM; }

using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorFactura {
    private:
        Conexion^ c = gcnew Conexion();
        Usuario^ usuario;
        VentanaPrincipal^ ventanaPrincipal;
        int idCliente;
        String^ nombreCliente;
        String^ apellidoCliente;
        VistaFactura^ vistaFactura;

        void verDetalleButton_Click(Object^ sender, EventArgs^ e);
        void volverButtonDetalle_Click(Object^ sender, EventArgs^ e);
        void volverButton_Click(Object^ sender, EventArgs^ e);

    public:
        ControladorFactura() {}

        ControladorFactura(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal, int idCliente, String^ nombreCliente, String^ apellidoCliente) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            this->idCliente = idCliente;
            this->nombreCliente = nombreCliente;
            this->apellidoCliente = apellidoCliente;

            this->vistaFactura = gcnew VistaFactura();
            this->vistaFactura->labelTitulo->Text = L"Facturas de: " + nombreCliente + L" " + apellidoCliente;
            ventanaPrincipal->setVista(this->vistaFactura->panelFactura);

            cargarFacturas(this->vistaFactura->tableFacturas, idCliente);

            this->vistaFactura->verDetalleButton->Click += gcnew EventHandler(this, &ControladorFactura::verDetalleButton_Click);
            this->vistaFactura->volverButton->Click += gcnew EventHandler(this, &ControladorFactura::volverButton_Click);
        }

        void cargarFacturas(DataGridView^ tabla, int idCliente) {
            tabla->Columns->Clear();
            tabla->Columns->Add(L"id", L"Nro");
            tabla->Columns->Add(L"numero", L"Factura");
            tabla->Columns->Add(L"fecha", L"Fecha");
            tabla->Columns->Add(L"total", L"Total ($)");
            tabla->Columns->Add(L"vendedor", L"Vendedor");
            tabla->Columns[0]->Visible = false;

            tabla->Rows->Clear();
            auto facturas = obtenerFacturasPorCliente(idCliente);
            for each (auto f in facturas) {
                tabla->Rows->Add(f[0], f[1], f[2], f[3], f[4]);
            }
        }

        List<array<Object^>^>^ obtenerFacturasPorCliente(int idCliente) {
            auto facturas = gcnew List<array<Object^>^>();
            c->conectar();
            String^ sql = "SELECT id, numero_factura, fecha_emision, total_compra, nombre_vendedor, apellido_vendedor FROM facturas WHERE id_cliente = ?id ORDER BY fecha_emision DESC, id DESC";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", idCliente);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) {
                facturas->Add(gcnew array<Object^> {
                    Convert::ToInt32(rs["id"]),
                    rs["numero_factura"]->ToString(),
                    rs["fecha_emision"]->ToString(),
                    Convert::ToDouble(rs["total_compra"]),
                    rs["nombre_vendedor"]->ToString() + L" " + rs["apellido_vendedor"]->ToString()
                });
            }
            rs->Close();
            return facturas;
        }

        void cargarFacturaCompleta(VistaDetallesFactura^ vista, int idFactura) {
            c->conectar();
            String^ sql = "SELECT f.id_cliente, f.id_vendedor, f.numero_factura, f.fecha_emision, f.nombre_cliente, f.apellido_cliente, f.nombre_vendedor, f.apellido_vendedor, f.subtotal, f.descuento_porcentaje, f.valor_descontado, f.total_compra, c.dni, c.direccion FROM facturas f JOIN clientes c ON f.id_cliente = c.id WHERE f.id = ?id";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", idFactura);
            auto rs = cmd->ExecuteReader();
            if (rs->Read()) {
                vista->textFieldNumeroFactura->Text = rs["numero_factura"]->ToString();
                vista->textFieldFecha->Text = rs["fecha_emision"]->ToString();
                vista->textFieldNombreCliente->Text = rs["nombre_cliente"]->ToString();
                vista->textFieldApellidoCliente->Text = rs["apellido_cliente"]->ToString();
                vista->textFieldNombreVendedor->Text = rs["nombre_vendedor"]->ToString();
                vista->textFieldApellidoVendedor->Text = rs["apellido_vendedor"]->ToString();
                vista->textFieldSubtotal->Text = L"$ " + Convert::ToDouble(rs["subtotal"]).ToString(L"F2");
                vista->textFieldPorcentajeDescuento->Text = Convert::ToInt32(rs["descuento_porcentaje"]).ToString() + L"%";
                vista->textFieldDescontado->Text = L"$ " + Convert::ToDouble(rs["valor_descontado"]).ToString(L"F2");
                vista->textFieldTotal->Text = L"$ " + Convert::ToDouble(rs["total_compra"]).ToString(L"F2");
                vista->textFieldDNICliente->Text = rs["dni"]->ToString();
                vista->textFieldDireccionCliente->Text = rs["direccion"]->ToString();
                vista->textFieldIDCliente->Text = rs["id_cliente"]->ToString();
                vista->textFieldIDVendedor->Text = rs["id_vendedor"]->ToString();
            }
            rs->Close();
        }

        void cargarDetalles(DataGridView^ tabla, int idFactura) {
            tabla->Columns->Clear();
            tabla->Columns->Add(L"ID", L"ID");
            tabla->Columns->Add(L"Producto", L"Producto");
            tabla->Columns->Add(L"Cantidad", L"Cantidad");
            tabla->Columns->Add(L"P/U", L"P/U");
            tabla->Columns->Add(L"Descuento", L"Descuento %");
            tabla->Columns->Add(L"Subtotal", L"Subtotal");

            tabla->Rows->Clear();
            c->conectar();
            String^ sql = "SELECT p.id, df.cantidad, df.precio_unitario, df.descuento, df.subtotal, p.descripcion FROM detalles_de_facturas df JOIN productos p ON df.id_producto = p.id WHERE df.id_factura = ?id";
            auto cmd = gcnew MySqlCommand(sql, c->con);
            cmd->Parameters->AddWithValue("?id", idFactura);
            auto rs = cmd->ExecuteReader();
            while (rs->Read()) {
                tabla->Rows->Add(
                    Convert::ToInt32(rs["id"]),
                    rs["descripcion"]->ToString(),
                    Convert::ToInt32(rs["cantidad"]),
                    Convert::ToDouble(rs["precio_unitario"]),
                    Convert::ToInt32(rs["descuento"]),
                    Convert::ToDouble(rs["subtotal"])
                );
            }
            rs->Close();
        }
    };
}
