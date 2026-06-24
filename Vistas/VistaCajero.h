#pragma once
#include "..\Filtros\FiltroPrecio.h"
#include "..\Filtros\FiltroNumerico.h"
#include "..\Filtros\FiltroAlfanumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

namespace Vistas {
    public ref class VistaCajero {
    public:
        Panel^ panelCajero;
        DataGridView^ tableCarrito;
        Label^ labelNombreCajero;
        TextBox^ textFieldNombreCajero;
        TextBox^ textFieldApellidoCajero;
        TextBox^ textFieldIDCajero;
        TextBox^ textFieldNombreCliente;
        TextBox^ textFieldApellidoCliente;
        TextBox^ textFieldDNICliente;
        TextBox^ textFieldDomicilioCliente;
        TextBox^ textFieldTelefonoCliente;
        TextBox^ textFieldMailCliente;
        TextBox^ textFieldBuscarCliente;
        TextBox^ textFieldIDCliente;
        Button^ buscarClienteButton;
        Button^ modificarClienteButton;
        Button^ nuevoClienteButton;
        TextBox^ textFieldBuscarProducto;
        TextBox^ textFieldIDProducto;
        TextBox^ textFieldDescripcionProducto;
        TextBox^ textFieldPrecioProducto;
        TextBox^ textFieldCantidadProducto;
        TextBox^ textFieldDescuentoProducto;
        TextBox^ textFieldStock;
        TextBox^ textFieldProveedorProducto;
        TextBox^ textFieldSubtotal;
        TextBox^ textFieldDescuento;
        TextBox^ textFieldTotal;
        TextBox^ textFieldValorDescontado;
        Button^ buscarProductoButton;
        Button^ modificarProductoButton;
        Button^ nuevoProductoButton;
        Button^ agregarAlCarroButton;
        Button^ modificarArticuloButton;
        Button^ eliminarArticuloButton;
        Button^ calcularTotalButton;
        Button^ finalizarCompraButton;
        Button^ cancelarCompraButton;
        Button^ volverButton;

        VistaCajero() {
            auto azul = Color::LightSkyBlue;

            panelCajero = gcnew Panel();
            panelCajero->Size = System::Drawing::Size(800, 630);

            // ========= Header Row =========
            auto lblCajero = gcnew Label();
            lblCajero->Text = L"Cajero:";
            lblCajero->Location = Point(10, 8);
            lblCajero->Size = System::Drawing::Size(55, 22);
            lblCajero->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblCajero);

            textFieldNombreCajero = gcnew TextBox();
            textFieldNombreCajero->ReadOnly = true;
            textFieldNombreCajero->Location = Point(68, 8);
            textFieldNombreCajero->Size = System::Drawing::Size(140, 22);
            panelCajero->Controls->Add(textFieldNombreCajero);

            auto lblApellido = gcnew Label();
            lblApellido->Text = L"Apellido:";
            lblApellido->Location = Point(212, 8);
            lblApellido->Size = System::Drawing::Size(60, 22);
            lblApellido->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblApellido);

            textFieldApellidoCajero = gcnew TextBox();
            textFieldApellidoCajero->ReadOnly = true;
            textFieldApellidoCajero->Location = Point(275, 8);
            textFieldApellidoCajero->Size = System::Drawing::Size(140, 22);
            panelCajero->Controls->Add(textFieldApellidoCajero);

