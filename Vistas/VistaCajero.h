#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

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
            panelCajero = gcnew Panel();
            panelCajero->Size = System::Drawing::Size(800, 600);

            // Cajero info
            auto lblCajero = gcnew Label();
            lblCajero->Text = L"Cajero:";
            lblCajero->Location = Point(10, 10);
            lblCajero->Size = System::Drawing::Size(50, 20);
            panelCajero->Controls->Add(lblCajero);

            textFieldNombreCajero = gcnew TextBox();
            textFieldNombreCajero->Location = Point(60, 10);
            textFieldNombreCajero->Size = System::Drawing::Size(140, 20);
            textFieldNombreCajero->ReadOnly = true;
            panelCajero->Controls->Add(textFieldNombreCajero);

            textFieldApellidoCajero = gcnew TextBox();
            textFieldApellidoCajero->Location = Point(205, 10);
            textFieldApellidoCajero->Size = System::Drawing::Size(140, 20);
            textFieldApellidoCajero->ReadOnly = true;
            panelCajero->Controls->Add(textFieldApellidoCajero);

            auto lblIDCajero = gcnew Label();
            lblIDCajero->Text = L"ID:";
            lblIDCajero->Location = Point(350, 10);
            lblIDCajero->Size = System::Drawing::Size(30, 20);
            panelCajero->Controls->Add(lblIDCajero);

            textFieldIDCajero = gcnew TextBox();
            textFieldIDCajero->Location = Point(380, 10);
            textFieldIDCajero->Size = System::Drawing::Size(90, 20);
            textFieldIDCajero->ReadOnly = true;
            panelCajero->Controls->Add(textFieldIDCajero);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(690, 8);
            volverButton->Size = System::Drawing::Size(80, 25);
            panelCajero->Controls->Add(volverButton);

            // --- Client Section ---
            auto groupCliente = gcnew GroupBox();
            groupCliente->Text = L"Cliente";
            groupCliente->Location = Point(10, 40);
            groupCliente->Size = System::Drawing::Size(370, 180);
            panelCajero->Controls->Add(groupCliente);

            auto lblBuscarCliente = gcnew Label();
            lblBuscarCliente->Text = L"Buscar DNI:";
            lblBuscarCliente->Location = Point(10, 20);
            lblBuscarCliente->Size = System::Drawing::Size(70, 20);
            groupCliente->Controls->Add(lblBuscarCliente);

            textFieldBuscarCliente = gcnew TextBox();
            textFieldBuscarCliente->Location = Point(85, 20);
            textFieldBuscarCliente->Size = System::Drawing::Size(100, 20);
            groupCliente->Controls->Add(textFieldBuscarCliente);

            buscarClienteButton = gcnew Button();
            buscarClienteButton->Text = L"Buscar";
            buscarClienteButton->Location = Point(190, 18);
            buscarClienteButton->Size = System::Drawing::Size(70, 23);
            groupCliente->Controls->Add(buscarClienteButton);

            nuevoClienteButton = gcnew Button();
            nuevoClienteButton->Text = L"Nuevo";
            nuevoClienteButton->Location = Point(265, 18);
            nuevoClienteButton->Size = System::Drawing::Size(70, 23);
            groupCliente->Controls->Add(nuevoClienteButton);

            array<String^>^ clLbls = { L"ID:", L"Nombre:", L"Apellido:", L"DNI:", L"Direccion:", L"Telefono:", L"Mail:" };
            array<TextBox^>^ clTbs = gcnew array<TextBox^>(7);
            int clY = 50;
            for (int i = 0; i < 3; i++) {
                auto lbl = gcnew Label();
                lbl->Text = clLbls[i];
                lbl->Location = Point(10, clY);
                lbl->Size = System::Drawing::Size(60, 20);
                groupCliente->Controls->Add(lbl);

                clTbs[i] = gcnew TextBox();
                clTbs[i]->Location = Point(70, clY);
                clTbs[i]->Size = System::Drawing::Size(100, 20);
                groupCliente->Controls->Add(clTbs[i]);

                auto lbl2 = gcnew Label();
                lbl2->Text = clLbls[i + 3];
                lbl2->Location = Point(175, clY);
                lbl2->Size = System::Drawing::Size(60, 20);
                groupCliente->Controls->Add(lbl2);

                clTbs[i + 3] = gcnew TextBox();
                clTbs[i + 3]->Location = Point(235, clY);
                clTbs[i + 3]->Size = System::Drawing::Size(120, 20);
                groupCliente->Controls->Add(clTbs[i + 3]);
                clY += 25;
            }

            auto lblMail = gcnew Label();
            lblMail->Text = L"Mail:";
            lblMail->Location = Point(10, clY);
            lblMail->Size = System::Drawing::Size(60, 20);
            groupCliente->Controls->Add(lblMail);

            clTbs[6] = gcnew TextBox();
            clTbs[6]->Location = Point(70, clY);
            clTbs[6]->Size = System::Drawing::Size(200, 20);
            groupCliente->Controls->Add(clTbs[6]);

            textFieldIDCliente = clTbs[0];
            textFieldNombreCliente = clTbs[1];
            textFieldApellidoCliente = clTbs[2];
            textFieldDNICliente = clTbs[3];
            textFieldDomicilioCliente = clTbs[4];
            textFieldTelefonoCliente = clTbs[5];
            textFieldMailCliente = clTbs[6];

            modificarClienteButton = gcnew Button();
            modificarClienteButton->Text = L"Modificar Cliente";
            modificarClienteButton->Location = Point(10, clY + 25);
            modificarClienteButton->Size = System::Drawing::Size(120, 23);
            groupCliente->Controls->Add(modificarClienteButton);

            // --- Product Section ---
            auto groupProducto = gcnew GroupBox();
            groupProducto->Text = L"Producto";
            groupProducto->Location = Point(390, 40);
            groupProducto->Size = System::Drawing::Size(380, 180);
            panelCajero->Controls->Add(groupProducto);

            auto lblBuscarProd = gcnew Label();
            lblBuscarProd->Text = L"Buscar:";
            lblBuscarProd->Location = Point(10, 20);
            lblBuscarProd->Size = System::Drawing::Size(50, 20);
            groupProducto->Controls->Add(lblBuscarProd);

            textFieldBuscarProducto = gcnew TextBox();
            textFieldBuscarProducto->Location = Point(60, 20);
            textFieldBuscarProducto->Size = System::Drawing::Size(100, 20);
            groupProducto->Controls->Add(textFieldBuscarProducto);

            buscarProductoButton = gcnew Button();
            buscarProductoButton->Text = L"Buscar";
            buscarProductoButton->Location = Point(165, 18);
            buscarProductoButton->Size = System::Drawing::Size(70, 23);
            groupProducto->Controls->Add(buscarProductoButton);

            nuevoProductoButton = gcnew Button();
            nuevoProductoButton->Text = L"Nuevo";
            nuevoProductoButton->Location = Point(240, 18);
            nuevoProductoButton->Size = System::Drawing::Size(70, 23);
            groupProducto->Controls->Add(nuevoProductoButton);

            array<String^>^ prLbls = { L"ID:", L"Descripcion:", L"Precio:", L"Stock:" };
            array<TextBox^>^ prTbs = gcnew array<TextBox^>(4);
            int prY = 50;
            for (int i = 0; i < 4; i++) {
                auto lbl = gcnew Label();
                lbl->Text = prLbls[i];
                lbl->Location = Point(10, prY);
                lbl->Size = System::Drawing::Size(70, 20);
                groupProducto->Controls->Add(lbl);

                prTbs[i] = gcnew TextBox();
                prTbs[i]->Location = Point(85, prY);
                prTbs[i]->Size = System::Drawing::Size(100, 20);
                groupProducto->Controls->Add(prTbs[i]);
                prY += 25;
            }

            textFieldIDProducto = prTbs[0];
            textFieldDescripcionProducto = prTbs[1];
            textFieldPrecioProducto = prTbs[2];
            textFieldStock = prTbs[3];

            auto lblCant = gcnew Label();
            lblCant->Text = L"Cantidad:";
            lblCant->Location = Point(200, 50);
            lblCant->Size = System::Drawing::Size(60, 20);
            groupProducto->Controls->Add(lblCant);

            textFieldCantidadProducto = gcnew TextBox();
            textFieldCantidadProducto->Location = Point(260, 50);
            textFieldCantidadProducto->Size = System::Drawing::Size(80, 20);
            groupProducto->Controls->Add(textFieldCantidadProducto);

            auto lblDesc = gcnew Label();
            lblDesc->Text = L"Descuento%:";
            lblDesc->Location = Point(200, 75);
            lblDesc->Size = System::Drawing::Size(70, 20);
            groupProducto->Controls->Add(lblDesc);

            textFieldDescuentoProducto = gcnew TextBox();
            textFieldDescuentoProducto->Location = Point(270, 75);
            textFieldDescuentoProducto->Size = System::Drawing::Size(70, 20);
            groupProducto->Controls->Add(textFieldDescuentoProducto);

            modificarProductoButton = gcnew Button();
            modificarProductoButton->Text = L"Modificar Producto";
            modificarProductoButton->Location = Point(10, prY + 5);
            modificarProductoButton->Size = System::Drawing::Size(120, 23);
            groupProducto->Controls->Add(modificarProductoButton);

            agregarAlCarroButton = gcnew Button();
            agregarAlCarroButton->Text = L"Agregar al carrito >>";
            agregarAlCarroButton->Location = Point(210, prY + 5);
            agregarAlCarroButton->Size = System::Drawing::Size(140, 23);
            groupProducto->Controls->Add(agregarAlCarroButton);

            // --- Cart Table ---
            tableCarrito = gcnew DataGridView();
            tableCarrito->Location = Point(10, 220);
            tableCarrito->Size = System::Drawing::Size(760, 200);
            tableCarrito->AllowUserToAddRows = false;
            tableCarrito->AllowUserToDeleteRows = false;
            tableCarrito->ReadOnly = true;
            tableCarrito->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableCarrito->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelCajero->Controls->Add(tableCarrito);

            // --- Cart Action Buttons ---
            modificarArticuloButton = gcnew Button();
            modificarArticuloButton->Text = L"Modificar Articulo";
            modificarArticuloButton->Location = Point(10, 430);
            modificarArticuloButton->Size = System::Drawing::Size(110, 25);
            panelCajero->Controls->Add(modificarArticuloButton);

            eliminarArticuloButton = gcnew Button();
            eliminarArticuloButton->Text = L"Eliminar Articulo";
            eliminarArticuloButton->Location = Point(125, 430);
            eliminarArticuloButton->Size = System::Drawing::Size(110, 25);
            panelCajero->Controls->Add(eliminarArticuloButton);

            // --- Totals ---
            auto lblSubtotal = gcnew Label();
            lblSubtotal->Text = L"Subtotal:";
            lblSubtotal->Location = Point(10, 470);
            lblSubtotal->Size = System::Drawing::Size(60, 20);
            panelCajero->Controls->Add(lblSubtotal);

            textFieldSubtotal = gcnew TextBox();
            textFieldSubtotal->Location = Point(70, 470);
            textFieldSubtotal->Size = System::Drawing::Size(100, 20);
            textFieldSubtotal->ReadOnly = true;
            panelCajero->Controls->Add(textFieldSubtotal);

            auto lblDescGlobal = gcnew Label();
            lblDescGlobal->Text = L"Descuento %:";
            lblDescGlobal->Location = Point(180, 470);
            lblDescGlobal->Size = System::Drawing::Size(80, 20);
            panelCajero->Controls->Add(lblDescGlobal);

            textFieldDescuento = gcnew TextBox();
            textFieldDescuento->Location = Point(260, 470);
            textFieldDescuento->Size = System::Drawing::Size(60, 20);
            panelCajero->Controls->Add(textFieldDescuento);

            auto lblDescontado = gcnew Label();
            lblDescontado->Text = L"Descontado:";
            lblDescontado->Location = Point(330, 470);
            lblDescontado->Size = System::Drawing::Size(70, 20);
            panelCajero->Controls->Add(lblDescontado);

            textFieldValorDescontado = gcnew TextBox();
            textFieldValorDescontado->Location = Point(400, 470);
            textFieldValorDescontado->Size = System::Drawing::Size(70, 20);
            textFieldValorDescontado->ReadOnly = true;
            panelCajero->Controls->Add(textFieldValorDescontado);

            auto lblTotal = gcnew Label();
            lblTotal->Text = L"Total:";
            lblTotal->Location = Point(480, 470);
            lblTotal->Size = System::Drawing::Size(50, 20);
            panelCajero->Controls->Add(lblTotal);

            textFieldTotal = gcnew TextBox();
            textFieldTotal->Location = Point(530, 470);
            textFieldTotal->Size = System::Drawing::Size(100, 20);
            textFieldTotal->ReadOnly = true;
            panelCajero->Controls->Add(textFieldTotal);

            calcularTotalButton = gcnew Button();
            calcularTotalButton->Text = L"Calcular Total";
            calcularTotalButton->Location = Point(640, 468);
            calcularTotalButton->Size = System::Drawing::Size(100, 25);
            panelCajero->Controls->Add(calcularTotalButton);

            // --- Final Action Buttons ---
            finalizarCompraButton = gcnew Button();
            finalizarCompraButton->Text = L"Finalizar Compra";
            finalizarCompraButton->Location = Point(10, 510);
            finalizarCompraButton->Size = System::Drawing::Size(130, 35);
            finalizarCompraButton->BackColor = Color::LightGreen;
            panelCajero->Controls->Add(finalizarCompraButton);

            cancelarCompraButton = gcnew Button();
            cancelarCompraButton->Text = L"Cancelar Compra";
            cancelarCompraButton->Location = Point(150, 510);
            cancelarCompraButton->Size = System::Drawing::Size(130, 35);
            cancelarCompraButton->BackColor = Color::LightCoral;
            panelCajero->Controls->Add(cancelarCompraButton);
        }
    };
}
