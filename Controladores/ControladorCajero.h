#pragma once
#include "..\Models\Usuario.h"
#include "..\Servicios\Conexion.h"
#include "..\Vistas\VentanaPrincipal.h"
#include "..\Vistas\VistaCajero.h"
#include "..\Vistas\VistaFormulario.h"
#include "..\Vistas\VistaClienteABM.h"

namespace Controladores {
    ref class ControladorAdmin;
    ref class ControladorLogin;
    ref class ControladorClienteABM;
    ref class ControladorDepositoABM;
    ref class ControladorProveedorABM;
}

using namespace Models;
using namespace Servicios;
using namespace Vistas;
using namespace MySql::Data::MySqlClient;

namespace Controladores {
    public ref class ControladorCajero {
    private:
        Conexion^ c = gcnew Conexion();
        Usuario^ usuario;
        VistaCajero^ vista;
        VentanaPrincipal^ ventanaPrincipal;

        // Navigation handlers — defined in ControladoresImpl.h
        void volverButton_Click(Object^ sender, EventArgs^ e);
        void buscarClienteButton_Click(Object^ sender, EventArgs^ e);
        void modificarClienteButton_Click(Object^ sender, EventArgs^ e);
        void nuevoClienteButton_Click(Object^ sender, EventArgs^ e);
        void buscarProductoButton_Click(Object^ sender, EventArgs^ e);
        void modificarProductoButton_Click(Object^ sender, EventArgs^ e);
        void nuevoProductoButton_Click(Object^ sender, EventArgs^ e);

        String^ generarNumeroFactura() {
            return L"FACT-" + DateTime::Now.ToString(L"yyyyMMdd-HHmmss");
        }

        void actualizarTotales(DataGridView^ tabla, TextBox^ txtSubtotal, TextBox^ txtDescuento, TextBox^ txtTotal, TextBox^ txtDescontado) {
            double subtotal = 0.0;
            for each (DataGridViewRow^ row in tabla->Rows) {
                if (row->Cells[5]->Value != nullptr) {
                    subtotal += Convert::ToDouble(row->Cells[5]->Value);
                }
            }
            txtSubtotal->Text = subtotal.ToString(L"F2");
            txtDescuento->Text = L"";
            txtTotal->Text = L"";
            txtDescontado->Text = L"";
        }

        void limpiarCamposProducto() {
            vista->textFieldIDProducto->Text = L"";
            vista->textFieldDescripcionProducto->Text = L"";
            vista->textFieldPrecioProducto->Text = L"";
            vista->textFieldStock->Text = L"";
            vista->textFieldProveedorProducto->Text = L"";
            vista->textFieldCantidadProducto->Text = L"";
            vista->textFieldDescuentoProducto->Text = L"";
        }

        void limpiarCamposCliente() {
            vista->textFieldIDCliente->Text = L"";
            vista->textFieldNombreCliente->Text = L"";
            vista->textFieldApellidoCliente->Text = L"";
            vista->textFieldDNICliente->Text = L"";
            vista->textFieldDomicilioCliente->Text = L"";
            vista->textFieldTelefonoCliente->Text = L"";
            vista->textFieldMailCliente->Text = L"";
        }

        void limpiarCarrito() {
            vista->tableCarrito->Rows->Clear();
            limpiarCamposCliente();
            limpiarCamposProducto();
            vista->textFieldSubtotal->Text = L"";
            vista->textFieldDescuento->Text = L"";
            vista->textFieldTotal->Text = L"";
            vista->textFieldValorDescontado->Text = L"";
            vista->textFieldBuscarCliente->Text = L"";
            vista->textFieldBuscarProducto->Text = L"";
        }

        // Inline event handlers (no gcnew of other controladores)
        void agregarAlCarroButton_Click(Object^ sender, EventArgs^ e) {
            String^ idStr = this->vista->textFieldIDProducto->Text->Trim();
            if (String::IsNullOrEmpty(idStr)) {
                MessageBox::Show(L"No hay producto seleccionado");
                return;
            }

            String^ descripcion = this->vista->textFieldDescripcionProducto->Text;
            double precio = Double::Parse(this->vista->textFieldPrecioProducto->Text);
            String^ cantidadStr = this->vista->textFieldCantidadProducto->Text->Trim();
            if (String::IsNullOrEmpty(cantidadStr)) {
                MessageBox::Show(L"Debe especificar la cantidad a agregar al carro");
                return;
            }
            int cantidad = Int32::Parse(cantidadStr);
            if (cantidad <= 0) {
                MessageBox::Show(L"La cantidad debe ser mayor a 0");
                return;
            }

            String^ descuentoStr = this->vista->textFieldDescuentoProducto->Text->Trim();
            int descuento = String::IsNullOrEmpty(descuentoStr) ? 0 : Int32::Parse(descuentoStr);
            double subtotal = precio * cantidad * (100 - descuento) / 100.0;

            this->vista->tableCarrito->Rows->Add(idStr, descripcion, precio, cantidad, descuento + L"%", subtotal);
            this->actualizarTotales(this->vista->tableCarrito, this->vista->textFieldSubtotal, this->vista->textFieldDescuento, this->vista->textFieldTotal, this->vista->textFieldValorDescontado);
            this->limpiarCamposProducto();
        }

        void modificarArticuloButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tableCarrito->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un articulo del carrito");
                return;
            }
            auto fila = this->vista->tableCarrito->SelectedRows[0];
            String^ cantidadActual = fila->Cells[3]->Value->ToString();
            String^ descuentoActual = fila->Cells[4]->Value->ToString()->Replace(L"%", L"");