            auto lblIDCajero = gcnew Label();
            lblIDCajero->Text = L"ID:";
            lblIDCajero->Location = Point(420, 8);
            lblIDCajero->Size = System::Drawing::Size(25, 22);
            lblIDCajero->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblIDCajero);

            textFieldIDCajero = gcnew TextBox();
            textFieldIDCajero->ReadOnly = true;
            textFieldIDCajero->Location = Point(448, 8);
            textFieldIDCajero->Size = System::Drawing::Size(250, 22);
            panelCajero->Controls->Add(textFieldIDCajero);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(710, 6);
            volverButton->Size = System::Drawing::Size(80, 25);
            volverButton->BackColor = Color::Gainsboro;
            panelCajero->Controls->Add(volverButton);

            // ========= Client GroupBox =========
            auto groupCliente = gcnew GroupBox();
            groupCliente->Text = L"CLIENTE";
            groupCliente->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            groupCliente->Location = Point(10, 40);
            groupCliente->Size = System::Drawing::Size(385, 240);
            panelCajero->Controls->Add(groupCliente);

            auto lblBuscarCliente = gcnew Label();
            lblBuscarCliente->Text = L"DNI Cliente:";
            lblBuscarCliente->Location = Point(10, 22);
            lblBuscarCliente->Size = System::Drawing::Size(72, 18);
            lblBuscarCliente->TextAlign = ContentAlignment::MiddleLeft;
            groupCliente->Controls->Add(lblBuscarCliente);

            textFieldBuscarCliente = gcnew TextBox();
            textFieldBuscarCliente->Location = Point(84, 22);
            textFieldBuscarCliente->Size = System::Drawing::Size(215, 18);
            groupCliente->Controls->Add(textFieldBuscarCliente);

            buscarClienteButton = gcnew Button();
            buscarClienteButton->Text = L"Buscar";
            buscarClienteButton->Location = Point(303, 20);
            buscarClienteButton->Size = System::Drawing::Size(72, 22);
            buscarClienteButton->BackColor = azul;
            groupCliente->Controls->Add(buscarClienteButton);

            // Client fields (7 rows)
            array<String^>^ clLbls = { L"ID:", L"Nombre:", L"Apellido:", L"DNI:", L"Domicilio:", L"Telefono:", L"Mail:" };
            array<TextBox^>^ clTbs = gcnew array<TextBox^>(7);
            int clY = 48;
            for (int r = 0; r < 7; r++) {
                auto lbl = gcnew Label();
                lbl->Text = clLbls[r];
                lbl->Location = Point(12, clY);
                lbl->Size = System::Drawing::Size(65, 16);
                lbl->TextAlign = ContentAlignment::MiddleLeft;
                groupCliente->Controls->Add(lbl);

                clTbs[r] = gcnew TextBox();
                clTbs[r]->ReadOnly = true;
                clTbs[r]->Location = Point(80, clY);
                clTbs[r]->Size = System::Drawing::Size(295, 16);
                groupCliente->Controls->Add(clTbs[r]);

                clY += 22;
            }
            textFieldIDCliente = clTbs[0];
            textFieldNombreCliente = clTbs[1];
            textFieldApellidoCliente = clTbs[2];
            textFieldDNICliente = clTbs[3];
            textFieldDomicilioCliente = clTbs[4];
            textFieldTelefonoCliente = clTbs[5];
            textFieldMailCliente = clTbs[6];

            modificarClienteButton = gcnew Button();
            modificarClienteButton->Text = L"Modificar";
            modificarClienteButton->Location = Point(10, 210);
            modificarClienteButton->Size = System::Drawing::Size(180, 22);
            modificarClienteButton->BackColor = azul;
            groupCliente->Controls->Add(modificarClienteButton);

            nuevoClienteButton = gcnew Button();
            nuevoClienteButton->Text = L"Nuevo";
            nuevoClienteButton->Location = Point(195, 210);
            nuevoClienteButton->Size = System::Drawing::Size(180, 22);
            nuevoClienteButton->BackColor = azul;
            groupCliente->Controls->Add(nuevoClienteButton);

            // ========= Product GroupBox =========
            auto groupProducto = gcnew GroupBox();
            groupProducto->Text = L"PRODUCTO";
            groupProducto->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            groupProducto->Location = Point(398, 40);
            groupProducto->Size = System::Drawing::Size(385, 240);
            panelCajero->Controls->Add(groupProducto);

            auto lblBuscarProd = gcnew Label();
            lblBuscarProd->Text = L"ID o Descripcion:";
            lblBuscarProd->Location = Point(10, 22);
            lblBuscarProd->Size = System::Drawing::Size(120, 18);
            lblBuscarProd->TextAlign = ContentAlignment::MiddleLeft;
            groupProducto->Controls->Add(lblBuscarProd);

            textFieldBuscarProducto = gcnew TextBox();
            textFieldBuscarProducto->Location = Point(134, 22);
            textFieldBuscarProducto->Size = System::Drawing::Size(165, 18);
            groupProducto->Controls->Add(textFieldBuscarProducto);

            buscarProductoButton = gcnew Button();
            buscarProductoButton->Text = L"Buscar";
            buscarProductoButton->Location = Point(303, 20);
            buscarProductoButton->Size = System::Drawing::Size(72, 22);
            buscarProductoButton->BackColor = azul;
            groupProducto->Controls->Add(buscarProductoButton);

            // Product fields (7 rows)
            array<String^>^ prLbls = { L"ID:", L"Descripcion:", L"Precio:", L"Stock:", L"Proveedor:", L"Cantidad:", L"Descuento:" };
            array<TextBox^>^ prTbs = gcnew array<TextBox^>(7);
            int prY = 48;
            for (int r = 0; r < 7; r++) {
                auto lbl = gcnew Label();
                lbl->Text = prLbls[r];
                lbl->Location = Point(12, prY);
                lbl->Size = System::Drawing::Size(85, 16);
                lbl->TextAlign = ContentAlignment::MiddleLeft;
                groupProducto->Controls->Add(lbl);

                prTbs[r] = gcnew TextBox();
                if (r < 5) prTbs[r]->ReadOnly = true;
                prTbs[r]->Location = Point(100, prY);
                prTbs[r]->Size = System::Drawing::Size(275, 16);
                groupProducto->Controls->Add(prTbs[r]);

                prY += 22;
            }
            textFieldIDProducto = prTbs[0];
            textFieldDescripcionProducto = prTbs[1];
            textFieldPrecioProducto = prTbs[2];
            FiltroPrecio::Aplicar(textFieldPrecioProducto);
            textFieldStock = prTbs[3];
            textFieldProveedorProducto = prTbs[4];
            textFieldCantidadProducto = prTbs[5];
            textFieldDescuentoProducto = prTbs[6];

            modificarProductoButton = gcnew Button();
            modificarProductoButton->Text = L"Modificar";
            modificarProductoButton->Location = Point(10, 210);
            modificarProductoButton->Size = System::Drawing::Size(115, 22);
            modificarProductoButton->BackColor = azul;
            groupProducto->Controls->Add(modificarProductoButton);

            agregarAlCarroButton = gcnew Button();
            agregarAlCarroButton->Text = L"Agregar al Carro";
            agregarAlCarroButton->Location = Point(135, 210);
            agregarAlCarroButton->Size = System::Drawing::Size(115, 22);
            agregarAlCarroButton->BackColor = Color::FromArgb(255, 200, 100);
            groupProducto->Controls->Add(agregarAlCarroButton);

            nuevoProductoButton = gcnew Button();
            nuevoProductoButton->Text = L"Nuevo";
            nuevoProductoButton->Location = Point(260, 210);
            nuevoProductoButton->Size = System::Drawing::Size(115, 22);
            nuevoProductoButton->BackColor = azul;
            groupProducto->Controls->Add(nuevoProductoButton);

            // Filters
            FiltroNumerico::Aplicar(textFieldBuscarCliente);
            FiltroAlfanumerico::Aplicar(textFieldBuscarProducto);
            FiltroNumerico::Aplicar(textFieldCantidadProducto);
            FiltroNumerico::Aplicar(textFieldDescuentoProducto);

            // ========= Carrito DataGridView =========
            tableCarrito = gcnew DataGridView();
            tableCarrito->Location = Point(10, 290);
            tableCarrito->Size = System::Drawing::Size(760, 185);
            tableCarrito->AllowUserToAddRows = false;
            tableCarrito->AllowUserToDeleteRows = false;
            tableCarrito->ReadOnly = true;
            tableCarrito->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableCarrito->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelCajero->Controls->Add(tableCarrito);

            // ========= Carrito Action Buttons =========
            modificarArticuloButton = gcnew Button();
            modificarArticuloButton->Text = L"Modificar Articulo";
            modificarArticuloButton->Location = Point(10, 483);
            modificarArticuloButton->Size = System::Drawing::Size(180, 25);
            modificarArticuloButton->BackColor = azul;
            panelCajero->Controls->Add(modificarArticuloButton);

            eliminarArticuloButton = gcnew Button();
            eliminarArticuloButton->Text = L"Eliminar Articulo";
            eliminarArticuloButton->Location = Point(200, 483);
            eliminarArticuloButton->Size = System::Drawing::Size(180, 25);
            eliminarArticuloButton->BackColor = azul;
            panelCajero->Controls->Add(eliminarArticuloButton);

            calcularTotalButton = gcnew Button();
            calcularTotalButton->Text = L"Calcular Total";
            calcularTotalButton->Location = Point(600, 483);
            calcularTotalButton->Size = System::Drawing::Size(160, 25);
            calcularTotalButton->BackColor = Color::FromArgb(255, 200, 100);
            panelCajero->Controls->Add(calcularTotalButton);

            // ========= Totals Section =========
            auto lblSubtotal = gcnew Label();
            lblSubtotal->Text = L"Subtotal:";
            lblSubtotal->Location = Point(390, 517);
            lblSubtotal->Size = System::Drawing::Size(70, 22);
            lblSubtotal->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblSubtotal);

            textFieldSubtotal = gcnew TextBox();
            textFieldSubtotal->ReadOnly = true;
            textFieldSubtotal->Location = Point(464, 517);
            textFieldSubtotal->Size = System::Drawing::Size(100, 22);
            panelCajero->Controls->Add(textFieldSubtotal);

            auto lblDescGlobal = gcnew Label();
            lblDescGlobal->Text = L"Descuento %:";
            lblDescGlobal->Location = Point(570, 517);
            lblDescGlobal->Size = System::Drawing::Size(90, 22);
            lblDescGlobal->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblDescGlobal);

            textFieldDescuento = gcnew TextBox();
            textFieldDescuento->Location = Point(664, 517);
            textFieldDescuento->Size = System::Drawing::Size(100, 22);
            panelCajero->Controls->Add(textFieldDescuento);
            FiltroNumerico::Aplicar(textFieldDescuento);

            auto lblDescontado = gcnew Label();
            lblDescontado->Text = L"Descontado:";
            lblDescontado->Location = Point(390, 545);
            lblDescontado->Size = System::Drawing::Size(70, 22);
            lblDescontado->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblDescontado);

            textFieldValorDescontado = gcnew TextBox();
            textFieldValorDescontado->ReadOnly = true;
            textFieldValorDescontado->Location = Point(464, 545);
            textFieldValorDescontado->Size = System::Drawing::Size(100, 22);
            panelCajero->Controls->Add(textFieldValorDescontado);

            auto lblTotal = gcnew Label();
            lblTotal->Text = L"Total:";
            lblTotal->Font = gcnew System::Drawing::Font(lblTotal->Font, FontStyle::Bold);
            lblTotal->Location = Point(570, 545);
            lblTotal->Size = System::Drawing::Size(60, 22);
            lblTotal->TextAlign = ContentAlignment::MiddleLeft;
            panelCajero->Controls->Add(lblTotal);

            textFieldTotal = gcnew TextBox();
            textFieldTotal->ReadOnly = true;
            textFieldTotal->Font = gcnew System::Drawing::Font(textFieldTotal->Font, FontStyle::Bold);
            textFieldTotal->Location = Point(634, 545);
            textFieldTotal->Size = System::Drawing::Size(130, 22);
            panelCajero->Controls->Add(textFieldTotal);

            // ========= Bottom Buttons =========
            cancelarCompraButton = gcnew Button();
            cancelarCompraButton->Text = L"Cancelar Compra";
            cancelarCompraButton->Location = Point(15, 580);
            cancelarCompraButton->Size = System::Drawing::Size(240, 28);
            cancelarCompraButton->BackColor = Color::LightCoral;
            panelCajero->Controls->Add(cancelarCompraButton);

            finalizarCompraButton = gcnew Button();
            finalizarCompraButton->Text = L"Finalizar Compra";
            finalizarCompraButton->Location = Point(530, 580);
            finalizarCompraButton->Size = System::Drawing::Size(240, 28);
            finalizarCompraButton->BackColor = Color::LightGreen;
            panelCajero->Controls->Add(finalizarCompraButton);
        }
    };
}
