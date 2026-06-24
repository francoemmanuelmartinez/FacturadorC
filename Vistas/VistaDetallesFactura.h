#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaDetallesFactura {
    public:
        Panel^ panelDetallesFactura;
        Label^ labelTitulo;
        TextBox^ textFieldNumeroFactura;
        TextBox^ textFieldFecha;
        TextBox^ textFieldNombreCliente;
        TextBox^ textFieldApellidoCliente;
        TextBox^ textFieldDNICliente;
        TextBox^ textFieldDireccionCliente;
        TextBox^ textFieldNombreVendedor;
        TextBox^ textFieldApellidoVendedor;
        TextBox^ textFieldTotal;
        TextBox^ textFieldIDCliente;
        TextBox^ textFieldIDVendedor;
        TextBox^ textFieldDescontado;
        TextBox^ textFieldPorcentajeDescuento;
        TextBox^ textFieldSubtotal;
        DataGridView^ tableDetalles;
        Button^ volverButton;

        VistaDetallesFactura() {
            auto azul = Color::LightSkyBlue;

            panelDetallesFactura = gcnew Panel();
            panelDetallesFactura->Size = System::Drawing::Size(800, 600);

            // Volver button top-right
            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 10);
            volverButton->Size = System::Drawing::Size(100, 28);
            volverButton->BackColor = Color::Gainsboro;
            panelDetallesFactura->Controls->Add(volverButton);

            // FACTURA title centered
            labelTitulo = gcnew Label();
            labelTitulo->Text = L"FACTURA";
            labelTitulo->Font = gcnew System::Drawing::Font(L"Arial", 18, FontStyle::Bold);
            labelTitulo->Location = Point(200, 40);
            labelTitulo->Size = System::Drawing::Size(400, 35);
            labelTitulo->TextAlign = ContentAlignment::MiddleCenter;
            panelDetallesFactura->Controls->Add(labelTitulo);

            // N° Factura + Fecha row
            auto lblNroFactura = gcnew Label();
            lblNroFactura->Text = L"N" + (char)0xba + L" Factura:";
            lblNroFactura->Location = Point(50, 85);
            lblNroFactura->Size = System::Drawing::Size(90, 24);
            lblNroFactura->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblNroFactura);

            textFieldNumeroFactura = gcnew TextBox();
            textFieldNumeroFactura->ReadOnly = true;
            textFieldNumeroFactura->Location = Point(145, 85);
            textFieldNumeroFactura->Size = System::Drawing::Size(200, 24);
            panelDetallesFactura->Controls->Add(textFieldNumeroFactura);

            auto lblFecha = gcnew Label();
            lblFecha->Text = L"Fecha:";
            lblFecha->Location = Point(450, 85);
            lblFecha->Size = System::Drawing::Size(60, 24);
            lblFecha->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblFecha);

            textFieldFecha = gcnew TextBox();
            textFieldFecha->ReadOnly = true;
            textFieldFecha->Location = Point(515, 85);
            textFieldFecha->Size = System::Drawing::Size(200, 24);
            panelDetallesFactura->Controls->Add(textFieldFecha);

            // Cliente GroupBox
            auto groupCliente = gcnew GroupBox();
            groupCliente->Text = L"CLIENTE";
            groupCliente->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            groupCliente->Location = Point(10, 120);
            groupCliente->Size = System::Drawing::Size(370, 150);
            panelDetallesFactura->Controls->Add(groupCliente);

            array<String^>^ clLbls = { L"ID:", L"Nombre:", L"Apellido:", L"DNI:", L"Direccion:" };
            array<TextBox^>^ clTbs = gcnew array<TextBox^>(5);
            int clY = 20;
            for (int r = 0; r < 5; r++) {
                auto lbl = gcnew Label();
                lbl->Text = clLbls[r];
                lbl->Location = Point(10, clY);
                lbl->Size = System::Drawing::Size(65, 22);
                lbl->TextAlign = ContentAlignment::MiddleLeft;
                groupCliente->Controls->Add(lbl);

                clTbs[r] = gcnew TextBox();
                clTbs[r]->ReadOnly = true;
                clTbs[r]->Location = Point(80, clY);
                clTbs[r]->Size = System::Drawing::Size(275, 22);
                groupCliente->Controls->Add(clTbs[r]);

                clY += 26;
            }
            textFieldIDCliente = clTbs[0];
            textFieldNombreCliente = clTbs[1];
            textFieldApellidoCliente = clTbs[2];
            textFieldDNICliente = clTbs[3];
            textFieldDireccionCliente = clTbs[4];

            // Vendedor GroupBox
            auto groupVendedor = gcnew GroupBox();
            groupVendedor->Text = L"VENDEDOR";
            groupVendedor->Font = gcnew System::Drawing::Font(L"Arial", 9, FontStyle::Bold);
            groupVendedor->Location = Point(395, 120);
            groupVendedor->Size = System::Drawing::Size(370, 150);
            panelDetallesFactura->Controls->Add(groupVendedor);

            array<String^>^ vdLbls = { L"ID:", L"Nombre:", L"Apellido:" };
            array<TextBox^>^ vdTbs = gcnew array<TextBox^>(3);
            int vdY = 20;
            for (int r = 0; r < 3; r++) {
                auto lbl = gcnew Label();
                lbl->Text = vdLbls[r];
                lbl->Location = Point(10, vdY);
                lbl->Size = System::Drawing::Size(65, 22);
                lbl->TextAlign = ContentAlignment::MiddleLeft;
                groupVendedor->Controls->Add(lbl);

                vdTbs[r] = gcnew TextBox();
                vdTbs[r]->ReadOnly = true;
                vdTbs[r]->Location = Point(80, vdY);
                vdTbs[r]->Size = System::Drawing::Size(275, 22);
                groupVendedor->Controls->Add(vdTbs[r]);

                vdY += 26;
            }
            textFieldIDVendedor = vdTbs[0];
            textFieldNombreVendedor = vdTbs[1];
            textFieldApellidoVendedor = vdTbs[2];

            // Detalles table
            tableDetalles = gcnew DataGridView();
            tableDetalles->Location = Point(10, 280);
            tableDetalles->Size = System::Drawing::Size(780, 235);
            tableDetalles->AllowUserToAddRows = false;
            tableDetalles->AllowUserToDeleteRows = false;
            tableDetalles->ReadOnly = true;
            tableDetalles->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelDetallesFactura->Controls->Add(tableDetalles);

            // Totals row 1: Subtotal + % Descuento
            auto lblSubtotal = gcnew Label();
            lblSubtotal->Text = L"Subtotal:";
            lblSubtotal->Location = Point(130, 525);
            lblSubtotal->Size = System::Drawing::Size(80, 24);
            lblSubtotal->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblSubtotal);

            textFieldSubtotal = gcnew TextBox();
            textFieldSubtotal->ReadOnly = true;
            textFieldSubtotal->Location = Point(215, 525);
            textFieldSubtotal->Size = System::Drawing::Size(150, 24);
            panelDetallesFactura->Controls->Add(textFieldSubtotal);

            auto lblPctDesc = gcnew Label();
            lblPctDesc->Text = L"% Descuento:";
            lblPctDesc->Location = Point(420, 525);
            lblPctDesc->Size = System::Drawing::Size(80, 24);
            lblPctDesc->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblPctDesc);

            textFieldPorcentajeDescuento = gcnew TextBox();
            textFieldPorcentajeDescuento->ReadOnly = true;
            textFieldPorcentajeDescuento->Location = Point(505, 525);
            textFieldPorcentajeDescuento->Size = System::Drawing::Size(150, 24);
            panelDetallesFactura->Controls->Add(textFieldPorcentajeDescuento);

            // Totals row 2: Descontado + Total
            auto lblDescontado = gcnew Label();
            lblDescontado->Text = L"Descontado:";
            lblDescontado->Location = Point(130, 555);
            lblDescontado->Size = System::Drawing::Size(80, 24);
            lblDescontado->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblDescontado);

            textFieldDescontado = gcnew TextBox();
            textFieldDescontado->ReadOnly = true;
            textFieldDescontado->Location = Point(215, 555);
            textFieldDescontado->Size = System::Drawing::Size(150, 24);
            panelDetallesFactura->Controls->Add(textFieldDescontado);

            auto lblTotal = gcnew Label();
            lblTotal->Text = L"Total:";
            lblTotal->Font = gcnew System::Drawing::Font(lblTotal->Font, FontStyle::Bold);
            lblTotal->Location = Point(420, 555);
            lblTotal->Size = System::Drawing::Size(80, 24);
            lblTotal->TextAlign = ContentAlignment::MiddleRight;
            panelDetallesFactura->Controls->Add(lblTotal);

            textFieldTotal = gcnew TextBox();
            textFieldTotal->ReadOnly = true;
            textFieldTotal->Font = gcnew System::Drawing::Font(textFieldTotal->Font, FontStyle::Bold);
            textFieldTotal->Location = Point(505, 555);
            textFieldTotal->Size = System::Drawing::Size(150, 24);
            panelDetallesFactura->Controls->Add(textFieldTotal);
        }
    };
}