            auto valores = VistaFormulario::mostrarDialogo(L"Modificar Articulo",
                gcnew VistaFormulario::Campo(L"Cantidad:", cantidadActual, L"Numerico", true),
                gcnew VistaFormulario::Campo(L"Descuento %:", descuentoActual, L"Numerico", true)
            );
            if (valores != nullptr) {
                try {
                    int nuevaCantidad = Int32::Parse(valores[L"Cantidad:"]);
                    int nuevoDescuento = Int32::Parse(valores[L"Descuento %:"]);
                    if (nuevaCantidad <= 0) {
                        MessageBox::Show(L"La cantidad debe ser mayor a 0");
                        return;
                    }
                    if (nuevoDescuento < 0 || nuevoDescuento > 100) {
                        MessageBox::Show(L"El descuento debe ser entre 0 y 100");
                        return;
                    }
                    double precio = Convert::ToDouble(fila->Cells[2]->Value);
                    double nuevoSubtotal = precio * nuevaCantidad * (100 - nuevoDescuento) / 100.0;
                    fila->Cells[3]->Value = nuevaCantidad;
                    fila->Cells[4]->Value = nuevoDescuento + L"%";
                    fila->Cells[5]->Value = nuevoSubtotal;
                    this->actualizarTotales(this->vista->tableCarrito, this->vista->textFieldSubtotal, this->vista->textFieldDescuento, this->vista->textFieldTotal, this->vista->textFieldValorDescontado);
                }
                catch (FormatException^) {
                    MessageBox::Show(L"Ingrese valores numericos validos");
                }
            }
        }

        void eliminarArticuloButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tableCarrito->SelectedRows->Count == 0) {
                MessageBox::Show(L"Seleccione un articulo del carrito");
                return;
            }
            auto confirm = MessageBox::Show(L"?Eliminar articulo del carrito?", L"Confirmar", MessageBoxButtons::YesNo);
            if (confirm == DialogResult::Yes) {
                this->vista->tableCarrito->Rows->Remove(this->vista->tableCarrito->SelectedRows[0]);
                this->actualizarTotales(this->vista->tableCarrito, this->vista->textFieldSubtotal, this->vista->textFieldDescuento, this->vista->textFieldTotal, this->vista->textFieldValorDescontado);
            }
        }

        void calcularTotalButton_Click(Object^ sender, EventArgs^ e) {
            String^ subtotalStr = this->vista->textFieldSubtotal->Text->Trim();
            if (String::IsNullOrEmpty(subtotalStr)) {
                MessageBox::Show(L"No hay articulos en el carrito");
                return;
            }
            double subtotal = Double::Parse(subtotalStr);
            String^ descuentoStr = this->vista->textFieldDescuento->Text->Trim();
            int descuento = String::IsNullOrEmpty(descuentoStr) ? 0 : Int32::Parse(descuentoStr);
            if (descuento < 0 || descuento > 100) {
                MessageBox::Show(L"El descuento debe ser entre 0 y 100");
                return;
            }
            double total = subtotal * (100 - descuento) / 100.0;
            double valorDescontado = subtotal - total;
            this->vista->textFieldTotal->Text = total.ToString(L"F2");
            this->vista->textFieldValorDescontado->Text = valorDescontado.ToString(L"F2");
        }

        void finalizarCompraButton_Click(Object^ sender, EventArgs^ e) {
            String^ idClienteStr = this->vista->textFieldIDCliente->Text->Trim();
            if (String::IsNullOrEmpty(idClienteStr)) {
                MessageBox::Show(L"Debe seleccionar un cliente");
                return;
            }
            if (this->vista->tableCarrito->Rows->Count == 0) {
                MessageBox::Show(L"El carrito esta vacio");
                return;
            }
            if (String::IsNullOrEmpty(this->vista->textFieldTotal->Text->Trim())) {
                MessageBox::Show(L"Debe calcular el total primero");
                return;
            }

            auto confirm = MessageBox::Show(L"?Confirmar finalizacion de la compra?", L"Confirmar", MessageBoxButtons::YesNo);
            if (confirm != DialogResult::Yes) return;

            int idCliente = Int32::Parse(idClienteStr);
            String^ nombreCliente = this->vista->textFieldNombreCliente->Text->Trim();
            String^ apellidoCliente = this->vista->textFieldApellidoCliente->Text->Trim();
            int idVendedor = Int32::Parse(this->usuario->Id);
            String^ nombreVendedor = this->vista->textFieldNombreCajero->Text->Trim();
            String^ apellidoVendedor = this->vista->textFieldApellidoCajero->Text->Trim();

            auto carrito = gcnew List<array<Object^>^>();
            for each (DataGridViewRow^ row in this->vista->tableCarrito->Rows) {
                if (row->Cells[0]->Value != nullptr) {
                    carrito->Add(gcnew array<Object^> {
                        row->Cells[0]->Value, row->Cells[1]->Value, row->Cells[2]->Value,
                        row->Cells[3]->Value, row->Cells[4]->Value, row->Cells[5]->Value
                    });
                }
            }

            double subtotalVal = Double::Parse(this->vista->textFieldSubtotal->Text->Trim());
            String^ descuentoStrVal = this->vista->textFieldDescuento->Text->Trim();
            int descuentoPorcentaje = String::IsNullOrEmpty(descuentoStrVal) ? 0 : Int32::Parse(descuentoStrVal);
            double totalVal = Double::Parse(this->vista->textFieldTotal->Text->Trim());
            double valorDescontadoVal = subtotalVal - totalVal;

            auto cc = gcnew ControladorCajero();
            if (cc->finalizarCompra(idCliente, nombreCliente, apellidoCliente, idVendedor, nombreVendedor, apellidoVendedor, carrito, subtotalVal, descuentoPorcentaje, valorDescontadoVal, totalVal)) {
                this->limpiarCarrito();
            }
        }

        void cancelarCompraButton_Click(Object^ sender, EventArgs^ e) {
            if (this->vista->tableCarrito->Rows->Count == 0) return;
            auto confirm = MessageBox::Show(L"?Cancelar la compra? Se perderan todos los datos del carrito", L"Confirmar", MessageBoxButtons::YesNo);
            if (confirm == DialogResult::Yes) {
                this->limpiarCarrito();
            }
        }

    public:
        ControladorCajero() {}

        ControladorCajero(Usuario^ usuario, VentanaPrincipal^ ventanaPrincipal) {
            this->usuario = usuario;
            this->ventanaPrincipal = ventanaPrincipal;
            this->vista = gcnew VistaCajero();
            ventanaPrincipal->setVista(vista->panelCajero);

            vista->textFieldNombreCajero->Text = usuario->Nombre;
            vista->textFieldApellidoCajero->Text = usuario->Apellido;
            vista->textFieldIDCajero->Text = usuario->Id;

            vista->tableCarrito->Columns->Add(L"ID", L"ID");
            vista->tableCarrito->Columns->Add(L"Descripcion", L"Descripcion");
            vista->tableCarrito->Columns->Add(L"Precio", L"Precio Unit.");
            vista->tableCarrito->Columns->Add(L"Cantidad", L"Cantidad");
            vista->tableCarrito->Columns->Add(L"Descuento", L"Descuento");
            vista->tableCarrito->Columns->Add(L"Subtotal", L"Subtotal");

            vista->volverButton->Click += gcnew EventHandler(this, &ControladorCajero::volverButton_Click);
            vista->buscarClienteButton->Click += gcnew EventHandler(this, &ControladorCajero::buscarClienteButton_Click);
            vista->modificarClienteButton->Click += gcnew EventHandler(this, &ControladorCajero::modificarClienteButton_Click);
            vista->nuevoClienteButton->Click += gcnew EventHandler(this, &ControladorCajero::nuevoClienteButton_Click);
            vista->buscarProductoButton->Click += gcnew EventHandler(this, &ControladorCajero::buscarProductoButton_Click);
            vista->modificarProductoButton->Click += gcnew EventHandler(this, &ControladorCajero::modificarProductoButton_Click);
            vista->nuevoProductoButton->Click += gcnew EventHandler(this, &ControladorCajero::nuevoProductoButton_Click);
            vista->agregarAlCarroButton->Click += gcnew EventHandler(this, &ControladorCajero::agregarAlCarroButton_Click);
            vista->modificarArticuloButton->Click += gcnew EventHandler(this, &ControladorCajero::modificarArticuloButton_Click);
            vista->eliminarArticuloButton->Click += gcnew EventHandler(this, &ControladorCajero::eliminarArticuloButton_Click);
            vista->calcularTotalButton->Click += gcnew EventHandler(this, &ControladorCajero::calcularTotalButton_Click);
            vista->finalizarCompraButton->Click += gcnew EventHandler(this, &ControladorCajero::finalizarCompraButton_Click);
            vista->cancelarCompraButton->Click += gcnew EventHandler(this, &ControladorCajero::cancelarCompraButton_Click);
        }

        String^ generarNumeroFacturaStatic() {
            return L"FACT-" + DateTime::Now.ToString(L"yyyyMMdd-HHmmss");
        }

        bool finalizarCompra(int idCliente, String^ nombreCliente, String^ apellidoCliente,
            int idVendedor, String^ nombreVendedor, String^ apellidoVendedor,
            List<array<Object^>^>^ carrito, double subtotal, int descuentoPorcentaje,
            double valorDescontado, double totalCompra) {
            try {
                c->conectar();
                auto transaction = c->con->BeginTransaction();

                String^ numeroFactura = generarNumeroFacturaStatic();
                String^ fechaEmision = DateTime::Now.ToString(L"yyyy-MM-dd");

                String^ sqlFactura = "INSERT INTO facturas(numero_factura, id_cliente, nombre_cliente, apellido_cliente, id_vendedor, nombre_vendedor, apellido_vendedor, fecha_emision, subtotal, descuento_porcentaje, valor_descontado, total_compra) VALUES(?num, ?idc, ?nomc, ?ape, ?idv, ?nomv, ?apev, ?fecha, ?sub, ?desc, ?val, ?total)";
                auto cmdFactura = gcnew MySqlCommand(sqlFactura, c->con, transaction);
                cmdFactura->Parameters->AddWithValue("?num", numeroFactura);
                cmdFactura->Parameters->AddWithValue("?idc", idCliente);
                cmdFactura->Parameters->AddWithValue("?nomc", nombreCliente);
                cmdFactura->Parameters->AddWithValue("?ape", apellidoCliente);
                cmdFactura->Parameters->AddWithValue("?idv", idVendedor);
                cmdFactura->Parameters->AddWithValue("?nomv", nombreVendedor);
                cmdFactura->Parameters->AddWithValue("?apev", apellidoVendedor);
                cmdFactura->Parameters->AddWithValue("?fecha", fechaEmision);
                cmdFactura->Parameters->AddWithValue("?sub", subtotal);
                cmdFactura->Parameters->AddWithValue("?desc", descuentoPorcentaje);
                cmdFactura->Parameters->AddWithValue("?val", valorDescontado);
                cmdFactura->Parameters->AddWithValue("?total", totalCompra);
                cmdFactura->ExecuteNonQuery();

                int idFactura = safe_cast<int>(cmdFactura->LastInsertedId);

                String^ sqlDetalle = "INSERT INTO detalles_de_facturas(id_factura, id_producto, cantidad, precio_unitario, descuento, subtotal) VALUES(?idf, ?idp, ?cant, ?pre, ?desc, ?sub)";
                auto cmdDetalle = gcnew MySqlCommand(sqlDetalle, c->con, transaction);

                String^ sqlStock = "UPDATE productos SET stock = stock - ?cant WHERE id = ?id AND stock >= ?cant";

                for each (array<Object^>^ fila in carrito) {
                    int idProducto = Int32::Parse(fila[0]->ToString());
                    int cantidad = safe_cast<int>(fila[3]);
                    double precioUnitario = Convert::ToDouble(fila[2]);
                    int descuento = 0;
                    if (fila[4]->ToString()->Contains(L"%")) {
                        descuento = Int32::Parse(fila[4]->ToString()->Replace(L"%", L""));
                    }
                    double subtotalDetalle = Convert::ToDouble(fila[5]);

                    cmdDetalle->Parameters->Clear();
                    cmdDetalle->Parameters->AddWithValue("?idf", idFactura);
                    cmdDetalle->Parameters->AddWithValue("?idp", idProducto);
                    cmdDetalle->Parameters->AddWithValue("?cant", cantidad);
                    cmdDetalle->Parameters->AddWithValue("?pre", precioUnitario);
                    cmdDetalle->Parameters->AddWithValue("?desc", descuento);
                    cmdDetalle->Parameters->AddWithValue("?sub", subtotalDetalle);
                    cmdDetalle->ExecuteNonQuery();

                    auto cmdStock = gcnew MySqlCommand(sqlStock, c->con, transaction);
                    cmdStock->Parameters->AddWithValue("?cant", cantidad);
                    cmdStock->Parameters->AddWithValue("?id", idProducto);
                    int affected = cmdStock->ExecuteNonQuery();
                    if (affected == 0) {
                        transaction->Rollback();
                        MessageBox::Show(L"Stock insuficiente para el producto ID: " + idProducto);
                        return false;
                    }
                }

                transaction->Commit();
                MessageBox::Show(L"Compra finalizada exitosamente. Factura Nro: " + numeroFactura);
                return true;
            }
            catch (Exception^ ex) {
                try {
                    c->con->Close();
                }
                catch (...) {}
                MessageBox::Show(L"Error al finalizar la compra: " + ex->Message);
                return false;
            }
        }
    };
}
